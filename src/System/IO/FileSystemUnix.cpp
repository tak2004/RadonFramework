#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/IO/AccessMode.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/Collections/Queue.hpp"
#include "RadonFramework/IO/Log.hpp"
#include "RadonFramework/IO/Uri.hpp"

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
#include <sys/mman.h>
#include <errno.h>

namespace RadonFramework { namespace System { namespace IO { namespace FileSystem {

namespace Unix {

inline RF_Type::Bool Access(const RF_Type::String& Path, const AccessMode::Type Mode)
{ 
    int modes[AccessMode::MAX] = {-1, F_OK, R_OK, F_OK | R_OK, W_OK, W_OK | F_OK,
                                W_OK | R_OK, W_OK | R_OK | F_OK, X_OK, X_OK | F_OK,
                                X_OK | R_OK, X_OK | R_OK | F_OK, X_OK | W_OK,
                                X_OK | W_OK | F_OK, X_OK | W_OK | R_OK, X_OK | W_OK | R_OK | F_OK};
    Assert(modes[Mode] >= 0 && modes[Mode] <= X_OK | W_OK | R_OK | F_OK, "Invalid argument.");
    return access(Path.c_str(), modes[Mode])==0;
}

inline AutoPointer<FileStatus> Stat(const RF_Type::String& Path)
{
    AutoPointer<FileStatus> result;
    struct stat buf;
    if(stat(Path.c_str(), &buf) == 0)
    {
        result = AutoPointer<FileStatus>(new FileStatus);
        result->Size = buf.st_size;
        result->CreateionTimestamp = buf.st_ctime;
        result->LastAccessTimestamp = buf.st_atime;
        result->LastModificationTimestamp = buf.st_mtime;
        result->IsDirectory = (buf.st_mode & S_IFDIR) != 0;
        result->IsHidden = false;//some linux distributions hide on '.' some on '~' no restrictive rule.
    }
    return result;
}

void RealPath(const RF_Type::String& Path, RF_Type::String& ResolvedPath)
{
    char out[PATH_MAX];
    char* resolvedPath = realpath(Path.c_str(), out);
    if(resolvedPath == out || 
       (resolvedPath == 0 && errno == ENOENT))
    {
        ResolvedPath = RF_Type::String(out, PATH_MAX);
    }
}

RF_Type::Bool ChangeMode(const RF_Type::String& Path, const AccessMode::Type NewMode)
{
    int modes[AccessMode::MAX] = {-1, F_OK, R_OK, F_OK | R_OK, W_OK, W_OK | F_OK,
                                W_OK | R_OK, W_OK | R_OK | F_OK, X_OK, X_OK | F_OK,
                                X_OK | R_OK, X_OK | R_OK | F_OK, X_OK | W_OK,
                                X_OK | W_OK | F_OK, X_OK | W_OK | R_OK, X_OK | W_OK | R_OK | F_OK};
    return chmod(Path.c_str(), modes[NewMode]) == 0;
}

RF_Type::Bool CreatePreAllocatedFile(const RF_Type::String& Path, const RF_Type::Size FileSize)
{
    RF_Type::Bool result = false;
    int fd = open(Path.c_str(), O_CREAT);
    if(fd)
    {
#ifdef RF_HAVE_POSIX_FALLOCATE
        result = posix_fallocate(fd, 0, FileSize) == 0;
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

RF_Type::String WorkingDirectory()
{
    long size = pathconf(".", _PC_PATH_MAX);
    AutoPointerArray<char> buffer(size);
    RF_Type::String result;
    if(getcwd(buffer.Get(), size))
        result = RF_Type::String(buffer.Release().Ptr, size, DataManagment::TransfereOwnership);
    return result;
}

RF_Type::String HomeDirectory()
{
    return RF_Type::String::UnsafeStringCreation(getenv("HOME"));
}

RF_Type::String ApplicationDirectory()
{
    char buffer[BUFSIZ];
    readlink("/proc/self/exe", buffer, BUFSIZ);
    return RF_Type::String(buffer);
}

RF_Type::Bool ChangeDirectory(const RF_Type::String& Destination)
{
    return chdir(Destination.c_str()) == 0;
}

RF_Type::Bool CreateDirectory(const RF_Type::String& Path)
{
    mode_t mode = ACCESSPERMS;
    struct stat buf;

    if(stat((Path + "/..").c_str(), &buf) == 0)
    {
        mode = mode & buf.st_mode;
    }
    return mkdir(Path.c_str(), mode) == 0 || errno == EEXIST;
}

AutoPointerArray<RF_Type::String> DirectoryContent(const RF_Type::String& Path)
{
    AutoPointerArray<RF_Type::String> result;
    List<RF_Type::String> list;
    DIR* dir = 0;
    dir = opendir(Path.c_str());
    if(dir)
    {
        struct dirent* direntry = 0;
        while((direntry = readdir(dir)) != 0)
            list.AddLast(RF_Type::String(direntry->d_name));
        closedir(dir);
        result = AutoPointerArray<RF_Type::String>(list.Count());
        for(RF_Type::UInt32 i = 0; i < result.Count(); ++i)
            result[i].Swap(list[i]);
    }
    return result;
}

RF_Type::Bool CreateFile(const RF_Type::String& Path)
{
    RF_Type::Bool result = false;
    FILE* f = fopen(Path.c_str(), "w");
    if(f != 0)
    {
        fclose(f);
        result = true;
    }
    return result;
}

RF_Type::Bool CopyFile(const RF_Type::String& From, const RF_Type::String& To)
{
    RF_Type::Bool result = false;
    int in_fd = open(From.c_str(), O_RDONLY);
#ifdef RF_HAVE_POSIX_FADVISE
    posix_fadvise(in_fd, 0, 0, POSIX_FADV_SEQUENTIAL);
#else
#ifdef RF_HAVE_FREADAHEAD
    fcntl(in_fd, F_READAHEAD, 1);
#endif
#endif
    if(in_fd)
    {
        AutoPointer<FileStatus> stats = ::Stat(From);
        if(stats)
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

FileHandle OpenFile(const RF_Type::String& Filepath, const FileAccessMode::Type AccessMode,
    const FileAccessPriority::Type AccessPriority)
{
    FileHandle result = FileHandle::Zero();
    int file = open(Filepath.c_str(), GetNativeFlags(AccessMode), S_IRWXU | S_IRWXG | S_IRWXO);
    if(file != 0)
    {
#ifdef RF_HAVE_POSIX_FADVISE
        // set file access pattern advise
        posix_fadvise(file, 0, 0, GetNativeAccessPriority(AccessPriority));
#endif
        result = FileHandle::GenerateFromID(file);
    }
    return result;
}

RF_Type::Bool CloseFile(FileHandle& Handle)
{
    int file = static_cast<int>(Handle.GetID());
    RF_Type::Bool result = close(file) == 0;
    Handle = FileHandle::Zero();
    return result;
}

MemoryMappingHandle MapFileIntoMemory(const FileHandle& Handle)
{
    MemoryMappingHandle result;
    int file = static_cast<int>(Handle.GetID());
    if(file != 0)
    {
        void* mapping = mmap(0, 0, PROT_READ | PROT_WRITE, MAP_FILE | MAP_SHARED, file, 0);
        if(mapping)
        {
            result = MemoryMappingHandle::GenerateFromPointer(mapping);
        }
    }
    return result;
}

RF_Type::Bool UnmapMemoryFile(MemoryMappingHandle& Handle)
{
    RF_Type::Bool result = false;
    if(Handle.GetPointer() != 0)
    {
        munmap(Handle.GetPointer(), 0);
    }
    return result;
}

void* GetMemoryFile(const MemoryMappingHandle& Handle)
{
    return Handle.GetPointer();
}

RF_Type::Bool ReadFile(const FileHandle& Handle, RF_Type::UInt8* Buffer, 
    const RF_Type::UInt64 ReadBytes, RF_Type::UInt64& BytesRead)
{
    int file = static_cast<int>(Handle.GetID());
    BytesRead = read(file, Buffer, ReadBytes);
    return ReadBytes == BytesRead;
}

RF_Type::Bool WriteFile(const FileHandle& Handle, const RF_Type::UInt8* Buffer, 
    const RF_Type::UInt64 WriteBytes, RF_Type::UInt64& BytesWritten)
{
    int file = static_cast<int>(Handle.GetID());
    return write(file, Buffer, WriteBytes) > 0;
}

RF_Type::Bool FlushFile(const FileHandle& Handle)
{
    int file = static_cast<int>(Handle.GetID());
    return fsync(file) == 0;
}

RF_Type::UInt64 SeekFile(const FileHandle& Handle, const RF_Type::Int64 Offset, 
    const SeekOrigin::Type Origin)
{
    static const int NativeSeek[SeekOrigin::MAX] = {SEEK_SET, SEEK_CUR, SEEK_END};
    int file = static_cast<int>(Handle.GetID());
    return lseek(file, Offset, NativeSeek[Origin]);
}

RF_Type::UInt64 TellFile(const FileHandle& Handle)
{
    int file = static_cast<int>(Handle.GetID());
    return lseek(file, 0, SEEK_CUR);
}

RF_Type::String PathSeperator()
{
    static const RF_Type::String result(";");
    return result;
}

RF_Type::String Seperator()
{
    static const RF_Type::String result("/");
    return result;
}

RF_Type::Bool DeleteFile(const RF_Type::String& Path)
{
    return unlink(Path.c_str()) == 0;
}

RF_Type::Bool DeleteDirectory(const RF_Type::String& Path)
{
    return rmdir(Path.c_str()) == 0;
}

RF_Type::Bool RenameFile(const RF_Type::String& From, const RF_Type::String& To)
{
    return rename(From.c_str(), To.c_str()) == 0;
}

RF_Type::Bool SystemPathToUri(const RF_Type::String& SystemPath,
    RF_IO::Uri& UriInterpretation)
{
    RF_Type::String uriPath = "file://"_rfs + SystemPath;
    RF_IO::Uri uri1(uriPath, RF_IO::UriKind::Absolute);
    UriInterpretation = uri1;
    return true;
}

RF_Type::Bool UriToSystemPath(const RF_IO::Uri& Uri,
    RF_Type::String& SystemPath)
{
    SystemPath = Uri.GetComponents(RF_IO::UriComponents::Path);
    return true;
}

}

void Dispatch()
{
    OpenFile = Unix::OpenFile;
    CloseFile = Unix::CloseFile;
    MapFileIntoMemory = Unix::MapFileIntoMemory;
    UnmapMemoryFile = Unix::UnmapMemoryFile;
    GetMemoryFile = Unix::GetMemoryFile;
    ReadFile = Unix::ReadFile;
    WriteFile = Unix::WriteFile;
    FlushFile = Unix::FlushFile;
    SeekFile = Unix::SeekFile;
    TellFile = Unix::TellFile;
    Access = Unix::Access;
    PathSeperator = Unix::PathSeperator;
    Seperator = Unix::Seperator;
    Stat = Unix::Stat;
    RealPath = Unix::RealPath;
    ChangeMode = Unix::ChangeMode;
    CreatePreAllocatedFile = Unix::CreatePreAllocatedFile;
    CreateFile = Unix::CreateFile;
    CopyFile = Unix::CopyFile;
    RenameFile = Unix::RenameFile;
    DeleteFile = Unix::DeleteFile;
    WorkingDirectory = Unix::WorkingDirectory;
    HomeDirectory = Unix::HomeDirectory;
    ApplicationDirectory = Unix::ApplicationDirectory;
    ChangeDirectory = Unix::ChangeDirectory;
    CreateDirectory = Unix::CreateDirectory;
    DirectoryContent = Unix::DirectoryContent;
    SystemPathToUri = Unix::SystemPathToUri;
    UriToSystemPath = Unix::UriToSystemPath;
    DeleteDirectory = Unix::DeleteDirectory;

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

} } } }