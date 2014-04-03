#ifndef RF_IPADDRESS_HPP
#define RF_IPADDRESS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/AddressFamily.hpp>
#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework
{
    namespace Net
    {
        class IPAddress
        {
            public:
                IPAddress();
                IPAddress(const Collections::Array<RFTYPE::UInt8>& bytes);
                IPAddress(const IPAddress &Copy);
                IPAddress(const RFTYPE::UInt32 IP4Address);
                IPAddress(const RFTYPE::UInt8 IPv4Byte1,const RFTYPE::UInt8 IPv4Byte2,
                          const RFTYPE::UInt8 IPv4Byte3,const RFTYPE::UInt8 IPv4Byte4);
                IPAddress(const RFTYPE::UInt16 IPv6Part1,const RFTYPE::UInt16 IPv6Part2,
                          const RFTYPE::UInt16 IPv6Part3,const RFTYPE::UInt16 IPv6Part4,
                          const RFTYPE::UInt16 IPv6Part5,const RFTYPE::UInt16 IPv6Part6,
                          const RFTYPE::UInt16 IPv6Part7,const RFTYPE::UInt16 IPv6Part8);
                ~IPAddress();

                RFTYPE::String ToString()const;
                RFTYPE::UInt32 ToUInt32()const;

                Collections::Array<RFTYPE::UInt8> GetAddressBytes()const;
                IPAddress& operator=(const IPAddress &Copy);
                IPAddress& operator<<(const RFTYPE::String& str);

                RFTYPE::Bool operator==(const IPAddress &Other);
                const AddressFamily::Type AddressFamily()const;

                static IPAddress GetBroadCastAddress(IPAddress IP, IPAddress NetMask);
                static IPAddress GetNetworkAddress(IPAddress IP, IPAddress NetMask);
                static RFTYPE::Bool IsInSameSubnet(IPAddress IP1, IPAddress IP2, IPAddress NetMask);
                static RFTYPE::Bool IsPrivateNetworkAddress(IPAddress IP);
                static RFTYPE::Bool IsValidIP(const RFTYPE::String& Text);
                static RFTYPE::Bool IsValidIPv4(const RFTYPE::String& Text);
                static RFTYPE::Bool IsValidIPv6(const RFTYPE::String& Text);

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
                AddressFamily::Type m_AddressFamily;
                Collections::Array<RFTYPE::UInt8> m_IP;
        };
    }
}

#endif
