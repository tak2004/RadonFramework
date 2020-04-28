#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/IO/AccessMode.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/Collections/Queue.hpp"
#include "RadonFramework/IO/Log.hpp"
#include "RadonFramework/IO/Uri.hpp"
#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <windows.h>
#include <direct.h>
#include <Shlobj.h>

#ifdef CreateDirectory
#undef CreateDirectory
#endif
#ifdef CopyFile
#undef CopyFile
#endif
#ifdef CreateFile
#undef CreateFile
#endif
#ifdef DeleteFile
#undef DeleteFile
#endif

namespace RadonFramework::System::IO::FileSystem::Windows {

DWORD GetNativeAccessMode(FileAccessMode::Type AccessMode)
{
    static DWORD result[FileAccessMode::MAX]={
        GENERIC_READ, GENERIC_WRITE, GENERIC_WRITE | GENERIC_READ
    };
    return result[AccessMode];
}

DWORD GetNativePriority(FileAccessPriority::Type AccessPriority)
{
    static DWORD result[FileAccessPriority::MAX] = {FILE_ATTRIBUTE_NORMAL,
        FILE_FLAG_SEQUENTIAL_SCAN, FILE_FLAG_RANDOM_ACCESS, FILE_FLAG_WRITE_THROUGH, 
        FILE_ATTRIBUTE_NORMAL
    };
    return result[AccessPriority];
}

DWORD GetNativeCreationDisposition(FileAccessMode::Type AccessMode)
{
    static DWORD result[FileAccessMode::MAX] = {
        OPEN_EXISTING, CREATE_ALWAYS, OPEN_ALWAYS
    };
    return result[AccessMode];
}

DWORD GetNativeSeekOrigin(RF_IO::SeekOrigin::Type Origin)
{
    static DWORD result[RF_IO::SeekOrigin::MAX]={
        FILE_BEGIN, FILE_CURRENT, FILE_END
    };
    return result[Origin];
}

FileHandle OpenFile(const RF_Type::String& FilePath, 
    const FileAccessMode::Type AccessMode,
    const FileAccessPriority::Type AccessPriority)
{
    FileHandle result = FileHandle::Zero();
    HANDLE file = CreateFileA(FilePath.c_str(), GetNativeAccessMode(AccessMode), 
        0, 0, GetNativeCreationDisposition(AccessMode), GetNativePriority(AccessPriority), 0);
    if (file != INVALID_HANDLE_VALUE)
        result=FileHandle::GenerateFromPointer(file);
    return result;
}

RF_Type::Bool CloseFile(FileHandle& Handle)
{
    HANDLE file=reinterpret_cast<HANDLE>(Handle.GetPointer());
    RF_Type::Bool result=static_cast<RF_Type::Bool>(CloseHandle(file) == TRUE);
    Handle=FileHandle::Zero();
    return result;
}

struct FileMapping
{
    HANDLE fileMapping;
    void* data;
};

MemoryMappingHandle MapFileIntoMemory(const FileHandle& Handle)
{
    MemoryMappingHandle result;
    HANDLE file=CreateFileMapping(reinterpret_cast<HANDLE>(Handle.GetPointer()),
                                  0, PAGE_READWRITE | SEC_RESERVE, 0, 0, 0);
    if (file)
    {
        FileMapping* fileMapping=new FileMapping;
        fileMapping->fileMapping=file;
        fileMapping->data=MapViewOfFile(file, FILE_MAP_WRITE|FILE_MAP_READ, 0, 0, 0);
        result=MemoryMappingHandle::GenerateFromPointer(fileMapping);
    }
    return result;
}

RF_Type::Bool UnmapMemoryFile(MemoryMappingHandle& Handle)
{
    FileMapping* fileMapping=reinterpret_cast<FileMapping*>(Handle.GetPointer());
    if (fileMapping!=0 &&
        UnmapViewOfFile(fileMapping->fileMapping) &&
        CloseHandle(fileMapping->fileMapping) )
    {
        delete fileMapping;
        Handle=FileHandle::Zero();
        return true;
    }
    return false;
}

void* GetMemoryFile(const MemoryMappingHandle& Handle)
{
    FileMapping* fileMapping=reinterpret_cast<FileMapping*>(Handle.GetPointer());
    if (fileMapping!=0)
        return fileMapping->data;
    return 0;
}

RF_Type::Bool ReadFile(const FileHandle& Handle, RF_Type::UInt8* Buffer, 
    const RF_Type::UInt64 ReadBytes, RF_Type::UInt64& BytesRead)
{
    DWORD lowReadBytes=0;
    BOOL result = ::ReadFile(reinterpret_cast<HANDLE>(Handle.GetPointer()), 
                             reinterpret_cast<void*>(Buffer), static_cast<DWORD>(ReadBytes),
                             reinterpret_cast<DWORD*>(&lowReadBytes),
                             reinterpret_cast<LPOVERLAPPED>(0)) == TRUE;
    BytesRead = lowReadBytes;
    return result == TRUE;
}

RF_Type::Bool WriteFile(const FileHandle& Handle, const RF_Type::UInt8* Buffer, 
    const RF_Type::UInt64 WriteBytes, RF_Type::UInt64& BytesWritten)
{
    DWORD lowWriteBytes = 0;
    BOOL result = ::WriteFile(reinterpret_cast<HANDLE>(Handle.GetPointer()), 
                              reinterpret_cast<const void*>(Buffer), static_cast<DWORD>(WriteBytes),
                              reinterpret_cast<DWORD*>(&lowWriteBytes),
                              reinterpret_cast<LPOVERLAPPED>(0)) == TRUE;
    BytesWritten = lowWriteBytes;
    return result == TRUE;
}

RF_Type::Bool FlushFile(const FileHandle& Handle)
{
    return ::FlushFileBuffers(reinterpret_cast<HANDLE>(Handle.GetPointer())) == TRUE;
}

RF_Type::UInt64 SeekFile(const FileHandle& Handle, const RF_Type::Int64 Offset, 
    const RF_IO::SeekOrigin::Type Origin)
{
    long hi = static_cast<long>(Offset >> 32), lo = static_cast<long>(Offset);
    lo=SetFilePointer(reinterpret_cast<HANDLE>(Handle.GetPointer()), lo, &hi, GetNativeSeekOrigin(Origin));
    if (lo!=INVALID_SET_FILE_POINTER)
        return (static_cast<RF_Type::UInt64>(hi) << 32) + lo;
    else
        return 0;
}

RF_Type::UInt64 TellFile(const FileHandle& Handle)
{
    long hi=0, lo;
    lo=SetFilePointer(reinterpret_cast<HANDLE>(Handle.GetPointer()), 0, &hi, FILE_CURRENT);
    if (lo!=INVALID_SET_FILE_POINTER)
        return (static_cast<RF_Type::UInt64>(hi) << 32) + lo;
    else
        return 0;
}

RF_Type::String GenerateTempFilename(const RF_Type::String& Path)
{
    char buf[MAX_PATH];
    RF_Type::UInt32 len=GetTempFileName(Path.c_str(), "tmp", 0, buf);
    RF_Type::String result(buf, len);
    return result;
}

RF_Type::Bool Access(const RF_Type::String& Path, const RF_IO::AccessMode::Type Mode)
{
    RF_Type::Bool result = true;

    if(Mode != RF_IO::AccessMode::None)
    {
        int mask = 0;
        
        if(!Path.IsEmpty())
        {// a path on a drive
            if(Mode & RF_IO::AccessMode::Exists)
            {
                mask |= _access(Path.c_str(), 0);
            }

            if(Mode & RF_IO::AccessMode::Read)
            {
                mask |= _access(Path.c_str(), 4);
            }

            if(Mode & RF_IO::AccessMode::Write)
            {
                mask |= _access(Path.c_str(), 2);
            }

            result = mask == 0;
        }
        else
        {// root path list all drives
            if(Mode & (RF_IO::AccessMode::Read | RF_IO::AccessMode::Write))
            {// the root path exists but isn't readable or writable
                result = false;
            }
        }
    }
    return result;
}

RF_Type::String PathSeperator()
{
    return ";"_rfs;
}

RF_Type::String Seperator()
{
    return "/"_rfs;
}

RF_Mem::AutoPointer<RF_IO::FileStatus> Stat(const RF_Type::String& Path)
{
    RF_Mem::AutoPointer<RF_IO::FileStatus> result;
    BY_HANDLE_FILE_INFORMATION info;
    HANDLE fHndl = CreateFileA(Path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
    if (INVALID_HANDLE_VALUE != fHndl)
    {
        if (0 != GetFileInformationByHandle(fHndl, &info))
        {
            result=RF_Mem::AutoPointer<RF_IO::FileStatus>(new RF_IO::FileStatus);
            result->Size = info.nFileSizeHigh;
            result->Size <<= 32;
            result->Size += info.nFileSizeLow;
            
            result->CreateionTimestamp = info.ftCreationTime.dwHighDateTime;
            result->CreateionTimestamp <<= 32;
            result->CreateionTimestamp += info.ftCreationTime.dwLowDateTime;

            result->LastAccessTimestamp = info.ftLastAccessTime.dwHighDateTime;
            result->LastAccessTimestamp <<= 32;
            result->LastAccessTimestamp += info.ftLastAccessTime.dwLowDateTime;
            
            result->LastModificationTimestamp = info.ftLastWriteTime.dwHighDateTime;
            result->LastModificationTimestamp <<= 32;
            result->LastModificationTimestamp += info.ftLastWriteTime.dwLowDateTime;

            result->IsDirectory=(info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)!=0;
            result->IsHidden=(info.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)!=0;
        }
        CloseHandle(fHndl);
    }
    return result;
}

RF_Type::Bool ChangeMode( const RF_Type::String& Path, const RF_IO::AccessMode::Type NewMode )
{
    return false;
}

RF_Type::Bool CreatePreAllocatedFile(const RF_Type::String& Path, const RF_Type::Size FileSize)
{
    RF_Type::Bool result=false;
    HANDLE hFile = CreateFileA(Path.c_str(),GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_FLAG_SEQUENTIAL_SCAN,NULL);
    if (hFile!=INVALID_HANDLE_VALUE)
    {
        LARGE_INTEGER size;
        size.QuadPart=FileSize;
        result=SetFilePointerEx(hFile, size, 0, FILE_BEGIN)==TRUE;
        if (result)
            result=SetEndOfFile(hFile)==TRUE;
        CloseHandle(hFile);
    }
    return result;
}

RF_Type::Bool CreateFile(const RF_Type::String& Path)
{
    RF_Type::Bool result=false;
    HANDLE hFile = CreateFileA(Path.c_str(),0,0,0,CREATE_ALWAYS,0,NULL);
    if (hFile!=INVALID_HANDLE_VALUE)
    {        
        CloseHandle(hFile);
    }
    return result;
}

RF_Type::Bool CopyFile(const RF_Type::String& From, const RF_Type::String& To)
{
    return CopyFileA(From.c_str(),To.c_str(),false)==TRUE;
}

RF_Type::Bool DeleteFile(const RF_Type::String& Path)
{
    return DeleteFileA(Path.c_str())!=0;
}

RF_Type::Bool DeleteDirectory(const RF_Type::String& Path)
{
    return RemoveDirectory(Path.c_str()) != 0;
}

RF_Type::Bool RenameFile(const RF_Type::String& From, const RF_Type::String& To)
{
    return MoveFile(From.c_str(), To.c_str()) != 0;
}

RF_Type::String WinToUri(const RF_Type::String& WinPath)
{
    RF_Type::String result("file:///"_rfs+WinPath);
    for (RF_Type::UInt32 i=0;i<result.Length();++i)
    {
        if (result[i]=='\\')
            result[i]='/';
    }
    return result;
}

void RealPath(const RF_Type::String& Path, RF_Type::String& ResolvedPath)
{
    TCHAR** lppPart = {0};
    DWORD neededBufferSize = GetFullPathName(Path.c_str(), 0, 0, lppPart);
    if(neededBufferSize > 0)
    {
        RF_Mem::AutoPointerArray<char> buffer(neededBufferSize);
        GetFullPathName(Path.c_str(), neededBufferSize, buffer.Get(), lppPart);
        ResolvedPath = RF_Type::String(buffer.Release().Ptr, neededBufferSize, 
            RF_Core::DataManagment::TransfereOwnership)
                .Replace(
                RF_Type::String("\\"), RF_Type::String("/"));
    }
}

RF_Type::String WorkingDirectory()
{
    char buffer[1024];
    RF_Type::String result;
    if (GetCurrentDirectory(1024,buffer)!=0)
        result=RF_Type::String(buffer, 1024);
    return result;
}

RF_Type::String HomeDirectory()
{
    // getenv return a unix like path
    char buf[MAX_PATH];
    GetEnvironmentVariable("%USERPROFILE%", buf, MAX_PATH);
    RF_Type::String path(buf, MAX_PATH);
    return path;
}

RF_Type::String ApplicationDirectory()
{
    const static RF_Type::String PathDelimiter("\\");
    char buf[MAX_PATH];
    GetModuleFileName(NULL,buf,MAX_PATH);
    RF_Type::String result(buf, MAX_PATH);
    RF_Type::Int32 index = result.LastIndexOf(PathDelimiter);
    if(index > 0)
    {
        result = result.SubString(0, index + PathDelimiter.Length());
    }
    else
    {
        result = RF_Type::String();
    }

    return result;
}

RF_Type::String UserApplicationDataDirectory()
{
    RF_Type::String result;
    char buf[MAX_PATH];
    if (SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, buf) == S_OK)
        result = RF_Type::String(buf, MAX_PATH);
    return result;
}

RF_Type::String ApplicationDataDirectory()
{
    RF_Type::String result;
    char buf[MAX_PATH];
    if (SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, buf) == S_OK)
        result = RF_Type::String(buf, MAX_PATH);
    return result;
}

RF_Type::String TemporaryDirectory()
{
    RF_Type::String result;
    char buf[MAX_PATH];
    if(::GetTempPath(MAX_PATH, buf) > 0)
        result = RF_Type::String(buf, MAX_PATH);
    return result;
}

RF_Type::Bool ChangeDirectory( const RF_Type::String& Destination )
{
    return SetCurrentDirectory(Destination.c_str())==0;
}

RF_Type::Bool CreateDirectory( const RF_Type::String& Path )
{
    return CreateDirectoryA(Path.c_str(), NULL) == TRUE;
}

RF_Mem::AutoPointerArray<RF_Type::String> DirectoryContent(const RF_Type::String& Path)
{
    RF_Mem::AutoPointerArray<RF_Type::String> result;
    RF_Collect::List<RF_Type::String> list;
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;    
    RF_Type::String winPath=Path+"\\*";// search for everything

    if(Path.IsEmpty())
    {// list all drives
        RF_Type::Char driveSymbol[] = ("A:");
        RF_Type::UInt32 driveMask = _getdrives();
        static const RF_Type::UInt32 CURRENT_DRIVE_MASK = 1;
        static const RF_Type::UInt32 NEXT_DRIVE = 1;
        static const RF_Type::UInt32 EMPTY_MASK = 0;

        while(driveMask != EMPTY_MASK)
        {
            if(driveMask & CURRENT_DRIVE_MASK)
            {
                list.AddLast(RF_Type::String(driveSymbol));
            }

            ++driveSymbol[0];
            driveMask >>= NEXT_DRIVE;
        }        
    }
    else
    {// just a normal directory listing
        hFind = FindFirstFile(winPath.c_str(), &findFileData);
        if(hFind != INVALID_HANDLE_VALUE)
        {
            do
            {
                if(strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0)
                    list.AddLast(RF_Type::String(findFileData.cFileName, MAX_PATH));
            } while(FindNextFile(hFind, &findFileData) != 0);
            FindClose(hFind);
        }
    }

    result = RF_Mem::AutoPointerArray<RF_Type::String>(list.Count());
    for(RF_Type::UInt32 i = 0; i < result.Count(); ++i)
        result[i].Swap(list[i]);

    return result;
}

class FileWatcherObject
{
    public:
        HANDLE m_FileHandle;
        HANDLE m_AsyncHandle;
        OVERLAPPED m_Overlapped;
        RF_Type::UInt8 m_FrontBuffer[8096];
        RF_Type::UInt8 m_BackBuffer[8096];
        RF_Collect::Queue<FileWatcherEvent> m_Events;
        RF_Type::String m_Path;
        RF_Type::String m_LastModifiedEvent;

        void Process(const RF_Type::UInt32 Bytes);
};

void FileWatcherObject::Process(const RF_Type::UInt32 Bytes)
{
    if (Bytes)
    {
        size_t offset = 0;
        int count;
        TCHAR szFile[MAX_PATH];
        PFILE_NOTIFY_INFORMATION pNotify;
        FileWatcherEvent args;
        do
        {
            pNotify = (PFILE_NOTIFY_INFORMATION) &m_FrontBuffer[offset];
            offset += pNotify->NextEntryOffset;
            count = WideCharToMultiByte(CP_ACP, 0, pNotify->FileName,
                                        pNotify->FileNameLength / sizeof(WCHAR),
                                        szFile, MAX_PATH - 1, NULL, NULL);
            szFile[count] = TEXT('\0');
            args.Name = RF_Type::String(szFile, count).Replace("\\"_rfs, "/"_rfs);

            switch(pNotify->Action)
            {
                
                case FILE_ACTION_RENAMED_NEW_NAME:
                case FILE_ACTION_ADDED:
                    args.ChangeType=WatcherChangeTypes::Created;
                    m_LastModifiedEvent = ""_rfs;
                    m_Events.Enqueue(args);
                    break;
                case FILE_ACTION_RENAMED_OLD_NAME:
                case FILE_ACTION_REMOVED:
                    args.ChangeType=WatcherChangeTypes::Deleted;
                    m_LastModifiedEvent = ""_rfs;
                    m_Events.Enqueue(args);
                    break;
                case FILE_ACTION_MODIFIED:
                    args.ChangeType=WatcherChangeTypes::Changed;
                    // windows generates this message twice for each file change
                    // because of changing the last write and time stamp
                    if(m_LastModifiedEvent != args.Name)
                    {
                        m_Events.Enqueue(args);
                        m_LastModifiedEvent = args.Name;
                    }
                    else
                    {
                        m_LastModifiedEvent = ""_rfs;
                    }
                    break;
            };
        }
        while(pNotify->NextEntryOffset != 0);
    }
}

FileWatcherHandle CreateFileWatcher(const RF_Type::String& Path)
{
    FileWatcherObject* pimpl=new FileWatcherObject();
    FileWatcherHandle result=FileWatcherHandle::GenerateFromPointer(pimpl);
    pimpl->m_Path = Path;
    WCHAR directory[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, pimpl->m_Path.c_str(), pimpl->m_Path.Size(),
        directory, MAX_PATH * sizeof(WCHAR));
    pimpl->m_FileHandle = CreateFileW(directory, FILE_LIST_DIRECTORY,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);
    return result;
}

void DestroyFileWatcher(FileWatcherHandle& Handle)
{
    if (Handle.GetPointer())
    {
        FileWatcherObject* pimpl=reinterpret_cast<FileWatcherObject*>(Handle.GetPointer());
        CloseHandle(pimpl->m_FileHandle);
        delete pimpl;
        Handle=FileWatcherHandle::Zero();
    }
}

void CALLBACK NotificationCompletion(DWORD errorCode, DWORD tferred, LPOVERLAPPED over)
{
    if (errorCode == ERROR_SUCCESS)
    {
        FileWatcherObject* data = reinterpret_cast<FileWatcherObject*>(over->hEvent);
        RF_Type::Size bufSize = sizeof(data->m_BackBuffer);
        DWORD bytes=0;

        RF_SysMem::Copy(data->m_FrontBuffer, data->m_BackBuffer, bufSize);

        RF_Type::Bool result = ReadDirectoryChangesW(data->m_AsyncHandle,
            data->m_BackBuffer, bufSize, true,
            FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
            FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION,
            &bytes, &data->m_Overlapped, NotificationCompletion) != 0 ? true : false;

        if (!result)
        {
            DWORD   dwLastError = ::GetLastError();
            LPVOID   lpBuffer=0;
            if (dwLastError != 0)    // Don't want to see a "operation done successfully" error ;-)
                ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                FORMAT_MESSAGE_FROM_SYSTEM |
                FORMAT_MESSAGE_IGNORE_INSERTS,                 // It´s a system error
                NULL,                                      // No string to be formatted needed
                dwLastError,                               // Hey Windows: Please explain this error!
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),  // Do it in the standard language
                (LPTSTR)&lpBuffer,              // Put the message here
                0,                     // Number of bytes to store the message
                NULL);
            RF_IO::LogError((char*)lpBuffer);
        }

        data->Process(tferred);
    }
}

RF_Type::Bool WaitForFileWatcher(const FileWatcherHandle& Handle, FileWatcherEvent& Event)
{
    FileWatcherObject* pimpl=reinterpret_cast<FileWatcherObject*>(Handle.GetPointer());
    DWORD dwBytes=0;
    RF_Type::Bool result=false;
    if (pimpl)
    {
        if (!pimpl->m_Events.IsEmpty())
        {
            result=pimpl->m_Events.Dequeue(Event);
        }
        else
        {
            result=ReadDirectoryChangesW(pimpl->m_FileHandle, pimpl->m_BackBuffer,
                sizeof(pimpl->m_BackBuffer), true,
                FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME |
                FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION,
                &dwBytes, 0, 0) == TRUE ? true : false;
            if (result)
            {
                pimpl->Process(dwBytes);
                result=pimpl->m_Events.Dequeue(Event);
            }
        }
    }
    return result;
}

void StartFileWatcher(const FileWatcherHandle& Handle)
{
    FileWatcherObject* pimpl=reinterpret_cast<FileWatcherObject*>(Handle.GetPointer());
    if (pimpl)
    {
        pimpl->m_AsyncHandle=CreateFileA(pimpl->m_Path.c_str(),
            FILE_LIST_DIRECTORY, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
            NULL);

        if (pimpl->m_AsyncHandle!=INVALID_HANDLE_VALUE)
        {
            ZeroMemory(&pimpl->m_Overlapped,sizeof(pimpl->m_Overlapped));
            pimpl->m_Overlapped.hEvent=pimpl;

            NotificationCompletion(ERROR_SUCCESS,0,&pimpl->m_Overlapped);
        }
    }
}

void StopFileWatcher(const FileWatcherHandle& Handle)
{
    FileWatcherObject* pimpl=reinterpret_cast<FileWatcherObject*>(Handle.GetPointer());
    if (pimpl!=0 && pimpl->m_AsyncHandle!=INVALID_HANDLE_VALUE)
    {
        CancelIo(pimpl->m_AsyncHandle);
        ReadDirectoryChangesW(pimpl->m_AsyncHandle, pimpl->m_BackBuffer, 
            sizeof(pimpl->m_BackBuffer), true,
            FILE_NOTIFY_CHANGE_FILE_NAME|FILE_NOTIFY_CHANGE_DIR_NAME|
            FILE_NOTIFY_CHANGE_LAST_WRITE|FILE_NOTIFY_CHANGE_CREATION,
            0, &pimpl->m_Overlapped, 0);
        CloseHandle(pimpl->m_AsyncHandle);
        pimpl->m_AsyncHandle=INVALID_HANDLE_VALUE;
    }
}

RF_Type::Bool GetFileWatcherEvent(const FileWatcherHandle& Handle, FileWatcherEvent& Event)
{
    RF_Type::Bool result=false;
    FileWatcherObject* pimpl=reinterpret_cast<FileWatcherObject*>(Handle.GetPointer());
    if (pimpl!=0)
        result = pimpl->m_Events.Dequeue(Event);
    return result;
}

RF_Type::Bool SystemPathToUri(const RF_Type::String& SystemPath,
    RF_IO::Uri& UriInterpretation)
{
    RF_Type::String uriPath=WinToUri(SystemPath);
    RF_IO::Uri uri1(uriPath, RF_IO::UriKind::Absolute);
    UriInterpretation = uri1;
    return true;
}

RF_Type::Bool UriToSystemPath(const RF_IO::Uri& Uri,
    RF_Type::String& SystemPath)
{
    SystemPath = Uri.GetComponents(RF_IO::UriComponents::Path);
    if(SystemPath.Length() > 0)
    {
        SystemPath = SystemPath.SubString(1, SystemPath.Length() - 1);
    }
    return true;
}

}

namespace RadonFramework::System::IO::FileSystem {

void Dispatch()
{
    OpenFile=Windows::OpenFile;
    CloseFile= Windows::CloseFile;
    MapFileIntoMemory= Windows::MapFileIntoMemory;
    UnmapMemoryFile= Windows::UnmapMemoryFile;
    GetMemoryFile= Windows::GetMemoryFile;
    ReadFile= Windows::ReadFile;
    WriteFile= Windows::WriteFile;
    FlushFile= Windows::FlushFile;
    SeekFile= Windows::SeekFile;
    TellFile= Windows::TellFile;
    Access= Windows::Access;
    PathSeperator= Windows::PathSeperator;
    Seperator= Windows::Seperator;
    Stat= Windows::Stat;
    RealPath= Windows::RealPath;
    //ChangeMode=::ChangeMode;
    CreatePreAllocatedFile= Windows::CreatePreAllocatedFile;
    CreateFile= Windows::CreateFile;
    CopyFile= Windows::CopyFile;
    RenameFile= Windows::RenameFile;
    DeleteFile= Windows::DeleteFile;
    WorkingDirectory= Windows::WorkingDirectory;
    HomeDirectory= Windows::HomeDirectory;
    ApplicationDirectory= Windows::ApplicationDirectory;
    UserApplicationDataDirectory = Windows::UserApplicationDataDirectory;
    ApplicationDataDirectory = Windows::ApplicationDataDirectory;
    TemporaryDirectory = Windows::TemporaryDirectory;
    ChangeDirectory= Windows::ChangeDirectory;
    CreateDirectory= Windows::CreateDirectory;
    DirectoryContent= Windows::DirectoryContent;
    CreateFileWatcher= Windows::CreateFileWatcher;
    DestroyFileWatcher= Windows::DestroyFileWatcher;
    WaitForFileWatcher= Windows::WaitForFileWatcher;
    StartFileWatcher= Windows::StartFileWatcher;
    StopFileWatcher= Windows::StopFileWatcher;
    GetFileWatcherEvent= Windows::GetFileWatcherEvent;
    GenerateTempFilename= Windows::GenerateTempFilename;
    SystemPathToUri = Windows::SystemPathToUri;
    UriToSystemPath = Windows::UriToSystemPath;
    DeleteDirectory = Windows::DeleteDirectory;
}

}