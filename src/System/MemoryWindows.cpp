#include <cstdlib>
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/precompiled.hpp"
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>

using namespace RadonFramework::Core::Types;

UInt32 GetPageSizeWindows()
{
  SYSTEM_INFO systemInfo;
  GetSystemInfo(&systemInfo);
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
// Only a 64Bit binary on Windows 64Bit already have set this flag but no other
// combination.
#if !defined(RF_WINDOWS) && !defined(RF_64BIT) && _WIN32_WINNT >= 0x0600
  (void)HeapSetInformation(GetProcessHeap(), HeapEnableTerminationOnCorruption,
                           NULL, 0);
#endif
}

Size PageAllocationSizeWindows(const void* FirstPage)
{
  RF_Type::Size result = 0;
  MEMORY_BASIC_INFORMATION info;
  if(VirtualQuery(FirstPage, &info, sizeof(MEMORY_BASIC_INFORMATION)) ==
     sizeof(MEMORY_BASIC_INFORMATION))
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

void* MapMemoryWindows(void* Memory, RF_Type::Size Bytes)
{
  return CreateFileMappingA(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE,
                            (unsigned long long)Bytes >> 32,
                            Bytes & 0xffffffffu, nullptr);
}

void UnmapMemoryWindows(void* MemoryMapHandle)
{
  CloseHandle(MemoryMapHandle);
}

void* MapViewWindows(void* MemoryMapHandle,
                     const RF_Type::Size Bytes,
                     void* View)
{
  return MapViewOfFileEx(MemoryMapHandle, FILE_MAP_ALL_ACCESS, 0, 0, Bytes,
                         View);
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
  MapMemory = MapMemoryWindows;
  UnmapMemory = UnmapMemoryWindows;
  MapView = MapViewWindows;
}