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

using AccessCallback = RF_Type::Bool(*)(const RF_Type::String& Path,
                                        const RF_IO::AccessMode::Type Mode);

using PathSeperatorCallback = RF_Type::String(*)();

using SeperatorCallback = RF_Type::String(*)();

using StatCallback = RF_Mem::AutoPointer<RF_IO::FileStatus>(*)(
    const RF_Type::String& Path);

using RealPathCallback = void(*)(const RF_Type::String& Path,
                                 RF_Type::String& ResolvedPath);

using ChangeModeCallback = RF_Type::Bool(*)(const RF_Type::String& Path,
                                            const RF_IO::AccessMode::Type NewMode);
// memory mapping

using MapFileIntoMemoryCallback = MemoryMappingHandle(*)(const FileHandle& Handle);

using UnmapMemoryFileCallback = RF_Type::Bool(*)(MemoryMappingHandle& Handle);

using GetMemoryFileCallback = void* (*)(const MemoryMappingHandle& Handle);

// file

using OpenFileCallback = FileHandle(*)(const RF_Type::String& Filepath,
                                       const FileAccessMode::Type AccessMode,
                                       const FileAccessPriority::Type AccessPriority);

using CloseFileCallback = RF_Type::Bool(*)(FileHandle& Handle);

using ReadFileCallback = RF_Type::Bool(*)(const FileHandle& Handle,
                                          RF_Type::UInt8* Buffer, 
                                          const RF_Type::UInt64 ReadBytes,
                                          RF_Type::UInt64& BytesRead);

using WriteFileCallback = RF_Type::Bool(*)(const FileHandle& Handle,
                                           const RF_Type::UInt8* Buffer, 
                                           const RF_Type::UInt64 WriteBytes,
                                           RF_Type::UInt64& BytesWritten);

using FlushFileCallback = RF_Type::Bool(*)(const FileHandle& Handle);

using SeekFileCallback = RF_Type::UInt64(*)(const FileHandle& Handle,
                                            const RF_Type::UInt64 Offset,
                                            const RF_IO::SeekOrigin::Type Origin );

using TellFileCallback = RF_Type::UInt64(*)(const FileHandle& Handle);

using GenerateTempFilenameCallback = RF_Type::String(*)(const RF_Type::String& Path);

using CreatePreAllocatedFileCallback = RF_Type::Bool(*)(
    const RF_Type::String& Path, const RF_Type::Size FileSize);

using CreateFileCallback = RF_Type::Bool(*)(const RF_Type::String& Path);

using CopyFileCallback = RF_Type::Bool(*)(const RF_Type::String& From,
                                          const RF_Type::String& To);

using RenameFileCallback = RF_Type::Bool(*)(const RF_Type::String& From,
                                            const RF_Type::String& To);

using DeleteFileCallback = RF_Type::Bool(*)(const RF_Type::String& Path);

// directory

using WorkingDirectoryCallback = RF_Type::String(*)();

using HomeDirectoryCallback = RF_Type::String(*)();

using ApplicationDirectoryCallback = RF_Type::String(*)();

using UserApplicationDataDirectoryCallback = RF_Type::String(*)();

using ApplicationDataDirectoryCallback = RF_Type::String(*)();

using ChangeDirectoryCallback = RF_Type::Bool (*)(const RF_Type::String& Destination);

using CreateDirectoryCallback = RF_Type::Bool(*)(const RF_Type::String& Path);

using DirectoryContentCallback = RF_Mem::AutoPointerArray<RF_Type::String>(*)(
    const RF_Type::String& Path);

// file watcher

using CreateFileWatcherCallback = FileWatcherHandle(*)(const RF_Type::String& Path);

using DestroyFileWatcherCallback = void(*)(FileWatcherHandle& Handle);

using WaitForFileWatcherCallback = RF_Type::Bool(*)(const FileWatcherHandle& Handle, 
                                                    FileWatcherEvent& Event);

using StartFileWatcherCallback = void(*)(const FileWatcherHandle& Handle);

using StopFileWatcherCallback = void(*)(const FileWatcherHandle& Handle);

using GetFileWatcherEventCallback = RF_Type::Bool(*)(const FileWatcherHandle& Handle, 
                                                     FileWatcherEvent& Event);

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
extern RealPathCallback RealPath;
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