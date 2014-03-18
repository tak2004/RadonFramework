#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/IO/Uri.hpp"

using namespace RadonFramework;
using namespace RadonFramework::Memory;
using namespace RadonFramework::IO;
using namespace RadonFramework::System::IO;
using namespace RadonFramework::System::IO::FileSystem;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Common;
using namespace RadonFramework::Collections;

Bool Access_SystemAPIDispatcher(const String& Path, const AccessMode::Type Mode)
{
    Dispatch();
    Assert(Access != Access_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return Access(Path, Mode);
}

Char PathSeperator_SystemAPIDispatcher()
{
    Dispatch();
    Assert(PathSeperator != PathSeperator_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return PathSeperator();
}

Char Seperator_SystemAPIDispatcher()
{
    Dispatch();
    Assert(Seperator != Seperator_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return Seperator();
}

AutoPointer<FileStatus> Stat_SystemAPIDispatcher(const Core::Types::String& Path)
{
    Dispatch();
    Assert(Stat != Stat_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return Stat(Path);
}

RFTYPE::Bool ChangeMode_SystemAPIDispatcher(const RFTYPE::String& Path,
    const AccessMode::Type NewMode)
{
    Dispatch();
    Assert(ChangeMode != ChangeMode_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ChangeMode(Path, NewMode);
}

MemoryMappingHandle MapFileIntoMemory_SystemAPIDispatcher(const FileHandle& Handle)
{
    Dispatch();
    Assert(MapFileIntoMemory != MapFileIntoMemory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return MapFileIntoMemory(Handle);
}

RFTYPE::Bool UnmapMemoryFile_SystemAPIDispatcher(MemoryMappingHandle& Handle)
{
    Dispatch();
    Assert(UnmapMemoryFile != UnmapMemoryFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return UnmapMemoryFile(Handle);
}

void* GetMemoryFile_SystemAPIDispatcher(const MemoryMappingHandle& Handle)
{
    Dispatch();
    Assert(GetMemoryFile != GetMemoryFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return GetMemoryFile(Handle);
}

FileHandle OpenFile_SystemAPIDispatcher(const RFTYPE::String& Filepath, 
    const FileAccessMode::Type AccessMode, const FileAccessPriority::Type AccessPriority)
{
    Dispatch();
    Assert(OpenFile != OpenFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return OpenFile(Filepath, AccessMode, AccessPriority);
}

RFTYPE::Bool CloseFile_SystemAPIDispatcher(FileHandle& Handle)
{
    Dispatch();
    Assert(CloseFile != CloseFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return CloseFile(Handle);
}

RFTYPE::Bool ReadFile_SystemAPIDispatcher(const FileHandle& Handle,
    UInt8* Buffer, const UInt64 ReadBytes, UInt64& BytesRead)
{
    Dispatch();
    Assert(ReadFile != ReadFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ReadFile(Handle, Buffer, ReadBytes, BytesRead);
}

RFTYPE::Bool WriteFile_SystemAPIDispatcher(const FileHandle& Handle,
    const UInt8* Buffer, const UInt64 WriteBytes, UInt64& BytesWritten)
{
    Dispatch();
    Assert(WriteFile != WriteFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return WriteFile(Handle, Buffer, WriteBytes, BytesWritten);
}

RFTYPE::Bool FlushFile_SystemAPIDispatcher(const FileHandle& Handle)
{
    Dispatch();
    Assert(FlushFile != FlushFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return FlushFile(Handle);
}

RFTYPE::UInt64 SeekFile_SystemAPIDispatcher(const FileHandle& Handle,
    const RFTYPE::UInt64 Offset, const SeekOrigin::Type Origin )
{
    Dispatch();
    Assert(SeekFile != SeekFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return SeekFile(Handle, Offset, Origin);
}

RFTYPE::UInt64 TellFile_SystemAPIDispatcher(const FileHandle& Handle)
{
    Dispatch();
    Assert(TellFile != TellFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return TellFile(Handle);
}

RFTYPE::String GenerateTempFilename_SystemAPIDispatcher(const RFTYPE::String& Path)
{
    Dispatch();
    Assert(GenerateTempFilename != GenerateTempFilename_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return GenerateTempFilename(Path);
}

RFTYPE::Bool CreatePreAllocatedFile_SystemAPIDispatcher(
    const RFTYPE::String& Path, const RFTYPE::Size FileSize)
{
    Dispatch();
    Assert(CreatePreAllocatedFile != CreatePreAllocatedFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return CreatePreAllocatedFile(Path, FileSize);
}

RFTYPE::Bool CreateFile_SystemAPIDispatcher(const RFTYPE::String& Path)
{
    Dispatch();
    Assert(CreateFile != CreateFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return CreateFile(Path);
}

RFTYPE::Bool CopyFile_SystemAPIDispatcher(const Core::Types::String& From,
                                          const Core::Types::String& To)
{
    Dispatch();
    Assert(CopyFile != CopyFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return CopyFile(From, To);
}

RFTYPE::Bool RenameFile_SystemAPIDispatcher(const Core::Types::String& From,
                                            const Core::Types::String& To)
{
    Dispatch();
    Assert(RenameFile != RenameFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return RenameFile(From, To);
}

RFTYPE::Bool DeleteFile_SystemAPIDispatcher(const RFTYPE::String& Path)
{
    Dispatch();
    Assert(DeleteFile != DeleteFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return DeleteFile(Path);
}

RFTYPE::String WorkingDirectory_SystemAPIDispatcher()
{
    Dispatch();
    Assert(WorkingDirectory != WorkingDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return WorkingDirectory();
}

RFTYPE::String HomeDirectory_SystemAPIDispatcher()
{
    Dispatch();
    Assert(HomeDirectory != HomeDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return HomeDirectory();
}

RFTYPE::String ApplicationDirectory_SystemAPIDispatcher()
{
    Dispatch();
    Assert(ApplicationDirectory != ApplicationDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ApplicationDirectory();
}

RFTYPE::String UserApplicationDataDirectory_SystemAPIDispatcher()
{
    Dispatch();
    Assert(UserApplicationDataDirectory != UserApplicationDataDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return UserApplicationDataDirectory();
}

RFTYPE::String ApplicationDataDirectory_SystemAPIDispatcher()
{
    Dispatch();
    Assert(ApplicationDataDirectory != ApplicationDataDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ApplicationDataDirectory();
}

RFTYPE::Bool ChangeDirectory_SystemAPIDispatcher(const RFTYPE::String& Destination)
{
    Dispatch();
    Assert(ChangeDirectory != ChangeDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ChangeDirectory(Destination);
}

RFTYPE::Bool CreateDirectory_SystemAPIDispatcher(const RFTYPE::String& Path)
{
    Dispatch();
    Assert(CreateDirectory != CreateDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return CreateDirectory(Path);
}

RadonFramework::Memory::AutoPointerArray<RFTYPE::String>
    DirectoryContent_SystemAPIDispatcher(const RFTYPE::String& Path)
{
    Dispatch();
    Assert(DirectoryContent != DirectoryContent_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return DirectoryContent(Path);
}

FileWatcherHandle CreateFileWatcher_SystemAPIDispatcher(const RFTYPE::String& Path)
{
    Dispatch();
    Assert(CreateFileWatcher != CreateFileWatcher_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return CreateFileWatcher(Path);
}

void DestroyFileWatcher_SystemAPIDispatcher(FileWatcherHandle& Handle)
{
    Dispatch();
    Assert(DestroyFileWatcher != DestroyFileWatcher_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    DestroyFileWatcher(Handle);
}

RFTYPE::Bool WaitForFileWatcher_SystemAPIDispatcher(const FileWatcherHandle& Handle, FileWatcherEvent& Event)
{
    Dispatch();
    Assert(WaitForFileWatcher != WaitForFileWatcher_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return WaitForFileWatcher(Handle, Event);
}

void StartFileWatcher_SystemAPIDispatcher(const FileWatcherHandle& Handle)
{
    Dispatch();
    Assert(StartFileWatcher != StartFileWatcher_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    StartFileWatcher(Handle);
}

void StopFileWatcher_SystemAPIDispatcher(const FileWatcherHandle& Handle)
{
    Dispatch();
    Assert(StopFileWatcher != StopFileWatcher_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    StopFileWatcher(Handle);
}

RFTYPE::Bool GetFileWatcherEvent_SystemAPIDispatcher(const FileWatcherHandle& Handle, FileWatcherEvent& Event)
{
    Dispatch();
    Assert(GetFileWatcherEvent != GetFileWatcherEvent_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return GetFileWatcherEvent(Handle, Event);
}

OpenFileCallback RFFILE::OpenFile = OpenFile_SystemAPIDispatcher;
CloseFileCallback RFFILE::CloseFile = CloseFile_SystemAPIDispatcher;
MapFileIntoMemoryCallback RFFILE::MapFileIntoMemory = MapFileIntoMemory_SystemAPIDispatcher;
UnmapMemoryFileCallback RFFILE::UnmapMemoryFile = UnmapMemoryFile_SystemAPIDispatcher;
GetMemoryFileCallback RFFILE::GetMemoryFile = GetMemoryFile_SystemAPIDispatcher;
ReadFileCallback RFFILE::ReadFile = ReadFile_SystemAPIDispatcher;
WriteFileCallback RFFILE::WriteFile = WriteFile_SystemAPIDispatcher;
FlushFileCallback RFFILE::FlushFile = FlushFile_SystemAPIDispatcher;
SeekFileCallback RFFILE::SeekFile = SeekFile_SystemAPIDispatcher;
TellFileCallback RFFILE::TellFile = TellFile_SystemAPIDispatcher;
GenerateTempFilenameCallback RFFILE::GenerateTempFilename = GenerateTempFilename_SystemAPIDispatcher;
AccessCallback RFFILE::Access = Access_SystemAPIDispatcher;
PathSeperatorCallback RFFILE::PathSeperator = PathSeperator_SystemAPIDispatcher;
SeperatorCallback RFFILE::Seperator = Seperator_SystemAPIDispatcher;
StatCallback RFFILE::Stat = Stat_SystemAPIDispatcher;
ChangeModeCallback RFFILE::ChangeMode = ChangeMode_SystemAPIDispatcher;
CreatePreAllocatedFileCallback RFFILE::CreatePreAllocatedFile = CreatePreAllocatedFile_SystemAPIDispatcher;
CreateFileCallback RFFILE::CreateFile = CreateFile_SystemAPIDispatcher;
CopyFileCallback RFFILE::CopyFile = CopyFile_SystemAPIDispatcher;
RenameFileCallback RFFILE::RenameFile = RenameFile_SystemAPIDispatcher;
DeleteFileCallback RFFILE::DeleteFile = DeleteFile_SystemAPIDispatcher;
WorkingDirectoryCallback RFFILE::WorkingDirectory = WorkingDirectory_SystemAPIDispatcher;
HomeDirectoryCallback RFFILE::HomeDirectory = HomeDirectory_SystemAPIDispatcher;
ApplicationDirectoryCallback RFFILE::ApplicationDirectory = ApplicationDirectory_SystemAPIDispatcher;
ApplicationDataDirectoryCallback RFFILE::UserApplicationDataDirectory = UserApplicationDataDirectory_SystemAPIDispatcher;
UserApplicationDataDirectoryCallback RFFILE::ApplicationDataDirectory = ApplicationDataDirectory_SystemAPIDispatcher;
ChangeDirectoryCallback RFFILE::ChangeDirectory = ChangeDirectory_SystemAPIDispatcher;
CreateDirectoryCallback RFFILE::CreateDirectory = CreateDirectory_SystemAPIDispatcher;
DirectoryContentCallback RFFILE::DirectoryContent = DirectoryContent_SystemAPIDispatcher;
CreateFileWatcherCallback RFFILE::CreateFileWatcher = CreateFileWatcher_SystemAPIDispatcher;
DestroyFileWatcherCallback RFFILE::DestroyFileWatcher = DestroyFileWatcher_SystemAPIDispatcher;
WaitForFileWatcherCallback RFFILE::WaitForFileWatcher = WaitForFileWatcher_SystemAPIDispatcher;
StartFileWatcherCallback RFFILE::StartFileWatcher = StartFileWatcher_SystemAPIDispatcher;
StopFileWatcherCallback RFFILE::StopFileWatcher = StopFileWatcher_SystemAPIDispatcher;
GetFileWatcherEventCallback RFFILE::GetFileWatcherEvent = GetFileWatcherEvent_SystemAPIDispatcher;

Bool RFFILE::IsSuccessfullyDispatched()
{
    Bool result=true;
    result=result && OpenFile != OpenFile_SystemAPIDispatcher;
    result=result && CloseFile != CloseFile_SystemAPIDispatcher;
    result=result && MapFileIntoMemory != MapFileIntoMemory_SystemAPIDispatcher;
    result=result && UnmapMemoryFile != UnmapMemoryFile_SystemAPIDispatcher;
    result=result && GetMemoryFile != GetMemoryFile_SystemAPIDispatcher;
    result=result && ReadFile != ReadFile_SystemAPIDispatcher;
    result=result && WriteFile != WriteFile_SystemAPIDispatcher;
    result=result && FlushFile != FlushFile_SystemAPIDispatcher;
    result=result && SeekFile != SeekFile_SystemAPIDispatcher;
    result=result && TellFile != TellFile_SystemAPIDispatcher;
    result=result && GenerateTempFilename != GenerateTempFilename_SystemAPIDispatcher;
    result=result && Access != Access_SystemAPIDispatcher;
    result=result && PathSeperator != PathSeperator_SystemAPIDispatcher;
    result=result && Seperator != Seperator_SystemAPIDispatcher;
    result=result && Stat != Stat_SystemAPIDispatcher;
    result=result && ChangeMode != ChangeMode_SystemAPIDispatcher;
    result=result && CreatePreAllocatedFile != CreatePreAllocatedFile_SystemAPIDispatcher;
    result=result && CreateFile != CreateFile_SystemAPIDispatcher;
    result=result && CopyFile != CopyFile_SystemAPIDispatcher;
    result=result && RenameFile != RenameFile_SystemAPIDispatcher;
    result=result && DeleteFile != DeleteFile_SystemAPIDispatcher;
    result=result && WorkingDirectory != WorkingDirectory_SystemAPIDispatcher;
    result=result && HomeDirectory != HomeDirectory_SystemAPIDispatcher;
    result=result && ApplicationDirectory != ApplicationDirectory_SystemAPIDispatcher;
    result=result && UserApplicationDataDirectory != UserApplicationDataDirectory_SystemAPIDispatcher;
    result=result && ApplicationDataDirectory != ApplicationDataDirectory_SystemAPIDispatcher;
    result=result && ChangeDirectory != ChangeDirectory_SystemAPIDispatcher;
    result=result && CreateDirectory != CreateDirectory_SystemAPIDispatcher;
    result=result && DirectoryContent != DirectoryContent_SystemAPIDispatcher;
    result=result && CreateFileWatcher != CreateFileWatcher_SystemAPIDispatcher;
    result=result && DestroyFileWatcher != DestroyFileWatcher_SystemAPIDispatcher;
    result=result && WaitForFileWatcher != WaitForFileWatcher_SystemAPIDispatcher;
    result=result && StartFileWatcher != StartFileWatcher_SystemAPIDispatcher;
    result=result && StopFileWatcher != StopFileWatcher_SystemAPIDispatcher;
    result=result && GetFileWatcherEvent != GetFileWatcherEvent_SystemAPIDispatcher;
    return result;
}

void RFFILE::GetNotDispatchedFunctions(List<RFTYPE::String>& Result)
{
    if (OpenFile == OpenFile_SystemAPIDispatcher) 
        Result.AddLast("OpenFile");
    if (CloseFile == CloseFile_SystemAPIDispatcher)
        Result.AddLast("CloseFile");
    if (MapFileIntoMemory == MapFileIntoMemory_SystemAPIDispatcher) 
        Result.AddLast("MapFileIntoMemory");
    if (UnmapMemoryFile == UnmapMemoryFile_SystemAPIDispatcher) 
        Result.AddLast("UnmapMemoryFile");
    if (GetMemoryFile == GetMemoryFile_SystemAPIDispatcher) 
        Result.AddLast("GetMemoryFile");
    if (ReadFile == ReadFile_SystemAPIDispatcher)
        Result.AddLast("ReadFile");
    if (WriteFile == WriteFile_SystemAPIDispatcher)
        Result.AddLast("WriteFile");
    if (FlushFile == FlushFile_SystemAPIDispatcher)
        Result.AddLast("FlushFile");
    if (SeekFile == SeekFile_SystemAPIDispatcher)
        Result.AddLast("SeekFile");
    if (TellFile == TellFile_SystemAPIDispatcher)
        Result.AddLast("TellFile");
    if (GenerateTempFilename == GenerateTempFilename_SystemAPIDispatcher)
        Result.AddLast("GenerateTempFilename");
    if (Access == Access_SystemAPIDispatcher)
        Result.AddLast("Access");
    if (PathSeperator == PathSeperator_SystemAPIDispatcher)
        Result.AddLast("PathSeperator");
    if (Seperator == Seperator_SystemAPIDispatcher)
        Result.AddLast("Seperator");
    if (Stat == Stat_SystemAPIDispatcher)
        Result.AddLast("Stat");
    if (ChangeMode == ChangeMode_SystemAPIDispatcher)
        Result.AddLast("ChangeMode");
    if (CreatePreAllocatedFile == CreatePreAllocatedFile_SystemAPIDispatcher)
        Result.AddLast("CreatePreAllocatedFile");
    if (CreateFile == CreateFile_SystemAPIDispatcher)
        Result.AddLast("CreateFile");
    if (CopyFile == CopyFile_SystemAPIDispatcher)
        Result.AddLast("CopyFile");
    if (RenameFile == RenameFile_SystemAPIDispatcher)
        Result.AddLast("RenameFile");
    if (DeleteFile == DeleteFile_SystemAPIDispatcher)
        Result.AddLast("DeleteFile");
    if (WorkingDirectory == WorkingDirectory_SystemAPIDispatcher)
        Result.AddLast("WorkingDirectory");
    if (HomeDirectory == HomeDirectory_SystemAPIDispatcher)
        Result.AddLast("HomeDirectory");
    if (ApplicationDirectory == ApplicationDirectory_SystemAPIDispatcher)
        Result.AddLast("ApplicationDirectory");
    if (UserApplicationDataDirectory == UserApplicationDataDirectory_SystemAPIDispatcher)
        Result.AddLast("UserApplicationDataDirectory");
    if (ApplicationDataDirectory == ApplicationDataDirectory_SystemAPIDispatcher)
        Result.AddLast("ApplicationDataDirectory");
    if (ChangeDirectory == ChangeDirectory_SystemAPIDispatcher)
        Result.AddLast("ChangeDirectory");
    if (CreateDirectory == CreateDirectory_SystemAPIDispatcher)
        Result.AddLast("CreateDirectory");
    if (DirectoryContent == DirectoryContent_SystemAPIDispatcher)
        Result.AddLast("DirectoryContent");
    if (CreateFileWatcher == CreateFileWatcher_SystemAPIDispatcher)
        Result.AddLast("CreateFileWatcher");
    if (DestroyFileWatcher == DestroyFileWatcher_SystemAPIDispatcher)
        Result.AddLast("DestroyFileWatcher");
    if (WaitForFileWatcher == WaitForFileWatcher_SystemAPIDispatcher)
        Result.AddLast("WaitForFileWatcher");
    if (StartFileWatcher == StartFileWatcher_SystemAPIDispatcher)
        Result.AddLast("StartFileWatcher");
    if (StopFileWatcher == StopFileWatcher_SystemAPIDispatcher)
        Result.AddLast("StopFileWatcher");
    if (GetFileWatcherEvent == GetFileWatcherEvent_SystemAPIDispatcher)
        Result.AddLast("GetFileWatcherEvent");
}