module;
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include <psapi.h>
#include <tlhelp32.h>
export module rf.core.os:process_implementation;
import rf.core.types;
import rf.core.memory;
import :process;
import :time;

export namespace rf {
arr<PID> getProcessIds(StackAdapter &Scratchpad) {
  DWORD bytesWritten;
  mem arena;
  bool error;
  do {
    Scratchpad.pop(arena);
    arena = Scratchpad.push(bytesWritten+ sizeof(DWORD) * 1024);
    error = EnumProcesses(reinterpret_cast<DWORD *>(arena.address),
                                arena.bytes, &bytesWritten);
  } while (error == 0 && arena.bytes == bytesWritten);
  arr<PID> result = {reinterpret_cast<PID*>(arena.address), bytesWritten / sizeof(PID)};  
  return result;
}

PID getCurrentProcessId(){
    return GetCurrentProcessId();
}

bool getGeneralInfo(PID PId, GeneralInfo &Info, StackAdapter& Scratchpad) {
        bool result = false;
    Info.id = PId;

    HANDLE hProcess;
    hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, PId);//win vista and newer
    if (nullptr==hProcess)
    {
        hProcess=OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, PId);//win2k and newer
    }
    
    if (nullptr != hProcess)
    {
      auto arena = Scratchpad.push(MAX_PATH);
      auto bytesWritten =
          GetProcessImageFileName(hProcess, reinterpret_cast<LPSTR>(arena.address), arena.bytes);
        CloseHandle(hProcess);
        hProcess=nullptr;
        Info.binaryName = {arena.address, bytesWritten};
        result = true;
    }

    hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE, PId);
    if (hProcess!=nullptr)
    {
        HMODULE hMod;
        DWORD cbNeeded;
        if(EnumProcessModules(hProcess,&hMod,sizeof(hMod),&cbNeeded))
        {
          auto arena = Scratchpad.push(MAX_PATH);
          auto bytesWritten =
              GetModuleBaseName(hProcess, hMod, reinterpret_cast<LPSTR>(arena.address), arena.bytes);
          Info.name = {arena.address, bytesWritten};
        }
        CloseHandle(hProcess);
        hProcess=nullptr;
        result = true;
    }
    return result;
}

bool getIOInfo(PID PId, IOInfo &Info){
        bool result = false;

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION,FALSE, PId );//win vista and newer
    if (nullptr==hProcess)
    {
        hProcess=OpenProcess(PROCESS_QUERY_INFORMATION,FALSE, PId );//win2k and newer
    }

    if (nullptr != hProcess)
    {
        IO_COUNTERS c;
        if (GetProcessIoCounters(hProcess, &c) != 0)
        {
            Info.readOperationCount=c.ReadOperationCount;
            Info.readTransferedBytes=c.ReadTransferCount;
            Info.writeOperationCount=c.WriteOperationCount;
            Info.writeTransferedBytes=c.WriteTransferCount;
            Info.otherOperationCount=c.OtherOperationCount;
            Info.otherTransferedBytes=c.OtherTransferCount;
            result = true;
        }
        CloseHandle(hProcess);
        hProcess=nullptr;
    }
    return result;
}

bool getMemoryInfo(PID PId, MemoryInfo &Info){
        PROCESS_MEMORY_COUNTERS pmc;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE, PId );

    if (nullptr != hProcess)
    {
        Info.memoryAccessRights = true;
        if ( GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
        {
            Info.memoryUsage = pmc.WorkingSetSize;
            Info.peakMemoryUsage = pmc.PeakWorkingSetSize;
            Info.usableVirtualMemory = pmc.PagefileUsage;
            Info.nonPagedPool = pmc.QuotaNonPagedPoolUsage;
            Info.pagedPool = pmc.QuotaPagedPoolUsage;
            Info.pageFaultCount = pmc.PageFaultCount;
        }
        CloseHandle(hProcess);
        hProcess=nullptr;
    }
    else
    {
        Info.memoryAccessRights = false;
    }
    return true;
}

timeval FILETIMEToTimeSpan(const FILETIME &Time)  {
  timeval t = (static_cast<timeval>(Time.dwHighDateTime)) << 32;
  t += Time.dwLowDateTime;
  return t; 
}

timeval FILETIMEToDate(const FILETIME &Time)  {
  timeval t = (static_cast<timeval>(Time.dwHighDateTime)) << 32;
  t += Time.dwLowDateTime;
  t += DateTime::CreateByTime(1601, 1, 1).refDelta.ticks;
  return t;
}

bool getTimingInfo(PID PId, TimingInfo &Info){
        bool result = false;
    HANDLE hProcess=OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION,FALSE, PId );//win vista and newer
    if (nullptr==hProcess)
    {
        hProcess=OpenProcess(PROCESS_QUERY_INFORMATION,FALSE, PId );//win2k and newer
    }

    if (nullptr != hProcess)
    {
        FILETIME ct = {0, 0}, et = {0, 0}, kt = {0, 0}, ut = {0, 0};

        if (GetProcessTimes(hProcess, &ct, &et, &kt, &ut) != 0)
        {
            Info.creationTime = FILETIMEToDate(ct);
            Info.exitTime = FILETIMEToDate(et);
            Info.kernelTime = FILETIMEToTimeSpan(kt);
            Info.userTime = FILETIMEToTimeSpan(ut);
            result = true;
        }
        CloseHandle(hProcess);
        hProcess=nullptr;
    }
    return result;
}

arr<ThreadInfo> getThreadInfo(PID PId, StackAdapter &Scratchpad) {
    arr<ThreadInfo> result;
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap != INVALID_HANDLE_VALUE)
    {
        te32.dwSize = sizeof(THREADENTRY32);
        if(Thread32First(hThreadSnap, &te32) != 0)
        {
            do
            {
                if(te32.th32OwnerProcessID == PId)
                {
                    HANDLE hThread=nullptr;
                    hThread=OpenThread(THREAD_QUERY_LIMITED_INFORMATION,0,te32.th32ThreadID);
                    if(hThread==nullptr)
                    {
                        hThread=OpenThread(THREAD_QUERY_INFORMATION,0,te32.th32ThreadID);
                    }
                    if (hThread!=nullptr)
                    {
                        auto arena = Scratchpad.push(sizeof(ThreadInfo));
                        auto info = reinterpret_cast<ThreadInfo *>(arena.address);
                        if (result.elements == nullptr)
                          result.elements = info;
                        result.count++;

                        int prio=GetThreadPriority(hThread);
                        switch(prio)
                        {
                        case THREAD_PRIORITY_ABOVE_NORMAL:
                            info->priority = ThreadPriority::Maximal;
                            break;
                        case THREAD_PRIORITY_BELOW_NORMAL:
                            info->priority = ThreadPriority::Minimal;
                            break;
                        case THREAD_PRIORITY_HIGHEST:
                            info->priority = ThreadPriority::Maximal;
                            break;
                        case THREAD_PRIORITY_IDLE:
                            info->priority = ThreadPriority::Minimal;
                            break;
                        case THREAD_PRIORITY_LOWEST:
                            info->priority = ThreadPriority::Minimal;
                            break;
                        case THREAD_PRIORITY_NORMAL:
                            info->priority = ThreadPriority::Normal;
                            break;
                        case THREAD_PRIORITY_TIME_CRITICAL:
                            info->priority = ThreadPriority::Maximal;
                            break;
                        default:
                            info->priority = ThreadPriority::Normal;
                        }
                        CloseHandle(hThread);
                        hThread = nullptr;

                        FILETIME ct = {0, 0}, et = {0, 0}, kt = {0, 0}, ut = {0, 0};

                        if (GetThreadTimes(hThread, &ct, &et, &kt, &ut) != 0)
                        {
                            info->timing.creationTime = FILETIMEToDate(ct);
                            info->timing.exitTime = FILETIMEToDate(et);
                            info->timing.kernelTime = FILETIMEToTimeSpan(kt);
                            info->timing.userTime = FILETIMEToTimeSpan(ut);
                        }

                        info->id = te32.th32ThreadID;
                        CloseHandle(hThread);                        
                    }
                }
            } while (Thread32Next(hThreadSnap, &te32) != 0);
        }
        CloseHandle(hThreadSnap);
    }
    return result;
}

PID executeProgram(strview Executeable, strview Parameters,
                   StackAdapter &Scratchpad) {
    	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
    mem arena = Scratchpad.push(Executeable.bytes + Parameters.bytes + 2);
    copy({Executeable.address,Executeable.bytes}, arena);
    copy({Parameters.address, Parameters.bytes},
         slice(arena, Executeable.bytes + 1));
    auto p = reinterpret_cast<char *>(arena.address);
	if (CreateProcessA(nullptr, p, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi) == FALSE) {
		return -1;
    }
	WaitForSingleObject(pi.hProcess, INFINITE);
    Scratchpad.pop(arena);
	return 0;
}
} // namespace rf