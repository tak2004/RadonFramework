export module rf.core.system:filesystem;
import rf.core.types;
import rf.core.memory;

export namespace rf {
using FileHandle = ptr;
using FileWatcherHandle = ptr;

enum class FileAccessMode : u8 { Read, Write, ReadWrite };

enum class FileAccessPriority : u8 {
  /// No priority, use system default.
  None,
  /// Optimize for sequential reading(prefetch upcomming blocks).
  ReadThroughput,
  /// Optimize for random position reading(no prefetching).
  RandomAccess,
  /// Optimize for direct reading and writing access(disable system
  /// caching mechanics, use own or no caching instead).
  DirectReadWrite,
  /// The system should care of optimized reading and writing(using caching).
  DelayReadWrite
};

enum class SeekOrigin:u8
{
  Begin=0,
  Current,
  End
};

enum class WatcherChangeTypes:u8
{
  Invalid = 0,
  Created = 1,  // file or directory was created
  Deleted = 2,  // file or directory was removed
  Changed = 4,  // file or directory content changed
  All = 7
};

struct FileWatcherEvent {
  strview filename;
  WatcherChangeTypes type;
};

class FileWatcher;

using FileWatcherCallback = void (*)(const FileWatcher& Self, const FileWatcherEvent& Event, ptr UserHandle);

class FileWatcher{
public:
    FileWatcher(const AllocatorAdapter& LongLiving, const StackAdapter& Stack, FileWatcherCallback Callback, ptr UserHandle);
    ~FileWatcher();
    bool watch(const strview& Path);
    // Blocking interface
    void waitForNext();
    // ASync interface
    void start();    
    void getNext();
    void stop();
protected:
  AllocatorAdapter allocator;
  StackAdapter stack;
  FileWatcherCallback callback;
  ptr userHandle;
  ptr handle; 
};

struct MemoryMapping {
  ptr fileHandle;
  ptr viewHandle;
};

enum AccessMode: u8
{
  None = 0,
  Exists,
  Write,
  WriteExists,
  Read,
  ReadExists,
  WriteRead,
  WriteReadExists,
  Execute,
  ExecuteExists,
  ExecuteWrite,
  ExecuteWriteExists,
  ExecuteRead,
  ExecuteReadExists,
  ExecuteWriteRead,
  ExecuteWriteReadExists
};

struct FileStatus
{
  u64 size;
  u64 lastModificationTimestamp;
  u64 lastAccessTimestamp;
  u64 createionTimestamp;
  bool isDirectory;
  bool isHidden;
  u8 reserved[6];
};

FileWatcher::FileWatcher(const AllocatorAdapter& LongLiving, const StackAdapter& Stack,
  FileWatcherCallback Callback, ptr UserHandle)
:allocator(LongLiving)
,stack(Stack)
,callback(Callback)
,userHandle(UserHandle)
,handle(nullptr)
{
}

} // namespace rf