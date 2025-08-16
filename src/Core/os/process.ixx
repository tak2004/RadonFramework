export module rf.core.os:process;
import rf.core.types;
import rf.core.memory;
import :threading;

export namespace rf {

using PID = u32;

struct GeneralInfo {
  PID id;
  strview binaryName;
  strview name;
};

struct IOInfo {
  u64 readOperationCount;
  u64 writeOperationCount;
  u64 otherOperationCount;
  u64 readTransferedBytes;
  u64 writeTransferedBytes;
  u64 otherTransferedBytes;
};

struct MemoryInfo {
  /// Total memory usage.
  u64 memoryUsage;
  /// Maximum used memory till yet.
  u64 peakMemoryUsage;
  /// Available virtual memory for this process.
  u64 usableVirtualMemory;
  /// Number of bytes not in page pool.
  u64 nonPagedPool;
  /// Number of bytes in page pool(swap).
  u64 pagedPool;
  /// Number of memory access on page pool.
  u64 pageFaultCount;
  /// This process has read permission for the memory information.
  bool memoryAccessRights;
};

struct TimingInfo {
  timeval creationTime;
  timeval exitTime;
  timeval kernelTime;
  timeval userTime;
};

struct ThreadInfo {
  u64 id;
  ThreadPriority priority;
  TimingInfo timing;
};

/// Return an array of all process IDs.
arr<PID> getProcessIds(StackAdapter &Scratchpad);
/// Return the current process id.
PID getCurrentProcessId();
/// Return the general information of the specified process and return true else false.
bool getGeneralInfo(PID Pid, GeneralInfo &Info, StackAdapter &Scratchpad);
/// Return the IO information of the specified process and return true else false.
bool getIOInfo(PID Pid, IOInfo &IoInfo);
/// Return the memory information of the specified process and return true else false.
bool getMemoryInfo(PID Pid, MemoryInfo &MemInfo);
/// Return the timing information of the specified process and return true else false.
bool getTimingInfo(PID Pid, TimingInfo &TimeInfo);
/// Return the thread information of the specified process.
arr<ThreadInfo> getThreadInfo(PID Pid, StackAdapter &Scratchpad);
/// Execute a program and return the PID of it.
PID executeProgram(strview Executeable, strview Parameters,
                   StackAdapter &Scratchpad);

} // namespace rf