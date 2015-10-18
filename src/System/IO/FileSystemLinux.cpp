#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/IO/AccessMode.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/Collections/Queue.hpp"
#include "RadonFramework/IO/Log.hpp"

using namespace RadonFramework::Core::Common;
using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Collections;

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

namespace RadonFramework { namespace System { namespace IO { namespace FileSystem {

RF_Type::Bool CopyFileLinux(const RF_Type::String& From, const RF_Type::String& To)
{
    RF_Type::Bool result = false;
    int in_fd = open(From.c_str(), O_RDONLY);
    int out_fd = open(To.c_str(),O_WRONLY);
    if (in_fd && out_fd)
    {
        AutoPointer<FileStatus> stats=Stat(From);
        if (stats)
        {
            sendfile(out_fd, in_fd, 0, stats->Size);
        }
        close(in_fd);
        close(out_fd);
    }
    return result;
}

int GetNativeFlags(const FileAccessMode::Type AccessMode, const FileAccessPriority::Type Priority)
{
    static const int mode[FileAccessMode::MAX] = {O_RDONLY,
        O_WRONLY | O_CREAT | O_TRUNC,
        O_RDWR | O_CREAT | O_TRUNC};
    static const int prio[FileAccessPriority::MAX] = {0, 0, 0, O_DIRECT, 0};
    return mode[AccessMode] | prio[Priority];
}

int GetNativeAccessPriority(const FileAccessPriority::Type Priority)
{
    static const int result[FileAccessPriority::MAX] = {POSIX_FADV_SEQUENTIAL,
        POSIX_FADV_RANDOM, POSIX_FADV_NORMAL, POSIX_FADV_NORMAL};
    return result[Priority];
}

FileHandle OpenFileLinux(const RF_Type::String& Filepath, const FileAccessMode::Type AccessMode,
    const FileAccessPriority::Type AccessPriority)
{
    FileHandle result = FileHandle::Zero();
    int file = open(Filepath.c_str(), GetNativeFlags(AccessMode, AccessPriority));
    if(file != 0)
    {
        // set file access pattern advise
        posix_fadvise(file, 0, 0, GetNativeAccessPriority(AccessPriority));
        result = FileHandle::GenerateFromID(file);
    }
    return result;
}

void Dispatch_Linux()
{
    CopyFile = CopyFileLinux;
    OpenFile = OpenFileLinux;
}

} } } }