#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/IO/FileSystem.hpp"
#include "RadonFramework/IO/AccessMode.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/Collections/Queue.hpp"
#include "RadonFramework/IO/Log.hpp"
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

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Collections;
using namespace RadonFramework::System::IO::FileSystem;

DWORD GetNativeAccessMode(FileAccessMode::Type AccessMode)
{
    static DWORD result[FileAccessMode::MAX]={
        GENERIC_READ, GENERIC_WRITE, GENERIC_WRITE | GENERIC_READ
    };
    return result[AccessMode];
}

DWORD GetNativePriority(FileAccessPriority::Type AccessPriority)
{
    static DWORD result[FileAccessPriority::MAX]={
        FILE_FLAG_SEQUENTIAL_SCAN, FILE_FLAG_RANDOM_ACCESS, FILE_FLAG_WRITE_THROUGH, FILE_ATTRIBUTE_NORMAL
    };
    return result[AccessPriority];
}

DWORD GetNativeCreationDisposition(FileAccessMode::Type AccessMode)
{
    static DWORD result[FileAccessMode::MAX] = {
        OPEN_EXISTING, OPEN_ALWAYS, OPEN_ALWAYS
    };
    return result[AccessMode];
}

DWORD GetNativeSeekOrigin(SeekOrigin::Type Origin)
{
    static DWORD result[SeekOrigin::MAX]={
        FILE_BEGIN, FILE_CURRENT, FILE_END
    };
    return result[Origin];
}

FileHandle OpenFile(const String& FilePath, const FileAccessMode::Type AccessMode,
                    const FileAccessPriority::Type AccessPriority)
{
    FileHandle result = FileHandle::Zero();
    HANDLE file = CreateFileA(FilePath.c_str(), GetNativeAccessMode(AccessMode), 
        0, 0, GetNativeCreationDisposition(AccessMode), GetNativePriority(AccessPriority), 0);
    if (file != INVALID_HANDLE_VALUE)
        result=FileHandle::GenerateFromPointer(file);
    return result;
}

Bool CloseFile(FileHandle& Handle)
{
    HANDLE file=reinterpret_cast<HANDLE>(Handle.GetPointer());
    Bool result=static_cast<Bool>(CloseHandle(file) == TRUE);
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

Bool UnmapMemoryFile(MemoryMappingHandle& Handle)
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

Bool ReadFile(const FileHandle& Handle, UInt8* Buffer, const UInt64 ReadBytes, UInt64& BytesRead)
{
    DWORD lowReadBytes=0;
    BOOL result = ::ReadFile(reinterpret_cast<HANDLE>(Handle.GetPointer()), 
                             reinterpret_cast<void*>(Buffer), static_cast<DWORD>(ReadBytes),
                             reinterpret_cast<DWORD*>(&lowReadBytes),
                             reinterpret_cast<LPOVERLAPPED>(0)) == TRUE;
    BytesRead = lowReadBytes;
    return result == TRUE;
}

Bool WriteFile(const FileHandle& Handle, const UInt8* Buffer, const UInt64 WriteBytes, UInt64& BytesWritten)
{
    DWORD lowWriteBytes = 0;
    BOOL result = ::WriteFile(reinterpret_cast<HANDLE>(Handle.GetPointer()), 
                              reinterpret_cast<const void*>(Buffer), static_cast<DWORD>(WriteBytes),
                              reinterpret_cast<DWORD*>(&lowWriteBytes),
                              reinterpret_cast<LPOVERLAPPED>(0)) == TRUE;
    BytesWritten = lowWriteBytes;
    return result == TRUE;
}

Bool FlushFile(const FileHandle& Handle)
{
    return ::FlushFileBuffers(reinterpret_cast<HANDLE>(Handle.GetPointer())) == TRUE;
}

UInt64 SeekFile(const FileHandle& Handle, const UInt64 Offset, const SeekOrigin::Type Origin)
{
    long hi=static_cast<long>(Offset), lo=Offset>>32;
    lo=SetFilePointer(reinterpret_cast<HANDLE>(Handle.GetPointer()), lo, &hi, GetNativeSeekOrigin(Origin));
    if (lo!=INVALID_SET_FILE_POINTER)
        return (static_cast<UInt64>(hi) << 32) + lo;
    else
        return 0;
}

UInt64 TellFile(const FileHandle& Handle)
{
    long hi=0, lo;
    lo=SetFilePointer(reinterpret_cast<HANDLE>(Handle.GetPointer()), 0, &hi, FILE_CURRENT);
    if (lo!=INVALID_SET_FILE_POINTER)
        return (static_cast<UInt64>(hi) << 32) + lo;
    else
        return 0;
}

String GenerateTempFilename(const String& Path)
{
    char buf[MAX_PATH];
    UInt32 len=GetTempFileName(Path.c_str(), "tmp", 0, buf);
    String result(buf, len);
    return result;
}

Bool Access(const String& Path, const AccessMode::Type Mode)
{
    if(Mode != AccessMode::None)
    {
        int result = 0;
        if(Mode & AccessMode::Exists)
            result |= _access(Path.c_str(), 0);
        if(Mode & AccessMode::Read)
            result |= _access(Path.c_str(), 4);
        if(Mode & AccessMode::Write)
            result |= _access(Path.c_str(), 2);
        return result == 0;
    }
    return true;
}

String PathSeperator()
{
    return String(";");
}

String Seperator()
{
    return String("\\");
}

AutoPointer<FileStatus> Stat(const String& Path)
{
    AutoPointer<FileStatus> result;
    BY_HANDLE_FILE_INFORMATION info;
    HANDLE fHndl = CreateFileA(Path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
    if (0 != fHndl)
    {
        if (0 != GetFileInformationByHandle(fHndl, &info))
        {
            result=AutoPointer<FileStatus>(new FileStatus);
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

Bool ChangeMode( const String& Path, const AccessMode::Type NewMode )
{
    return false;
}

Bool CreatePreAllocatedFile(const String& Path, const Size FileSize)
{
    Bool result=false;
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

Bool CreateFile(const String& Path)
{
    Bool result=false;
    HANDLE hFile = CreateFileA(Path.c_str(),0,0,0,CREATE_ALWAYS,0,NULL);
    if (hFile!=INVALID_HANDLE_VALUE)
    {        
        CloseHandle(hFile);
    }
    return result;
}

Bool CopyFile(const String& From, const String& To)
{
    return CopyFileA(From.c_str(),To.c_str(),true)==TRUE;
}

Bool DeleteFile(const String& Path)
{
    return DeleteFileA(Path.c_str())==0;
}

Bool RenameFile(const String& From, const String& To)
{
    if (MoveFile(From.c_str(), To.c_str())==0)
        return true;
    return false;
}

String WinToUri(const String& WinPath)
{
    String result(String("file:///")+WinPath);
    for (UInt32 i=0;i<result.Length();++i)
    {
        if (result[i]=='\\')
            result[i]='/';
    }
    return result;
}

void RealPath(const String& Path, String& ResolvedPath)
{
    TCHAR** lppPart = {0};
    DWORD neededBufferSize = GetFullPathName(Path.c_str(), 0, 0, lppPart);
    if(neededBufferSize > 0)
    {
        AutoPointerArray<char> buffer(new TCHAR[neededBufferSize], neededBufferSize);
        GetFullPathName(Path.c_str(), neededBufferSize, buffer.Get(), lppPart);
        ResolvedPath = WinToUri(String(buffer.Release().Ptr, neededBufferSize, RF_Common::DataManagment::TransfereOwnership));
    }
}

String WorkingDirectory()
{
    char buffer[1024];
    String result;
    if (GetCurrentDirectory(1024,buffer)!=0)
        result=WinToUri(String(buffer, 1024));
    return result;
}

String HomeDirectory()
{
    // getenv return a unix like path
    char buf[MAX_PATH];
    GetEnvironmentVariable("%USERPROFILE%", buf, MAX_PATH);
    String path(buf, MAX_PATH);
    return WinToUri(path);
}

String ApplicationDirectory()
{
    char buf[MAX_PATH];
    GetModuleFileName(NULL,buf,MAX_PATH);
    String result(buf, MAX_PATH);
    
    RF_Type::Int32 index = result.LastIndexOf(::Seperator());
    if(index > 0)
    {
        result = result.SubString(0, index + ::Seperator().Length());
        result = WinToUri(result);
    }
    else
    {
        result = String();
    }

    return result;
}

String UserApplicationDataDirectory()
{
    String result;
    char buf[MAX_PATH];
    if (SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, buf) == S_OK)
        result = WinToUri(String(buf, MAX_PATH));
    return result;
}

String ApplicationDataDirectory()
{
    String result;
    char buf[MAX_PATH];
    if (SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, buf) == S_OK)
        result = WinToUri(String(buf, MAX_PATH));
    return result;
}

Bool ChangeDirectory( const String& Destination ) 
{
    return SetCurrentDirectory(Destination.c_str())==0;
}

Bool CreateDirectory( const String& Path ) 
{
    return CreateDirectoryA(Path.c_str(), NULL) == TRUE;
}

AutoPointerArray<String> DirectoryContent(const String& Path) 
{
    AutoPointerArray<String> result;
    List<String> list;
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;    
    String winPath=Path+"\\*";// search for everything
    hFind=FindFirstFile(winPath.c_str(),&findFileData);    
    if (hFind!=INVALID_HANDLE_VALUE)
    {
        do
        {
            if (strcmp(findFileData.cFileName,".")!=0 && strcmp(findFileData.cFileName,"..")!=0)
                list.AddLast(String(findFileData.cFileName, MAX_PATH));
        }while(FindNextFile(hFind,&findFileData)!=0);
        FindClose(hFind);
        result = AutoPointerArray<String>(new String[list.Count()], list.Count());
        for (UInt32 i=0;i<result.Count();++i)
            result[i].Swap(list[i]);
    }    
    return result;
}

class FileWatcherObject
{
    public:
        HANDLE m_FileHandle;
        HANDLE m_AsyncHandle;
        OVERLAPPED m_Overlapped;
        UInt8 m_Buf[8096];
        Queue<FileWatcherEvent> m_Events;
        String m_Path;

        void Process(const UInt32 Bytes);
};

void FileWatcherObject::Process(const UInt32 Bytes)
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
            pNotify = (PFILE_NOTIFY_INFORMATION) &m_Buf[offset];
            offset += pNotify->NextEntryOffset;
            count = WideCharToMultiByte(CP_ACP, 0, pNotify->FileName,
                                        pNotify->FileNameLength / sizeof(WCHAR),
                                        szFile, MAX_PATH - 1, NULL, NULL);
            szFile[count] = TEXT('\0');
            args.Name = String(szFile, count).Replace("\\", "/");

            switch(pNotify->Action)
            {
                
                case FILE_ACTION_RENAMED_NEW_NAME:
                case FILE_ACTION_ADDED:
                    args.ChangeType=WatcherChangeTypes::Created;
                    break;
                case FILE_ACTION_RENAMED_OLD_NAME:
                case FILE_ACTION_REMOVED:
                    args.ChangeType=WatcherChangeTypes::Deleted;
                    break;
                case FILE_ACTION_MODIFIED:
                    args.ChangeType=WatcherChangeTypes::Changed;
                    break;
            };
            m_Events.Enqueue(args);
        }
        while(pNotify->NextEntryOffset != 0);
    }
}

FileWatcherHandle CreateFileWatcher(const String& Path)
{
    FileWatcherObject* pimpl=new FileWatcherObject();
    FileWatcherHandle result=FileWatcherHandle::GenerateFromPointer(pimpl);
    pimpl->m_Path = Path;
    pimpl->m_FileHandle = CreateFileA(pimpl->m_Path.c_str(), FILE_LIST_DIRECTORY,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
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
        data->Process(tferred);
        Size bufSize = sizeof(data->m_Buf);
        Bool result=ReadDirectoryChangesW(data->m_AsyncHandle,data->m_Buf, bufSize,true,
            FILE_NOTIFY_CHANGE_FILE_NAME|FILE_NOTIFY_CHANGE_DIR_NAME|
            FILE_NOTIFY_CHANGE_LAST_WRITE|FILE_NOTIFY_CHANGE_CREATION,
            0,&data->m_Overlapped,NotificationCompletion)!=0?true:false;
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
            LogError((char*)lpBuffer);
        }
    }
}

Bool WaitForFileWatcher(const FileWatcherHandle& Handle, FileWatcherEvent& Event)
{
    FileWatcherObject* pimpl=reinterpret_cast<FileWatcherObject*>(Handle.GetPointer());
    DWORD dwBytes=0;
    Bool result=false;
    if (pimpl)
    {
        if (!pimpl->m_Events.IsEmpty())
        {
            result=pimpl->m_Events.Dequeue(Event);
        }
        else
        {
            result=ReadDirectoryChangesW(pimpl->m_FileHandle, pimpl->m_Buf,sizeof(pimpl->m_Buf),true,
                FILE_NOTIFY_CHANGE_FILE_NAME|FILE_NOTIFY_CHANGE_DIR_NAME|
                FILE_NOTIFY_CHANGE_LAST_WRITE|FILE_NOTIFY_CHANGE_CREATION,
                &dwBytes,0,0)==TRUE?true:false;
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
        ReadDirectoryChangesW(pimpl->m_AsyncHandle, pimpl->m_Buf, sizeof(pimpl->m_Buf),true,
                FILE_NOTIFY_CHANGE_FILE_NAME|FILE_NOTIFY_CHANGE_DIR_NAME|
                FILE_NOTIFY_CHANGE_LAST_WRITE|FILE_NOTIFY_CHANGE_CREATION,
                0,&pimpl->m_Overlapped,0);
        CloseHandle(pimpl->m_AsyncHandle);
        pimpl->m_AsyncHandle=INVALID_HANDLE_VALUE;
    }
}

Bool GetFileWatcherEvent(const FileWatcherHandle& Handle, FileWatcherEvent& Event)
{
    Bool result=false;
    FileWatcherObject* pimpl=reinterpret_cast<FileWatcherObject*>(Handle.GetPointer());
    if (pimpl!=0 && !pimpl->m_Events.IsEmpty())
        result = pimpl->m_Events.Dequeue(Event);
    return result;
}

void RadonFramework::System::IO::FileSystem::Dispatch()
{
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
    RealPath=::RealPath;
    //ChangeMode=::ChangeMode;
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
    GenerateTempFilename=::GenerateTempFilename;
}