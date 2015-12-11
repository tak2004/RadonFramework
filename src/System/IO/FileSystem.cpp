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
    Assert(Access != Access_SystemAPIDispatcher && Access != 0,
           "Funtion was called and couldn't be dispatched");
    return Access(Path, Mode);
}

String PathSeperator_SystemAPIDispatcher()
{
    PathSeperator = 0;
    Dispatch();
    Assert(PathSeperator != PathSeperator_SystemAPIDispatcher && PathSeperator != 0,
           "Funtion was called and couldn't be dispatched");
    return PathSeperator();
}

String Seperator_SystemAPIDispatcher()
{
    Seperator = 0;
    Dispatch();
    Assert(Seperator != Seperator_SystemAPIDispatcher && Seperator != 0,
           "Funtion was called and couldn't be dispatched");
    return Seperator();
}

AutoPointer<FileStatus> Stat_SystemAPIDispatcher(const Core::Types::String& Path)
{
    Stat = 0;
    Dispatch();
    Assert(Stat != Stat_SystemAPIDispatcher && Stat != 0,
           "Funtion was called and couldn't be dispatched");
    return Stat(Path);
}

void RealPath_SystemAPIDispatcher(const RF_Type::String& Path, 
                                  RF_Type::String& ResolvedPath)
{
    RealPath = 0;
    Dispatch();
    Assert(RealPath != RealPath_SystemAPIDispatcher && RealPath != 0,
           "Funtion was called and couldn't be dispatched");
    RealPath(Path, ResolvedPath);
}

RF_Type::Bool ChangeMode_SystemAPIDispatcher(const RF_Type::String& Path,
    const AccessMode::Type NewMode)
{
    ChangeMode = 0;
    Dispatch();
    Assert(ChangeMode != ChangeMode_SystemAPIDispatcher && ChangeMode != 0,
           "Funtion was called and couldn't be dispatched");
    return ChangeMode(Path, NewMode);
}

MemoryMappingHandle MapFileIntoMemory_SystemAPIDispatcher(const FileHandle& Handle)
{
    MapFileIntoMemory = 0;
    Dispatch();
    Assert(MapFileIntoMemory != MapFileIntoMemory_SystemAPIDispatcher &&
           MapFileIntoMemory != 0,
           "Funtion was called and couldn't be dispatched");
    return MapFileIntoMemory(Handle);
}

RF_Type::Bool UnmapMemoryFile_SystemAPIDispatcher(MemoryMappingHandle& Handle)
{
    UnmapMemoryFile = 0;
    Dispatch();
    Assert(UnmapMemoryFile != UnmapMemoryFile_SystemAPIDispatcher &&
           UnmapMemoryFile != 0,
           "Funtion was called and couldn't be dispatched");
    return UnmapMemoryFile(Handle);
}

void* GetMemoryFile_SystemAPIDispatcher(const MemoryMappingHandle& Handle)
{
    GetMemoryFile = 0;
    Dispatch();
    Assert(GetMemoryFile != GetMemoryFile_SystemAPIDispatcher &&
           GetMemoryFile != 0,
           "Funtion was called and couldn't be dispatched");
    return GetMemoryFile(Handle);
}

FileHandle OpenFile_SystemAPIDispatcher(const RF_Type::String& Filepath, 
    const FileAccessMode::Type AccessMode, const FileAccessPriority::Type AccessPriority)
{
    OpenFile = 0;
    Dispatch();
    Assert(OpenFile != OpenFile_SystemAPIDispatcher &&
           OpenFile != 0,
           "Funtion was called and couldn't be dispatched");
    return OpenFile(Filepath, AccessMode, AccessPriority);
}

RF_Type::Bool CloseFile_SystemAPIDispatcher(FileHandle& Handle)
{
    CloseFile = 0;
    Dispatch();
    Assert(CloseFile != CloseFile_SystemAPIDispatcher &&
           CloseFile != 0,
           "Funtion was called and couldn't be dispatched");
    return CloseFile(Handle);
}

RF_Type::Bool ReadFile_SystemAPIDispatcher(const FileHandle& Handle,
    UInt8* Buffer, const UInt64 ReadBytes, UInt64& BytesRead)
{
    ReadFile = 0;
    Dispatch();
    Assert(ReadFile != ReadFile_SystemAPIDispatcher &&
           ReadFile != 0,
           "Funtion was called and couldn't be dispatched");
    return ReadFile(Handle, Buffer, ReadBytes, BytesRead);
}

RF_Type::Bool WriteFile_SystemAPIDispatcher(const FileHandle& Handle,
    const UInt8* Buffer, const UInt64 WriteBytes, UInt64& BytesWritten)
{
    WriteFile = 0;
    Dispatch();
    Assert(WriteFile != WriteFile_SystemAPIDispatcher &&
           WriteFile != 0,
           "Funtion was called and couldn't be dispatched");
    return WriteFile(Handle, Buffer, WriteBytes, BytesWritten);
}

RF_Type::Bool FlushFile_SystemAPIDispatcher(const FileHandle& Handle)
{
    FlushFile = 0;
    Dispatch();
    Assert(FlushFile != FlushFile_SystemAPIDispatcher &&
           FlushFile != 0,
           "Funtion was called and couldn't be dispatched");
    return FlushFile(Handle);
}

RF_Type::UInt64 SeekFile_SystemAPIDispatcher(const FileHandle& Handle,
    const RF_Type::Int64 Offset, const SeekOrigin::Type Origin )
{
    SeekFile = 0;
    Dispatch();
    Assert(SeekFile != SeekFile_SystemAPIDispatcher &&
           SeekFile != 0,
           "Funtion was called and couldn't be dispatched");
    return SeekFile(Handle, Offset, Origin);
}

RF_Type::UInt64 TellFile_SystemAPIDispatcher(const FileHandle& Handle)
{
    TellFile = 0;
    Dispatch();
    Assert(TellFile != TellFile_SystemAPIDispatcher &&
           TellFile != 0,
           "Funtion was called and couldn't be dispatched");
    return TellFile(Handle);
}

RF_Type::String GenerateTempFilename_SystemAPIDispatcher(const RF_Type::String& Path)
{
    GenerateTempFilename = 0;
    Dispatch();
    Assert(GenerateTempFilename != GenerateTempFilename_SystemAPIDispatcher &&
           GenerateTempFilename != 0,
           "Funtion was called and couldn't be dispatched");
    return GenerateTempFilename(Path);
}

RF_Type::Bool CreatePreAllocatedFile_SystemAPIDispatcher(
    const RF_Type::String& Path, const RF_Type::Size FileSize)
{
    CreatePreAllocatedFile = 0;
    Dispatch();
    Assert(CreatePreAllocatedFile != CreatePreAllocatedFile_SystemAPIDispatcher &&
           CreatePreAllocatedFile != 0,
           "Funtion was called and couldn't be dispatched");
    return CreatePreAllocatedFile(Path, FileSize);
}

RF_Type::Bool CreateFile_SystemAPIDispatcher(const RF_Type::String& Path)
{
    CreateFile = 0;
    Dispatch();
    Assert(CreateFile != CreateFile_SystemAPIDispatcher &&
           CreateFile != 0,
           "Funtion was called and couldn't be dispatched");
    return CreateFile(Path);
}

RF_Type::Bool CopyFile_SystemAPIDispatcher(const Core::Types::String& From,
                                          const Core::Types::String& To)
{
    CopyFile = 0;
    Dispatch();
    Assert(CopyFile != CopyFile_SystemAPIDispatcher &&
           CopyFile != 0,
           "Funtion was called and couldn't be dispatched");
    return CopyFile(From, To);
}

RF_Type::Bool RenameFile_SystemAPIDispatcher(const Core::Types::String& From,
                                            const Core::Types::String& To)
{
    RenameFile = 0;
    Dispatch();
    Assert(RenameFile != RenameFile_SystemAPIDispatcher &&
           RenameFile != 0,
           "Funtion was called and couldn't be dispatched");
    return RenameFile(From, To);
}

RF_Type::Bool DeleteFile_SystemAPIDispatcher(const RF_Type::String& Path)
{
    DeleteFile = 0;
    Dispatch();
    Assert(DeleteFile != DeleteFile_SystemAPIDispatcher &&
           DeleteFile != 0,
           "Funtion was called and couldn't be dispatched");
    return DeleteFile(Path);
}

RF_Type::Bool DeleteDirectory_SystemAPIDispatcher(const RF_Type::String& Path)
{
    DeleteDirectory = 0;
    Dispatch();
    Assert(DeleteDirectory != DeleteDirectory_SystemAPIDispatcher &&
        DeleteDirectory != 0,
        "Funtion was called and couldn't be dispatched");
    return DeleteDirectory(Path);
}

RF_Type::String WorkingDirectory_SystemAPIDispatcher()
{
    WorkingDirectory = 0;
    Dispatch();
    Assert(WorkingDirectory != WorkingDirectory_SystemAPIDispatcher &&
           WorkingDirectory != 0,
           "Funtion was called and couldn't be dispatched");
    return WorkingDirectory();
}

RF_Type::String HomeDirectory_SystemAPIDispatcher()
{
    HomeDirectory = 0;
    Dispatch();
    Assert(HomeDirectory != HomeDirectory_SystemAPIDispatcher &&
           HomeDirectory != 0,
           "Funtion was called and couldn't be dispatched");
    return HomeDirectory();
}

RF_Type::String ApplicationDirectory_SystemAPIDispatcher()
{
    ApplicationDataDirectory = 0;
    Dispatch();
    Assert(ApplicationDirectory != ApplicationDirectory_SystemAPIDispatcher &&
           ApplicationDirectory != 0,
           "Funtion was called and couldn't be dispatched");
    return ApplicationDirectory();
}

RF_Type::String UserApplicationDataDirectory_SystemAPIDispatcher()
{
    UserApplicationDataDirectory = 0;
    Dispatch();
    Assert(UserApplicationDataDirectory != UserApplicationDataDirectory_SystemAPIDispatcher &&
           UserApplicationDataDirectory != 0,
           "Funtion was called and couldn't be dispatched");
    return UserApplicationDataDirectory();
}

RF_Type::String ApplicationDataDirectory_SystemAPIDispatcher()
{
    ApplicationDataDirectory = 0;
    Dispatch();
    Assert(ApplicationDataDirectory != ApplicationDataDirectory_SystemAPIDispatcher &&
           ApplicationDataDirectory != 0,
           "Funtion was called and couldn't be dispatched");
    return ApplicationDataDirectory();
}

RF_Type::Bool ChangeDirectory_SystemAPIDispatcher(const RF_Type::String& Destination)
{
    ChangeDirectory = 0;
    Dispatch();
    Assert(ChangeDirectory != ChangeDirectory_SystemAPIDispatcher &&
           ChangeDirectory != 0,
           "Funtion was called and couldn't be dispatched");
    return ChangeDirectory(Destination);
}

RF_Type::Bool CreateDirectory_SystemAPIDispatcher(const RF_Type::String& Path)
{
    CreateDirectory = 0;
    Dispatch();
    Assert(CreateDirectory != CreateDirectory_SystemAPIDispatcher &&
           CreateDirectory != 0,
           "Funtion was called and couldn't be dispatched");
    return CreateDirectory(Path);
}

RF_Mem::AutoPointerArray<RF_Type::String>
    DirectoryContent_SystemAPIDispatcher(const RF_Type::String& Path)
{
    DirectoryContent = 0;
    Dispatch();
    Assert(DirectoryContent != DirectoryContent_SystemAPIDispatcher &&
           DirectoryContent != 0,
           "Funtion was called and couldn't be dispatched");
    return DirectoryContent(Path);
}

FileWatcherHandle CreateFileWatcher_SystemAPIDispatcher(const RF_Type::String& Path)
{
    CreateFileWatcher = 0;
    Dispatch();
    Assert(CreateFileWatcher != CreateFileWatcher_SystemAPIDispatcher &&
           CreateFileWatcher != 0,
           "Funtion was called and couldn't be dispatched");
    return CreateFileWatcher(Path);
}

void DestroyFileWatcher_SystemAPIDispatcher(FileWatcherHandle& Handle)
{
    DestroyFileWatcher = 0;
    Dispatch();
    Assert(DestroyFileWatcher != DestroyFileWatcher_SystemAPIDispatcher &&
           DestroyFileWatcher != 0,
           "Funtion was called and couldn't be dispatched");
    DestroyFileWatcher(Handle);
}

RF_Type::Bool WaitForFileWatcher_SystemAPIDispatcher(const FileWatcherHandle& Handle, FileWatcherEvent& Event)
{
    WaitForFileWatcher = 0;
    Dispatch();
    Assert(WaitForFileWatcher != WaitForFileWatcher_SystemAPIDispatcher &&
           WaitForFileWatcher != 0,
           "Funtion was called and couldn't be dispatched");
    return WaitForFileWatcher(Handle, Event);
}

void StartFileWatcher_SystemAPIDispatcher(const FileWatcherHandle& Handle)
{
    StartFileWatcher = 0;
    Dispatch();
    Assert(StartFileWatcher != StartFileWatcher_SystemAPIDispatcher &&
           StartFileWatcher != 0,
           "Funtion was called and couldn't be dispatched");
    StartFileWatcher(Handle);
}

void StopFileWatcher_SystemAPIDispatcher(const FileWatcherHandle& Handle)
{
    StopFileWatcher = 0;
    Dispatch();
    Assert(StopFileWatcher != StopFileWatcher_SystemAPIDispatcher &&
           StopFileWatcher != 0,
           "Funtion was called and couldn't be dispatched");
    StopFileWatcher(Handle);
}

RF_Type::Bool GetFileWatcherEvent_SystemAPIDispatcher(const FileWatcherHandle& Handle, FileWatcherEvent& Event)
{
    GetFileWatcherEvent = 0;
    Dispatch();
    Assert(GetFileWatcherEvent != GetFileWatcherEvent_SystemAPIDispatcher &&
           GetFileWatcherEvent != 0,
           "Funtion was called and couldn't be dispatched");
    return GetFileWatcherEvent(Handle, Event);
}

RF_Type::Bool SystemPathToUri_SystemAPIDispatcher(const RF_Type::String& SystemPath,
    RF_IO::Uri& UriInterpretation)
{
    SystemPathToUri = 0;
    Dispatch();
    Assert(SystemPathToUri != SystemPathToUri_SystemAPIDispatcher &&
        SystemPathToUri != 0,
        "Funtion was called and couldn't be dispatched");
    return SystemPathToUri(SystemPath, UriInterpretation);
}

RF_Type::Bool UriToSystemPath_SystemAPIDispatcher(const RF_IO::Uri& Uri,
    RF_Type::String& SystemPath)
{
    UriToSystemPath = 0;
    Dispatch();
    Assert(UriToSystemPath != UriToSystemPath_SystemAPIDispatcher &&
        UriToSystemPath != 0,
        "Funtion was called and couldn't be dispatched");
    return UriToSystemPath(Uri, SystemPath);
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
RealPathCallback RFFILE::RealPath = RealPath_SystemAPIDispatcher;
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
/// Every directory created by this function will use the permissions of the parent directory.
CreateDirectoryCallback RFFILE::CreateDirectory = CreateDirectory_SystemAPIDispatcher;
DirectoryContentCallback RFFILE::DirectoryContent = DirectoryContent_SystemAPIDispatcher;
CreateFileWatcherCallback RFFILE::CreateFileWatcher = CreateFileWatcher_SystemAPIDispatcher;
DestroyFileWatcherCallback RFFILE::DestroyFileWatcher = DestroyFileWatcher_SystemAPIDispatcher;
WaitForFileWatcherCallback RFFILE::WaitForFileWatcher = WaitForFileWatcher_SystemAPIDispatcher;
StartFileWatcherCallback RFFILE::StartFileWatcher = StartFileWatcher_SystemAPIDispatcher;
StopFileWatcherCallback RFFILE::StopFileWatcher = StopFileWatcher_SystemAPIDispatcher;
GetFileWatcherEventCallback RFFILE::GetFileWatcherEvent = GetFileWatcherEvent_SystemAPIDispatcher;
SystemPathToUriCallback RFFILE::SystemPathToUri = SystemPathToUri_SystemAPIDispatcher;
UriToSystemPathCallback RFFILE::UriToSystemPath = UriToSystemPath_SystemAPIDispatcher;
DeleteDirectoryCallback RFFILE::DeleteDirectory = DeleteDirectory_SystemAPIDispatcher;

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
    result=result && RealPath != RealPath_SystemAPIDispatcher && RealPath != 0;
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
    result = result && SystemPathToUri != SystemPathToUri_SystemAPIDispatcher && SystemPathToUri != 0;
    result = result && UriToSystemPath != UriToSystemPath_SystemAPIDispatcher && UriToSystemPath != 0;
    result = result && DeleteDirectory != DeleteDirectory_SystemAPIDispatcher && DeleteDirectory != 0;
    return result;
}

void RFFILE::GetNotDispatchedFunctions(List<RF_Type::String>& Result)
{
    if (OpenFile == OpenFile_SystemAPIDispatcher || OpenFile == 0) 
        Result.AddLast(RF_Type::String("OpenFile", sizeof("OpenFile")));
    if (CloseFile == CloseFile_SystemAPIDispatcher || CloseFile == 0)
        Result.AddLast(RF_Type::String("CloseFile", sizeof("CloseFile")));
    if (MapFileIntoMemory == MapFileIntoMemory_SystemAPIDispatcher || MapFileIntoMemory == 0)
        Result.AddLast(RF_Type::String("MapFileIntoMemory", sizeof("MapFileIntoMemory")));
    if (UnmapMemoryFile == UnmapMemoryFile_SystemAPIDispatcher || UnmapMemoryFile == 0) 
        Result.AddLast(RF_Type::String("UnmapMemoryFile", sizeof("UnmapMemoryFile")));
    if (GetMemoryFile == GetMemoryFile_SystemAPIDispatcher || GetMemoryFile == 0) 
        Result.AddLast(RF_Type::String("GetMemoryFile", sizeof("GetMemoryFile")));
    if (ReadFile == ReadFile_SystemAPIDispatcher || ReadFile == 0)
        Result.AddLast(RF_Type::String("ReadFile", sizeof("ReadFile")));
    if (WriteFile == WriteFile_SystemAPIDispatcher || WriteFile == 0)
        Result.AddLast(RF_Type::String("WriteFile", sizeof("WriteFile")));
    if (FlushFile == FlushFile_SystemAPIDispatcher || FlushFile == 0)
        Result.AddLast(RF_Type::String("FlushFile", sizeof("FlushFile")));
    if (SeekFile == SeekFile_SystemAPIDispatcher || SeekFile == 0)
        Result.AddLast(RF_Type::String("SeekFile", sizeof("SeekFile")));
    if (TellFile == TellFile_SystemAPIDispatcher || TellFile == 0)
        Result.AddLast(RF_Type::String("TellFile", sizeof("TellFile")));
    if (GenerateTempFilename == GenerateTempFilename_SystemAPIDispatcher || GenerateTempFilename == 0)
        Result.AddLast(RF_Type::String("GenerateTempFilename", sizeof("GenerateTempFilename")));
    if (Access == Access_SystemAPIDispatcher || Access == 0)
        Result.AddLast(RF_Type::String("Access", sizeof("Access")));
    if (PathSeperator == PathSeperator_SystemAPIDispatcher || PathSeperator == 0)
        Result.AddLast(RF_Type::String("PathSeperator", sizeof("PathSeperator")));
    if (Seperator == Seperator_SystemAPIDispatcher || Seperator == 0)
        Result.AddLast(RF_Type::String("Seperator", sizeof("Seperator")));
    if (Stat == Stat_SystemAPIDispatcher || Stat == 0)
        Result.AddLast(RF_Type::String("Stat", sizeof("Stat")));
    if(RealPath == RealPath_SystemAPIDispatcher || RealPath == 0)
        Result.AddLast(RF_Type::String("RealPath", sizeof("RealPath")));
    if (ChangeMode == ChangeMode_SystemAPIDispatcher || ChangeMode == 0)
        Result.AddLast(RF_Type::String("ChangeMode", sizeof("ChangeMode")));
    if (CreatePreAllocatedFile == CreatePreAllocatedFile_SystemAPIDispatcher || CreatePreAllocatedFile == 0)
        Result.AddLast(RF_Type::String("CreatePreAllocatedFile", sizeof("CreatePreAllocatedFile")));
    if (CreateFile == CreateFile_SystemAPIDispatcher || CreateFile == 0)
        Result.AddLast(RF_Type::String("CreateFile", sizeof("CreateFile")));
    if (CopyFile == CopyFile_SystemAPIDispatcher || CopyFile == 0)
        Result.AddLast(RF_Type::String("CopyFile", sizeof("CopyFile")));
    if (RenameFile == RenameFile_SystemAPIDispatcher || RenameFile == 0)
        Result.AddLast(RF_Type::String("RenameFile", sizeof("RenameFile")));
    if (DeleteFile == DeleteFile_SystemAPIDispatcher || DeleteFile == 0)
        Result.AddLast(RF_Type::String("DeleteFile", sizeof("DeleteFile")));
    if (WorkingDirectory == WorkingDirectory_SystemAPIDispatcher || WorkingDirectory == 0)
        Result.AddLast(RF_Type::String("WorkingDirectory", sizeof("WorkingDirectory")));
    if (HomeDirectory == HomeDirectory_SystemAPIDispatcher || HomeDirectory == 0)
        Result.AddLast(RF_Type::String("HomeDirectory", sizeof("HomeDirectory")));
    if (ApplicationDirectory == ApplicationDirectory_SystemAPIDispatcher || ApplicationDataDirectory == 0)
        Result.AddLast(RF_Type::String("ApplicationDirectory", sizeof("ApplicationDirectory")));
    if (UserApplicationDataDirectory == UserApplicationDataDirectory_SystemAPIDispatcher || UserApplicationDataDirectory == 0)
        Result.AddLast(RF_Type::String("UserApplicationDataDirectory", sizeof("UserApplicationDataDirectory")));
    if (ApplicationDataDirectory == ApplicationDataDirectory_SystemAPIDispatcher || ApplicationDataDirectory == 0)
        Result.AddLast(RF_Type::String("ApplicationDataDirectory", sizeof("ApplicationDataDirectory")));
    if (ChangeDirectory == ChangeDirectory_SystemAPIDispatcher || ChangeDirectory == 0)
        Result.AddLast(RF_Type::String("ChangeDirectory", sizeof("ChangeDirectory")));
    if (CreateDirectory == CreateDirectory_SystemAPIDispatcher || CreateDirectory == 0)
        Result.AddLast(RF_Type::String("CreateDirectory", sizeof("CreateDirectory")));
    if (DirectoryContent == DirectoryContent_SystemAPIDispatcher || DirectoryContent == 0)
        Result.AddLast(RF_Type::String("DirectoryContent", sizeof("DirectoryContent")));
    if (CreateFileWatcher == CreateFileWatcher_SystemAPIDispatcher || CreateFileWatcher == 0)
        Result.AddLast(RF_Type::String("CreateFileWatcher", sizeof("CreateFileWatcher")));
    if (DestroyFileWatcher == DestroyFileWatcher_SystemAPIDispatcher || DestroyFileWatcher == 0)
        Result.AddLast(RF_Type::String("DestroyFileWatcher", sizeof("DestroyFileWatcher")));
    if (WaitForFileWatcher == WaitForFileWatcher_SystemAPIDispatcher || WaitForFileWatcher == 0)
        Result.AddLast(RF_Type::String("WaitForFileWatcher", sizeof("WaitForFileWatcher")));
    if (StartFileWatcher == StartFileWatcher_SystemAPIDispatcher || StartFileWatcher == 0)
        Result.AddLast(RF_Type::String("StartFileWatcher", sizeof("StartFileWatcher")));
    if (StopFileWatcher == StopFileWatcher_SystemAPIDispatcher || StopFileWatcher == 0)
        Result.AddLast(RF_Type::String("StopFileWatcher", sizeof("StopFileWatcher")));
    if (GetFileWatcherEvent == GetFileWatcherEvent_SystemAPIDispatcher || GetFileWatcherEvent == 0)
        Result.AddLast(RF_Type::String("GetFileWatcherEvent", sizeof("GetFileWatcherEvent")));
    if(SystemPathToUri == SystemPathToUri_SystemAPIDispatcher || SystemPathToUri == 0)
        Result.AddLast(RF_Type::String("SystemPathToUri", sizeof("SystemPathToUri")));
    if(UriToSystemPath == UriToSystemPath_SystemAPIDispatcher || UriToSystemPath == 0)
        Result.AddLast(RF_Type::String("UriToSystemPath", sizeof("UriToSystemPath")));
    if(DeleteDirectory == DeleteDirectory_SystemAPIDispatcher || DeleteDirectory == 0)
        Result.AddLast(RF_Type::String("DeleteDirectory", sizeof("DeleteDirectory")));
}