#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Network/NetService.hpp"
#include "RadonFramework/Core/Policies/CMemoryOperation.hpp"
#include "RadonFramework/System/Network/OSSocketError.hpp"

using namespace RadonFramework::Memory;
using namespace RadonFramework::Net;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Policies;
using namespace RadonFramework::System::Network;

UInt32 SocketBlockingMode[2]={1,0};

#if defined(RF_WINDOWS)
/** Define WINVER and NT Version to WIN_VERSION_XP.
  * GetAdaptersInfo is available since windows xp(NT Kernel 501).
  * To be sure that all the cool features of windows API are available it's
  * necessary to define windows xp as minimum API.
  **/
static const int WIN_VERSION_XP=0x501;
#define WINVER 0x501
#define _WIN32_WINNT 0x501
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

int SockShutdown[SocketShutdown::MAX]={SD_BOTH, SD_RECEIVE, SD_SEND};

int SocketOption[static_cast<RF_Type::Size>(SocketOptionName::MAX)] =
{
    0,//Unset
    SO_DEBUG,//Debug
    SO_ACCEPTCONN,//AcceptConnection
    SO_REUSEADDR,//ReuseAddress
    SO_KEEPALIVE,//KeepAlive
    SO_DONTROUTE,//DontRoute
    SO_BROADCAST,//Broadcast
    SO_USELOOPBACK,//UseLoopback
    SO_LINGER,//Linger
    SO_OOBINLINE,//OutOfBandInline
    SO_DONTLINGER,//DontLinger
    SO_EXCLUSIVEADDRUSE,//ExclusiveAddressUse
    SO_SNDBUF,//SendBuffer
    SO_RCVBUF,//ReceiveBuffer
    SO_SNDLOWAT,//SendLowWater
    SO_RCVLOWAT,//ReceiveLowWater
    SO_SNDTIMEO,//SendTimeout
    SO_RCVTIMEO,//ReceiveTimeout
    0,//Error
    SO_TYPE,//SocketType
    0,//MaxConnections
    IP_OPTIONS,//IPOptions
    IP_HDRINCL,//HeaderIncluded
    IP_TOS,//TypeOfService
    IP_TTL,//IPTimeToLive
    IP_MULTICAST_IF,//MulticastInterface
    IP_MULTICAST_TTL,//MutlicastTimeToLive
    IP_MULTICAST_LOOP,//MulticastLoopback
    IP_ADD_MEMBERSHIP,//AddMembership
    IP_DROP_MEMBERSHIP,//DropMembership
    IP_DONTFRAGMENT,//DontFragment
    IP_ADD_SOURCE_MEMBERSHIP,//AddSourceMembership
    IP_DROP_SOURCE_MEMBERSHIP,//DropSourceMembership
    IP_BLOCK_SOURCE,//BlockSource
    IP_UNBLOCK_SOURCE,//UnblockSource
    IP_PKTINFO,//PacketInformation
    0,//HopLimit
    TCP_NODELAY,//NoDelay
    0,//BsdUrgent
    TCP_EXPEDITED_1122,//Expedited
    UDP_NOCHECKSUM,//NoChecksum
    0,//ChecksumCoverage
    0,//UpdateAcceptContext
    0,//UpdateConnectContext
    SO_REUSEADDR//ReusePort
};

inline Error InitializeImplementation()
{
    static WSADATA m_Handle;
    int err=WSAStartup(MAKEWORD(2,2),&m_Handle);
    if (err==0)
        return Error::Ok;
    else
        return OSSocketError::ConvertOSError(err);        
}

inline Error FreeImplementation()
{
    int err=WSACleanup();
    if (err==0)
        return Error::Ok;
    else
        return OSSocketError::ConvertOSError(err); 
}

inline Array<NetworkAdapter> GetLocalInterfacesImplementation()
{
    Array<NetworkAdapter> result;
    UInt32 buflen=sizeof(IP_ADAPTER_INFO)*10;// reserve memory for 10 adapter
    AutoPointerArray<UInt8> adapterInfo(new UInt8[buflen],buflen);

    // try to get the adapter
    if(GetAdaptersInfo(reinterpret_cast<PIP_ADAPTER_INFO>(adapterInfo.Get()),
        reinterpret_cast<long unsigned int*>(&buflen))==ERROR_BUFFER_OVERFLOW)
    {
        // there are more adapters as the buffer can take, generate a new buffer
        adapterInfo=AutoPointerArray<UInt8>(new UInt8[buflen],buflen);

        // get all adapters
        if (GetAdaptersInfo(reinterpret_cast<PIP_ADAPTER_INFO>(adapterInfo.Get()),
            reinterpret_cast<long unsigned int*>(&buflen))!=NO_ERROR)
            return result;
    }

    // get the number of the Ethernet adapters
    PIP_ADAPTER_INFO pAdapter=reinterpret_cast<PIP_ADAPTER_INFO>(adapterInfo.Get());
    UInt32 adapterCount=0;
    while(pAdapter)
    {
        if (pAdapter->Type==MIB_IF_TYPE_ETHERNET)
            ++adapterCount;
    }

    // reserve memory for the adapters and configure them
    result=Array<NetworkAdapter>(adapterCount);
    pAdapter=reinterpret_cast<PIP_ADAPTER_INFO>(adapterInfo.Get());
    UInt32 i=0;
    while(pAdapter)
    {
        if (pAdapter->Type==MIB_IF_TYPE_ETHERNET)
        {
            String ip=String(pAdapter->IpAddressList.IpAddress.String, sizeof(IP_ADDRESS_STRING));
            String netmask=String(pAdapter->IpAddressList.IpMask.String, sizeof(IP_ADDRESS_STRING));
            IPAddress::Resolve(ip, result(i).IP);
            IPAddress::Resolve(netmask, result(i).Netmask);
            ++i;
        }
        pAdapter=pAdapter->Next;
    }

    return result;
}

inline Error SetBlockingModeImplementation(
    const NetService::SocketHandler Handler, const Bool NewValue)
{
    UInt32 mode=SocketBlockingMode[NewValue];
    if (ioctlsocket(Handler,FIONBIO,reinterpret_cast<u_long*>(&mode)) >= 0)
        return Error::Ok;
    else
        return OSSocketError::ConvertOSError();
}

inline Error CloseImplementation(const NetService::SocketHandler Handler)
{
    if (closesocket(Handler)!=SOCKET_ERROR)
        return Error::Ok;
    else
        return OSSocketError::ConvertOSError();
}
#endif // RF_WINDOWS

#if defined(RF_UNIX)

#define INVALID_SOCKET -1
#define SOCKET_ERROR   -1

#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

int SockShutdown[SocketShutdown::MAX]={SHUT_RDWR, SHUT_RD, SHUT_WR};

int SocketOption[SocketOptionName::MAX]=
    {
        0,//Unset
        SO_DEBUG,//Debug
        SO_ACCEPTCONN,//AcceptConnection
        SO_REUSEADDR,//ReuseAddress
        SO_KEEPALIVE,//KeepAlive
        SO_DONTROUTE,//DontRoute
        SO_BROADCAST,//Broadcast
        0,//UseLoopback
        SO_LINGER,//Linger
        SO_OOBINLINE,//OutOfBandInline
        0,//DontLinger
        0,//ExclusiveAddressUse
        SO_SNDBUF,//SendBuffer
        SO_RCVBUF,//ReceiveBuffer
        SO_SNDLOWAT,//SendLowWater
        SO_RCVLOWAT,//ReceiveLowWater
        SO_SNDTIMEO,//SendTimeout
        SO_RCVTIMEO,//ReceiveTimeout
        0,//Error
        SO_TYPE,//SocketType
        0,//MaxConnections
        IP_OPTIONS,//IPOptions
        IP_HDRINCL,//HeaderIncluded
        IP_TOS,//TypeOfService
        IP_TTL,//IPTimeToLive
        IP_MULTICAST_IF,//MulticastInterface
        IP_MULTICAST_TTL,//MutlicastTimeToLive
        IP_MULTICAST_LOOP,//MulticastLoopback
        IP_ADD_MEMBERSHIP,//AddMembership
        IP_DROP_MEMBERSHIP,//DropMembership
        0,//DontFragment
        IP_ADD_SOURCE_MEMBERSHIP,//AddSourceMembership
        IP_DROP_SOURCE_MEMBERSHIP,//DropSourceMembership
        IP_BLOCK_SOURCE,//BlockSource
        IP_UNBLOCK_SOURCE,//UnblockSource
        IP_PKTINFO,//PacketInformation
        0,//HopLimit
        TCP_NODELAY,//NoDelay
        0,//BsdUrgent
        0,//Expedited
        0,//NoChecksum
        0,//ChecksumCoverage
        0,//UpdateAcceptContext
        0,//UpdateConnectContext
        SO_REUSEPORT//ReusePort
    };

inline Error InitializeImplementation()
{    
    return Error::Ok;
}

inline Error FreeImplementation()
{
    return Error::Ok;
}

inline Array<NetworkAdapter> GetLocalInterfacesImplementation()
{
    Array<NetworkAdapter> result;
    ifaddrs* ifaddr=0;
    ifaddrs* p=0;
    getifaddrs(&ifaddr);
    p=ifaddr;
    UInt32 len=0,i=0;

    while(p!=0)
    {
        if(p->ifa_addr->sa_family==AF_INET)
            ++len;
        p=p->ifa_next;        
    }

    result=Array<NetworkAdapter>(len);
    p=ifaddr;
    while(p!=0)
    {
        if(p->ifa_addr->sa_family==AF_INET)
        {
            result(i).IP=IPAddress((UInt32)((sockaddr_in*)p->ifa_addr)->sin_addr.s_addr);
            result(i).Netmask=IPAddress((UInt32)((sockaddr_in*)p->ifa_netmask)->sin_addr.s_addr);
            ++i;
        }
        p=p->ifa_next;
    }
    freeifaddrs(ifaddr);
    return result;
}

inline Error SetBlockingModeImplementation(
    const NetService::SocketHandler Handler, const Bool NewValue)
{
    Int32 opts;
    opts = fcntl(Handler,F_GETFL);
    if (opts < 0)
        return Error::InternalError;
    Bool blocking=(opts & O_NONBLOCK)!=O_NONBLOCK;

    if (blocking != NewValue)
    {
        if (NewValue)
            opts = (opts & !O_NONBLOCK);
        else
            opts = (opts | O_NONBLOCK);
    }

    if (fcntl(Handler,F_SETFL,opts) < 0)
        return Error::InternalError;

    return Error::Ok;
}

inline Error CloseImplementation(const NetService::SocketHandler Handler)
{
    if (close(Handler)!=SOCKET_ERROR)
        return Error::Ok;
    else
        return OSSocketError::ConvertOSError();
}
#endif // RF_LINUX

int SocketAddressFamily[static_cast<RF_Type::Size>(AddressFamily::MAX)]=
    {
        AF_INET,
        AF_INET6,
        AF_UNIX,
        0
    };

int SocketSocketType[static_cast<RF_Type::Size>(SocketType::MAX)] =
    {
        SOCK_DGRAM,
        SOCK_STREAM,
        SOCK_RAW,
        0
    };

int SocketProtocolType[static_cast<RF_Type::Size>(SocketType::MAX)] =
    {
        IPPROTO_UDP,
        IPPROTO_TCP,
        0,
        0
    };

int SockOptionLevel[static_cast<RF_Type::Size>(SocketOptionLevel::MAX)] =
    {
        0,//Unset
        SOL_SOCKET,//Socket
        IPPROTO_IP,//IPv4
        IPPROTO_IPV6,//IPv6
        IPPROTO_TCP,//TCP
        IPPROTO_UDP//UDP
    };

//This assign the OptionName to the right OptionLevel types.
SocketOptionLevel SocketOptionAviableLevel[static_cast<RF_Type::Size>(SocketOptionName::MAX)] =
{
    SocketOptionLevel::Unset,//Unset
    SocketOptionLevel::Socket,//Debug
    SocketOptionLevel::Unset,//AcceptConnection
    SocketOptionLevel::Socket,//ReuseAddress
    SocketOptionLevel::Socket,//KeepAlive
    SocketOptionLevel::Socket,//DontRoute
    SocketOptionLevel::Socket,//Broadcast
    SocketOptionLevel::Unset,//UseLoopback
    SocketOptionLevel::Socket,//Linger
    SocketOptionLevel::Socket,//OutOfBandInline
    SocketOptionLevel::Socket,//DontLinger
    SocketOptionLevel::Socket,//ExclusiveAddressUse
    SocketOptionLevel::Socket,//SendBuffer
    SocketOptionLevel::Socket,//ReceiveBuffer
    SocketOptionLevel::Unset,//SendLowWater
    SocketOptionLevel::Unset,//ReceiveLowWater
    SocketOptionLevel::Socket,//SendTimeout
    SocketOptionLevel::Socket,//ReceiveTimeout
    SocketOptionLevel::Unset,//Error
    SocketOptionLevel::Unset,//SocketType
    SocketOptionLevel::Unset,//MaxConnections
    SocketOptionLevel::Unset,//IPOptions
    SocketOptionLevel::Unset,//HeaderIncluded
    SocketOptionLevel::Unset,//TypeOfService
    SocketOptionLevel::Unset,//IPTimeToLive
    SocketOptionLevel::IPv4,//MulticastInterface
    SocketOptionLevel::IPv4,//MutlicastTimeToLive
    SocketOptionLevel::IPv4,//MulticastLoopback
    SocketOptionLevel::IPv4,//AddMembership
    SocketOptionLevel::IPv4,//DropMembership
    SocketOptionLevel::Unset,//DontFragment
    SocketOptionLevel::Unset,//AddSourceMembership
    SocketOptionLevel::Unset,//DropSourceMembership
    SocketOptionLevel::Unset,//BlockSource
    SocketOptionLevel::Unset,//UnblockSource
    SocketOptionLevel::Unset,//PacketInformation
    SocketOptionLevel::Unset,//HopLimit
    SocketOptionLevel::TCP,//NoDelay
    SocketOptionLevel::Unset,//BsdUrgent
    SocketOptionLevel::Unset,//Expedited
    SocketOptionLevel::Unset,//NoChecksum
    SocketOptionLevel::Unset,//ChecksumCoverage
    SocketOptionLevel::Socket,//UpdateAcceptContext
    SocketOptionLevel::Unset,//UpdateConnectContext
    SocketOptionLevel::Socket//ReusePort
};

Error NetService::Initialize()
{
    OSSocketError::InitializeLookupTable();
    return InitializeImplementation();
}

Error NetService::Free()
{
    return FreeImplementation();
}

IPHostEntry NetService::GetHostEntry( const RF_Type::String& HostnameOrAddress )
{
    List<RF_Type::String> s;
    List<IPAddress> i;
    struct addrinfo hints,*servinfo,*element;

    RF_SysMem::Set(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    // collect all IP's
    if (getaddrinfo(HostnameOrAddress.c_str(),NULL,&hints,&servinfo)!=0)
        return IPHostEntry(RF_Type::String(),s,i);

    // collect all names related to the IP's
    for (element=servinfo;element!=NULL;element=element->ai_next)
    {
        char hostname[NI_MAXHOST]="";
        getnameinfo(element->ai_addr, static_cast<socklen_t>(element->ai_addrlen), 
                    hostname, NI_MAXHOST, NULL, 0, 0);
        i.AddLast(IPAddress(((sockaddr_in*)element->ai_addr)->sin_addr.s_addr));
        if (*hostname)
            s.AddLast(RF_Type::String(hostname, NI_MAXHOST));
    }
    freeaddrinfo(servinfo);
    IPHostEntry result(HostnameOrAddress,s,i);
    return result;
}

String NetService::GetHostname()
{
    char szHostname[255];
    RF_Type::String str;
    if (gethostname(szHostname, 255)==0)
        str=RF_Type::String(szHostname, 255);
    return str;
}

Array<NetworkAdapter> NetService::GetLocalInterfaces()
{
    return GetLocalInterfacesImplementation();
}

Error NetService::Accept(const NetService::SocketHandler& Listener,
    NetService::SocketHandler& NewClient, EndPoint& ClientEndPoint)
{
    int clientSocket;
    sockaddr addr;
    socklen_t addrsize=sizeof(sockaddr);

    clientSocket=static_cast<int>(accept(Listener, &addr, &addrsize));
    if (clientSocket!=INVALID_SOCKET)
    {
        NewClient=clientSocket;
        sockaddr_in *p=reinterpret_cast<sockaddr_in*>(&addr);
        ClientEndPoint.Address(IPAddress(p->sin_addr.s_addr));
        ClientEndPoint.Port(ntohs(p->sin_port));
        return Error::Ok;
    }
    else
        return OSSocketError::ConvertOSError();
}

Error NetService::Create(NetService::SocketHandler& Handler,
    const AddressFamily Family, const SocketType Type)
{
    int af = SocketAddressFamily[static_cast<RF_Type::Size>(Family)];
    int st = SocketSocketType[static_cast<RF_Type::Size>(Type)];
    int pt = SocketProtocolType[static_cast<RF_Type::Size>(Type)];
    int sock=SOCKET_ERROR;

    sock=static_cast<int>(socket(af,st,pt));
    if (sock!=SOCKET_ERROR)
    {
        Handler=sock;
        return Error::Ok;
    }
    else
        return OSSocketError::ConvertOSError();
}

Error NetService::Bind(const NetService::SocketHandler Handler, 
    EndPoint &LocalEP)
{
    sockaddr_in addrIn;
    int addrSize=sizeof(sockaddr_in);
    addrIn.sin_family = SocketAddressFamily[static_cast<RF_Type::Size>(LocalEP.Address().GetAddressFamily())];
    addrIn.sin_port=htons(LocalEP.Port());
    const UInt8* addr=LocalEP.Address().AsByteArray();

    switch(LocalEP.Address().GetAddressFamily())
    {
        case AddressFamily::InterNetwork:
            addrIn.sin_addr.s_addr=htonl(*reinterpret_cast<const u_long*>(addr));
            break;
        default:
            return Error::InternalError;
    }

    if(bind(Handler, reinterpret_cast<sockaddr*>(&addrIn), addrSize) != SOCKET_ERROR)
    {
        if(getsockname(Handler, reinterpret_cast<sockaddr*>(&addrIn), &addrSize) == 0)
        {
            IPAddress publicIP(ntohl(addrIn.sin_addr.s_addr));
            LocalEP.Address(publicIP);
        }
        return Error::Ok;
    }
    else
        return OSSocketError::ConvertOSError(); 
}

Error NetService::Close(const NetService::SocketHandler Handler)
{
    return CloseImplementation(Handler);
}

Error NetService::Connect(const NetService::SocketHandler Handler, 
    const EndPoint &RemoteEP)
{
    sockaddr_in addrIn;
    int addrSize=sizeof(sockaddr_in);

    RF_Type::String str=RemoteEP.Address().ToString();
    addrIn.sin_addr.s_addr=inet_addr(str.c_str());
    addrIn.sin_family = SocketAddressFamily[static_cast<RF_Type::Size>(RemoteEP.Address().GetAddressFamily())];
    addrIn.sin_port=htons(RemoteEP.Port());

    if (connect(Handler,reinterpret_cast<sockaddr*>(&addrIn),addrSize)!=SOCKET_ERROR)
        return Error::Ok;
    else
        return OSSocketError::ConvertOSError();
}

Error NetService::Listen(const NetService::SocketHandler Handler,
    const UInt32 MaxWaitingClients)
{
    if (listen(Handler,MaxWaitingClients)!=SOCKET_ERROR)
        return Error::Ok;
    else
        return OSSocketError::ConvertOSError();
}

Error NetService::Receive(const NetService::SocketHandler Handler,
    AutoPointerArray<UInt8>& Data)
{
    char Buffer[2048];//totaly enough(1400-1500 is normal)

    int ret=recv(Handler,Buffer,2048,0);
    if (ret>0)
    {
        Data=AutoPointerArray<UInt8>(new UInt8[ret],ret);
        RF_SysMem::Copy(Data.Get(),Buffer,ret);
        return Error::Ok;
    }
    else
    {
        if (ret==SOCKET_ERROR)
            return OSSocketError::ConvertOSError();
        else// ret==0
            return Error::ConnectionReset;
    }
}

Error NetService::ReceiveFrom(const NetService::SocketHandler Handler,
    AutoPointerArray<UInt8> &Data, const EndPoint &RemoteEP)
{
    char Buffer[2048];
    sockaddr_in src;
    socklen_t addrSize=sizeof(sockaddr_in);
    src.sin_family = SocketAddressFamily[static_cast<RF_Type::Size>(RemoteEP.Address().GetAddressFamily())];
    src.sin_port=htons(RemoteEP.Port());
    const UInt8* addr = RemoteEP.Address().AsByteArray();

    switch(RemoteEP.Address().GetAddressFamily())
    {
    case AddressFamily::InterNetwork:
        src.sin_addr.s_addr=htonl(*reinterpret_cast<const u_long*>(addr));
        break;
    default:
        return Error::InternalError;
    }

    int ret=recvfrom(Handler,Buffer,2048,0,(sockaddr*)&src,&addrSize);
    if (ret>0)
    {
        Data=AutoPointerArray<UInt8>(new UInt8[ret],ret);
        RF_SysMem::Copy(Data.Get(),Buffer,ret);
        return Error::Ok;
    }
    else
    {
        if (ret==SOCKET_ERROR)
            return OSSocketError::ConvertOSError();
        else// ret==0
            return Error::ConnectionReset;
    }	
}

Error NetService::Send(const NetService::SocketHandler Handler,
    const UInt8* Data, const UInt32 DataSize, UInt32 *SendDataSize)
{
    int ret=send(Handler,reinterpret_cast<const char*>(Data),DataSize,0);
    if (ret!=SOCKET_ERROR)
    {
        if (SendDataSize)
            *SendDataSize=ret;
        return Error::Ok;
    }
    else
        return OSSocketError::ConvertOSError();
}

Error NetService::SendTo(const NetService::SocketHandler Handler,
    const AutoPointerArray<UInt8>& Data, const EndPoint &RemoteEP, UInt32 *SendDataSize)
{
    sockaddr_in dst;
    dst.sin_family = SocketAddressFamily[static_cast<RF_Type::Size>(RemoteEP.Address().GetAddressFamily())];
    dst.sin_port=htons(RemoteEP.Port());
    const UInt8* addr = RemoteEP.Address().AsByteArray();

    switch(RemoteEP.Address().GetAddressFamily())
    {
    case AddressFamily::InterNetwork:
        dst.sin_addr.s_addr=htonl(*reinterpret_cast<const u_long*>(addr));
        break;
    default:
        return Error::InternalError;
    }

    int ret=sendto(Handler, reinterpret_cast<const char*>(Data.Get()),
        static_cast<int>(Data.Size()), 0, reinterpret_cast<sockaddr*>(&dst),
        sizeof(sockaddr_in));
    if (ret!=SOCKET_ERROR)
    {
        if (SendDataSize)
            *SendDataSize=ret;
        return Error::Ok;
    }
    else
        return OSSocketError::ConvertOSError();
}

Error NetService::Shutdown(const NetService::SocketHandler Handler,
    const SocketShutdown::Type What)
{
    int what=SockShutdown[What];
    if (shutdown(Handler,what)!=SOCKET_ERROR)
        return Error::Ok;
    else
        return OSSocketError::ConvertOSError();
}

Error NetService::SetBlockingMode(const NetService::SocketHandler Handler,
    const Bool NewValue)
{
    return SetBlockingModeImplementation(Handler,NewValue);
}

Error NetService::GetSocketOptionWrapper(const NetService::SocketHandler Handler, 
    const SocketOptionLevel OptionLevel, 
    const SocketOptionName OptionName, 
    AutoPointerArray<UInt8>& Value)
{
    if(OptionLevel != SocketOptionLevel::Unset && SocketOptionAviableLevel[(RF_Type::Size)OptionName] == OptionLevel)
    {
        if(SocketOption[(RF_Type::Size)OptionName]>0)
        {
            Size len=Value.Size();
            if (len>0)// memory was passed by parameter
            {
                if(SOCKET_ERROR != getsockopt(Handler, SockOptionLevel[(RF_Type::Size)OptionLevel],
                    SocketOption[(RF_Type::Size)OptionName], reinterpret_cast<char*>(Value.Get()),
                    reinterpret_cast<socklen_t*>(&len)))
                {
                    if (len==Value.Size())
                        return Error::Ok;
                    else
                        return Error::InvalidArgument;
                }
                else
                    return OSSocketError::ConvertOSError();
            }
            else// need to allocate memory
            {
                len=2048;
                Error result=Error::Ok;
                // BadAddress will be raised if there is not enough memory.
                // The loop will continue and allocate a new bigger buffer.
                do 
                {
                    AutoPointerArray<UInt8> buf(new UInt8[len],len);
                    if(SOCKET_ERROR != getsockopt(Handler, SockOptionLevel[(RF_Type::Size)OptionLevel],
                        SocketOption[(RF_Type::Size)OptionName], reinterpret_cast<char*>(buf.Get()),
                        reinterpret_cast<socklen_t*>(&len)))
                    {
                        Value=AutoPointerArray<UInt8>(new UInt8[len],len);
                        CMemoryOperation::Copy<UInt8>(Value.Get(),buf.Get(),len);
                    }
                    else
                    {
                        result=OSSocketError::ConvertOSError();
                        len=len<<1;
                    }
                } 
                while (result!=Error::BadAddress);
                return result;
            }	
        }
        else
            return Error::BadProtocolOption;
    }
    else
        return Error::InvalidArgument;
}

Error NetService::SetSocketOption(const NetService::SocketHandler Handler, 
    const SocketOptionLevel OptionLevel, 
    const SocketOptionName OptionName, 
    const void* const OptionValue, const UInt32 OptionLength)
{
    if(OptionLevel != SocketOptionLevel::Unset && SocketOptionAviableLevel[(RF_Type::Size)OptionName] == OptionLevel)
    {
        if(SocketOption[(RF_Type::Size)OptionName]>0)
        {
            if(setsockopt(Handler, SockOptionLevel[(RF_Type::Size)OptionLevel],
                SocketOption[(RF_Type::Size)OptionName], reinterpret_cast<const char*>(OptionValue), OptionLength) != SOCKET_ERROR)
                return Error::Ok;
            else
                return OSSocketError::ConvertOSError();
        }
        else
            return Error::BadProtocolOption;
    }
    else
        return Error::InvalidArgument;
}

Error NetService::AddMembership(const NetService::SocketHandler Handler, 
                                const RF_Net::MulticastRequest& OptionValue)
{
    struct ip_mreq multicastRequest;
    u_long address = OptionValue.MulticastAddress.ToUInt32();
    u_long interface = OptionValue.Interface.ToUInt32();
    memcpy(&multicastRequest.imr_multiaddr, &address, sizeof(u_long));
    memcpy(&multicastRequest.imr_interface, &interface, sizeof(u_long));    
    return SetSocketOption(Handler, SocketOptionLevel::IPv4, 
        SocketOptionName::AddMembership, &multicastRequest, sizeof(ip_mreq));
}

Error NetService::DropMembership(const NetService::SocketHandler Handler,
                                const RF_Net::MulticastRequest& OptionValue)
{
    struct ip_mreq multicastRequest;
    u_long address = OptionValue.MulticastAddress.ToUInt32();
    u_long interface = OptionValue.Interface.ToUInt32();
    memcpy(&multicastRequest.imr_multiaddr, &address, sizeof(u_long));
    memcpy(&multicastRequest.imr_interface, &interface, sizeof(u_long));
    return SetSocketOption(Handler, SocketOptionLevel::IPv4,
        SocketOptionName::DropMembership, &multicastRequest, sizeof(ip_mreq));
}

Error NetService::SetMulticastInterface(const NetService::SocketHandler Handler, 
                                        const RF_Net::IPAddress& OptionValue)
{
    RF_Type::UInt32 ip = OptionValue.ToUInt32();
    return SetSocketOption(Handler, SocketOptionLevel::IPv4, 
        SocketOptionName::MulticastInterface, &ip, sizeof(RF_Type::UInt32));
}

