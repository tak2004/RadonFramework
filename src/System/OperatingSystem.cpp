#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/OperatingSystem.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System;
using namespace RadonFramework::Core::Common;

OperatingSystem::OperatingSystem()
:m_Platform(PlatformID::Unknown)
{
}

OperatingSystem::OperatingSystem(const PlatformID::Type Platform, 
                                 const Version& VersionNumber)
:m_Platform(Platform)
,m_VersionNumber(VersionNumber)
{
}

PlatformID::Type OperatingSystem::Platform()const
{
    return m_Platform;
}

RFTYPE::String OperatingSystem::PlatformString()const
{
    RFTYPE::String result;
    switch (m_Platform) 
    {
        case PlatformID::Win32NT:
            result = "Microsoft Windows NT";
            break;
        case PlatformID::Win32s:
            result = "Microsoft Win32S";
            break;
        case PlatformID::Win32Windows:
            result = "Microsoft Windows";
            break;
        case PlatformID::WinCE:
            result = "Microsoft Windows CE";
            break;
        case PlatformID::Unix:
            result = "Unix";
            break;
        case PlatformID::XBox:
            result = "XBox";
            break;
        case PlatformID::MacOSX:
            result = "OSX";
            break;
        default:
            result = "Unknown";
            break;
    }
    return result;
}

RFTYPE::String OperatingSystem::VersionString()const
{
    RFTYPE::String result=PlatformString()+" "+m_VersionNumber.ToString();
    return result;
}

const Version& OperatingSystem::VersionNumber()const
{
    return m_VersionNumber;
}
