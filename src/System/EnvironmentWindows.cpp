#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/System/CompilerConfig.hpp"
#include "RadonFramework/Core/Common/DataManagment.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Common;
using namespace RadonFramework::System;

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>

#ifndef VER_PLATFORM_WIN32_CE
#define VER_PLATFORM_WIN32_CE 3
#endif

typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
LPFN_ISWOW64PROCESS fnIsWow64Process;

Version GetOSVersion()
{
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    if (GetVersionEx((OSVERSIONINFO*) &osvi))
    {
        return Version(osvi.dwMajorVersion,osvi.dwMinorVersion,osvi.dwBuildNumber);
    }
    return Version();
}

PlatformID::Type Platform()
{
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    Bool isOSVersionAvailable=GetVersionEx((OSVERSIONINFO*) &osvi)!=0;

    if (isOSVersionAvailable)
    {
        switch (osvi.dwPlatformId)
        {
            case VER_PLATFORM_WIN32_NT:
                return PlatformID::Win32NT;
            case VER_PLATFORM_WIN32_WINDOWS:
                return PlatformID::Win32Windows;
            case VER_PLATFORM_WIN32s:
                return PlatformID::Win32s;
            case VER_PLATFORM_WIN32_CE:
                return PlatformID::WinCE;
        }
    }
    return PlatformID::Unknown;
}

Bool Is32BitEmulation()
{
    BOOL bIsWow64 = FALSE;
    HMODULE module = GetModuleHandle("kernel32");
    if(0 != module)
    {
        fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(module, "IsWow64Process");
        if(NULL != fnIsWow64Process)
        {
            fnIsWow64Process(GetCurrentProcess(), &bIsWow64);
        }            
    }
    return bIsWow64!=0;
}

MemoryArchitecture::Type MemoryArchitectureOfOS()
{
    static const MemoryArchitecture::Type arch = false==Is32BitEmulation()
        && CompilerConfig::CompiledForArchitecture==MemoryArchitecture::_32Bit
        ? MemoryArchitecture::_32Bit : MemoryArchitecture::_64Bit;
    return arch;
}

const OperatingSystem& OSVersion()
{
    static OperatingSystem os=OperatingSystem(Platform(),GetOSVersion());
    return os;
}

void GetVariable(const RF_Type::String& Name, RF_Type::String& Result)
{
    char buf[MAX_PATH];
    GetEnvironmentVariableA(Name.c_str(), buf, MAX_PATH);
    Result=RF_Type::String(buf, MAX_PATH);
}

OperatingSystemFamily::Type OSFamily()
{
    return OperatingSystemFamily::Windows;
}

void RadonFramework::System::Environment::Dispatch()
{
    MemoryArchitectureOfOS=::MemoryArchitectureOfOS;
    Is32BitEmulation=::Is32BitEmulation;
    OSVersion=::OSVersion;
    GetVariable=::GetVariable;
    Platform=::Platform;
    OSFamily=::OSFamily;
}