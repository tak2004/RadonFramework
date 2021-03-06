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
    SO_REUSEADDR,//ReusePort
    IPV6_MULTICAST_HOPS,//MulticastHops
    IPV6_UNICAST_HOPS,//UnicastHops
    IPV6_MULTICAST_LOOP//MulticastLoopbackIPv6
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

    UInt32 outBufLen = 0;
    AutoPointerArray<UInt8> addressInfo;
    UInt32 family = AF_UNSPEC;
    UInt32 flags = GAA_FLAG_INCLUDE_PREFIX;
    UInt32 returnValue = NO_ERROR;
    UInt32 addressCount = 0;
    do 
    {
        outBufLen += 15000;// suggested value by Microsoft
        addressInfo=AutoPointerArray<UInt8>(new UInt8[outBufLen], outBufLen);
        // get all adapters
        returnValue = GetAdaptersAddresses(family, flags, NULL, 
            reinterpret_cast<PIP_ADAPTER_ADDRESSES>(addressInfo.Get()), 
            reinterpret_cast<PULONG>(&outBufLen));
        // if an ERROR_BUFFER_OVERFLOW occur then run again with more memory
    } while (returnValue == ERROR_BUFFER_OVERFLOW);    

    PIP_ADAPTER_UNICAST_ADDRESS pUnicastAddress = 0;
    PIP_ADAPTER_ADDRESSES pCurrAddresses = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(addressInfo.Get());
    // get the number of the Ethernet adapters
    while(pCurrAddresses)
    {
        if(pCurrAddresses->OperStatus == IfOperStatusUp)
        {
            pUnicastAddress = pCurrAddresses->FirstUnicastAddress;
            while(pUnicastAddress)
            {
                pUnicastAddress = pUnicastAddress->Next;
                ++addressCount;
            }
        }
        pCurrAddresses = pCurrAddresses->Next;
    }

    // reserve memory for the adapters and configure them
    result = Array<NetworkAdapter>(addressCount);
    pCurrAddresses = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(addressInfo.Get());
    UInt32 i = 0;
    while(pCurrAddresses)
    {
        if(pCurrAddresses->OperStatus == IfOperStatusUp)
        {
            pUnicastAddress = pCurrAddresses->FirstUnicastAddress;
            for(; pUnicastAddress != NULL; ++i)
            {
                if (pUnicastAddress->Address.lpSockaddr->sa_family == AF_INET)
                {
                    auto* addr = reinterpret_cast<struct sockaddr_in*>(pUnicastAddress->Address.lpSockaddr);
                    result(i).IP = IPAddress(static_cast<UInt32>(addr->sin_addr.s_addr));
                }
                else
                {
                    auto* addr = reinterpret_cast<struct sockaddr_in6*>(pUnicastAddress->Address.lpSockaddr);
                    result(i).IP = IPAddress(addr->sin6_addr.u.Word[0],
                        addr->sin6_addr.u.Word[1], addr->sin6_addr.u.Word[2],
                        addr->sin6_addr.u.Word[3], addr->sin6_addr.u.Word[4],
                        addr->sin6_addr.u.Word[5], addr->sin6_addr.u.Word[6],
                        addr->sin6_addr.u.Word[7]);
                }
                pUnicastAddress = pUnicastAddress->Next;
            }
        }
        pCurrAddresses = pCurrAddresses->Next;
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

typedef int AddrSize;
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

int SocketOption[static_cast<RF_Type::Size>(SocketOptionName::MAX)]=
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
        SO_REUSEPORT,//ReusePort
        IPV6_MULTICAST_HOPS,//MulticastHops    
        IPV6_UNICAST_HOPS,//UnicastHops
        IPV6_MULTICAST_LOOP//MulticastLoopbackIPv6
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

typedef socklen_t AddrSize;
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
    SocketOptionLevel::Socket,//ReusePort
    SocketOptionLevel::IPv6,//MulticastHops
    SocketOptionLevel::IPv6,//UnicastHops
    SocketOptionLevel::IPv6//MulticastLoopbackIPv6
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

Error BindIPv4(const NetService::SocketHandler Handler, EndPoint &LocalEP)
{
    Error result = Error::Ok;

    sockaddr_in addrIn;
    AddrSize addrSize = sizeof(sockaddr_in);
    RF_SysMem::Set(&addrIn, 0, addrSize);
    addrIn.sin_family = SocketAddressFamily[static_cast<RF_Type::Size>(LocalEP.Address().GetAddressFamily())];
    addrIn.sin_port = htons(LocalEP.Port());
    const UInt8* addr = LocalEP.Address().AsByteArray();// always most significant byte first
    addrIn.sin_addr.s_addr = *reinterpret_cast<const u_long*>(addr);

    if(bind(Handler, reinterpret_cast<sockaddr*>(&addrIn), addrSize) != SOCKET_ERROR)
    {
        if(getsockname(Handler, reinterpret_cast<sockaddr*>(&addrIn), &addrSize) == 0)
        {
            IPAddress publicIP(addrIn.sin_addr.s_addr);
            LocalEP.Address(publicIP);
            LocalEP.Port(ntohs(addrIn.sin_port));
        }
    }
    else
        result = OSSocketError::ConvertOSError();

    return result;
}

Error BindIPv6(const NetService::SocketHandler Handler, EndPoint &LocalEP)
{
    Error result = Error::Ok;

    sockaddr_in6 addrIn;
    AddrSize addrSize = sizeof(sockaddr_in6);
    RF_SysMem::Set(&addrIn, 0, addrSize);
    addrIn.sin6_family = SocketAddressFamily[static_cast<RF_Type::Size>(LocalEP.Address().GetAddressFamily())];
    addrIn.sin6_port = htons(LocalEP.Port());
    RF_SysMem::Copy(addrIn.sin6_addr.s6_addr, LocalEP.Address().AsByteArray(), 16);

    if(bind(Handler, reinterpret_cast<sockaddr*>(&addrIn), addrSize) != SOCKET_ERROR)
    {
        if(getsockname(Handler, reinterpret_cast<sockaddr*>(&addrIn), &addrSize) == 0)
        {
            RF_Collect::Array<RF_Type::UInt8> address(16);
            RF_SysMem::Copy(&address(0), addrIn.sin6_addr.s6_addr, 16);
            IPAddress publicIP(address);
            LocalEP.Address(publicIP);
        }
    }
    else
        result = OSSocketError::ConvertOSError();

    return result;
}

Error NetService::Bind(const NetService::SocketHandler Handler, 
    EndPoint &LocalEP)
{
    Error result = Error::Ok;

    switch(LocalEP.Address().GetAddressFamily())
    {
    case AddressFamily::InterNetwork:
        result = BindIPv4(Handler, LocalEP);
        break;
    case AddressFamily::InterNetwork6:
        result = BindIPv6(Handler, LocalEP);
        break;
    default:
        result = Error::InternalError;
    }

    return result;
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
    char Buffer[2048];// MTU of 1400-1500 byte is common

    int ret=recv(Handler,Buffer,2048,0);
    if (ret>0)
    {
        Data=AutoPointerArray<UInt8>(ret);
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
    AutoPointerArray<UInt8> &Data, EndPoint &RemoteEP)
{
    char Buffer[2048];
    sockaddr_in src;
    RF_SysMem::Set(&src, 0, sizeof(src));
    int addrSize = sizeof(src);

    int ret=recvfrom(Handler,Buffer,2048,0,(sockaddr*)&src,reinterpret_cast<socklen_t*>(&addrSize));
    if (ret>0)
    {
        Data=AutoPointerArray<UInt8>(ret);
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
    const UInt8* Data, const UInt32 DataSize, const EndPoint &RemoteEP, 
    UInt32 *SendDataSize)
{
    int ret = SOCKET_ERROR;
    sockaddr_in dstV4;
    sockaddr_in6 dstV6;
    const UInt8* addrV4 = 0;
    const char* data = reinterpret_cast<const char*>(Data);
    sockaddr* addr = 0;
    int addrSize = 0;

    RF_SysMem::Set(&dstV4, 0, sizeof(dstV4));
    RF_SysMem::Set(&dstV6, 0, sizeof(dstV6));

    switch(RemoteEP.Address().GetAddressFamily())
    {
    case AddressFamily::InterNetwork:
        dstV4.sin_family = SocketAddressFamily[static_cast<RF_Type::Size>(RemoteEP.Address().GetAddressFamily())];
        dstV4.sin_port = htons(RemoteEP.Port());
        addrV4 = RemoteEP.Address().AsByteArray();// always most significant byte first
        dstV4.sin_addr.s_addr= (*reinterpret_cast<const u_long*>(addrV4));
        addr = reinterpret_cast<sockaddr*>(&dstV4);
        addrSize = sizeof(dstV4);
        break;
    case AddressFamily::InterNetwork6:
        dstV6.sin6_family = SocketAddressFamily[static_cast<RF_Type::Size>(RemoteEP.Address().GetAddressFamily())];
        dstV6.sin6_port = htons(RemoteEP.Port());
        RF_SysMem::Copy(dstV6.sin6_addr.s6_addr, RemoteEP.Address().AsByteArray(), 16);        
        addr = reinterpret_cast<sockaddr*>(&dstV6);
        addrSize = sizeof(dstV6);
        break;
    default:
        return Error::InternalError;
    }

    ret = sendto(Handler, data, DataSize, 0, addr, addrSize);

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
                    AutoPointerArray<UInt8> buf(len);
                    if(SOCKET_ERROR != getsockopt(Handler, SockOptionLevel[(RF_Type::Size)OptionLevel],
                        SocketOption[(RF_Type::Size)OptionName], reinterpret_cast<char*>(buf.Get()),
                        reinterpret_cast<socklen_t*>(&len)))
                    {
                        Value=AutoPointerArray<UInt8>(len);
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
    RF_SysMem::Set(&multicastRequest, 0, sizeof(multicastRequest));
    multicastRequest.imr_interface.s_addr = OptionValue.Interface.ToUInt32();
    multicastRequest.imr_multiaddr.s_addr = OptionValue.MulticastAddress.ToUInt32();
    return SetSocketOption(Handler, SocketOptionLevel::IPv4, 
        SocketOptionName::AddMembership, &multicastRequest, sizeof(ip_mreq));
}

Error NetService::DropMembership(const NetService::SocketHandler Handler,
                                const RF_Net::MulticastRequest& OptionValue)
{
    struct ip_mreq multicastRequest;
    RF_SysMem::Set(&multicastRequest, 0, sizeof(multicastRequest));
    multicastRequest.imr_interface.s_addr = OptionValue.Interface.ToUInt32();
    multicastRequest.imr_multiaddr.s_addr = OptionValue.MulticastAddress.ToUInt32();
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

template<>
RF_Net::Error NetService::SetSocketOption<RF_Net::IPAddress>(
    const NetService::SocketHandler Handler,
    const RF_Net::SocketOptionLevel OptionLevel,
    const RF_Net::SocketOptionName OptionName,
    const RF_Net::IPAddress& OptionValue)
{
    if(OptionName == RF_Net::SocketOptionName::MulticastInterface &&
        OptionLevel == RF_Net::SocketOptionLevel::IPv4)
    {
        return SetMulticastInterface(Handler, OptionValue);
    }
    else
    {
        return RF_Net::Error::InvalidArgument;
    }
}

template<>
RF_Net::Error NetService::SetSocketOption<RF_Net::MulticastRequest>(
    const NetService::SocketHandler Handler,
    const RF_Net::SocketOptionLevel OptionLevel,
    const RF_Net::SocketOptionName OptionName,
    const RF_Net::MulticastRequest& OptionValue)
{
    if(OptionName == RF_Net::SocketOptionName::AddMembership &&
        OptionLevel == RF_Net::SocketOptionLevel::IPv4)
    {
        return AddMembership(Handler, OptionValue);
    }
    else if(OptionName == RF_Net::SocketOptionName::DropMembership &&
        OptionLevel == RF_Net::SocketOptionLevel::IPv4)
    {
        return DropMembership(Handler, OptionValue);
    }
    else
    {
        return RF_Net::Error::InvalidArgument;
    }
}

NetService::SocketHandler NetService::InvalidSocketHandler = SOCKET_ERROR;
