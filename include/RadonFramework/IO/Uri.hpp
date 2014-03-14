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

namespace RadonFramework
{
    namespace IO
    {
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
                Uri(const Core::Types::String& UriString,
                    const UriKind::Type UriKind=UriKind::RelativeOrAbsolute);

                // Make a copy from an existing instance.
                Uri(const Uri& Copy);
            
                // Cleanup.
                ~Uri();

                // Methods
            
                // Gets the specified components of the current instance using the
                // specified escaping for special characters.
                Core::Types::String GetComponents(const UriComponents::Type Components=UriComponents::All,
                                                  const UriFormat::Type Format=UriFormat::Unescaped)const;

                // Static methods

                // Determines whether the specified host name is a valid DNS name.
                static UriHostNameType::Type HostNameType(const Core::Types::String& Name);
            
                // Determines whether the specified scheme name is valid.
                static Core::Types::Bool CheckSchemeName(const Core::Types::String& SchemeName);
            
                // Compares the specified parts of two URIs using the specified 
                // comparison rules. If the result is 0 then they are equal, -1 means
                // they are different in length and greater 0 is the position of the
                // first difference.
                static Core::Types::Int32 Compare(const Uri& Uri1, const Uri& Uri2,
                                                  const UriComponents::Type PartToCompare,
                                                  const UriFormat::Type CompareFormat);

                // Converts a string to its escaped representation.
                static Core::Types::String EscapeDataString(
                    const Core::Types::String& StringToEscape);
            
                // Converts a URI string to its escaped representation.
                static Core::Types::String EscapeUriString(
                    const Core::Types::String& StringToEscape);
            
                // Gets the decimal value of a hexadecimal digit.
                static Core::Types::Int32 FromHex(const Core::Types::Char Digit);

                // Converts a specified character into its hexadecimal equivalent.
                static Core::Types::String HexEscape(const Core::Types::Char Character);
            
                // Converts a specified hexadecimal representation of a character 
                // to the character.
                static Core::Types::Char HexUnescape(const Core::Types::String& Pattern, 
                                                     Core::Types::UInt32& Index);

                // Determines whether a specified character is a valid hexadecimal digit.
                static Core::Types::Bool IsHexDigit(const Core::Types::Char Character);

                // Determines whether a character in a string is hexadecimal encoded.
                static Core::Types::Bool IsHexEncoding(const Core::Types::String& Pattern,
                                                       const Core::Types::UInt32 Index);

                // Converts a string to its unescaped representation.
                static Core::Types::String UnescapeDataString(
                    const Core::Types::String& StringToUnescape);

                // Properties

                // Gets the path of the URI.
                Core::Types::String Path()const;

                // Gets the user data, Domain Name System (DNS) host name or IP address 
                // and the port number for a server.
                Core::Types::String Authority()const;

                // Gets the escaped URI fragment.
                Core::Types::String Fragment()const;
            
                // Gets the host component of this instance.
                Core::Types::String Host()const;
            
                // Gets the type of the host name specified in the URI.
                UriHostNameType::Type HostNameType()const;
            
                // Gets whether the Uri instance is absolute.
                Core::Types::Bool IsAbsolute()const;
            
                // Gets whether the port value of the URI is the default for this scheme.
                Core::Types::Bool IsDefaultPort()const;

                // Gets whether the userinfo of the URI is the default for this scheme.
                Core::Types::Bool IsDefaultUser()const;

                // Gets the original URI string that was passed to the Uri constructor.
                Core::Types::String OriginalString()const;
            
                // Gets the port number of this URI.
                Core::Types::Int32 Port()const;
            
                // Gets any query information included in the specified URI.
                Core::Types::String Query()const;
            
                // Gets the scheme name for this URI.
                Core::Types::String Scheme()const;
            
                // Gets the scheme specific part for this URI.
                Core::Types::String SchemeSpecificPart()const;

                // Indicates that the URI string was completely escaped before the
                // Uri instance was created.
                Core::Types::Bool UserEscaped()const;

                // Gets the user name, password, or other user-specific information
                // associated with the specified URI.
                Core::Types::String UserInfo()const;

                // An opaque URI is an absolute URI whose scheme-specific part does
                // not begin with a slash character('/').
                Core::Types::Bool IsOpaque()const;

                // Specifies the characters that separate the communication protocol
                // scheme from the address portion of the URI.
                static Core::Types::String SchemeDelimiter;
                /// Represent a URI path seperator.
                static Core::Types::String PathSeperator;

                bool operator ==(const Uri& Other);
                bool operator !=(const Uri& Other);
            protected:
                // Uri
                Core::Types::String m_OriginalString;
                // basic components
                Core::Types::String m_Path;
                Core::Types::String m_Authority;
                Core::Types::String m_Fragment;
                Core::Types::String m_Query;
                Core::Types::String m_Scheme;
                Core::Types::String m_SchemeSpecificPart;
                // split up data
                Core::Types::String m_Host;
                Core::Types::String m_UserInfo;
                UriHostNameType::Type m_HostNameType;
                Core::Types::Int32 m_Port;
                Core::Types::Bool m_IsAbsolute;
                Core::Types::Bool m_IsDefaultPort;
                Core::Types::Bool m_IsDefaultUser;
                Core::Types::Bool m_UserEscaped;
                Core::Types::Bool m_IsOpaque;
                static Core::Types::Char HexUpperChars[16];
                static Core::Types::Bool NeedToEscapeUriChar[256];
                static Core::Types::Bool NeedToEscapeDataChar[256];
        };
    }
}

#endif // RF_IO_URI_HPP
