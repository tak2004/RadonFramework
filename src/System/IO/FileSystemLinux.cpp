#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/IO/AccessMode.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/Collections/Queue.hpp"
#include "RadonFramework/IO/Log.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Common;
using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Collections;
using namespace RadonFramework::System::IO::FileSystem;

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
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

void RFFILE::Dispatch()
{/*
    OpenFile=::OpenFile;
    CloseFile=::CloseFile;
    MapFileIntoMemory=::MapFileIntoMemory;
    UnmapMemoryFile=::UnmapMemoryFile;
    GetMemoryFile=::GetMemoryFile;
    ReadFile=::ReadFile;
    WriteFile=::WriteFile;
    FlushFile=::FlushFile;
    SeekFile=::SeekFile;
    TellFile=::TellFile;
    Access=::Access;
    PathSeperator=::PathSeperator;
    Seperator=::Seperator;
    Stat=::Stat;
    ChangeMode=::ChangeMode;
    CreatePreAllocatedFile=::CreatePreAllocatedFile;
    CreateFile=::CreateFile;
    CopyFile=::CopyFile;
    RenameFile=::RenameFile;
    DeleteFile=::DeleteFile;
    WorkingDirectory=::WorkingDirectory;
    HomeDirectory=::HomeDirectory;
    ApplicationDirectory=::ApplicationDirectory;
    UserApplicationDataDirectory = ::UserApplicationDataDirectory;
    ApplicationDataDirectory = ::ApplicationDataDirectory;
    ChangeDirectory=::ChangeDirectory;
    CreateDirectory=::CreateDirectory;
    DirectoryContent=::DirectoryContent;
    CreateFileWatcher=::CreateFileWatcher;
    DestroyFileWatcher=::DestroyFileWatcher;
    WaitForFileWatcher=::WaitForFileWatcher;
    StartFileWatcher=::StartFileWatcher;
    StopFileWatcher=::StopFileWatcher;
    GetFileWatcherEvent=::GetFileWatcherEvent;
    GenerateTempFilename=::GenerateTempFilename;*/
}