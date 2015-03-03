#ifndef RF_IPADDRESS_HPP
#define RF_IPADDRESS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/AddressFamily.hpp>
#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework { namespace Net {

class IPAddress
{
public:
    IPAddress();
    IPAddress(const Collections::Array<RF_Type::UInt8>& bytes);
    IPAddress(const IPAddress &Copy);
    IPAddress(const RF_Type::UInt32 IP4Address);
    IPAddress(const RF_Type::UInt8 IPv4Byte1,const RF_Type::UInt8 IPv4Byte2,
                const RF_Type::UInt8 IPv4Byte3,const RF_Type::UInt8 IPv4Byte4);
    IPAddress(const RF_Type::UInt16 IPv6Part1,const RF_Type::UInt16 IPv6Part2,
                const RF_Type::UInt16 IPv6Part3,const RF_Type::UInt16 IPv6Part4,
                const RF_Type::UInt16 IPv6Part5,const RF_Type::UInt16 IPv6Part6,
                const RF_Type::UInt16 IPv6Part7,const RF_Type::UInt16 IPv6Part8);
    ~IPAddress();

    RF_Type::String ToString()const;
    RF_Type::UInt32 ToUInt32()const;

    Collections::Array<RF_Type::UInt8> GetAddressBytes()const;
    const RF_Type::UInt8* AsByteArray()const;
    RF_Type::Size GetByteArraySize()const;
    IPAddress& operator=(const IPAddress &Copy);
    //IPAddress& operator<<(const RF_Type::String& str);

    RF_Type::Bool operator==(const IPAddress &Other);
    const AddressFamily GetAddressFamily()const;

    static IPAddress GetBroadCastAddress(IPAddress IP, IPAddress NetMask);
    static IPAddress GetNetworkAddress(IPAddress IP, IPAddress NetMask);
    static RF_Type::Bool IsInSameSubnet(IPAddress IP1, IPAddress IP2, IPAddress NetMask);
    static RF_Type::Bool IsPrivateNetworkAddress(IPAddress IP);
    
    static RF_Type::Bool IsValidIP(const RF_Type::String& Text);
    static RF_Type::Bool IsValidIPv4(const RF_Type::String& Text);
    static RF_Type::Bool IsValidIPv6(const RF_Type::String& Text);
    
    static RF_Type::Bool Resolve(const RF_Type::String& Text, IPAddress& ResolvedAddress);
    static RF_Type::Bool ResolveIP4(const RF_Type::String& Text, IPAddress& ResolvedAddress);
    static RF_Type::Bool ResolveIP6(const RF_Type::String& Text, IPAddress& ResolvedAddress);
    static RF_Type::Bool ResolveIP6Hybrid(const RF_Type::String& Text, IPAddress& ResolvedAddress);

    static IPAddress IPv4Any;
    static IPAddress IPv4Loopback;
    static IPAddress IPv4None;

    static IPAddress IPv6Any;
    static IPAddress IPv6Loopback;
    static IPAddress IPv6None;
protected:
    enum IPSymbol{
        Colon,
        Interpunct,
        Hex,
        Number
    };
    AddressFamily m_AddressFamily;
    RF_Type::UInt8 m_IP[16];
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_NET
#define RF_SHORTHAND_NAMESPACE_NET
namespace RF_Net = RadonFramework::Net;
#endif

#endif
