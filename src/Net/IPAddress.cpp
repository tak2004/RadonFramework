#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/IPAddress.hpp"
#include "RadonFramework/IO/Log.hpp"
#include "RadonFramework/Collections/Stack.hpp"
#include "RadonFramework/Collections/Algorithm/FindAll.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Collections;

namespace RadonFramework { namespace Net {

IPAddress IPAddress::IPv4Any=IPAddress(0,0,0,0);
IPAddress IPAddress::IPv4Loopback=IPAddress(127,0,0,1);
IPAddress IPAddress::IPv4None=IPAddress(255,255,255,255);

IPAddress IPAddress::IPv6Any=IPAddress(0,0,0,0,0,0,0,0);
IPAddress IPAddress::IPv6Loopback=IPAddress(0,0,0,0,0,0,0,1);
IPAddress IPAddress::IPv6None=IPAddress(0,0,0,0,0,0,0,0);

IPAddress::IPAddress()
{
    m_AddressFamily=AddressFamily::None;
}

Size IPAddress::GetByteArraySize() const
{
    Size result = 0;
    switch(m_AddressFamily)
    {
    case AddressFamily::InterNetwork:
        result = 4;
        break;
    case AddressFamily::InterNetwork6:
        result = 16;
        break;
    }
    return result;
}

const RF_Type::UInt8* IPAddress::AsByteArray() const
{
    return m_IP;
}

IPAddress::IPAddress(const Array<UInt8>& bytes)
{
    switch (bytes.Count())
    {
    case 4:
        m_AddressFamily = AddressFamily::InterNetwork;
        break;
    case 16:
        m_AddressFamily = AddressFamily::InterNetwork6;
        break;
    default:
        m_AddressFamily = AddressFamily::None;
        break;
    }
    if (m_AddressFamily != AddressFamily::None)
        RF_SysMem::Copy(m_IP, &bytes.Item(0), bytes.Count());
}

IPAddress IPAddress::GetBroadCastAddress(IPAddress IP, IPAddress NetMask)
{
    if(IP.GetAddressFamily() != NetMask.GetAddressFamily())
    {
        LogError("You merged different ip protocols which wouldn't work. The IP and NetMask must be of the same protocol type.");
        return IP;
    }

    IPAddress broadcastaddress(IP);
    for(Size i = 0; i<broadcastaddress.GetByteArraySize(); ++i)
        broadcastaddress.m_IP[i] |= NetMask.m_IP[i] ^ 255;

    return broadcastaddress;
}

IPAddress IPAddress::GetNetworkAddress(IPAddress IP, IPAddress NetMask)
{
    if(IP.GetAddressFamily() != NetMask.GetAddressFamily())
    {
        LogError("You merged different ip protocols which wouldn't work. The IP and NetMask must be of the same protocol type.");
        return IP;
    }

    IPAddress broadcastaddress(IP);
    for(Size i = 0; i<broadcastaddress.GetByteArraySize(); ++i)
        broadcastaddress.m_IP[i] = IP.m_IP[i] & NetMask.m_IP[i];

    return broadcastaddress;
}

Bool IPAddress::IsInSameSubnet(IPAddress IP1, IPAddress IP2, IPAddress NetMask)
{
    IPAddress network1=IPAddress::GetNetworkAddress(IP1,NetMask);
    IPAddress network2=IPAddress::GetNetworkAddress(IP2,NetMask);
    return network1==network2;
}

IPAddress::IPAddress( const IPAddress &Copy )
{
    m_AddressFamily=Copy.m_AddressFamily;
    if(m_AddressFamily != AddressFamily::None)
        RF_SysMem::Copy(m_IP, &Copy.m_IP, GetByteArraySize());
}

IPAddress::IPAddress(const UInt32 IP4Address)
{
    *reinterpret_cast<UInt32*>(m_IP)=IP4Address;
    m_AddressFamily=AddressFamily::InterNetwork;
}

IPAddress::IPAddress(const UInt8 IPv4Byte1,const UInt8 IPv4Byte2,
                     const UInt8 IPv4Byte3,const UInt8 IPv4Byte4)
{
    m_IP[0]=IPv4Byte1;
    m_IP[1]=IPv4Byte2;
    m_IP[2]=IPv4Byte3;
    m_IP[3]=IPv4Byte4;
    m_AddressFamily=AddressFamily::InterNetwork;
}

IPAddress::IPAddress(const UInt16 IPv6Part1,const UInt16 IPv6Part2,
                     const UInt16 IPv6Part3,const UInt16 IPv6Part4,
                     const UInt16 IPv6Part5,const UInt16 IPv6Part6,
                     const UInt16 IPv6Part7,const UInt16 IPv6Part8)
{
    *reinterpret_cast<UInt16*>(m_IP) = IPv6Part1;
    *reinterpret_cast<UInt16*>(m_IP+2) = IPv6Part2;
    *reinterpret_cast<UInt16*>(m_IP+4) = IPv6Part3;
    *reinterpret_cast<UInt16*>(m_IP+6) = IPv6Part4;
    *reinterpret_cast<UInt16*>(m_IP+8) = IPv6Part5;
    *reinterpret_cast<UInt16*>(m_IP+10) = IPv6Part6;
    *reinterpret_cast<UInt16*>(m_IP+12) = IPv6Part7;
    *reinterpret_cast<UInt16*>(m_IP+14) = IPv6Part8;
    m_AddressFamily=AddressFamily::InterNetwork6;
}

IPAddress::~IPAddress()
{
}

String IPAddress::ToString()const
{
    String ip;
    switch (m_AddressFamily)
    {
        case AddressFamily::InterNetwork:
            ip<<(Int32)m_IP[0]<<"."<<(Int32)m_IP[1]<<"."<<(Int32)m_IP[2]<<"."<<(Int32)m_IP[3];
            break;
        case AddressFamily::InterNetwork6:
            for (int i=0; i<16; i=i+2)
                if (i!=14)
                    ip+=String::Format("%x%x:"_rfs, m_IP[i], m_IP[i+1]);
                else
                    ip+=String::Format("%x%x"_rfs, m_IP[i], m_IP[i+1]);
            break;
        case AddressFamily::Unix:
            break;
        case AddressFamily::None:
            break;
        case AddressFamily::MAX:
            break;
    }
    return ip;
}

IPAddress& IPAddress::operator=( const IPAddress &Copy )
{
    if (&Copy!=this)
    {
        m_AddressFamily = Copy.m_AddressFamily;
        if(m_AddressFamily != AddressFamily::None)
            RF_SysMem::Copy(m_IP, &Copy.m_IP, GetByteArraySize());
    }
    else
        LogDebug("The code tried a self assignment, this could lead to an unexpected error.");
    return *this;
}

UInt32 IPAddress::ToUInt32()const
{
    Assert(m_AddressFamily==AddressFamily::InterNetwork,"Invalid operation.");
    return *reinterpret_cast<const UInt32*>(this->m_IP);
}

const AddressFamily IPAddress::GetAddressFamily()const
{
    return m_AddressFamily;
}

Bool IPAddress::operator==( const IPAddress &Other )
{
    Bool sameIP = RF_SysMem::Compare(m_IP, Other.m_IP, GetByteArraySize()) == 0;
    return (m_AddressFamily == Other.m_AddressFamily) && sameIP;
}

Bool IsHexChar(const char& chr)
{
    //check if 'A',...,'F' or 'a',...,'f'
    return (chr<71&&chr>64)||(chr>96&&chr<103)?true:false;
}

Bool IsNumber(const char& chr)
{
    //check if '0',...,'9'
    return (chr>47&&chr<58)?true:false;
}

Bool IPAddress::IsValidIP(const String& Text)
{
    return IsValidIPv4(Text) || IsValidIPv6(Text);
}

Bool IPAddress::IsValidIPv4(const String& Text)
{
    if(Text.Length() < 7)
        return false;

    AutoPointerArray<String> tokens = Text.Split("."_rfs);
    return tokens.Count() == 4 && RF_Algo::FindAll(tokens, [](AutoPointerArray<String>::ConstEnumeratorType& Text) {
        Size value;
        return Convert::ToSize(*Text, value) && value < 256;
    }).Count() == 4;
}

Bool IsHex(const String& Text)
{
    //check if 'A',...,'F' or 'a',...,'f' or '0',...,'9'
    for (UInt32 i=0;i<Text.Length();++i)
        if (!((Text[i]<71&&Text[i]>64) ||
              (Text[i]>96&&Text[i]<103)||
              (Text[i]>47&&Text[i]<58)))
            return false;
    return true;
}

Bool IPAddress::IsValidIPv6(const String& Text)
{/*
    if (Text.Length()>=2)
        return false;
    std::vector<String> tokens=Text.Split(":");
    Int32 n;
    for (UInt32 i=0;i<tokens.size();++i)
        if (!IsHex(tokens[i]))
            return false;
    return true;*/
    LogInfo("FIXME: IPAddress::IsValidIPv6() isn't implemented!!!");
    return false;
}

RF_Type::Bool IPAddress::ResolveIP4(const RF_Type::String& Text,
                                    IPAddress& ResolvedAddress)
{
    RF_Type::Bool result = true;
    if(Text.Length() < 7)
    {
        result = false;
    }

    if(result)
    {
        AutoPointerArray<UInt8> bytes(4);
        UInt8* fragments = bytes.Get();
        AutoPointerArray<String> tokens = Text.Split("."_rfs);
        result = tokens.Count() == 4 && 
            RF_Algo::FindAll(tokens, [fragments](AutoPointerArray<String>::ConstEnumeratorType& Text)
                 {
                     Bool result;
                     Size value;                     
                     result = Convert::ToSize(*Text, value) && value < 256;
                     fragments[Text.AtIndex()] = static_cast<UInt8>(value);
                     return result;
                 }).Count() == 4;
        if(result)
        {
            ResolvedAddress = IPAddress(bytes[0], bytes[1], bytes[2], bytes[3]);
        }
    }   

    return result;
}

Bool IPv6HexToShort(const String& Text, UInt16& Out)
{
    Bool result = true;

    if(Text.Length() <= 4)
    {
        UInt16 hexValue;
        Out = 0;
        Size offset = 0;
        for (Int32 i = Text.Length() - 1; i >= 0; --i)
        {
            if(Text[i] < 71 && Text[i] > 64)
                hexValue = Text[i] - 65;
            else
            if(Text[i] > 96 && Text[i] < 103)
                hexValue = Text[i] - 87;
            else
            if(Text[i] > 47 && Text[i] < 58)
                hexValue = Text[i] - 48;
            else
                result = false;

            if(result)
            {
                offset = Text.Length() - i - 1;
                Out += (hexValue * ((offset % 2) * 15 + 1)) << ((offset >> 1) << 3);
            }
        }
    }
    else
    {
        result = false;
    }

    return result;
}

Bool IPAddress::ResolveIP6(const String& Text, IPAddress& ResolvedAddress)
{
    Bool result = true;

    AutoPointerArray<UInt16> shorts(8);
    UInt16* fragments = shorts.Get();
    AutoPointerArray<String> tokens = Text.Split(":"_rfs);
    result = RF_Algo::FindAll(tokens, [fragments](AutoPointerArray<String>::ConstEnumeratorType& Text)
    {
        Bool result;
        UInt16 value;
        result = IsHex(*Text) && IPv6HexToShort(*Text, value);
        fragments[Text.AtIndex()] = value;
        return result;
    }).Count() == tokens.Count();

    if(result)
    {
        ResolvedAddress = IPAddress(shorts[0], shorts[1], shorts[2], shorts[3],
            shorts[4], shorts[5], shorts[6], shorts[7]);
    }

    return result;
}

RF_Type::Bool IPAddress::ResolveIP6Hybrid(const RF_Type::String& Text,
                                          IPAddress& ResolvedAddress)
{
return false;
}

RF_Type::Bool IPAddress::Resolve(const RF_Type::String& Text,
    IPAddress& ResolvedAddress)
{
    Bool IsIPv4Possible=true;
    Bool IsIPv6Possible=true;

    //check if it's a possible ip 4 or 6 address
    if (Text.Length()<2 || Text.Length()>39)//shortest and longest possibility is IPv6
        return false;
    
    if(Text.Contains("."_rfs) >= 0)
    {
        if(Text.Contains("::"_rfs) >= 0)
        {
            return ResolveIP6Hybrid(Text, ResolvedAddress);
        }
        else
        {
            return ResolveIP4(Text, ResolvedAddress);
        }
    }
    else
    {
        return ResolveIP6(Text, ResolvedAddress);
    }
}

Array<UInt8> IPAddress::GetAddressBytes()const
{
    Array<UInt8> result;
    switch(m_AddressFamily)
    {
    case AddressFamily::InterNetwork:
        result.Resize(4);
        RF_SysMem::Copy(&result(0), m_IP, 4);
        break;
    case AddressFamily::InterNetwork6:
        result.Resize(16);
        RF_SysMem::Copy(&result(0), m_IP, 16);
        break;
    }
    return result;
}

Bool IPAddress::IsPrivateNetworkAddress( IPAddress IP )
{
    Bool res=false;
    if (IP.m_AddressFamily==AddressFamily::InterNetwork)
    {
        res=res||IsInSameSubnet(IP,IPAddress(10,0,0,0),IPAddress(255,0,0,0));
        res=res||IsInSameSubnet(IP,IPAddress(172,16,0,0),IPAddress(255,240,0,0));
        res=res||IsInSameSubnet(IP,IPAddress(192,168,0,0),IPAddress(255,255,0,0));
        res=res||IsInSameSubnet(IP,IPAddress(169,254,0,0),IPAddress(255,255,0,0));
    }
    else
    if (IP.m_AddressFamily==AddressFamily::InterNetwork6)
    {
        // rfc4193 http://tools.ietf.org/html/rfc4193
        res=IsInSameSubnet(IP,IPAddress(0xFC,0,0,0,0,0,0,0),IPAddress(252,0,0,0,0,0,0,0));
    }
    else
    {
        LogInfo("Tried to use a not supported IP version(%s,AddressFamily=%u).",IP.ToString().c_str(),IP.GetAddressFamily());
    }
    return res;
}

} }