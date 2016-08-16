#ifndef RF_IO_URI_HPP
#define RF_IO_URI_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/IO/UriComponents.hpp>
#include <RadonFramework/IO/UriFormat.hpp>
#include <RadonFramework/IO/UriHostNameType.hpp>
#include <RadonFramework/IO/UriKind.hpp>
#include <RadonFramework/IO/UriPartial.hpp>

namespace RadonFramework { namespace IO {
/*
    foo://example.com:8042/over/there?name=ferret#nose
    \_/   \______________/\_________/ \_________/ \__/
     |           |            |            |        |
  scheme     authority       path        query   fragment
     |   _____________________|__
    / \ /                        \
    urn:example:animal:ferret:nose
*/

class Uri
{
public:
    // Constructors & Destructor
    Uri();
    Uri(const RF_Type::String& UriString,
        const UriKind::Type UriKind=UriKind::RelativeOrAbsolute);

    // Make a copy from an existing instance.
    Uri(const Uri& Copy);
            
    // Cleanup.
    ~Uri();

    // Methods
            
    // Gets the specified components of the current instance using the
    // specified escaping for special characters.
    RF_Type::String GetComponents(const UriComponents::Type Components=UriComponents::All,
                                        const UriFormat::Type Format=UriFormat::Unescaped)const;

    // Static methods

    // Determines whether the specified host name is a valid DNS name.
    static UriHostNameType::Type HostNameType(const RF_Type::String& Name);
            
    // Determines whether the specified scheme name is valid.
    static RF_Type::Bool CheckSchemeName(const RF_Type::String& SchemeName);
            
    // Compares the specified parts of two URIs using the specified 
    // comparison rules. If the result is 0 then they are equal, -1 means
    // they are different in length and greater 0 is the position of the
    // first difference.
    static RF_Type::Int32 Compare(const Uri& Uri1, const Uri& Uri2,
                                        const UriComponents::Type PartToCompare,
                                        const UriFormat::Type CompareFormat);

    // Converts a string to its escaped representation.
    static RF_Type::String EscapeDataString(
        const RF_Type::String& StringToEscape);
            
    // Converts a URI string to its escaped representation.
    static RF_Type::String EscapeUriString(
        const RF_Type::String& StringToEscape);
            
    // Gets the decimal value of a hexadecimal digit.
    static RF_Type::Int32 FromHex(const RF_Type::Char Digit);

    // Converts a specified character into its hexadecimal equivalent.
    static RF_Type::String HexEscape(const RF_Type::Char Character);
            
    // Converts a specified hexadecimal representation of a character 
    // to the character.
    static RF_Type::Char HexUnescape(const RF_Type::String& Pattern, 
                                            RF_Type::UInt32& Index);

    // Determines whether a specified character is a valid hexadecimal digit.
    static RF_Type::Bool IsHexDigit(const RF_Type::Char Character);

    // Determines whether a character in a string is hexadecimal encoded.
    static RF_Type::Bool IsHexEncoding(const RF_Type::String& Pattern,
                                            const RF_Type::UInt32 Index);

    // Converts a string to its unescaped representation.
    static RF_Type::String UnescapeDataString(
        const RF_Type::String& StringToUnescape);

    // Properties

    // Gets the path of the URI.
    const RF_Type::String& Path()const;

    // Gets the user data, Domain Name System (DNS) host name or IP address 
    // and the port number for a server.
    const RF_Type::String& Authority()const;

    // Gets the escaped URI fragment.
    const RF_Type::String& Fragment()const;
            
    // Gets the host component of this instance.
    const RF_Type::String& Host()const;
            
    // Gets the type of the host name specified in the URI.
    UriHostNameType::Type HostNameType()const;
            
    // Gets whether the Uri instance is absolute.
    RF_Type::Bool IsAbsolute()const;
            
    // Gets whether the port value of the URI is the default for this scheme.
    RF_Type::Bool IsDefaultPort()const;

    // Gets whether the userinfo of the URI is the default for this scheme.
    RF_Type::Bool IsDefaultUser()const;

    // Gets the original URI string that was passed to the Uri constructor.
    const RF_Type::String& OriginalString()const;
            
    // Gets the port number of this URI.
    RF_Type::Int32 Port()const;
            
    // Gets any query information included in the specified URI.
    const RF_Type::String& Query()const;
            
    // Gets the scheme name for this URI.
    const RF_Type::String& Scheme()const;
            
    // Gets the scheme specific part for this URI.
    const RF_Type::String& SchemeSpecificPart()const;

    // Indicates that the URI string was completely escaped before the
    // Uri instance was created.
    RF_Type::Bool UserEscaped()const;

    // Gets the user name, password, or other user-specific information
    // associated with the specified URI.
    const RF_Type::String& UserInfo()const;

    // An opaque URI is an absolute URI whose scheme-specific part does
    // not begin with a slash character('/').
    RF_Type::Bool IsOpaque()const;

    // Specifies the characters that separate the communication protocol
    // scheme from the address portion of the URI.
    static RF_Type::String SchemeDelimiter;
    /// Represent a URI path seperator.
    static RF_Type::String PathSeperator;

    bool operator ==(const Uri& Other);
    bool operator !=(const Uri& Other);

    Uri& operator =(const Uri& Other);
protected:
    // Uri
    RF_Type::String m_OriginalString;
    // basic components
    RF_Type::String m_Path;
    RF_Type::String m_Authority;
    RF_Type::String m_Fragment;
    RF_Type::String m_Query;
    RF_Type::String m_Scheme;
    RF_Type::String m_SchemeSpecificPart;
    // split up data
    RF_Type::String m_Host;
    RF_Type::String m_UserInfo;
    UriHostNameType::Type m_HostNameType;
    RF_Type::Int32 m_Port;
    RF_Type::Bool m_IsAbsolute;
    RF_Type::Bool m_IsDefaultPort;
    RF_Type::Bool m_IsDefaultUser;
    RF_Type::Bool m_UserEscaped;
    RF_Type::Bool m_IsOpaque;
    static RF_Type::String HexUpperChars[16];
    static RF_Type::Bool NeedToEscapeUriChar[256];
    static RF_Type::Bool NeedToEscapeDataChar[256];

    RF_Type::String Escape( RF_Type::String& str, const RF_Type::String& UriString );
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif // RF_IO_URI_HPP
