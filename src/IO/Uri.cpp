#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/Uri.hpp"
#include "RadonFramework/Net/IPAddress.hpp"
#include "RadonFramework/Math/Math.hpp"
#include "RadonFramework/IO/Log.hpp"

using namespace RadonFramework;
using namespace RadonFramework::IO;
using namespace RadonFramework::Core::Types;

Uri::Uri()
:m_HostNameType(UriHostNameType::Unknown)
,m_Port(0)
,m_IsAbsolute(false)
,m_IsDefaultPort(true)
,m_IsDefaultUser(true)
,m_UserEscaped(false)
,m_IsOpaque(false)
{
}

Uri::Uri(const String& UriString, const UriKind::Type UriKind)
:m_OriginalString(UriString)
,m_HostNameType(UriHostNameType::Unknown)
,m_Port(0)
,m_IsAbsolute(false)
,m_IsDefaultPort(true)
,m_IsDefaultUser(true)
,m_UserEscaped(true)
,m_IsOpaque(false)
{
    String str;
    // check if the uri is completly escaped
    for (UInt32 i=0;i<m_OriginalString.Length();++i)
        if (NeedToEscapeUriChar[static_cast<UInt8>(m_OriginalString[i])])
        {
            m_UserEscaped=false;
            str=Uri::EscapeUriString(UriString);
            break;
        }
    if (m_UserEscaped)
        str=m_OriginalString;

    // check if it's a absolute URI
    // absolute URI==schemename:....
    if (CheckSchemeName(str))
        m_IsAbsolute=true;

    Int32 lastEnd=0;

    // get scheme name if available
    if (m_IsAbsolute)
    {
        lastEnd=str.IndexOf(Uri::SchemeDelimiter);
        m_Scheme=str.SubString(0,lastEnd);
    }

    // get the scheme specific part
    Int32 fragmentStart=str.IndexOf(String("#",lastEnd+1));
    if (fragmentStart<0)
        m_SchemeSpecificPart=str.SubString(lastEnd+1,str.Length()-lastEnd-1);
    else
        m_SchemeSpecificPart=str.SubString(lastEnd+1,fragmentStart-lastEnd-1);

    // get the fragment part if available
    if (fragmentStart>=0)
        m_Fragment=str.SubString(fragmentStart+1,str.Length()-fragmentStart-1);

    // check if it's a opaque URI
    // opaque==absolute+no '/' at start of scheme specific part
    if (m_IsAbsolute)
        if (m_SchemeSpecificPart.IndexOf("/") == -1)
            m_IsOpaque=true;

    // non opaque uri's need more parsing
    if (!m_IsOpaque)
    {
        // [scheme:][//authority][path][?query][#fragment]
        //          |_________________________|

        lastEnd=0;
        // authority

        // The authority component is preceded by a double slash ("//") and is
        // terminated by the next slash ("/"), question mark ("?"), or number
        // sign ("#") character, or by the end of the URI.
        if (m_SchemeSpecificPart.StartsWith("//"))
        {

            Int32 authorityEnd=m_SchemeSpecificPart.IndexOf("/", 2);
            if (authorityEnd<0)
                authorityEnd=m_SchemeSpecificPart.IndexOf("?",2);
            if (authorityEnd<0)
                authorityEnd=m_SchemeSpecificPart.IndexOf("#",2);
            if (authorityEnd<0)
                authorityEnd=m_SchemeSpecificPart.Length();
            m_Authority=m_SchemeSpecificPart.SubString(2,authorityEnd-2);
            lastEnd=authorityEnd;
        }

        // path
        // If the lastEnd point to a "/" then there is a path.
        if (m_SchemeSpecificPart[lastEnd]=='/' || !m_IsAbsolute)
        {
            // The path is terminated by the first question mark ("?") or
            // number sign ("#") character, or by the end of the URI.
            Int32 pathEnd=m_SchemeSpecificPart.IndexOf("?",lastEnd);
            if (pathEnd<0)
                pathEnd=m_SchemeSpecificPart.IndexOf("#",lastEnd);
            if (pathEnd<0)
                pathEnd=m_SchemeSpecificPart.Length();
            m_Path=m_SchemeSpecificPart.SubString(lastEnd, pathEnd - lastEnd);
            lastEnd=pathEnd;
        }

        // query
        // If the lastEnd point to a "?" then there is a query.
        if (m_SchemeSpecificPart[lastEnd] == '?')
        {
            // The path is terminated by the first question mark ("?") or
            // number sign ("#") character, or by the end of the URI.
            Int32 queryEnd=m_SchemeSpecificPart.IndexOf("#", lastEnd);
            if (queryEnd<0)
                queryEnd=m_SchemeSpecificPart.Length();
            m_Query=m_SchemeSpecificPart.SubString(lastEnd + 1, queryEnd - lastEnd - 1);
            lastEnd=queryEnd;
        }
    }

    // parse authority
    if (0==m_Authority.Length())//if authority is empty then it's localhost and default port
    {
        m_Host="localhost";
        m_IsDefaultPort=true;
        m_IsDefaultUser=true;
        m_HostNameType=UriHostNameType::DomainName;
    }
    else
    {
        // get user info
        Int32 userinfoEnd=m_Authority.IndexOf("@");
        if (userinfoEnd>=0)
        {
            m_IsDefaultUser=false;
            m_UserInfo=m_Authority.SubString(0,userinfoEnd);
        }
        else
        {
            m_IsDefaultUser=true;
            userinfoEnd=0;
        }

        // get hostname
        // If there is a ']' which indicate that there is a IPv6 then check if
        // the hostnameEnd don't point to a ':' of the IPv6.
        // Check also if hostnameEnd point to a ':' of the user info.
        Int32 hostnameEnd=m_Authority.LastIndexOf(":");
        Int32 IPliteral=m_Authority.IndexOf("]");
        if (hostnameEnd<0 || hostnameEnd<IPliteral || hostnameEnd<userinfoEnd)
            hostnameEnd=m_Authority.Length();

        m_HostNameType=HostNameType(m_Authority.SubString(userinfoEnd+1,hostnameEnd-userinfoEnd-1));
        m_Host=m_Authority.SubString(userinfoEnd + 1,hostnameEnd-userinfoEnd - 1);

        // get port
        if (static_cast<UInt32>(hostnameEnd)<m_Authority.Length())
        {
            m_IsDefaultPort=false;
            Convert::ToInt32(m_Authority.SubString(hostnameEnd+1,m_Authority.Length()-hostnameEnd-1), m_Port);
        }
    }
}

Uri::Uri(const Uri& Copy)
{
    *this = Copy;
}

Uri::~Uri()
{
}

UriHostNameType::Type Uri::HostNameType(const String& Name)
{
    if (RF_Net::IPAddress::IsValidIPv4(Name))
        return UriHostNameType::IPv4;
    //check if hostname
    if (Name.Length()<=255)//only a max length of 255 character is allowed
    {
        UInt32 i=0;
        for (;i<Name.Length();++i)
            if ((Name[i]>='A' && Name[i]<='Z') || (Name[i]>='a' && Name[i]<='z') ||
                (Name[i]>='0' && Name[i]<='9') || Name[i]=='-')
                continue;
            else/*Check if current char is a dot, prev,next, char isn't a dot
                  and current char isn't first or last char of string.*/
                if (Name[i]=='.' && i!=0 && i!=Name.Length()-1 && Name[i+1]!='.')
                    continue;
                else
                    break;
        if (i==Name.Length())
            return UriHostNameType::DomainName;
    }
    if (Name.Length()>3 && Name[0]=='[' && Name[Name.Length()-1]==']')
        if (RF_Net::IPAddress::IsValidIPv6(Name.SubString(1,Name.Length()-2)))
            return UriHostNameType::IPv6;
    return UriHostNameType::Unknown;
}

Bool Uri::CheckSchemeName(const String& SchemeName)
{
    if (SchemeName.Length()<3)
        return false;
    for (UInt32 i=0;i<SchemeName.Length();++i)
    {
        if ((SchemeName[i]>='a' && SchemeName[i]<='z') ||
            (SchemeName[i]>='A' && SchemeName[i]<='Z') ||
            (SchemeName[i]>='0' && SchemeName[i]<='9') ||
            SchemeName[i]=='.' || SchemeName[i]=='-' || SchemeName[i]=='+')
            continue;
        else
        {
            if (SchemeName[i]==':')
                return true;
            break;
        }
    }
    return false;
}

Int32 Uri::Compare(const Uri& Uri1, const Uri& Uri2,
                   const UriComponents::Type PartToCompare,
                   const UriFormat::Type CompareFormat)
{
    String a=Uri1.GetComponents(PartToCompare,CompareFormat);
    String b=Uri2.GetComponents(PartToCompare,CompareFormat);
    return a.Compare(b);
}

String Uri::EscapeDataString(const String& StringToEscape)
{
    String str;
    for (UInt32 i=0;i<StringToEscape.Length();++i)
        if (NeedToEscapeDataChar[static_cast<UInt8>(StringToEscape[i])])
            str+=HexEscape(StringToEscape[i]);
        else
            str += StringToEscape.SubString(i,1);
    return str;
}

String Uri::EscapeUriString(const String& StringToEscape)
{
    String str;
    for (UInt32 i=0;i<StringToEscape.Length();++i)
        if (NeedToEscapeUriChar[static_cast<UInt8>(StringToEscape[i])])
            str+=HexEscape(StringToEscape[i]);
        else
            str+=StringToEscape.SubString(i,1);
    return str;
}

Int32 Uri::FromHex(const Char Digit)
{
    if(Digit >= '0' && Digit <= '9')
    {
        return Digit - '0';
    }
    if(Digit >= 'a' && Digit <= 'f')
    {
        return Digit - 'a' + 10;
    }
    if(Digit >= 'A' && Digit <= 'F')
    {
        return Digit - 'A' + 10;
    }
    return -1;
}

String Uri::GetComponents(const UriComponents::Type Components,
                          const UriFormat::Type Format)const
{
    String str;
    if ((Components & UriComponents::Scheme) && (m_Scheme.Length()>0))
        str=m_Scheme+":";

    if (((static_cast<int>(Components) & static_cast<int>(UriComponents::SchemeSpecificPart))!=0) && 
        (m_SchemeSpecificPart.Length()>0))
    {
        if ((static_cast<int>(Components) & static_cast<int>(UriComponents::SchemeSpecificPart)) == 
            static_cast<int>(UriComponents::SchemeSpecificPart))
        {
            str+=m_SchemeSpecificPart;
        }
        else
        {
            if (((static_cast<int>(Components) & static_cast<int>(UriComponents::Authority))!=0) && 
                (m_Authority.Length()>0))
            {
                str+="//";
                if ((static_cast<int>(Components) & static_cast<int>(UriComponents::Authority)) == 
                    static_cast<int>(UriComponents::Authority))
                {
                    str+=m_Authority;
                }
                else
                {
                    if (((static_cast<int>(Components) & static_cast<int>(UriComponents::UserInfo))!=0) && 
                        (m_UserInfo.Length()>0))
                    {
                        str=str+m_UserInfo+"@";
                    }

                    if (((static_cast<int>(Components) & static_cast<int>(UriComponents::Host))!=0) && 
                        (m_Host.Length()>0))
                    {
                        str+=m_Host;
                    }

                    if (((static_cast<int>(Components) & static_cast<int>(UriComponents::Port))!=0) && 
                        !m_IsDefaultPort)
                    {
                        str=str+":"+m_Port;
                    }
                }
            }

            if (((static_cast<int>(Components) & static_cast<int>(UriComponents::Path))!=0) && 
                (m_Path.Length()>0))
            {
                str+=m_Path;
            }

            if (((static_cast<int>(Components) & static_cast<int>(UriComponents::Query))!=0) && 
                (m_Query.Length()>0))
            {
                str=str+"?"+m_Query;
            }

            if (((static_cast<int>(Components) & static_cast<int>(UriComponents::Fragment))!=0) && 
                (m_Fragment.Length()>0))
            {
                str=str+"#"+m_Fragment;
            }
        }
    }

    if (Format & UriFormat::Unescaped)
        str=UnescapeDataString(str);

    return str;
}

String Uri::HexUpperChars[]={"0","1","2","3","4","5","6","7","8","9","A","B","C","D","E","F"};

String Uri::HexEscape(const Char Character)
{
    return String("%")+HexUpperChars[(Character & 0xf0)>>4]+
           HexUpperChars[(Character & 0x0f)];
}

Char Uri::HexUnescape(const String& Pattern, UInt32& Index)
{
    Char chr;
    if (IsHexEncoding(Pattern,Index))
    {
        Int32 value = (FromHex(Pattern[Index + 1]) * 16) + FromHex(Pattern[Index + 2]);
        chr = static_cast<Char>(value);
        Index+=3;
    }
    else
    {
        if (Pattern[Index]=='%' && Pattern.Length()>Index+1 && Pattern[Index+1]=='%')
        {
            chr='%';
            Index+=2;
        }
        else
        {
            chr=Pattern[Index];
            ++Index;
        }
    }
    return chr;
}

Bool Uri::IsHexDigit(const Char Character)
{
    return (Character>='0' && Character<='9') ||
           (Character>='a' && Character<='f') ||
           (Character>='A' && Character<='F');
}

Bool Uri::IsHexEncoding(const String& Pattern, const UInt32 Index)
{
    if (Index+2>Pattern.Length())
        return false;
    if (Pattern[Index]!='%')
        return false;
    if (!IsHexDigit(Pattern[Index+1]))
        return false;
    if (!IsHexDigit(Pattern[Index+2]))
        return false;
    return true;
}

String Uri::UnescapeDataString(const String& StringToUnescape)
{
    String str;
    UInt32 len=StringToUnescape.Length();
    for (UInt32 i = 0; i < len;)
        str+=HexUnescape(StringToUnescape,i);
    return str;
}

const String& Uri::Path()const
{
    return m_Path;
}

const String& Uri::Authority()const
{
    return m_Authority;
}

const String& Uri::Fragment()const
{
    return m_Fragment;
}

const String& Uri::Host()const
{
    return m_Host;
}

UriHostNameType::Type Uri::HostNameType()const
{
    return m_HostNameType;
}

Bool Uri::IsAbsolute()const
{
    return m_IsAbsolute;
}

Bool Uri::IsDefaultPort()const
{
    return m_IsDefaultPort;
}

Core::Types::Bool Uri::IsDefaultUser()const
{
    return m_IsDefaultUser;
}

const String& Uri::OriginalString()const
{
    return m_OriginalString;
}

Int32 Uri::Port()const
{
    return m_Port;
}

const String& Uri::Query()const
{
    return m_Query;
}

const String& Uri::Scheme()const
{
    return m_Scheme;
}

const String& Uri::SchemeSpecificPart()const
{
    return m_SchemeSpecificPart;
}

Bool Uri::IsOpaque()const
{
    return m_IsOpaque;
}

Bool Uri::UserEscaped()const
{
    return m_UserEscaped;
}

const String& Uri::UserInfo()const
{
    return m_UserInfo;
}

bool Uri::operator ==(const Uri& Other)
{
    return m_OriginalString == Other.m_OriginalString;
}

Uri& RadonFramework::IO::Uri::operator=(const Uri& Other)
{
    m_OriginalString = Other.m_OriginalString;
    m_Path = Other.m_Path;
    m_Authority = Other.m_Authority;
    m_Fragment = Other.m_Fragment;
    m_Query = Other.m_Query;
    m_Scheme = Other.m_Scheme;
    m_SchemeSpecificPart = Other.m_SchemeSpecificPart;
    m_Host = Other.m_Host;
    m_UserInfo = Other.m_UserInfo;
    m_HostNameType = Other.m_HostNameType;
    m_Port = Other.m_Port;
    m_IsAbsolute = Other.m_IsAbsolute;
    m_IsDefaultPort = Other.m_IsDefaultPort;
    m_IsDefaultUser = Other.m_IsDefaultUser;
    m_UserEscaped = Other.m_UserEscaped;
    m_IsOpaque = Other.m_IsOpaque;
    return *this;
}

bool Uri::operator !=(const Uri& Other)
{
    return !(*this==Other);
}

String Uri::SchemeDelimiter(":");

String Uri::PathSeperator("/");

Bool Uri::NeedToEscapeUriChar[256]={
    1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,//0-29 aren't prin
    1,1,1,0,1,0,0,1,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,//30-59
    1,0,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,//60-89
    0,0,1,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,//90-119
    0,0,0,1,1,1,0,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,//120-149
    1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,//150-179
    1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,//180-209
    1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,//210-239
    1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1//240-255
};

Bool Uri::NeedToEscapeDataChar[256]={
    1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,//0-29 aren't prin
    1,1,1,1,1,1,1,1,1,1, 1,1,1,1,0,0,1,0,0,0, 0,0,0,0,0,0,0,0,1,1,//30-59
    1,1,1,1,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,//60-89
    0,1,1,1,1,0,1,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,//90-119
    0,0,0,1,1,1,0,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,//120-149
    1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,//150-179
    1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,//180-209
    1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,//210-239
    1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1//240-255
};

RF_Type::String Uri::Escape( RF_Type::String str, const RF_Type::String& UriString )
{
    return String();
}
