module;
#include <cstddef>
#include <memory>
#include <windows.h>
#include <io.h>
#include <Shlobj.h>
#include <direct.h>
export module rf.core.system:filesystem_win;
import rf.core.types;
import :filesystem;

DWORD getNativeAccessMode(rf::FileAccessMode AccessMode)
{
    static DWORD result[]={
        GENERIC_READ, GENERIC_WRITE, GENERIC_WRITE | GENERIC_READ
    };
    return result[static_cast<int>(AccessMode)];
}

DWORD getNativePriority(rf::FileAccessPriority AccessPriority)
{
    static DWORD result[] = {FILE_ATTRIBUTE_NORMAL,
        FILE_FLAG_SEQUENTIAL_SCAN, FILE_FLAG_RANDOM_ACCESS, FILE_FLAG_WRITE_THROUGH, 
        FILE_ATTRIBUTE_NORMAL
    };
    return result[static_cast<int>(AccessPriority)];
}

DWORD getNativeCreationDisposition(rf::FileAccessMode AccessMode)
{
    static DWORD result[] = {
        OPEN_EXISTING, CREATE_ALWAYS, OPEN_ALWAYS
    };
    return result[static_cast<int>(AccessMode)];
}

DWORD getNativeSeekOrigin(rf::SeekOrigin Origin)
{
    static DWORD result[]={
        FILE_BEGIN, FILE_CURRENT, FILE_END
    };
    return result[static_cast<int>(Origin)];
}

export namespace rf {
FileHandle openFile(const strview& FilePath, FileAccessMode AccessMode, FileAccessPriority AccessPriority){
    FileHandle result = nullptr;
    HANDLE file = CreateFileA(reinterpret_cast<LPCSTR>(FilePath.address), getNativeAccessMode(AccessMode), 
        0, 0, getNativeCreationDisposition(AccessMode), getNativePriority(AccessPriority), 0);
    if (file != INVALID_HANDLE_VALUE)
        result=reinterpret_cast<ptr>(file);
    return result;
}

bool closeFile(FileHandle& Handle)
{
    HANDLE file=reinterpret_cast<HANDLE>(Handle);
    bool result=static_cast<bool>(CloseHandle(file) == TRUE);
    Handle=nullptr;
    return result;
}

MemoryMapping mapFileIntoMemory(FileHandle Handle)
{
    MemoryMapping result;
    HANDLE file=CreateFileMapping(reinterpret_cast<HANDLE>(Handle),
                                  0, PAGE_READWRITE | SEC_RESERVE, 0, 0, 0);
    if (file)
    {
        result.fileHandle=reinterpret_cast<ptr>(file);
        result.viewHandle=reinterpret_cast<ptr>(MapViewOfFile(file, FILE_MAP_WRITE|FILE_MAP_READ, 0, 0, 0));
    }
    return result;
}

bool unmapMemoryFile(MemoryMapping& Handle)
{
    if (UnmapViewOfFile(Handle.fileHandle) &&
        CloseHandle(Handle.fileHandle ))
    {
        Handle.fileHandle = nullptr;
        Handle.viewHandle = nullptr;
        return true;
    }
    return false;
}

ptr getMemoryFile(const MemoryMapping& Handle)
{
    return Handle.viewHandle;
}

bool readFile(FileHandle Handle, mem& Buffer, u64& BytesWrittenToBuffer)
{
    DWORD lowReadBytes=0;
    auto result = ::ReadFile(reinterpret_cast<HANDLE>(Handle), 
                             Buffer.address, static_cast<DWORD>(Buffer.bytes),
                             reinterpret_cast<DWORD*>(&lowReadBytes),
                             reinterpret_cast<LPOVERLAPPED>(0)) == TRUE;
    BytesWrittenToBuffer = lowReadBytes;
    return result == TRUE;
}

bool writeFile(FileHandle Handle, mem Buffer, u64& BytesWrittenFromBuffer)
{
    DWORD lowWriteBytes = 0;
    auto result = ::WriteFile(reinterpret_cast<HANDLE>(Handle), 
                              Buffer.address, Buffer.bytes,
                              reinterpret_cast<DWORD*>(&lowWriteBytes),
                              reinterpret_cast<LPOVERLAPPED>(0)) == TRUE;
    BytesWrittenFromBuffer = lowWriteBytes;
    return result == TRUE;
}

bool flushFile(FileHandle Handle)
{
    return ::FlushFileBuffers(reinterpret_cast<HANDLE>(Handle)) == TRUE;
}

u64 seekFile(FileHandle Handle, i64 Offset, SeekOrigin Origin)
{
    long hi = static_cast<long>(Offset >> 32), lo = static_cast<long>(Offset);
    lo=SetFilePointer(reinterpret_cast<HANDLE>(Handle), lo, &hi, getNativeSeekOrigin(Origin));
    if (lo!=INVALID_SET_FILE_POINTER)
        return (static_cast<u64>(hi) << 32) + lo;
    else
        return 0;
}

u64 tellFile(FileHandle Handle)
{
    long hi=0, lo;
    lo=SetFilePointer(reinterpret_cast<HANDLE>(Handle), 0, &hi, FILE_CURRENT);
    if (lo!=INVALID_SET_FILE_POINTER)
        return (static_cast<u64>(hi) << 32) + lo;
    else
        return 0;
}

bool access(const strview& Path, AccessMode Mode)
{
    bool result = true;
    if(Mode != AccessMode::None)
    {
        int mask = 0;
        const char* path = reinterpret_cast<const char*>(Path.address);
        if(Mode & AccessMode::Exists)
        {
            mask |= _access(path, 0);
        }
        if(Mode & AccessMode::Read)
        {
            mask |= _access(path, 4);
        }
        if(Mode & AccessMode::Write)
        {
            mask |= _access(path, 2);
        }
        result = mask == 0;
    }
    return result;
}

strview pathSeperator(){
    return { ";",1 };
}

strview seperator(){
    return {"/",1};
}

bool fileStatus(const strview& Path, FileStatus& Status)
{
    auto result = false;
    BY_HANDLE_FILE_INFORMATION info;
    HANDLE fHndl = CreateFileA(reinterpret_cast<const char*>(Path.address), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, NULL);
    if (INVALID_HANDLE_VALUE != fHndl)
    {
        if (0 != GetFileInformationByHandle(fHndl, &info))
        {
            result = true;
            Status.size = (static_cast<size>(info.nFileSizeHigh) << 32) + info.nFileSizeLow;
            Status.createionTimestamp = (static_cast<size>(info.ftCreationTime.dwHighDateTime) << 32) + info.ftCreationTime.dwLowDateTime;
            Status.lastAccessTimestamp = (static_cast<size>(info.ftLastAccessTime.dwHighDateTime) << 32) + info.ftLastAccessTime.dwLowDateTime;
            Status.lastModificationTimestamp = (static_cast<size>(info.ftLastWriteTime.dwHighDateTime) <<32)+info.ftLastWriteTime.dwLowDateTime;
            Status.isDirectory=(info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)!=0;
            Status.isHidden=(info.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)!=0;
        }
        CloseHandle(fHndl);
    }
    return result;
}

bool createPreAllocatedFile(const strview& Path, size FileSize)
{
    auto result=false;
    HANDLE hFile = CreateFileA(reinterpret_cast<const char*>(Path.address),GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_FLAG_SEQUENTIAL_SCAN,NULL);
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

bool createFile(const strview& Path)
{
    auto result=false;
    HANDLE hFile = CreateFileA(reinterpret_cast<const char*>(Path.address),0,0,0,CREATE_ALWAYS,0,NULL);
    if (hFile!=INVALID_HANDLE_VALUE)
    {        
        CloseHandle(hFile);
    }
    return result;
}

bool copyFile(const strview& From, const strview& To)
{
    return CopyFileA(reinterpret_cast<const char*>(From.address), reinterpret_cast<const char*>(To.address),false)==TRUE;
}

bool deleteFile(const strview& Path)
{
    return DeleteFileA(reinterpret_cast<const char*>(Path.address))!=0;
}

bool deleteDirectory(const strview& Path)
{
    return RemoveDirectory(reinterpret_cast<const char*>(Path.address)) != 0;
}

bool renameFile(const strview& From, const strview& To)
{
    return MoveFile(reinterpret_cast<const char*>(From.address), reinterpret_cast<const char*>(To.address)) != 0;
}

strview workingDirectory(mem& Buffer){
    auto written = GetCurrentDirectory(Buffer.bytes, reinterpret_cast<LPSTR>(Buffer.address));
    return {Buffer.address, written};
}

strview homeDirectory(mem& Buffer){
    auto written = GetEnvironmentVariable("%USERPROFILE%", reinterpret_cast<LPSTR>(Buffer.address), Buffer.bytes);
    return {Buffer.address, written};
}

strview applicationDirectory(mem& Buffer){
    auto written = GetModuleFileName(nullptr, reinterpret_cast<LPSTR>(Buffer.address), Buffer.bytes);
    return {Buffer.address, written};
}

strview userApplicationDataDirectory(mem& Buffer){
    PWSTR buf;
    strview result;
    if (SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &buf) == S_OK) {
        auto written = WideCharToMultiByte(CP_ACP, 0, buf, -1, reinterpret_cast<LPSTR>(Buffer.address), Buffer.bytes, nullptr, nullptr);
        free(buf);
        result.address = Buffer.address;
        result.bytes = written;
    }
    return result;
}

strview applicationDataDirectory(mem& Buffer){
    PWSTR buf;
    strview result;
    if (SHGetKnownFolderPath(FOLDERID_ProgramData, 0, NULL, &buf) == S_OK) {
        auto written = WideCharToMultiByte(CP_ACP, 0, buf, -1, reinterpret_cast<LPSTR>(Buffer.address), Buffer.bytes, nullptr, nullptr);
        free(buf);
        result.address = Buffer.address;
        result.bytes = written;
    }
    return result;
}

strview temporaryDirectory(mem& Buffer){
    auto written = GetTempPath(Buffer.bytes, reinterpret_cast<LPSTR>(Buffer.address));
    return {Buffer.address, written};
}

bool changeDirectory(const strview& Destination){
    return SetCurrentDirectory(reinterpret_cast<LPCSTR>(Destination.address)) == 0;
}

bool createDirectory(const strview& Path){
    return CreateDirectoryA(reinterpret_cast<LPCSTR>(Path.address), NULL) == TRUE;
}

template<class T>
void getDrives(void(*Callback)(const strview& Drive, T& Container), T& Container){
    utf8 drive[] = "A:";
    strview drivename = {drive,2};
    auto driveMask = _getdrives();
    while (driveMask != 0){
        if (driveMask & 1)
            Callback(drivename,Container);
        drive[0]++;
        driveMask >>= 1;
    }   
}

template<class T>
void getDirectoryContent(const strview& Path, void(*Callback)(const strview& Drive, T& Container), T& Container){
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(reinterpret_cast<LPSTR>(Path.address), &findFileData);
    if(hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            strview view = {findFileData.cFileName, MAX_PATH};
            Callback(view, Container);
        } while(FindNextFile(hFind, &findFileData) != 0);
        FindClose(hFind);
    }
}

struct FileWatcherObject{
    // fixed-size memory
    mem frontBuffer;
    mem backBuffer;
    strview path;
    // dynamic memory
    ptr queueHandle;
    mem (*enqueue)(ptr Self, size Bytes);
    mem (*dequeue)(ptr Self);    

    HANDLE fileHandle;
    HANDLE asyncHandle;
    OVERLAPPED overlapped;    
};

bool FileWatcher::watch(const strview& Path){
    auto impl = this->allocator.allocate(sizeof(FileWatcherObject));
    if (impl.address){
        this->handle = impl.address;
        auto fwObj = reinterpret_cast<FileWatcherObject*>(this->handle);
       // fwObj->frontBuffer = 
    }
    return false;
}

void processFileWatcherObject(FileWatcherObject& Self, u32 Bytes){
    if (Bytes)
    {
        size offset = 0;
        size count;
        TCHAR szFile[MAX_PATH];
        PFILE_NOTIFY_INFORMATION pNotify;
        FileWatcherEvent args;
        do
        {
            pNotify = (PFILE_NOTIFY_INFORMATION)slice(Self.frontBuffer, offset).address;
            auto arena = Self.enqueue(Self.queueHandle, sizeof(FileWatcherEvent) + pNotify->FileNameLength);
            auto event = reinterpret_cast<FileWatcherEvent*>(arena.address);
            //event->objectHandle = slice(Self.frontBuffer, offset);
            event->type = WatcherChangeTypes::Invalid;
            switch(pNotify->Action)
            {                
                case FILE_ACTION_RENAMED_NEW_NAME:
                case FILE_ACTION_ADDED:
                    args.type =WatcherChangeTypes::Created;
                    break;
                case FILE_ACTION_RENAMED_OLD_NAME:
                case FILE_ACTION_REMOVED:
                    args.type =WatcherChangeTypes::Deleted;
                    break;
                case FILE_ACTION_MODIFIED:
                    args.type =WatcherChangeTypes::Changed;                    
                    break;
            };
            //Self.enqueue(Self.queueHandle, args);
            offset += pNotify->NextEntryOffset;
        }
        while(pNotify->NextEntryOffset != 0);
    }
}

}