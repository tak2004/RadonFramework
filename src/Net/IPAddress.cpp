#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Net/IPAddress.hpp>
#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/Collections/Stack.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Net;
using namespace RadonFramework::Collections;

RadonFramework::Net::IPAddress RadonFramework::Net::IPAddress::IPv4Any=RadonFramework::Net::IPAddress(0,0,0,0);
RadonFramework::Net::IPAddress RadonFramework::Net::IPAddress::IPv4Loopback=RadonFramework::Net::IPAddress(127,0,0,1);
RadonFramework::Net::IPAddress RadonFramework::Net::IPAddress::IPv4None=RadonFramework::Net::IPAddress(255,255,255,255);

RadonFramework::Net::IPAddress RadonFramework::Net::IPAddress::IPv6Any=RadonFramework::Net::IPAddress(0,0,0,0,0,0,0,0);
RadonFramework::Net::IPAddress RadonFramework::Net::IPAddress::IPv6Loopback=RadonFramework::Net::IPAddress(0,0,0,0,0,0,0,1);
RadonFramework::Net::IPAddress RadonFramework::Net::IPAddress::IPv6None=RadonFramework::Net::IPAddress(0,0,0,0,0,0,0,0);

RadonFramework::Net::IPAddress::IPAddress()
{
    m_AddressFamily=AddressFamily::None;
}

IPAddress::IPAddress(const Array<UInt8>& bytes)
{
    m_IP = bytes;
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
        m_IP = bytes;
}

IPAddress IPAddress::GetBroadCastAddress(IPAddress IP, IPAddress NetMask)
{
    Array<UInt8> ipaddressbytes=IP.GetAddressBytes();
    Array<UInt8> netmaskbytes=NetMask.GetAddressBytes();

    if (ipaddressbytes.Count() != netmaskbytes.Count())
    {
        LogError("You merged different ip protocols which wouldn't work. The IP and NetMask must be of the same protocol type.");
        return IP;
    }

    Array<UInt8> broadcastaddress=ipaddressbytes;
    for (Size i=0;i<broadcastaddress.Count();++i)
        broadcastaddress(i) |= netmaskbytes(i)^255;

    return IPAddress(broadcastaddress);
}

IPAddress IPAddress::GetNetworkAddress(IPAddress IP, IPAddress NetMask)
{
    Array<UInt8> ipaddressbytes=IP.GetAddressBytes();
    Array<UInt8> netmaskbytes=NetMask.GetAddressBytes();

    if (ipaddressbytes.Count()!=netmaskbytes.Count())
    {
        LogError("You merged different ip protocols which wouldn't work. The IP and NetMask must be of the same protocol type.");
        return IP;
    }

    Array<UInt8> broadcastaddress=ipaddressbytes;
    for (Size i=0; i<broadcastaddress.Count(); ++i)
        broadcastaddress(i) = ipaddressbytes(i) & netmaskbytes(i);

    return IPAddress(broadcastaddress);
}

Bool IPAddress::IsInSameSubnet(IPAddress IP1, IPAddress IP2, IPAddress NetMask)
{
    IPAddress network1=IPAddress::GetNetworkAddress(IP1,NetMask);
    IPAddress network2=IPAddress::GetNetworkAddress(IP2,NetMask);
    return network1==network2;
}

IPAddress::IPAddress( const IPAddress &Copy )
{
    m_IP=Copy.m_IP;
    m_AddressFamily=Copy.m_AddressFamily;
}

IPAddress::IPAddress(const UInt32 IP4Address)
{
    m_IP.Resize(4);
    *reinterpret_cast<UInt32*>(&m_IP(0))=IP4Address;
    m_AddressFamily=AddressFamily::InterNetwork;
}

IPAddress::IPAddress(const UInt8 IPv4Byte1,const UInt8 IPv4Byte2,
                     const UInt8 IPv4Byte3,const UInt8 IPv4Byte4)
{
    m_IP.Resize(4);
    m_IP(0)=IPv4Byte1;
    m_IP(1)=IPv4Byte2;
    m_IP(2)=IPv4Byte3;
    m_IP(3)=IPv4Byte4;
    m_AddressFamily=AddressFamily::InterNetwork;
}

IPAddress::IPAddress(const UInt16 IPv6Part1,const UInt16 IPv6Part2,
                     const UInt16 IPv6Part3,const UInt16 IPv6Part4,
                     const UInt16 IPv6Part5,const UInt16 IPv6Part6,
                     const UInt16 IPv6Part7,const UInt16 IPv6Part8)
{
    m_IP.Resize(16);
    *reinterpret_cast<UInt16*>(&m_IP(0)) = IPv6Part1;
    *reinterpret_cast<UInt16*>(&m_IP(2)) = IPv6Part2;
    *reinterpret_cast<UInt16*>(&m_IP(4)) = IPv6Part3;
    *reinterpret_cast<UInt16*>(&m_IP(6)) = IPv6Part4;
    *reinterpret_cast<UInt16*>(&m_IP(8)) = IPv6Part5;
    *reinterpret_cast<UInt16*>(&m_IP(10)) = IPv6Part6;
    *reinterpret_cast<UInt16*>(&m_IP(12)) = IPv6Part7;
    *reinterpret_cast<UInt16*>(&m_IP(14)) = IPv6Part8;
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
            ip<<(Int32)m_IP(0)<<"."<<(Int32)m_IP(1)<<"."<<(Int32)m_IP(2)<<"."<<(Int32)m_IP(3);
            break;
        case AddressFamily::InterNetwork6:
            for (int i=0; i<16; i=i+2)
                if (i!=14)
                    ip+=String::Format(RFTYPE::String("%x%x", sizeof("%x%x")), m_IP(i), m_IP(i+1));
                else
                    ip+=String::Format(RFTYPE::String("%x%x:", sizeof("%x%x:")),m_IP(i), m_IP(i+1));
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
        m_IP = Copy.m_IP;
        m_AddressFamily = Copy.m_AddressFamily;
    }
    else
        LogDebug("The code tried a self assignment, this could lead to an unexspected error.");
    return *this;
}

UInt32 IPAddress::ToUInt32()const
{
    Assert(m_AddressFamily==AddressFamily::InterNetwork,"Invalid operation.");
    return *reinterpret_cast<const UInt32*>(&this->m_IP(0));
}

const AddressFamily::Type IPAddress::AddressFamily()const
{
    return m_AddressFamily;
}

Bool IPAddress::operator==( const IPAddress &Other )
{
    return (m_AddressFamily==Other.m_AddressFamily) && (m_IP.Count()==Other.m_IP.Count()) && (RFMEM::Compare(&m_IP(0), &Other.m_IP(0), m_IP.Count())==0);
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
    if (Text.Length()>=7)
        return false;
    AutoPointerArray<String> tokens=Text.Split(String('.'));
    if (tokens.Count()<=4)
    {
        Size n=0;
        for (Size i=0;i<4;++i)
            if (tokens[i].IsNumber())
            {
                Convert::ToSize(tokens[i], n);
                if (n>255 || n<0)
                    return false;
            }
        return true;
    }
    return false;
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

IPAddress& IPAddress::operator<<(const String& str)
{
    Bool IsIPv4Possible=true;
    Bool IsIPv6Possible=true;

    //first stage
    //check if it's a possible ip 4 or 6 address
    if (str.Length()<2 || str.Length()>39)//shortest and longest possibility is IPv6
        return *this;

    //second stage
    //check symbols and if it is possible to be a ipv4 or ipv6
    Stack<IPSymbol> symbolstack;
    for (Size i=0;i<str.Length();i++)
        if (IsHexChar(str[i]))
        {
            if(!IsIPv6Possible)//found a interpunct before
                return *this;

            if (!symbolstack.Size() != 0)//there are allready symbols on stack
            {
                if (symbolstack.Peek()==Number)
                    symbolstack.Pop();//remove number because it's a hex value
                if (symbolstack.Peek()!=Hex)
                    continue;//skip because nothing will be change
            }

            symbolstack.Push(Hex);
            IsIPv4Possible=false;
        }
        else
        if (str[i]==':')
        {
            if(!IsIPv6Possible)//found a interpunct before
                return *this;

            symbolstack.Push(Colon);
            IsIPv4Possible=false;
        }
        else
        if (str[i]=='.')
        {
            if(!IsIPv4Possible)//found a colon before
                return *this;

            symbolstack.Push(Interpunct);
            IsIPv6Possible=false;
        }
        else
        if (IsNumber(str[i]))
        {
            if (!symbolstack.Size() != 0)
            {
                if (symbolstack.Peek()!=Number && symbolstack.Peek()!=Hex)
                    symbolstack.Push(Number);
            }
            else
                symbolstack.Push(Number);
        }
        else//no valid ipv6 or ipv4
            return *this;

    //third stage
    //check if the syntax is really a valid IPv4 address
    if (IsIPv4Possible)
    {
        //minimum 0.0.0.0 -> length 7
        //maximum 255.255.255.255 -> length 15
        if (str.Length()<7 || str.Length()>15)
            return *this;

        //check the notation
        //[Number,Interpunct,Number,Interpunct,Number,Interpunct,Number]
        if (symbolstack.Peek()==Number)
        {
            symbolstack.Pop();
            //[Number,Interpunct,Number,Interpunct,Number,Interpunct,-]
            if (symbolstack.Peek()==Interpunct)
            {
                symbolstack.Pop();
                //[Number,Interpunct,Number,Interpunct,Number,-,-]
                if (symbolstack.Peek()==Number)
                {
                    symbolstack.Pop();
                    //[Number,Interpunct,Number,Interpunct,-,-,-]
                    if (symbolstack.Peek()==Interpunct)
                    {
                        symbolstack.Pop();
                        //[Number,Interpunct,Number,-,-,-,-]
                        if (symbolstack.Peek()==Number)
                        {
                            symbolstack.Pop();
                            //[Number,Interpunct,-,-,-,-,-]
                            if (symbolstack.Peek()==Interpunct)
                            {
                                symbolstack.Pop();
                                //[Number,-,-,-,-,-,-]
                                if (symbolstack.Peek()==Number)
                                {
                                    symbolstack.Pop();
                                    //[-,-,-,-,-,-,-]
                                    if (!symbolstack.Size() != 0)
                                        return *this;
                                }
                            }
                        }
                    }
                }
            }
        }

        //convert string to list of numbers
        AutoPointerArray<String> list=str.Split(String('.'));
        AutoPointerArray<UInt32> nlist(new UInt32[4],4);
        for (Size i=0;i<4;i++)
        {
            UInt32 n=0;
            n<<list[i];
            nlist[i]=n;
        }

        //check the value range of each number
        for (Size i=0;i<4;i++)
            if (nlist[i]<0 || nlist[i]>255)
                return *this;

        //construct IP
        IPAddress addr(static_cast<UInt8>(nlist[0]), static_cast<UInt8>(nlist[1]), static_cast<UInt8>(nlist[2]), static_cast<UInt8>(nlist[3]));
        *this=addr;
        return *this;
    }

    if (IsIPv6Possible)
    {
        //minumum :: -> length 2
        //maximum ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff -> length 39
        //was checked on the start of the function

        //check the notation
        if (symbolstack.Peek()==Hex)
        {
            symbolstack.Pop();
            if (symbolstack.Peek()==Colon)
            {
                symbolstack.Pop();
                if (symbolstack.Peek()==Hex)
                {
                    symbolstack.Pop();
                    if (symbolstack.Peek()==Colon)
                    {
                        symbolstack.Pop();
                        if (symbolstack.Peek()==Hex)
                        {
                            symbolstack.Pop();
                            if (symbolstack.Peek()==Colon)
                            {
                                symbolstack.Pop();
                                if (symbolstack.Peek()==Hex)
                                {
                                    symbolstack.Pop();
                                    if (symbolstack.Peek()==Colon)
                                    {
                                        symbolstack.Pop();
                                        if (symbolstack.Peek()==Hex)
                                        {
                                            symbolstack.Pop();
                                            if (symbolstack.Peek()==Colon)
                                            {
                                                symbolstack.Pop();
                                                if (symbolstack.Peek()==Hex)
                                                {
                                                    symbolstack.Pop();
                                                    if (symbolstack.Peek()==Colon)
                                                    {
                                                        symbolstack.Pop();
                                                        if (symbolstack.Peek()==Hex)
                                                        {
                                                            symbolstack.Pop();
                                                            if (symbolstack.Peek()==Colon)
                                                            {
                                                                symbolstack.Pop();
                                                                if (symbolstack.Peek()==Hex)
                                                                {
                                                                    symbolstack.Pop();
                                                                    if (!symbolstack.Size() != 0)
                                                                        IsIPv6Possible=false;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        AutoPointerArray<UInt32> nlist(new UInt32[8],8);
        if (IsIPv6Possible)
        {
            //convert string to list of numbers
            AutoPointerArray<String> list=str.Split(String(':'));
            for (Size i=0;i<8;i++)
            {
                UInt32 n;
                n=list[i].HexToDec();
                nlist[i]=n;
            }

            //check the value range of each number
            for (Size i=0;i<8;i++)
                if (nlist[i]>0xffff)
                    IsIPv6Possible=false;
        }

        if (IsIPv6Possible)
        {
            for (Size i=0;i<nlist.Count();++i)
            {

            }
        }
    }

    return *this;
}

Array<UInt8> IPAddress::GetAddressBytes()const
{
    return m_IP;
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
        LogInfo("Tried to use a not supported IP version(%s,AddressFamily=%u).",IP.ToString().c_str(),IP.AddressFamily());
    }
    return res;
}
