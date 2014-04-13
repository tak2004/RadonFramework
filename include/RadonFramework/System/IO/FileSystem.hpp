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
    typedef RadonFramework::Memory::PointerID FileHandle;
    typedef RadonFramework::Memory::PointerID MemoryMappingHandle;
    typedef RadonFramework::Memory::PointerID FileWatcherHandle;

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
            RFTYPE::String Name;//name of file or path
    };

    /// This function will be called by RadonFramework_Init function.
    void Dispatch();

    /** This function will be called by RadonFraemwork_Init function to
        * check if the dispatching was successfully.
        **/
    RFTYPE::Bool IsSuccessfullyDispatched();

    /// This function is for debugging purpose and return all unassigned functions.
    void GetNotDispatchedFunctions(RadonFramework::Collections::List<RFTYPE::String>& Result);

    // utilities
    typedef RFTYPE::Bool (*AccessCallback)(const RFTYPE::String& Path,
        const RadonFramework::IO::AccessMode::Type Mode);
    typedef RFTYPE::Char (*PathSeperatorCallback)();
    typedef RFTYPE::Char (*SeperatorCallback)();
    typedef RadonFramework::Memory::AutoPointer<RadonFramework::IO::FileStatus> (*StatCallback)(
        const RFTYPE::String& Path);
    typedef RFTYPE::Bool (*ChangeModeCallback)(const RFTYPE::String& Path,
        const RadonFramework::IO::AccessMode::Type NewMode);
    // memory mapping
    typedef MemoryMappingHandle (*MapFileIntoMemoryCallback)(const FileHandle& Handle);
    typedef RFTYPE::Bool (*UnmapMemoryFileCallback)(MemoryMappingHandle& Handle);
    typedef void* (*GetMemoryFileCallback)(const MemoryMappingHandle& Handle);
    // file
    typedef FileHandle (*OpenFileCallback)(const RFTYPE::String& Filepath, 
                                            const FileAccessMode::Type AccessMode,
                                            const FileAccessPriority::Type AccessPriority);
    typedef RFTYPE::Bool (*CloseFileCallback)(FileHandle& Handle);
    typedef RFTYPE::Bool (*ReadFileCallback)(const FileHandle& Handle,
                                            RFTYPE::UInt8* Buffer,
                                            const RFTYPE::UInt64 ReadBytes,
                                            RFTYPE::UInt64& BytesRead);
    typedef RFTYPE::Bool (*WriteFileCallback)(const FileHandle& Handle,
                                            const RFTYPE::UInt8* Buffer,
                                            const RFTYPE::UInt64 WriteBytes,
                                            RFTYPE::UInt64& BytesWritten);
    typedef RFTYPE::Bool (*FlushFileCallback)(const FileHandle& Handle);
    typedef RFTYPE::UInt64 (*SeekFileCallback)(const FileHandle& Handle,
                                                const RFTYPE::UInt64 Offset,
                                                const RadonFramework::IO::SeekOrigin::Type Origin );
    typedef RFTYPE::UInt64 (*TellFileCallback)(const FileHandle& Handle);
    typedef RFTYPE::String (*GenerateTempFilenameCallback)(const RFTYPE::String& Path);
    typedef RFTYPE::Bool (*CreatePreAllocatedFileCallback)(
        const RFTYPE::String& Path, const RFTYPE::Size FileSize);
    typedef RFTYPE::Bool (*CreateFileCallback)(const RFTYPE::String& Path);
    typedef RFTYPE::Bool (*CopyFileCallback)(const RFTYPE::String& From,
        const RFTYPE::String& To);
    typedef RFTYPE::Bool (*RenameFileCallback)(const RFTYPE::String& From,
        const RFTYPE::String& To);
    typedef RFTYPE::Bool (*DeleteFileCallback)(const RFTYPE::String& Path);
    // directory
    typedef RFTYPE::String (*WorkingDirectoryCallback)();
    typedef RFTYPE::String (*HomeDirectoryCallback)();
    typedef RFTYPE::String (*ApplicationDirectoryCallback)();
    typedef RFTYPE::String(*UserApplicationDataDirectoryCallback)();
    typedef RFTYPE::String(*ApplicationDataDirectoryCallback)();
    typedef RFTYPE::Bool (*ChangeDirectoryCallback)(const RFTYPE::String& Destination);
    typedef RFTYPE::Bool (*CreateDirectoryCallback)(const RFTYPE::String& Path);
    typedef RadonFramework::Memory::AutoPointerArray<RFTYPE::String> (*DirectoryContentCallback)(const RFTYPE::String& Path);
    // file watcher
    typedef FileWatcherHandle (*CreateFileWatcherCallback)(const RFTYPE::String& Path);
    typedef void (*DestroyFileWatcherCallback)(FileWatcherHandle& Handle);
    typedef RFTYPE::Bool (*WaitForFileWatcherCallback)(const FileWatcherHandle& Handle, FileWatcherEvent& Event);
    typedef void (*StartFileWatcherCallback)(const FileWatcherHandle& Handle);
    typedef void (*StopFileWatcherCallback)(const FileWatcherHandle& Handle);
    typedef RFTYPE::Bool (*GetFileWatcherEventCallback)(const FileWatcherHandle& Handle, FileWatcherEvent& Event);

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