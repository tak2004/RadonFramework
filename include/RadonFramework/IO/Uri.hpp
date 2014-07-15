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
    Uri(const RFTYPE::String& UriString,
        const UriKind::Type UriKind=UriKind::RelativeOrAbsolute);

    // Make a copy from an existing instance.
    Uri(const Uri& Copy);
            
    // Cleanup.
    ~Uri();

    // Methods
            
    // Gets the specified components of the current instance using the
    // specified escaping for special characters.
    RFTYPE::String GetComponents(const UriComponents::Type Components=UriComponents::All,
                                        const UriFormat::Type Format=UriFormat::Unescaped)const;

    // Static methods

    // Determines whether the specified host name is a valid DNS name.
    static UriHostNameType::Type HostNameType(const RFTYPE::String& Name);
            
    // Determines whether the specified scheme name is valid.
    static RFTYPE::Bool CheckSchemeName(const RFTYPE::String& SchemeName);
            
    // Compares the specified parts of two URIs using the specified 
    // comparison rules. If the result is 0 then they are equal, -1 means
    // they are different in length and greater 0 is the position of the
    // first difference.
    static RFTYPE::Int32 Compare(const Uri& Uri1, const Uri& Uri2,
                                        const UriComponents::Type PartToCompare,
                                        const UriFormat::Type CompareFormat);

    // Converts a string to its escaped representation.
    static RFTYPE::String EscapeDataString(
        const RFTYPE::String& StringToEscape);
            
    // Converts a URI string to its escaped representation.
    static RFTYPE::String EscapeUriString(
        const RFTYPE::String& StringToEscape);
            
    // Gets the decimal value of a hexadecimal digit.
    static RFTYPE::Int32 FromHex(const RFTYPE::Char Digit);

    // Converts a specified character into its hexadecimal equivalent.
    static RFTYPE::String HexEscape(const RFTYPE::Char Character);
            
    // Converts a specified hexadecimal representation of a character 
    // to the character.
    static RFTYPE::Char HexUnescape(const RFTYPE::String& Pattern, 
                                            RFTYPE::UInt32& Index);

    // Determines whether a specified character is a valid hexadecimal digit.
    static RFTYPE::Bool IsHexDigit(const RFTYPE::Char Character);

    // Determines whether a character in a string is hexadecimal encoded.
    static RFTYPE::Bool IsHexEncoding(const RFTYPE::String& Pattern,
                                            const RFTYPE::UInt32 Index);

    // Converts a string to its unescaped representation.
    static RFTYPE::String UnescapeDataString(
        const RFTYPE::String& StringToUnescape);

    // Properties

    // Gets the path of the URI.
    RFTYPE::String Path()const;

    // Gets the user data, Domain Name System (DNS) host name or IP address 
    // and the port number for a server.
    RFTYPE::String Authority()const;

    // Gets the escaped URI fragment.
    RFTYPE::String Fragment()const;
            
    // Gets the host component of this instance.
    RFTYPE::String Host()const;
            
    // Gets the type of the host name specified in the URI.
    UriHostNameType::Type HostNameType()const;
            
    // Gets whether the Uri instance is absolute.
    RFTYPE::Bool IsAbsolute()const;
            
    // Gets whether the port value of the URI is the default for this scheme.
    RFTYPE::Bool IsDefaultPort()const;

    // Gets whether the userinfo of the URI is the default for this scheme.
    RFTYPE::Bool IsDefaultUser()const;

    // Gets the original URI string that was passed to the Uri constructor.
    RFTYPE::String OriginalString()const;
            
    // Gets the port number of this URI.
    RFTYPE::Int32 Port()const;
            
    // Gets any query information included in the specified URI.
    RFTYPE::String Query()const;
            
    // Gets the scheme name for this URI.
    RFTYPE::String Scheme()const;
            
    // Gets the scheme specific part for this URI.
    RFTYPE::String SchemeSpecificPart()const;

    // Indicates that the URI string was completely escaped before the
    // Uri instance was created.
    RFTYPE::Bool UserEscaped()const;

    // Gets the user name, password, or other user-specific information
    // associated with the specified URI.
    RFTYPE::String UserInfo()const;

    // An opaque URI is an absolute URI whose scheme-specific part does
    // not begin with a slash character('/').
    RFTYPE::Bool IsOpaque()const;

    // Specifies the characters that separate the communication protocol
    // scheme from the address portion of the URI.
    static RFTYPE::String SchemeDelimiter;
    /// Represent a URI path seperator.
    static RFTYPE::String PathSeperator;

    bool operator ==(const Uri& Other);
    bool operator !=(const Uri& Other);
protected:
    // Uri
    RFTYPE::String m_OriginalString;
    // basic components
    RFTYPE::String m_Path;
    RFTYPE::String m_Authority;
    RFTYPE::String m_Fragment;
    RFTYPE::String m_Query;
    RFTYPE::String m_Scheme;
    RFTYPE::String m_SchemeSpecificPart;
    // split up data
    RFTYPE::String m_Host;
    RFTYPE::String m_UserInfo;
    UriHostNameType::Type m_HostNameType;
    RFTYPE::Int32 m_Port;
    RFTYPE::Bool m_IsAbsolute;
    RFTYPE::Bool m_IsDefaultPort;
    RFTYPE::Bool m_IsDefaultUser;
    RFTYPE::Bool m_UserEscaped;
    RFTYPE::Bool m_IsOpaque;
    static RFTYPE::Char HexUpperChars[16];
    static RFTYPE::Bool NeedToEscapeUriChar[256];
    static RFTYPE::Bool NeedToEscapeDataChar[256];
};

} }

#endif // RF_IO_URI_HPP
