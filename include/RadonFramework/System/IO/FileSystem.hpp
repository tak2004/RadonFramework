#ifndef RF_SYSTEM_IO_FILESYSTEM_HPP
#define RF_SYSTEM_IO_FILESYSTEM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/IO/AccessMode.hpp>
#include <RadonFramework/IO/FileStatus.hpp>
#include <RadonFramework/IO/SeekOrigin.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework { namespace System { namespace IO { namespace FileSystem {

typedef RF_Mem::PointerID FileHandle;
typedef RF_Mem::PointerID MemoryMappingHandle;
typedef RF_Mem::PointerID FileWatcherHandle;

namespace FileAccessMode
{
    enum Type
    {
        Read,
        Write,
        ReadWrite,
        MAX
    };
}

namespace FileAccessPriority
{
    enum Type
    {
        /// Optimize for sequential reading(prefetch upcomming blocks).
        ReadThroughput,
        /// Optimize for random position reading(no prefetching).
        RandomAccess,
        /// Optimize for direct reading and writing access(disable system
        /// caching mechanics, use own or no caching instead).
        DirectReadWrite,
        /// The system should care of optimized reading and writing(using caching).
        DelayReadWrite,
        MAX
    };
}

namespace WatcherChangeTypes
{
    enum Type
    {
        Invalid=0,
        Created=1,//file or directory was created
        Deleted=2,//file or directory was removed
        Changed=4,//file or directory content changed
        All=7
    };
}

class FileWatcherEvent
{
    public:
        FileWatcherEvent():ChangeType(WatcherChangeTypes::Invalid){}
        FileWatcherEvent(const FileWatcherEvent& Args):ChangeType(Args.ChangeType),Name(Args.Name){}
        FileWatcherEvent& operator=(const FileWatcherEvent& Args){ChangeType=Args.ChangeType;Name=Args.Name;return *this;}
        WatcherChangeTypes::Type ChangeType;
        RF_Type::String Name;//name of file or path
};

/// This function will be called by RadonFramework_Init function.
void Dispatch();

/** This function will be called by RadonFraemwork_Init function to
    * check if the dispatching was successfully.
    **/
RF_Type::Bool IsSuccessfullyDispatched();

/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(RadonFramework::Collections::List<RF_Type::String>& Result);

// utilities
typedef RF_Type::Bool (*AccessCallback)(const RF_Type::String& Path,
    const RF_IO::AccessMode::Type Mode);
typedef RF_Type::String (*PathSeperatorCallback)();
typedef RF_Type::String (*SeperatorCallback)();
typedef RF_Mem::AutoPointer<RF_IO::FileStatus> (*StatCallback)(
    const RF_Type::String& Path);
typedef RF_Type::Bool (*ChangeModeCallback)(const RF_Type::String& Path,
    const RF_IO::AccessMode::Type NewMode);
// memory mapping
typedef MemoryMappingHandle (*MapFileIntoMemoryCallback)(const FileHandle& Handle);
typedef RF_Type::Bool (*UnmapMemoryFileCallback)(MemoryMappingHandle& Handle);
typedef void* (*GetMemoryFileCallback)(const MemoryMappingHandle& Handle);
// file
typedef FileHandle (*OpenFileCallback)(const RF_Type::String& Filepath, 
                                        const FileAccessMode::Type AccessMode,
                                        const FileAccessPriority::Type AccessPriority);
typedef RF_Type::Bool (*CloseFileCallback)(FileHandle& Handle);
typedef RF_Type::Bool (*ReadFileCallback)(const FileHandle& Handle,
                                        RF_Type::UInt8* Buffer,
                                        const RF_Type::UInt64 ReadBytes,
                                        RF_Type::UInt64& BytesRead);
typedef RF_Type::Bool (*WriteFileCallback)(const FileHandle& Handle,
                                        const RF_Type::UInt8* Buffer,
                                        const RF_Type::UInt64 WriteBytes,
                                        RF_Type::UInt64& BytesWritten);
typedef RF_Type::Bool (*FlushFileCallback)(const FileHandle& Handle);
typedef RF_Type::UInt64 (*SeekFileCallback)(const FileHandle& Handle,
                                            const RF_Type::UInt64 Offset,
                                            const RF_IO::SeekOrigin::Type Origin );
typedef RF_Type::UInt64 (*TellFileCallback)(const FileHandle& Handle);
typedef RF_Type::String (*GenerateTempFilenameCallback)(const RF_Type::String& Path);
typedef RF_Type::Bool (*CreatePreAllocatedFileCallback)(
    const RF_Type::String& Path, const RF_Type::Size FileSize);
typedef RF_Type::Bool (*CreateFileCallback)(const RF_Type::String& Path);
typedef RF_Type::Bool (*CopyFileCallback)(const RF_Type::String& From,
    const RF_Type::String& To);
typedef RF_Type::Bool (*RenameFileCallback)(const RF_Type::String& From,
    const RF_Type::String& To);
typedef RF_Type::Bool (*DeleteFileCallback)(const RF_Type::String& Path);
// directory
typedef RF_Type::String (*WorkingDirectoryCallback)();
typedef RF_Type::String (*HomeDirectoryCallback)();
typedef RF_Type::String (*ApplicationDirectoryCallback)();
typedef RF_Type::String(*UserApplicationDataDirectoryCallback)();
typedef RF_Type::String(*ApplicationDataDirectoryCallback)();
typedef RF_Type::Bool (*ChangeDirectoryCallback)(const RF_Type::String& Destination);
typedef RF_Type::Bool (*CreateDirectoryCallback)(const RF_Type::String& Path);
typedef RF_Mem::AutoPointerArray<RF_Type::String> (*DirectoryContentCallback)(const RF_Type::String& Path);
// file watcher
typedef FileWatcherHandle (*CreateFileWatcherCallback)(const RF_Type::String& Path);
typedef void (*DestroyFileWatcherCallback)(FileWatcherHandle& Handle);
typedef RF_Type::Bool (*WaitForFileWatcherCallback)(const FileWatcherHandle& Handle, FileWatcherEvent& Event);
typedef void (*StartFileWatcherCallback)(const FileWatcherHandle& Handle);
typedef void (*StopFileWatcherCallback)(const FileWatcherHandle& Handle);
typedef RF_Type::Bool (*GetFileWatcherEventCallback)(const FileWatcherHandle& Handle, FileWatcherEvent& Event);

extern OpenFileCallback OpenFile;
extern CloseFileCallback CloseFile;
extern MapFileIntoMemoryCallback MapFileIntoMemory;
extern UnmapMemoryFileCallback UnmapMemoryFile;
extern GetMemoryFileCallback GetMemoryFile;
extern ReadFileCallback ReadFile;
extern WriteFileCallback WriteFile;
extern FlushFileCallback FlushFile;
extern SeekFileCallback SeekFile;
extern TellFileCallback TellFile;
extern GenerateTempFilenameCallback GenerateTempFilename;
extern AccessCallback Access;
extern PathSeperatorCallback PathSeperator;
extern SeperatorCallback Seperator;
extern StatCallback Stat;
extern ChangeModeCallback ChangeMode;
extern CreatePreAllocatedFileCallback CreatePreAllocatedFile;
extern CreateFileCallback CreateFile;
extern CopyFileCallback CopyFile;
extern RenameFileCallback RenameFile;
extern DeleteFileCallback DeleteFile;
extern WorkingDirectoryCallback WorkingDirectory;
extern HomeDirectoryCallback HomeDirectory;
extern ApplicationDirectoryCallback ApplicationDirectory;
extern UserApplicationDataDirectoryCallback UserApplicationDataDirectory;
extern ApplicationDataDirectoryCallback ApplicationDataDirectory;
extern ChangeDirectoryCallback ChangeDirectory;
extern CreateDirectoryCallback CreateDirectory;
extern DirectoryContentCallback DirectoryContent;
extern CreateFileWatcherCallback CreateFileWatcher;
extern DestroyFileWatcherCallback DestroyFileWatcher;
extern WaitForFileWatcherCallback WaitForFileWatcher;
extern StartFileWatcherCallback StartFileWatcher;
extern StopFileWatcherCallback StopFileWatcher;
extern GetFileWatcherEventCallback GetFileWatcherEvent;

} } } }

namespace RFFILE = RadonFramework::System::IO::FileSystem;

#endif // RF_SYSTEM_IO_FILESYSTEM_HPP