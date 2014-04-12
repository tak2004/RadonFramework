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
    Access = 0;
    Dispatch();
    Assert(Access != Access_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return Access(Path, Mode);
}

Char PathSeperator_SystemAPIDispatcher()
{
    PathSeperator = 0;
    Dispatch();
    Assert(PathSeperator != PathSeperator_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return PathSeperator();
}

Char Seperator_SystemAPIDispatcher()
{
    Seperator = 0;
    Dispatch();
    Assert(Seperator != Seperator_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return Seperator();
}

AutoPointer<FileStatus> Stat_SystemAPIDispatcher(const Core::Types::String& Path)
{
    Stat = 0;
    Dispatch();
    Assert(Stat != Stat_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return Stat(Path);
}

RFTYPE::Bool ChangeMode_SystemAPIDispatcher(const RFTYPE::String& Path,
    const AccessMode::Type NewMode)
{
    ChangeMode = 0;
    Dispatch();
    Assert(ChangeMode != ChangeMode_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ChangeMode(Path, NewMode);
}

MemoryMappingHandle MapFileIntoMemory_SystemAPIDispatcher(const FileHandle& Handle)
{
    MapFileIntoMemory = 0;
    Dispatch();
    Assert(MapFileIntoMemory != MapFileIntoMemory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return MapFileIntoMemory(Handle);
}

RFTYPE::Bool UnmapMemoryFile_SystemAPIDispatcher(MemoryMappingHandle& Handle)
{
    UnmapMemoryFile = 0;
    Dispatch();
    Assert(UnmapMemoryFile != UnmapMemoryFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return UnmapMemoryFile(Handle);
}

void* GetMemoryFile_SystemAPIDispatcher(const MemoryMappingHandle& Handle)
{
    GetMemoryFile = 0;
    Dispatch();
    Assert(GetMemoryFile != GetMemoryFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return GetMemoryFile(Handle);
}

FileHandle OpenFile_SystemAPIDispatcher(const RFTYPE::String& Filepath, 
    const FileAccessMode::Type AccessMode, const FileAccessPriority::Type AccessPriority)
{
    OpenFile = 0;
    Dispatch();
    Assert(OpenFile != OpenFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return OpenFile(Filepath, AccessMode, AccessPriority);
}

RFTYPE::Bool CloseFile_SystemAPIDispatcher(FileHandle& Handle)
{
    CloseFile = 0;
    Dispatch();
    Assert(CloseFile != CloseFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return CloseFile(Handle);
}

RFTYPE::Bool ReadFile_SystemAPIDispatcher(const FileHandle& Handle,
    UInt8* Buffer, const UInt64 ReadBytes, UInt64& BytesRead)
{
    ReadFile = 0;
    Dispatch();
    Assert(ReadFile != ReadFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ReadFile(Handle, Buffer, ReadBytes, BytesRead);
}

RFTYPE::Bool WriteFile_SystemAPIDispatcher(const FileHandle& Handle,
    const UInt8* Buffer, const UInt64 WriteBytes, UInt64& BytesWritten)
{
    WriteFile = 0;
    Dispatch();
    Assert(WriteFile != WriteFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return WriteFile(Handle, Buffer, WriteBytes, BytesWritten);
}

RFTYPE::Bool FlushFile_SystemAPIDispatcher(const FileHandle& Handle)
{
    FlushFile = 0;
    Dispatch();
    Assert(FlushFile != FlushFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return FlushFile(Handle);
}

RFTYPE::UInt64 SeekFile_SystemAPIDispatcher(const FileHandle& Handle,
    const RFTYPE::UInt64 Offset, const SeekOrigin::Type Origin )
{
    SeekFile = 0;
    Dispatch();
    Assert(SeekFile != SeekFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return SeekFile(Handle, Offset, Origin);
}

RFTYPE::UInt64 TellFile_SystemAPIDispatcher(const FileHandle& Handle)
{
    TellFile = 0;
    Dispatch();
    Assert(TellFile != TellFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return TellFile(Handle);
}

RFTYPE::String GenerateTempFilename_SystemAPIDispatcher(const RFTYPE::String& Path)
{
    GenerateTempFilename = 0;
    Dispatch();
    Assert(GenerateTempFilename != GenerateTempFilename_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return GenerateTempFilename(Path);
}

RFTYPE::Bool CreatePreAllocatedFile_SystemAPIDispatcher(
    const RFTYPE::String& Path, const RFTYPE::Size FileSize)
{
    CreatePreAllocatedFile = 0;
    Dispatch();
    Assert(CreatePreAllocatedFile != CreatePreAllocatedFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return CreatePreAllocatedFile(Path, FileSize);
}

RFTYPE::Bool CreateFile_SystemAPIDispatcher(const RFTYPE::String& Path)
{
    CreateFile = 0;
    Dispatch();
    Assert(CreateFile != CreateFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return CreateFile(Path);
}

RFTYPE::Bool CopyFile_SystemAPIDispatcher(const Core::Types::String& From,
                                          const Core::Types::String& To)
{
    CopyFile = 0;
    Dispatch();
    Assert(CopyFile != CopyFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return CopyFile(From, To);
}

RFTYPE::Bool RenameFile_SystemAPIDispatcher(const Core::Types::String& From,
                                            const Core::Types::String& To)
{
    RenameFile = 0;
    Dispatch();
    Assert(RenameFile != RenameFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return RenameFile(From, To);
}

RFTYPE::Bool DeleteFile_SystemAPIDispatcher(const RFTYPE::String& Path)
{
    DeleteFile = 0;
    Dispatch();
    Assert(DeleteFile != DeleteFile_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return DeleteFile(Path);
}

RFTYPE::String WorkingDirectory_SystemAPIDispatcher()
{
    WorkingDirectory = 0;
    Dispatch();
    Assert(WorkingDirectory != WorkingDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return WorkingDirectory();
}

RFTYPE::String HomeDirectory_SystemAPIDispatcher()
{
    HomeDirectory = 0;
    Dispatch();
    Assert(HomeDirectory != HomeDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return HomeDirectory();
}

RFTYPE::String ApplicationDirectory_SystemAPIDispatcher()
{
    ApplicationDataDirectory = 0;
    Dispatch();
    Assert(ApplicationDirectory != ApplicationDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ApplicationDirectory();
}

RFTYPE::String UserApplicationDataDirectory_SystemAPIDispatcher()
{
    UserApplicationDataDirectory = 0;
    Dispatch();
    Assert(UserApplicationDataDirectory != UserApplicationDataDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return UserApplicationDataDirectory();
}

RFTYPE::String ApplicationDataDirectory_SystemAPIDispatcher()
{
    ApplicationDataDirectory = 0;
    Dispatch();
    Assert(ApplicationDataDirectory != ApplicationDataDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ApplicationDataDirectory();
}

RFTYPE::Bool ChangeDirectory_SystemAPIDispatcher(const RFTYPE::String& Destination)
{
    ChangeDirectory = 0;
    Dispatch();
    Assert(ChangeDirectory != ChangeDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return ChangeDirectory(Destination);
}

RFTYPE::Bool CreateDirectory_SystemAPIDispatcher(const RFTYPE::String& Path)
{
    CreateDirectory = 0;
    Dispatch();
    Assert(CreateDirectory != CreateDirectory_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return CreateDirectory(Path);
}

RadonFramework::Memory::AutoPointerArray<RFTYPE::String>
    DirectoryContent_SystemAPIDispatcher(const RFTYPE::String& Path)
{
    DirectoryContent = 0;
    Dispatch();
    Assert(DirectoryContent != DirectoryContent_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return DirectoryContent(Path);
}

FileWatcherHandle CreateFileWatcher_SystemAPIDispatcher(const RFTYPE::String& Path)
{
    CreateFileWatcher = 0;
    Dispatch();
    Assert(CreateFileWatcher != CreateFileWatcher_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return CreateFileWatcher(Path);
}

void DestroyFileWatcher_SystemAPIDispatcher(FileWatcherHandle& Handle)
{
    DestroyFileWatcher = 0;
    Dispatch();
    Assert(DestroyFileWatcher != DestroyFileWatcher_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    DestroyFileWatcher(Handle);
}

RFTYPE::Bool WaitForFileWatcher_SystemAPIDispatcher(const FileWatcherHandle& Handle, FileWatcherEvent& Event)
{
    WaitForFileWatcher = 0;
    Dispatch();
    Assert(WaitForFileWatcher != WaitForFileWatcher_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    return WaitForFileWatcher(Handle, Event);
}

void StartFileWatcher_SystemAPIDispatcher(const FileWatcherHandle& Handle)
{
    StartFileWatcher = 0;
    Dispatch();
    Assert(StartFileWatcher != StartFileWatcher_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    StartFileWatcher(Handle);
}

void StopFileWatcher_SystemAPIDispatcher(const FileWatcherHandle& Handle)
{
    StopFileWatcher = 0;
    Dispatch();
    Assert(StopFileWatcher != StopFileWatcher_SystemAPIDispatcher,
           "Funtion was called and couldn't be dispatched");
    StopFileWatcher(Handle);
}

RFTYPE::Bool GetFileWatcherEvent_SystemAPIDispatcher(const FileWatcherHandle& Handle, FileWatcherEvent& Event)
{
    GetFileWatcherEvent = 0;
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
    result=result && OpenFile != OpenFile_SystemAPIDispatcher && OpenFile != 0;
    result=result && CloseFile != CloseFile_SystemAPIDispatcher && CloseFile != 0;
    result=result && MapFileIntoMemory != MapFileIntoMemory_SystemAPIDispatcher && MapFileIntoMemory != 0;
    result=result && UnmapMemoryFile != UnmapMemoryFile_SystemAPIDispatcher && UnmapMemoryFile != 0;
    result=result && GetMemoryFile != GetMemoryFile_SystemAPIDispatcher && GetMemoryFile != 0;
    result=result && ReadFile != ReadFile_SystemAPIDispatcher && ReadFile != 0;
    result=result && WriteFile != WriteFile_SystemAPIDispatcher && WriteFile != 0;
    result=result && FlushFile != FlushFile_SystemAPIDispatcher && FlushFile != 0;
    result=result && SeekFile != SeekFile_SystemAPIDispatcher && SeekFile != 0;
    result=result && TellFile != TellFile_SystemAPIDispatcher && TellFile != 0;
    result=result && GenerateTempFilename != GenerateTempFilename_SystemAPIDispatcher && GenerateTempFilename != 0;
    result=result && Access != Access_SystemAPIDispatcher && Access != 0;
    result=result && PathSeperator != PathSeperator_SystemAPIDispatcher && PathSeperator != 0;
    result=result && Seperator != Seperator_SystemAPIDispatcher && Seperator != 0;
    result=result && Stat != Stat_SystemAPIDispatcher && Stat != 0;
    result=result && ChangeMode != ChangeMode_SystemAPIDispatcher && ChangeMode != 0;
    result=result && CreatePreAllocatedFile != CreatePreAllocatedFile_SystemAPIDispatcher && CreatePreAllocatedFile != 0;
    result=result && CreateFile != CreateFile_SystemAPIDispatcher && CreateFile != 0;
    result=result && CopyFile != CopyFile_SystemAPIDispatcher && CopyFile != 0;
    result=result && RenameFile != RenameFile_SystemAPIDispatcher && RenameFile != 0;
    result=result && DeleteFile != DeleteFile_SystemAPIDispatcher && DeleteFile != 0;
    result=result && WorkingDirectory != WorkingDirectory_SystemAPIDispatcher && WorkingDirectory != 0;
    result=result && HomeDirectory != HomeDirectory_SystemAPIDispatcher && HomeDirectory != 0;
    result=result && ApplicationDirectory != ApplicationDirectory_SystemAPIDispatcher && ApplicationDirectory != 0;
    result=result && UserApplicationDataDirectory != UserApplicationDataDirectory_SystemAPIDispatcher && UserApplicationDataDirectory != 0;
    result=result && ApplicationDataDirectory != ApplicationDataDirectory_SystemAPIDispatcher && ApplicationDataDirectory != 0;
    result=result && ChangeDirectory != ChangeDirectory_SystemAPIDispatcher && ChangeDirectory != 0;
    result=result && CreateDirectory != CreateDirectory_SystemAPIDispatcher && CreateDirectory != 0;
    result=result && DirectoryContent != DirectoryContent_SystemAPIDispatcher && DirectoryContent != 0;
    result=result && CreateFileWatcher != CreateFileWatcher_SystemAPIDispatcher && CreateFileWatcher != 0;
    result=result && DestroyFileWatcher != DestroyFileWatcher_SystemAPIDispatcher && DestroyFileWatcher != 0;
    result=result && WaitForFileWatcher != WaitForFileWatcher_SystemAPIDispatcher && WaitForFileWatcher != 0;
    result=result && StartFileWatcher != StartFileWatcher_SystemAPIDispatcher && StartFileWatcher != 0;
    result=result && StopFileWatcher != StopFileWatcher_SystemAPIDispatcher && StopFileWatcher != 0;
    result=result && GetFileWatcherEvent != GetFileWatcherEvent_SystemAPIDispatcher && GetFileWatcherEvent != 0;
    return result;
}

void RFFILE::GetNotDispatchedFunctions(List<RFTYPE::String>& Result)
{
    if (OpenFile == OpenFile_SystemAPIDispatcher || OpenFile == 0) 
        Result.AddLast("OpenFile");
    if (CloseFile == CloseFile_SystemAPIDispatcher || CloseFile == 0)
        Result.AddLast("CloseFile");
    if (MapFileIntoMemory == MapFileIntoMemory_SystemAPIDispatcher || MapFileIntoMemory == 0)
        Result.AddLast("MapFileIntoMemory");
    if (UnmapMemoryFile == UnmapMemoryFile_SystemAPIDispatcher || UnmapMemoryFile == 0) 
        Result.AddLast("UnmapMemoryFile");
    if (GetMemoryFile == GetMemoryFile_SystemAPIDispatcher || GetMemoryFile == 0) 
        Result.AddLast("GetMemoryFile");
    if (ReadFile == ReadFile_SystemAPIDispatcher || ReadFile == 0)
        Result.AddLast("ReadFile");
    if (WriteFile == WriteFile_SystemAPIDispatcher || WriteFile == 0)
        Result.AddLast("WriteFile");
    if (FlushFile == FlushFile_SystemAPIDispatcher || FlushFile == 0)
        Result.AddLast("FlushFile");
    if (SeekFile == SeekFile_SystemAPIDispatcher || SeekFile == 0)
        Result.AddLast("SeekFile");
    if (TellFile == TellFile_SystemAPIDispatcher || TellFile == 0)
        Result.AddLast("TellFile");
    if (GenerateTempFilename == GenerateTempFilename_SystemAPIDispatcher || GenerateTempFilename == 0)
        Result.AddLast("GenerateTempFilename");
    if (Access == Access_SystemAPIDispatcher || Access == 0)
        Result.AddLast("Access");
    if (PathSeperator == PathSeperator_SystemAPIDispatcher || PathSeperator == 0)
        Result.AddLast("PathSeperator");
    if (Seperator == Seperator_SystemAPIDispatcher || Seperator == 0)
        Result.AddLast("Seperator");
    if (Stat == Stat_SystemAPIDispatcher || Stat == 0)
        Result.AddLast("Stat");
    if (ChangeMode == ChangeMode_SystemAPIDispatcher || ChangeMode == 0)
        Result.AddLast("ChangeMode");
    if (CreatePreAllocatedFile == CreatePreAllocatedFile_SystemAPIDispatcher || CreatePreAllocatedFile == 0)
        Result.AddLast("CreatePreAllocatedFile");
    if (CreateFile == CreateFile_SystemAPIDispatcher || CreateFile == 0)
        Result.AddLast("CreateFile");
    if (CopyFile == CopyFile_SystemAPIDispatcher || CopyFile == 0)
        Result.AddLast("CopyFile");
    if (RenameFile == RenameFile_SystemAPIDispatcher || RenameFile == 0)
        Result.AddLast("RenameFile");
    if (DeleteFile == DeleteFile_SystemAPIDispatcher || DeleteFile == 0)
        Result.AddLast("DeleteFile");
    if (WorkingDirectory == WorkingDirectory_SystemAPIDispatcher || WorkingDirectory == 0)
        Result.AddLast("WorkingDirectory");
    if (HomeDirectory == HomeDirectory_SystemAPIDispatcher || HomeDirectory == 0)
        Result.AddLast("HomeDirectory");
    if (ApplicationDirectory == ApplicationDirectory_SystemAPIDispatcher || ApplicationDataDirectory == 0)
        Result.AddLast("ApplicationDirectory");
    if (UserApplicationDataDirectory == UserApplicationDataDirectory_SystemAPIDispatcher || UserApplicationDataDirectory == 0)
        Result.AddLast("UserApplicationDataDirectory");
    if (ApplicationDataDirectory == ApplicationDataDirectory_SystemAPIDispatcher || ApplicationDataDirectory == 0)
        Result.AddLast("ApplicationDataDirectory");
    if (ChangeDirectory == ChangeDirectory_SystemAPIDispatcher || ChangeDirectory == 0)
        Result.AddLast("ChangeDirectory");
    if (CreateDirectory == CreateDirectory_SystemAPIDispatcher || CreateDirectory == 0)
        Result.AddLast("CreateDirectory");
    if (DirectoryContent == DirectoryContent_SystemAPIDispatcher || DirectoryContent == 0)
        Result.AddLast("DirectoryContent");
    if (CreateFileWatcher == CreateFileWatcher_SystemAPIDispatcher || CreateFileWatcher == 0)
        Result.AddLast("CreateFileWatcher");
    if (DestroyFileWatcher == DestroyFileWatcher_SystemAPIDispatcher || DestroyFileWatcher == 0)
        Result.AddLast("DestroyFileWatcher");
    if (WaitForFileWatcher == WaitForFileWatcher_SystemAPIDispatcher || WaitForFileWatcher == 0)
        Result.AddLast("WaitForFileWatcher");
    if (StartFileWatcher == StartFileWatcher_SystemAPIDispatcher || StartFileWatcher == 0)
        Result.AddLast("StartFileWatcher");
    if (StopFileWatcher == StopFileWatcher_SystemAPIDispatcher || StopFileWatcher == 0)
        Result.AddLast("StopFileWatcher");
    if (GetFileWatcherEvent == GetFileWatcherEvent_SystemAPIDispatcher || GetFileWatcherEvent == 0)
        Result.AddLast("GetFileWatcherEvent");
}