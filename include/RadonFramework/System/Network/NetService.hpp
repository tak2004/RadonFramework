#ifndef RF_SYSTEM_NETWORK_SERVICE_HPP
#define RF_SYSTEM_NETWORK_SERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/Error.hpp>
#include <RadonFramework/Net/IPHostEntry.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Net/NetworkAdapter.hpp>
#include <RadonFramework/Memory/PointerID.hpp>
#include <RadonFramework/Net/EndPoint.hpp>
#include <RadonFramework/Net/SocketType.hpp>
#include <RadonFramework/Net/SocketShutdown.hpp>
#include <RadonFramework/Net/SocketOptionLevel.hpp>
#include <RadonFramework/Net/SocketOptionName.hpp>

namespace RadonFramework { namespace System { namespace Network {

template<typename T>
struct Identity{typedef T Type;};

class NetService
{
public:
    typedef int SocketHandler;

    /** Initialize the network API.
        * This method will be called by RadonFramework_Init().
        **/
    static RF_Net::Error::Type Initialize();

    /** Shutdown and clean up the network service.
        * This method will be called by RadonFramework_Quit();
        **/
    static RF_Net::Error::Type Free();

    // Return all IPs and names related to the specified parameter.
    static RF_Net::IPHostEntry GetHostEntry(
        const RF_Type::String& HostnameOrAddress);

    // Return the hostname of the pc.
    static RF_Type::String GetHostname();

    // Return the IP and network mask of all network adapters.
    static Collections::Array<RF_Net::NetworkAdapter>
        GetLocalInterfaces();

    /** This method permits an incoming connection attempt on a socket.
    * \param Listener 
    * Descriptor identifying a socket that has been placed in 
    * a listening state with the listen function.
    * \param NewClient
    * If the method was successful then it will put the new 
    * client handler into the variable.
    * \param ClientEndPoint
    * If the method was successful then it will put the new
    * client address into the variable.
    **/
    static RF_Net::Error::Type Accept(const SocketHandler& Listener,
        SocketHandler& NewClient, RF_Net::EndPoint& ClientEndPoint);

    /** This method creates a socket that is bound to a specific 
    * service provider. 
    * \param Handler
    * If the method was successful then it will put the handler
    * into the variable.
    * \param Family Specify the address family of the socket.
    * \param Type Type specification for the new socket.
    **/
    static RF_Net::Error::Type Create(SocketHandler& Handler,
        const RF_Net::AddressFamily Family,
        const RF_Net::SocketType Type);

    // This function associates a local address with a socket.
    static RF_Net::Error::Type Bind(const SocketHandler Handler,
        const RF_Net::EndPoint &LocalEP);

    // This method closes an existing socket.
    static RF_Net::Error::Type Close(const SocketHandler Handler);

    // This method establishes a connection to a specified socket.
    static RF_Net::Error::Type Connect(const SocketHandler Handler,
        const RF_Net::EndPoint &RemoteEP);

    /** This method places a socket at a state where it is 
    * listening for an incoming connection.
    **/
    static RF_Net::Error::Type Listen(const SocketHandler Handler,
        const RF_Type::UInt32 MaxWaitingClients);

    // This method receives data from a connected socket.
    static RF_Net::Error::Type Receive(const SocketHandler Handler,
        RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data);

    // This method receives a datagram and stores the source address.
    static RF_Net::Error::Type ReceiveFrom(const SocketHandler Handler,
        RF_Mem::AutoPointerArray<RF_Type::UInt8> &Data, 
        const RF_Net::EndPoint &RemoteEP);

    // This method sends data on a connected socket.
    static RF_Net::Error::Type Send(const SocketHandler Handler,
        const RF_Type::UInt8* Data, 
        const RF_Type::UInt32 DataSize, 
        RF_Type::UInt32 *SendDataSize=0);

    // This method sends data to a specific destination.
    static RF_Net::Error::Type SendTo(const SocketHandler Handler,
        const RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data, 
        const RF_Net::EndPoint &RemoteEP,
        RF_Type::UInt32 *SendDataSize=0);
                    
    // This method disables sends or receives on a socket.
    static RF_Net::Error::Type Shutdown(const SocketHandler Handler,
        const RF_Net::SocketShutdown::Type What);

    // This method retrieves a socket option.
    template <typename T>
    static RF_Net::Error::Type GetSocketOption(const SocketHandler Handler,
        const RF_Net::SocketOptionLevel::Type OptionLevel,
        const RF_Net::SocketOptionName::Type OptionName,
        T& OptionValue);

    // This method sets a socket option.
    template <typename T>
    static RF_Net::Error::Type SetSocketOption(const SocketHandler Handler,
        const RF_Net::SocketOptionLevel::Type OptionLevel,
        const RF_Net::SocketOptionName::Type OptionName,
        const T& OptionValue);

    // This method set a socket to blocking or non blocking mode.
    static RF_Net::Error::Type SetBlockingMode(const SocketHandler Handler,
        const RF_Type::Bool NewValue);
private:
    // This method retrieves a socket option in generic way.
    template <typename T>
    static RF_Net::Error::Type GetSocketOptionWrapper(
        const SocketHandler Handler,
        const RF_Net::SocketOptionLevel::Type OptionLevel,
        const RF_Net::SocketOptionName::Type OptionName,
        T& OptionValue);

    /** This method is the internal version without any protection
    * against wrong pointer arithmetic and type size.
    **/
    static RF_Net::Error::Type GetSocketOptionWrapper(
        const SocketHandler Handler,
        const RF_Net::SocketOptionLevel::Type OptionLevel,
        const RF_Net::SocketOptionName::Type OptionName,
        RF_Mem::AutoPointerArray<RF_Type::UInt8>& Value);

    /** This method is the internal version without any protection
    * against wrong pointer arithmetic and type size.
    **/
    static RF_Net::Error::Type SetSocketOption(const SocketHandler Handler,
        const RF_Net::SocketOptionLevel::Type OptionLevel,
        const RF_Net::SocketOptionName::Type OptionName,
        const void* const OptionValue, const RF_Type::UInt32 OptionLength);
};

template <typename T>
RF_Net::Error::Type NetService::GetSocketOption(
    const NetService::SocketHandler Handler,
    const RF_Net::SocketOptionLevel::Type OptionLevel,
    const RF_Net::SocketOptionName::Type OptionName,
    T& OptionValue)
{
    return GetSocketOptionWrapper(Handler, OptionLevel, OptionName, OptionValue);
}

template <typename T>
RF_Net::Error::Type NetService::GetSocketOptionWrapper(
    const NetService::SocketHandler Handler,
    const RF_Net::SocketOptionLevel::Type OptionLevel,
    const RF_Net::SocketOptionName::Type OptionName,
    T& OptionValue)
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> arr(
        new RF_Type::UInt8[sizeof(T)], sizeof(T));
    RF_Net::Error::Type result =
        GetSocketOptionWrapper(Handler, OptionLevel, OptionName, arr);
    if(result == RF_Net::Error::Ok)
    {
        if(arr.Size() == sizeof(T))
            OptionValue = *arr.Get();
        else
            result = RF_Net::Error::InvalidArgument;
    }
    return result;
}

template <typename T>
RF_Net::Error::Type NetService::SetSocketOption(
    const NetService::SocketHandler Handler,
    const RF_Net::SocketOptionLevel::Type OptionLevel,
    const RF_Net::SocketOptionName::Type OptionName,
    const T& OptionValue)
{
    return SetSocketOption(Handler, OptionLevel, OptionName, &OptionValue, sizeof(T));
}

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SYS_NET
#define RF_SHORTHAND_NAMESPACE_SYS_NET
namespace RF_SysNet = RadonFramework::System::Network;
#endif

#endif // RF_SYSTEM_NETWORK_SERVICE_HPP
