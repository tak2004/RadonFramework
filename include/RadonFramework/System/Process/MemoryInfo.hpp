#ifndef RF_SYSTEM_PROCESS_MEMORYINFO_HPP
#define RF_SYSTEM_PROCESS_MEMORYINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace System { namespace Process {

struct MemoryInfo
{
    /// This process has read permission for the memory information.
    RFTYPE::Bool MemoryAccessRights;
    /// Total memory usage.
    RFTYPE::UInt64 MemoryUsage;
    /// Maximum used memory till yet.
    RFTYPE::UInt64 PeakMemoryUsage;
    /// Available virtual memory for this process.
    RFTYPE::UInt64 UsableVirtualMemory;
    /// Number of bytes not in page pool.
    RFTYPE::UInt64 NonPagedPool;
    /// Number of bytes in page pool(swap).
    RFTYPE::UInt64 PagedPool;
    /// Number of memory access on page pool.
    RFTYPE::UInt64 PageFaultCount;
};

} } }

namespace RFPROC = RadonFramework::System::Process;

#endif // RF_SYSTEM_PROCESS_MEMORYINFO_HPP