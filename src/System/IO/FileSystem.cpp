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

#if defined(RF_LINUX)
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>

inline Bool AccessImplementation(const String& Path, const AccessMode::Type Mode)
{
    int modes[AccessMode::MAX]={-1, F_OK, R_OK, F_OK|R_OK, W_OK, W_OK|F_OK, 
                                W_OK|R_OK, W_OK|R_OK|F_OK, X_OK, X_OK|F_OK,
                                X_OK|R_OK, X_OK|R_OK|F_OK, X_OK|W_OK,
                                X_OK|W_OK|F_OK, X_OK|W_OK|R_OK, X_OK|W_OK|R_OK|F_OK};
    Assert(modes[Mode]>=0 && modes[Mode]<=X_OK|W_OK|R_OK|F_OK,"Invalid argument.");
    return access(Path.c_str(),modes[Mode]);
}

inline AutoPointer<FileStatus> StatImplementation(const String& Path)
{
    AutoPointer<FileStatus> result;
    struct stat buf;
    if (stat(Path.c_str(),&buf)==0)
    {
        result=AutoPointer<FileStatus>(new FileStatus);
        result->Size=buf.st_size;
        result->CreateionTimestamp=buf.st_ctime;
        result->LastAccessTimestamp=buf.st_atime;
        result->LastModificationTimestamp=buf.st_mtime;
        result->IsDirectory=(buf.st_mode & S_IFDIR)!=0;
        result->IsHidden=false;//some linux distributions hide on '.' some on '~' no restrictive rule.
    }
    return result;
}

Bool ChangeModeImplementation( const String& Path, const AccessMode::Type NewMode )
{
    int modes[AccessMode::MAX]={-1, F_OK, R_OK, F_OK|R_OK, W_OK, W_OK|F_OK, 
                                W_OK|R_OK, W_OK|R_OK|F_OK, X_OK, X_OK|F_OK,
                                X_OK|R_OK, X_OK|R_OK|F_OK, X_OK|W_OK,
                                X_OK|W_OK|F_OK, X_OK|W_OK|R_OK, X_OK|W_OK|R_OK|F_OK};
    return chmod(Path.c_str(),modes[NewMode])==0;
}

Bool CreatePreAllocatedFileImplementation(const String& Path, const Size FileSize)
{
    Bool result=false;
    int hFile=open(Path.c_str(),O_CREAT);
    if (hFile)
    {
        result=posix_fallocate(hFile,0,FileSize)==0;
        close(hFile);
    }
    return result;
}

String WorkingDirectoryImplementation()
{
    long size = pathconf(".", _PC_PATH_MAX);
    AutoPointerArray<char> buffer(new char[size],size);
    String result;
    if (getcwd(buffer.Get(),size))
        result=String(buffer.Release().Ptr, DataManagment::TransfereOwnership);
    return result;
}

String HomeDirectoryImplementation()
{
    return String(getenv ("HOME"));
}

String ApplicationDirectoryImplementation()
{
    char buffer[BUFSIZ];
    readlink("/proc/self/exe", buffer, BUFSIZ);
    return String(buffer);
}

Bool ChangeDirectoryImplementation( const String& Destination ) 
{
    return chdir(Destination.c_str())==0;
}

Bool CreateDirectoryImplementation( const String& Path ) 
{    
    return mkdir(Path.c_str(),S_IRWXU | S_IRWXG | S_IRWXO)==0;
}

AutoPointerArray<String> DirectoryContentImplementation(const String& Path) 
{
    AutoPointerArray<String> result;
    List<String> list;
    DIR* dir=0;
    dir=opendir(Path.c_str());
    if (dir)
    {
        struct dirent* direntry=0;
        while ((direntry=readdir(dir))!=0)
            list.AddLast(String(direntry->d_name));
        closedir(dir);
        result=AutoPointerArray<String>(new String[list.Size()],list.Size());
        for (UInt32 i=0;i<result.Count();++i)
            result[i].Swap(list[i]);
    }    
    return result;
}

Bool CreateFileImplementation(const String& Path)
{
    Bool result=false;
    FILE* f=fopen(Path.c_str(),"w");
    if (f!=0)
    {
        fclose(f);
        result=true;
    }
    return result;
}

Bool CopyFileImplementation(const String& From, const String& To)
{
    Bool result=false;
    int in_fd = open(From.c_str(), O_RDONLY);
    posix_fadvise(in_fd, 0,0,POSIX_FADV_SEQUENTIAL);
    int out_fd=open(To.c_str(),O_WRONLY);
    if (in_fd && out_fd)
    {
        AutoPointer<FileStatus> stats=StatImplementation(From);
        if (stats)
        {
            result=posix_fallocate(out_fd,0,stats->Size);
            char buf[8192];
            while (result) 
            {
                ssize_t bytes = read(in_fd, &buf[0], sizeof(buf));
                if (bytes==0)
                    break;
                if (write(out_fd, &buf[0], bytes) != bytes)
                    break;
            }
            result&=true;
        }
        close(in_fd);
        close(out_fd);
    }
    return result;
}
#endif

OpenFileCallback RadonFramework::System::IO::FileSystem::OpenFile=0;
CloseFileCallback RadonFramework::System::IO::FileSystem::CloseFile=0;
MapFileIntoMemoryCallback RadonFramework::System::IO::FileSystem::MapFileIntoMemory=0;
UnmapMemoryFileCallback RadonFramework::System::IO::FileSystem::UnmapMemoryFile=0;
GetMemoryFileCallback RadonFramework::System::IO::FileSystem::GetMemoryFile=0;
ReadFileCallback RadonFramework::System::IO::FileSystem::ReadFile=0;
WriteFileCallback RadonFramework::System::IO::FileSystem::WriteFile=0;
FlushFileCallback RadonFramework::System::IO::FileSystem::FlushFile=0;
SeekFileCallback RadonFramework::System::IO::FileSystem::SeekFile=0;
TellFileCallback RadonFramework::System::IO::FileSystem::TellFile=0;
GenerateTempFilenameCallback RadonFramework::System::IO::FileSystem::GenerateTempFilename=0;
AccessCallback RadonFramework::System::IO::FileSystem::Access=0;
PathSeperatorCallback RadonFramework::System::IO::FileSystem::PathSeperator=0;
SeperatorCallback RadonFramework::System::IO::FileSystem::Seperator=0;
StatCallback RadonFramework::System::IO::FileSystem::Stat=0;
ChangeModeCallback RadonFramework::System::IO::FileSystem::ChangeMode=0;
CreatePreAllocatedFileCallback RadonFramework::System::IO::FileSystem::CreatePreAllocatedFile=0;
CreateFileCallback RadonFramework::System::IO::FileSystem::CreateFile=0;
CopyFileCallback RadonFramework::System::IO::FileSystem::CopyFile=0;
RenameFileCallback RadonFramework::System::IO::FileSystem::RenameFile=0;
DeleteFileCallback RadonFramework::System::IO::FileSystem::DeleteFile=0;
WorkingDirectoryCallback RadonFramework::System::IO::FileSystem::WorkingDirectory=0;
HomeDirectoryCallback RadonFramework::System::IO::FileSystem::HomeDirectory=0;
ApplicationDirectoryCallback RadonFramework::System::IO::FileSystem::ApplicationDirectory=0;
ApplicationDataDirectoryCallback RadonFramework::System::IO::FileSystem::UserApplicationDataDirectory = 0;
UserApplicationDataDirectoryCallback RadonFramework::System::IO::FileSystem::ApplicationDataDirectory = 0;
ChangeDirectoryCallback RadonFramework::System::IO::FileSystem::ChangeDirectory=0;
CreateDirectoryCallback RadonFramework::System::IO::FileSystem::CreateDirectory=0;
DirectoryContentCallback RadonFramework::System::IO::FileSystem::DirectoryContent=0;
CreateFileWatcherCallback RadonFramework::System::IO::FileSystem::CreateFileWatcher=0;
DestroyFileWatcherCallback RadonFramework::System::IO::FileSystem::DestroyFileWatcher=0;
WaitForFileWatcherCallback RadonFramework::System::IO::FileSystem::WaitForFileWatcher=0;
StartFileWatcherCallback RadonFramework::System::IO::FileSystem::StartFileWatcher=0;
StopFileWatcherCallback RadonFramework::System::IO::FileSystem::StopFileWatcher=0;
GetFileWatcherEventCallback RadonFramework::System::IO::FileSystem::GetFileWatcherEvent=0;

Bool RadonFramework::System::IO::FileSystem::IsSuccessfullyDispatched()
{
    Bool result=true;
    result=result && OpenFile!=0;
    result=result && CloseFile!=0;
    result=result && MapFileIntoMemory!=0;
    result=result && UnmapMemoryFile!=0;
    result=result && GetMemoryFile!=0;
    result=result && ReadFile!=0;
    result=result && WriteFile!=0;
    result=result && FlushFile!=0;
    result=result && SeekFile!=0;
    result=result && TellFile!=0;
    result=result && GenerateTempFilename!=0;
    result=result && Access!=0;
    result=result && PathSeperator!=0;
    result=result && Seperator!=0;
    result=result && Stat!=0;
    result=result && ChangeMode!=0;
    result=result && CreatePreAllocatedFile!=0;
    result=result && CreateFile!=0;
    result=result && CopyFile!=0;
    result=result && RenameFile!=0;
    result=result && DeleteFile!=0;
    result=result && WorkingDirectory!=0;
    result=result && HomeDirectory!=0;
    result=result && ApplicationDirectory!=0;
    result=result && UserApplicationDataDirectory!=0;
    result=result && ApplicationDataDirectory != 0;
    result=result && ChangeDirectory!=0;
    result=result && CreateDirectory!=0;
    result=result && DirectoryContent!=0;
    result=result && CreateFileWatcher!=0;
    result=result && DestroyFileWatcher!=0;
    result=result && WaitForFileWatcher!=0;
    result=result && StartFileWatcher!=0;
    result=result && StopFileWatcher!=0;
    result=result && GetFileWatcherEvent!=0;
    return result;
}

void RadonFramework::System::IO::FileSystem::GetNotDispatchedFunctions(List<RFTYPE::String>& Result)
{
    if (OpenFile==0) 
        Result.AddLast("OpenFile");
    if (CloseFile==0) 
        Result.AddLast("CloseFile");
    if (MapFileIntoMemory==0) 
        Result.AddLast("MapFileIntoMemory");
    if (UnmapMemoryFile==0) 
        Result.AddLast("UnmapMemoryFile");
    if (GetMemoryFile==0) 
        Result.AddLast("GetMemoryFile");
    if (ReadFile==0)
        Result.AddLast("ReadFile");
    if (WriteFile==0)
        Result.AddLast("WriteFile");
    if (FlushFile==0)
        Result.AddLast("FlushFile");
    if (SeekFile==0)
        Result.AddLast("SeekFile");
    if (TellFile==0)
        Result.AddLast("TellFile");
    if (GenerateTempFilename==0)
        Result.AddLast("GenerateTempFilename");
    if (Access==0)
        Result.AddLast("Access");
    if (PathSeperator==0)
        Result.AddLast("PathSeperator");
    if (Seperator==0)
        Result.AddLast("Seperator");
    if (Stat==0)
        Result.AddLast("Stat");
    if (ChangeMode==0)
        Result.AddLast("ChangeMode");
    if (CreatePreAllocatedFile==0)
        Result.AddLast("CreatePreAllocatedFile");
    if (CreateFile==0)
        Result.AddLast("CreateFile");
    if (CopyFile==0)
        Result.AddLast("CopyFile");
    if (RenameFile==0)
        Result.AddLast("RenameFile");
    if (DeleteFile==0)
        Result.AddLast("DeleteFile");
    if (WorkingDirectory==0)
        Result.AddLast("WorkingDirectory");
    if (HomeDirectory==0)
        Result.AddLast("HomeDirectory");
    if (ApplicationDirectory==0)
        Result.AddLast("ApplicationDirectory");
    if (UserApplicationDataDirectory == 0)
        Result.AddLast("UserApplicationDataDirectory");
    if (ApplicationDataDirectory == 0)
        Result.AddLast("ApplicationDataDirectory");
    if (ChangeDirectory==0)
        Result.AddLast("ChangeDirectory");
    if (CreateDirectory==0)
        Result.AddLast("CreateDirectory");
    if (DirectoryContent==0)
        Result.AddLast("DirectoryContent");
    if (CreateFileWatcher==0)
        Result.AddLast("CreateFileWatcher");
    if (DestroyFileWatcher==0)
        Result.AddLast("DestroyFileWatcher");
    if (WaitForFileWatcher==0)
        Result.AddLast("WaitForFileWatcher");
    if (StartFileWatcher==0)
        Result.AddLast("StartFileWatcher");
    if (StopFileWatcher==0)
        Result.AddLast("StopFileWatcher");
    if (GetFileWatcherEvent==0)
        Result.AddLast("GetFileWatcherEvent");
}