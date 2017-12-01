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

UInt32 GetBlockSizeWindows()
{
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);
    return systemInfo.dwAllocationGranularity;
}

void EnableTerminationOnHeapCorruptionWindows()
{
    // Only a 64Bit binary on Windows 64Bit already have set this flag but no other combination.
    #if !defined(RF_WINDOWS) && !defined(RF_64BIT) && _WIN32_WINNT>=0x0600
        (void)HeapSetInformation(GetProcessHeap(), HeapEnableTerminationOnCorruption, NULL, 0);
    #endif
}

Size PageAllocationSizeWindows(const void* FirstPage)
{
    RF_Type::Size result = 0;
    MEMORY_BASIC_INFORMATION info;
    if(VirtualQuery(FirstPage, &info, sizeof(MEMORY_BASIC_INFORMATION)) == sizeof(MEMORY_BASIC_INFORMATION))
    {
        result = info.RegionSize;
    }
    return result;
}

void* PageAllocateWindows(Size& Bytes)
{
    return VirtualAlloc(0, Bytes, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

void PageFreeWindows(void* FirstPage)
{
    VirtualFree(FirstPage, 0, MEM_RELEASE);
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
    GetBlockSize = GetBlockSizeWindows;
    EnableTerminationOnHeapCorruption = EnableTerminationOnHeapCorruptionWindows;
    PageAllocationSize = PageAllocationSizeWindows;
    PageAllocate = PageAllocateWindows;
    PageFree = PageFreeWindows;
    Allocate = AllocateWindows;
    Free = FreeWindows;
}