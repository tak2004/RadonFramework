#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Environment.hpp"
#include "RadonFramework/System/CompilerConfig.hpp"
#include "RadonFramework/Core/Common/DataManagment.hpp"
#include "RadonFramework/Util/UUID.hpp"
#include <rpc.h>
#include <VersionHelpers.h>
#pragma comment(lib, "Rpcrt4.lib")

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
    HMODULE kernelModule = GetModuleHandle("kernel32");
    if(0 != kernelModule)
    {
        fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(kernelModule, "IsWow64Process");
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

void FastRandomUUID_Windows(RF_Util::UUID& Target)
{
    UUID uuid;
    UuidCreate(&uuid);
    RF_SysMem::Copy(Target.Bytes.m_Vector, &uuid, 16);
}

void SecureRandomUUID_Windows(RF_Util::UUID& Target)
{
    UUID uuid;
    UuidCreateSequential(&uuid);
    RF_SysMem::Copy(Target.Bytes.m_Vector, &uuid,16);
}

void UUIDFromString_Windows(const RF_Type::String& Text, RF_Util::UUID& Target)
{
    UUID uuid;
    UuidFromString(reinterpret_cast<unsigned char*>(const_cast<char*>(Text.c_str())), &uuid);
    RF_SysMem::Copy(Target.Bytes.m_Vector, &uuid, 16);
}

RF_Type::String ActiveLanguage_Windows()
{
    WCHAR languageUtf16[LOCALE_NAME_MAX_LENGTH];
    char languageUtf8[LOCALE_NAME_MAX_LENGTH];
    RF_Type::String result;
    int writtenBytes = GetUserDefaultLocaleName(languageUtf16, LOCALE_USER_DEFAULT);
    if(writtenBytes > 0)
        writtenBytes = wcstombs(languageUtf8, languageUtf16, LOCALE_NAME_MAX_LENGTH);
    if(writtenBytes > 0)
        result = RF_Type::String(languageUtf8, writtenBytes + 1);
    return result;
}

RF_Type::String ActiveLanguageName_Windows()
{
    WCHAR languageUtf16[LOCALE_NAME_MAX_LENGTH];
    char languageUtf8[LOCALE_NAME_MAX_LENGTH];
    RF_Type::String result;
    int writtenBytes = GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SISO639LANGNAME, languageUtf16, LOCALE_NAME_MAX_LENGTH);
    if(writtenBytes > 0)
        writtenBytes = wcstombs(languageUtf8, languageUtf16, LOCALE_NAME_MAX_LENGTH);
    if(writtenBytes > 0)
        result = RF_Type::String(languageUtf8, writtenBytes + 1);
    return result;
}

RF_Type::String ActiveNativeLanguageName_Windows()
{
    WCHAR languageUtf16[LOCALE_NAME_MAX_LENGTH];
    char languageUtf8[LOCALE_NAME_MAX_LENGTH];
    RF_Type::String result;
    int writtenBytes = GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SNATIVELANGUAGENAME, languageUtf16, LOCALE_NAME_MAX_LENGTH);
    if(writtenBytes > 0)
        writtenBytes = wcstombs(languageUtf8, languageUtf16, LOCALE_NAME_MAX_LENGTH);
    if(writtenBytes > 0)
        result = RF_Type::String(languageUtf8, writtenBytes + 1);
    return result;
}

RF_Type::String ActiveLanguageLocation_Windows()
{
    WCHAR languageUtf16[LOCALE_NAME_MAX_LENGTH];
    char languageUtf8[LOCALE_NAME_MAX_LENGTH];
    RF_Type::String result;
    int writtenBytes = GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SISO3166CTRYNAME, languageUtf16, LOCALE_NAME_MAX_LENGTH);
    if(writtenBytes > 0)
        writtenBytes = wcstombs(languageUtf8, languageUtf16, LOCALE_NAME_MAX_LENGTH);
    if(writtenBytes > 0)
        result = RF_Type::String(languageUtf8, writtenBytes + 1);
    return result;
}

RF_Type::String ActiveNativeLanguageLocation_Windows()
{
    WCHAR languageUtf16[LOCALE_NAME_MAX_LENGTH];
    char languageUtf8[LOCALE_NAME_MAX_LENGTH];
    RF_Type::String result;
    int writtenBytes = GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SNATIVECOUNTRYNAME, languageUtf16, LOCALE_NAME_MAX_LENGTH);
    if(writtenBytes > 0)
        writtenBytes = wcstombs(languageUtf8, languageUtf16, LOCALE_NAME_MAX_LENGTH);
    if(writtenBytes > 0)
        result = RF_Type::String(languageUtf8, writtenBytes + 1);
    return result;
}

void RadonFramework::System::Environment::Dispatch()
{
    MemoryArchitectureOfOS=::MemoryArchitectureOfOS;
    Is32BitEmulation=::Is32BitEmulation;
    OSVersion=::OSVersion;
    GetVariable=::GetVariable;
    Platform=::Platform;
    OSFamily=::OSFamily;

    if(IsWindowsVistaOrGreater())
    {
        FastRandomUUID = ::FastRandomUUID_Windows;
        SecureRandomUUID = ::SecureRandomUUID_Windows;
        UUIDFromString = ::UUIDFromString_Windows;
        ActiveLanguage = ::ActiveLanguage_Windows;
        ActiveLanguageName = ::ActiveLanguageName_Windows;
        ActiveNativeLanguageName = ::ActiveNativeLanguageName_Windows;
        ActiveLanguageLocation = ::ActiveLanguageLocation_Windows;
        ActiveNativeLanguageLocation = ::ActiveNativeLanguageLocation_Windows;
    }
}