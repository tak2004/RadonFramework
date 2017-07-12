#ifndef RF_SYSTEM_PROCESS_MEMORYINFO_HPP
#define RF_SYSTEM_PROCESS_MEMORYINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::System::Process {

struct MemoryInfo
{
    /// This process has read permission for the memory information.
    RF_Type::Bool MemoryAccessRights;
    /// Total memory usage.
    RF_Type::UInt64 MemoryUsage;
    /// Maximum used memory till yet.
    RF_Type::UInt64 PeakMemoryUsage;
    /// Available virtual memory for this process.
    RF_Type::UInt64 UsableVirtualMemory;
    /// Number of bytes not in page pool.
    RF_Type::UInt64 NonPagedPool;
    /// Number of bytes in page pool(swap).
    RF_Type::UInt64 PagedPool;
    /// Number of memory access on page pool.
    RF_Type::UInt64 PageFaultCount;
};

}

namespace RFPROC = RadonFramework::System::Process;

#endif // RF_SYSTEM_PROCESS_MEMORYINFO_HPP