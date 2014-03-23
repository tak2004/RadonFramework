#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Memory.hpp"

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>

using namespace RadonFramework::Core::Types;

UInt32 GetPageSize()
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(& systemInfo);
    return systemInfo.dwPageSize;
}

void EnableTerminationOnHeapCorruption()
{
    // Only a 64Bit binary on Windows 64Bit all ready have set this flag but no other combination.
    #if !defined(RF_WINDOWS) && !defined(RF_64BIT) && _WIN32_WINNT>=0x0600
        (void)HeapSetInformation(GetProcessHeap(), HeapEnableTerminationOnCorruption, NULL, 0);
    #endif
}

void* Allocate(UInt32 Bytes)
{
    return HeapAlloc(GetProcessHeap(), 0, Bytes);
}

void Free(void* FirstPage)
{
    HeapFree(GetProcessHeap(), 0, FirstPage);
}

void RFMEM::Dispatch()
{
    GetPageSize=::GetPageSize;
    EnableTerminationOnHeapCorruption=::EnableTerminationOnHeapCorruption;
    Allocate=::Allocate;
    Free=::Free;
}