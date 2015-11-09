#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Memory.hpp"

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>

using namespace RadonFramework::Core::Types;

UInt32 GetPageSizeWindows()
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(& systemInfo);
    return systemInfo.dwPageSize;
}

void EnableTerminationOnHeapCorruptionWindows()
{
    // Only a 64Bit binary on Windows 64Bit all ready have set this flag but no other combination.
    #if !defined(RF_WINDOWS) && !defined(RF_64BIT) && _WIN32_WINNT>=0x0600
        (void)HeapSetInformation(GetProcessHeap(), HeapEnableTerminationOnCorruption, NULL, 0);
    #endif
}

void* AllocateWindows(const Size Bytes, const Size Alignment)
{
    return _aligned_malloc(Bytes, Alignment);
}

void FreeWindows(void* FirstPage)
{
    _aligned_free(FirstPage);
}

void RF_SysMem::Dispatch()
{
    GetPageSize = GetPageSizeWindows;
    EnableTerminationOnHeapCorruption = EnableTerminationOnHeapCorruptionWindows;
    Allocate = AllocateWindows;
    Free = FreeWindows;
}