#ifndef RF_SYSTEM_PLATFORMID_HPP
#define RF_SYSTEM_PLATFORMID_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::System::PlatformID {

enum Type
{
    Unknown,
    /** 
        * The operating system is Win32s. Win32s is a layer that runs on 
        * 16-bit versions of Windows to provide access to 32-bit applications.
        **/
    Win32s,
    Win32Windows, // The operating system is Windows 95 or Windows 98.
    Win32NT, // The operating system is Windows NT or later.
    WinCE, // The operating system is Windows CE.
    Unix, // The operating system is Unix.
    XBox, // The development platform is Xbox 360.
    MacOSX // The operating system is Macintosh.
};

}

#endif // RF_SYSTEM_PLATFORMID_HPP