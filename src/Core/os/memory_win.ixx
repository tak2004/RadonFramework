module;
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>
export module rf.core.os:memory;
import rf.core.types;

export namespace rf {
/// Return the granularity(in bytes) of memory allocation and validation.
size getAllocationGranularity();
/// Return the granularity(in bytes) of minimal allocated map of the OS.
size getMapGranularity();
struct SystemMemoryInformation {
	size totalRAM;
  size availableRAM;
  size totalVirtualMemory;
  size availableVirtualMemory;
};
void getSystemMemoryInformation(SystemMemoryInformation &MemoryInformation);

size getAllocationGranularity() {
  SYSTEM_INFO systemInfo;
  GetSystemInfo(&systemInfo);
  return systemInfo.dwPageSize;
}

size getMapGranularity() {
  SYSTEM_INFO systemInfo;
  GetSystemInfo(&systemInfo);
  return systemInfo.dwAllocationGranularity;
}

void getSystemMemoryInformation(SystemMemoryInformation &MemoryInformation) {
  MEMORYSTATUSEX mem;
  mem.dwLength = sizeof(mem);
  GlobalMemoryStatusEx(&mem);
  MemoryInformation.totalRAM = mem.ullTotalPhys;
  MemoryInformation.availableRAM = mem.ullAvailPhys;
  MemoryInformation.totalVirtualMemory = mem.ullTotalVirtual;
  MemoryInformation.availableVirtualMemory = mem.ullAvailVirtual;
}
} // namespace rf