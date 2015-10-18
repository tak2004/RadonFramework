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
#include <sys/param.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

inline Bool AccessUnix(const String& Path, const AccessMode::Type Mode)
{
    int modes[AccessMode::MAX]={-1, F_OK, R_OK, F_OK|R_OK, W_OK, W_OK|F_OK, 
                                W_OK|R_OK, W_OK|R_OK|F_OK, X_OK, X_OK|F_OK,
                                X_OK|R_OK, X_OK|R_OK|F_OK, X_OK|W_OK,
                                X_OK|W_OK|F_OK, X_OK|W_OK|R_OK, X_OK|W_OK|R_OK|F_OK};
    Assert(modes[Mode]>=0 && modes[Mode]<=X_OK|W_OK|R_OK|F_OK,"Invalid argument.");
    return access(Path.c_str(),modes[Mode]);
}

inline AutoPointer<FileStatus> StatUnix(const String& Path)
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

void RealPathUnix(const String& Path, String& ResolvedPath)
{
    char* resolvedPath = realpath(Path.c_str(), 0);
    if(resolvedPath)
    {
        ResolvedPath = String(resolvedPath, strlen(resolvedPath), RF_Common::DataManagment::TransfereOwnership);
    }    
}

Bool ChangeModeUnix( const String& Path, const AccessMode::Type NewMode )
{
    int modes[AccessMode::MAX]={-1, F_OK, R_OK, F_OK|R_OK, W_OK, W_OK|F_OK, 
                                W_OK|R_OK, W_OK|R_OK|F_OK, X_OK, X_OK|F_OK,
                                X_OK|R_OK, X_OK|R_OK|F_OK, X_OK|W_OK,
                                X_OK|W_OK|F_OK, X_OK|W_OK|R_OK, X_OK|W_OK|R_OK|F_OK};
    return chmod(Path.c_str(),modes[NewMode])==0;
}

Bool CreatePreAllocatedFileUnix(const String& Path, const Size FileSize)
{
    Bool result = false;
    int fd = open(Path.c_str(), O_CREAT);
    if(fd)
    {
#ifdef RF_HAVE_POSIX_FALLOCATE
        result=posix_fallocate(fd,0,FileSize)==0;
#else
        struct stat buf;
        if(!fstat(fd, &buf))
        {
            if(buf.st_size < FileSize && buf.st_blksize && !ftruncate(fd, FileSize))
            {
                const int block = buf.st_blksize;
                int written;
                RF_Type::Int64 writeBytes = ((buf.st_size + 2 * block - 1) / block)*block - 1;
                do
                {
                    written = 0;
                    if(lseek(fd, writeBytes, SEEK_SET) == writeBytes)
                        written = write(fd, "", 1);
                    writeBytes += block;
                } while(written == 1 && writeBytes < FileSize);
                result = written == 1;
            }
        }
#endif
        close(fd);
    }
    return result;
}

String WorkingDirectoryUnix()
{
    long size = pathconf(".", _PC_PATH_MAX);
    AutoPointerArray<char> buffer(size);
    String result;
    if (getcwd(buffer.Get(),size))
        result=String(buffer.Release().Ptr,size, DataManagment::TransfereOwnership);
    return result;
}

String HomeDirectoryUnix()
{
    return String::UnsafeStringCreation(getenv ("HOME"));
}

String ApplicationDirectoryUnix()
{
    char buffer[BUFSIZ];
    readlink("/proc/self/exe", buffer, BUFSIZ);
    return String(buffer);
}

Bool ChangeDirectoryUnix( const String& Destination ) 
{
    return chdir(Destination.c_str())==0;
}

Bool CreateDirectoryUnix( const String& Path ) 
{    
    return mkdir(Path.c_str(),S_IRWXU | S_IRWXG | S_IRWXO)==0;
}

AutoPointerArray<String> DirectoryContentUnix(const String& Path) 
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
        result=AutoPointerArray<String>(list.Count());
        for (UInt32 i=0;i<result.Count();++i)
            result[i].Swap(list[i]);
    }    
    return result;
}

Bool CreateFileUnix(const String& Path)
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

Bool CopyFileUnix(const String& From, const String& To)
{
    Bool result=false;
    int in_fd = open(From.c_str(), O_RDONLY);
#ifdef RF_HAVE_POSIX_FADVISE
    posix_fadvise(in_fd, 0,0,POSIX_FADV_SEQUENTIAL);
#else
    fcntl(in_fd, F_READAHEAD, 1);
#endif
    if (in_fd)
    {
        AutoPointer<FileStatus> stats=::Stat(From);
        if (stats)
        {
            CreatePreAllocatedFile(To, stats->Size);
            int out_fd = open(To.c_str(), O_WRONLY);
            if(out_fd)
            {
                char buf[8192];
                while(result)
                {
                    size_t bytes = read(in_fd, &buf[0], sizeof(buf));
                    if(bytes == 0)
                        break;
                    if(write(out_fd, &buf[0], bytes) != bytes)
                        break;
                }
                result &= true;
            }
            close(out_fd);
        }
        close(in_fd);
    }
    return result;
}

int GetNativeFlags(const FileAccessMode::Type AccessMode)
{
    static const int mode[FileAccessMode::MAX] = {O_RDONLY,
        O_WRONLY | O_CREAT | O_TRUNC,
        O_RDWR | O_CREAT | O_TRUNC};
    return mode[AccessMode];
}

#ifdef RF_HAVE_POSIX_FADVISE
int GetNativeAccessPriority(const FileAccessPriority::Type Priority)
{
    static const int result[FileAccessPriority::MAX] = {POSIX_FADV_SEQUENTIAL,
        POSIX_FADV_RANDOM, POSIX_FADV_NORMAL, POSIX_FADV_NORMAL};
    return result[Priority];
}
#endif

FileHandle OpenFileUnix(const RF_Type::String& Filepath, const FileAccessMode::Type AccessMode,
                    const FileAccessPriority::Type AccessPriority)
{
    FileHandle result = FileHandle::Zero();
    int file = open(Filepath.c_str(), GetNativeFlags(AccessMode));
    if (file != 0)
    {
#ifdef RF_HAVE_POSIX_FADVISE
        // set file access pattern advise
        posix_fadvise(file, 0, 0, GetNativeAccessPriority(AccessPriority));
#endif
        result = FileHandle::GenerateFromID(file);
    }
    return result;
}

RF_Type::Bool CloseFileUnix(FileHandle& Handle)
{
    int file = static_cast<int>(Handle.GetID());
    Bool result = close(file) == 0;
    Handle = FileHandle::Zero();
    return result;
}

Bool ReadFileUnix(const FileHandle& Handle, UInt8* Buffer, const UInt64 ReadBytes, UInt64& BytesRead)
{
    int file = static_cast<int>(Handle.GetID());
    BytesRead = read(file, Buffer, ReadBytes);
    return ReadBytes == BytesRead;
}

Bool WriteFileUnix(const FileHandle& Handle, const UInt8* Buffer, const UInt64 WriteBytes, UInt64& BytesWritten)
{
    int file = static_cast<int>(Handle.GetID());
    return write(file, Buffer, WriteBytes) > 0;
}

Bool FlushFileUnix(const FileHandle& Handle)
{
    int file = static_cast<int>(Handle.GetID());
    return fsync(file) == 0;
}

UInt64 SeekFileUnix(const FileHandle& Handle, const Int64 Offset, const SeekOrigin::Type Origin)
{
    static const int NativeSeek[SeekOrigin::MAX] = {SEEK_SET, SEEK_CUR, SEEK_END };
    int file = static_cast<int>(Handle.GetID());
    return lseek(file, Offset, NativeSeek[Origin]);
}

UInt64 TellFileUnix(const FileHandle& Handle)
{
    int file = static_cast<int>(Handle.GetID());
    return lseek(file, 0, SEEK_CUR);
}

RF_Type::String PathSeperatorUnix()
{
    static const RF_Type::String result(";");
    return result;
}

RF_Type::String SeperatorUnix()
{
    static const RF_Type::String result("/");
    return result;
}

Bool DeleteFileUnix(const String& Path)
{
    return unlink(Path.c_str()) == 0;
}

Bool RenameFileUnix(const String& From, const String& To)
{
    return rename(From.c_str(), To.c_str()) == 0;
}

void RFFILE::Dispatch()
{
    OpenFile = OpenFileUnix;
    CloseFile = CloseFileUnix;
    ReadFile = ReadFileUnix;
    WriteFile = WriteFileUnix;
    FlushFile = FlushFileUnix;
    SeekFile = SeekFileUnix;
    TellFile = TellFileUnix;
    Access = AccessUnix;
    PathSeperator = PathSeperatorUnix;
    Seperator = SeperatorUnix;
    Stat = StatUnix;
    RealPath = RealPathUnix;
    ChangeMode = ChangeModeUnix;
    CreatePreAllocatedFile = CreatePreAllocatedFileUnix;
    CreateFile = CreateFileUnix;
    CopyFile = CopyFileUnix;
    RenameFile = RenameFileUnix;
    DeleteFile = DeleteFileUnix;
    WorkingDirectory = WorkingDirectoryUnix;
    HomeDirectory = HomeDirectoryUnix;
    ApplicationDirectory = ApplicationDirectoryUnix;
    ChangeDirectory = ChangeDirectoryUnix;
    CreateDirectory = CreateDirectoryUnix;
    DirectoryContent = DirectoryContentUnix;

#ifdef RF_LINUX
    extern void Dispatch_Linux();
    Dispatch_Linux();
#else
#ifdef RF_OSX
    extern void Dispatch_OSX();
    Dispatch_OSX();
#endif
#endif
}