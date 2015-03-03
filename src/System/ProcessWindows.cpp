#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Process.hpp"
#include "RadonFramework/System/Process/GeneralInfo.hpp"
#include "RadonFramework/System/Process/IOInfo.hpp"
#include "RadonFramework/System/Process/MemoryInfo.hpp"
#include "RadonFramework/System/Process/TimingInfo.hpp"
#include "RadonFramework/System/Process/ModuleInfo.hpp"
#include "RadonFramework/System/Process/ThreadInfo.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"
#include "RadonFramework/Time/DateTime.hpp"
#include <Windows.h>
#include <psapi.h>
#include <TlHelp32.h>

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Time;
using namespace RadonFramework::Threading;

AutoPointerArray<RF_Type::UInt32> GetProcessList()
{
    AutoPointerArray<RF_Type::UInt32> result;
    
    RF_Type::UInt32 processcount=0;
    AutoPointerArray<RF_Type::UInt32> processes;
    RF_Type::UInt32 UsedMemory;

    do
    {
        processcount += 1024;
        processes = AutoPointerArray<RF_Type::UInt32>(new RF_Type::UInt32[processcount], processcount);
        EnumProcesses((DWORD*)processes.Get(), processcount*sizeof(RF_Type::UInt32),
                      (LPDWORD)&UsedMemory);
    } while (processcount * sizeof(RF_Type::UInt32) == UsedMemory);
    processcount = UsedMemory / sizeof(RF_Type::UInt32);
    result = AutoPointerArray<RF_Type::UInt32>(new RF_Type::UInt32[processcount], processcount);
    RF_SysMem::Copy(result.Get(), processes.Get(), UsedMemory);

    return result;
}

// Append "Implementation" at function name to avoid name collision with windows.
RF_Type::UInt32 GetCurrentProcessIdImplementation()
{
    return static_cast<RF_Type::UInt32>(GetCurrentProcessId());
}

TimeSpan FILETIMEToTimeSpan(const FILETIME &Time)
{
    UInt64 t=((UInt64)Time.dwHighDateTime)<<32;
    t+=Time.dwLowDateTime;
    return TimeSpan::CreateByTicks(t);
}

DateTime FILETIMEToDate(const FILETIME &Time)
{
    UInt64 t = ((UInt64)Time.dwHighDateTime)<<32;
    t += Time.dwLowDateTime;
    t += DateTime::CreateByTime(1601, 1, 1).Ticks();
    return DateTime::CreateByTicks(t);
}

RF_Type::Bool GetGeneralInfo(RF_Type::UInt32 PId, RFPROC::GeneralInfo& Info)
{
    RF_Type::Bool result = false;
    Info.ID = PId;

    HANDLE hProcess;
    hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, PId);//win vista and newer
    if (NULL==hProcess)
    {
        hProcess=OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, PId);//win2k and newer
    }

    if (NULL != hProcess)
    {
        TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
        GetProcessImageFileName(hProcess, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
        CloseHandle(hProcess);
        hProcess=NULL;
        Info.BinaryName = String(szProcessName, MAX_PATH);
        result = true;
    }

    hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE, PId);
    if (hProcess!=NULL)
    {
        HMODULE hMod;
        DWORD cbNeeded;
        if(EnumProcessModules(hProcess,&hMod,sizeof(hMod),&cbNeeded))
        {
            TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
            GetModuleBaseName(hProcess,hMod,szProcessName,sizeof(szProcessName)/sizeof(TCHAR));
            Info.Name = String(szProcessName, MAX_PATH);
        }
        CloseHandle(hProcess);
        hProcess=NULL;
        result = true;
    }
    return result;
}

RF_Type::Bool GetIOInfo(RF_Type::UInt32 PId, RFPROC::IOInfo& Info)
{
    RF_Type::Bool result = false;

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION,FALSE, PId );//win vista and newer
    if (NULL==hProcess)
    {
        hProcess=OpenProcess(PROCESS_QUERY_INFORMATION,FALSE, PId );//win2k and newer
    }

    if (NULL != hProcess)
    {
        IO_COUNTERS c;
        if (GetProcessIoCounters(hProcess, &c))
        {
            Info.ReadOperationCount=c.ReadOperationCount;
            Info.ReadTransferedBytes=c.ReadTransferCount;
            Info.WriteOperationCount=c.WriteOperationCount;
            Info.WriteTransferedBytes=c.WriteTransferCount;
            Info.OtherOperationCount=c.OtherOperationCount;
            Info.OtherTransferedBytes=c.OtherTransferCount;
            result = true;
        }
        CloseHandle(hProcess);
        hProcess=NULL;
    }
    return result;
}

RF_Type::Bool GetMemoryInfo(RF_Type::UInt32 PId, RFPROC::MemoryInfo& Info)
{
    PROCESS_MEMORY_COUNTERS pmc;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE, PId );

    if (NULL != hProcess)
    {
        Info.MemoryAccessRights = true;
        if ( GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
        {
            Info.MemoryUsage = pmc.WorkingSetSize;
            Info.PeakMemoryUsage = pmc.PeakWorkingSetSize;
            Info.UsableVirtualMemory = pmc.PagefileUsage;
            Info.NonPagedPool = pmc.QuotaNonPagedPoolUsage;
            Info.PagedPool = pmc.QuotaPagedPoolUsage;
            Info.PageFaultCount = pmc.PageFaultCount;
        }
        CloseHandle(hProcess);
        hProcess=NULL;
    }
    else
    {
        Info.MemoryAccessRights = false;
    }
    return true;
}

RF_Type::Bool GetTimingInfo(RF_Type::UInt32 PId, RFPROC::TimingInfo& Info)
{
    RF_Type::Bool result = false;
    HANDLE hProcess=OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION,FALSE, PId );//win vista and newer
    if (NULL==hProcess)
    {
        hProcess=OpenProcess(PROCESS_QUERY_INFORMATION,FALSE, PId );//win2k and newer
    }

    if (NULL != hProcess)
    {
        FILETIME ct = {0, 0}, et = {0, 0}, kt = {0, 0}, ut = {0, 0};

        if (GetProcessTimes(hProcess, &ct, &et, &kt, &ut))
        {
            Info.CreationTime = FILETIMEToDate(ct);
            Info.ExitTime = FILETIMEToDate(et);
            Info.KernelTime = FILETIMEToTimeSpan(kt);
            Info.UserTime = FILETIMEToTimeSpan(ut);
            result = true;
        }
        CloseHandle(hProcess);
        hProcess=NULL;
    }
    return result;
}

RF_Type::Bool GetModuleInfo(RF_Type::UInt32 PId, RFPROC::ModuleInfo& Info)
{
    RF_Type::Bool result = false;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                  FALSE, PId);
    if (hProcess)
    {
        HMODULE hMods[1024];
        DWORD cbNeeded;
        if( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
        {
            Info.Resize(cbNeeded / sizeof(HMODULE));
            for (UInt32 i = 0; i < Info.Count(); ++i)
            {
                TCHAR szModName[MAX_PATH];
                if (GetModuleFileNameEx(hProcess, hMods[i], szModName,
                    sizeof(szModName) / sizeof(TCHAR)))
                {
                    Info(i) = String(szModName, MAX_PATH);
                }
            }
            result = true;
        }
        CloseHandle( hProcess );
    }
    return result;
}

RF_Type::Bool GetThreadInfo(RF_Type::UInt32 PId, RFPROC::ThreadInfoList& Info)
{
    RF_Type::Bool result = false;
    HANDLE hThreadSnap = INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hThreadSnap != INVALID_HANDLE_VALUE)
    {
        te32.dwSize = sizeof(THREADENTRY32);
        RF_Type::UInt32 amount = 0, i = 0;
        if(Thread32First(hThreadSnap, &te32))
        {
            do
            {
                if (te32.th32OwnerProcessID == PId)
                {
                    ++amount;
                }
            }
            while(Thread32Next(hThreadSnap, &te32));

            Info.Resize(amount);
            Thread32First(hThreadSnap, &te32);

            do
            {
                if(te32.th32OwnerProcessID == PId)
                {
                    HANDLE hThread=NULL;
                    hThread=OpenThread(THREAD_QUERY_LIMITED_INFORMATION,false,te32.th32ThreadID);
                    if(hThread==NULL)
                    {
                        hThread=OpenThread(THREAD_QUERY_INFORMATION,false,te32.th32ThreadID);
                    }

                    if (hThread!=NULL)
                    {
                        int prio=GetThreadPriority(hThread);
                        switch(prio)
                        {
                        case THREAD_PRIORITY_ABOVE_NORMAL:
                            Info(i).Priority = ThreadPriority::Maximal;
                            break;
                        case THREAD_PRIORITY_BELOW_NORMAL:
                            Info(i).Priority = ThreadPriority::Minimal;
                            break;
                        case THREAD_PRIORITY_HIGHEST:
                            Info(i).Priority = ThreadPriority::Maximal;
                            break;
                        case THREAD_PRIORITY_IDLE:
                            Info(i).Priority = ThreadPriority::Minimal;
                            break;
                        case THREAD_PRIORITY_LOWEST:
                            Info(i).Priority = ThreadPriority::Minimal;
                            break;
                        case THREAD_PRIORITY_NORMAL:
                            Info(i).Priority = ThreadPriority::Normal;
                            break;
                        case THREAD_PRIORITY_TIME_CRITICAL:
                            Info(i).Priority = ThreadPriority::Maximal;
                            break;
                        default:
                            Info(i).Priority = ThreadPriority::Normal;
                        }
                        CloseHandle(hThread);
                        hThread = NULL;
                    }

                    hThread = OpenThread(THREAD_QUERY_LIMITED_INFORMATION,false,te32.th32ThreadID);
                    if(hThread == NULL)
                    {
                        hThread = OpenThread(THREAD_QUERY_INFORMATION, false, te32.th32ThreadID);
                    }

                    if (hThread != NULL)
                    {
                        FILETIME ct = {0, 0}, et = {0, 0}, kt = {0, 0}, ut = {0, 0};

                        if (GetThreadTimes(hThread, &ct, &et, &kt, &ut))
                        {
                            Info(i).CreationTime = FILETIMEToDate(ct);
                            Info(i).ExitTime = FILETIMEToDate(et);
                            Info(i).KernelTime = FILETIMEToTimeSpan(kt);
                            Info(i).UserTime = FILETIMEToTimeSpan(ut);
                        }
                        CloseHandle(hThread);
                    }

                    Info(i).ID = te32.th32ThreadID;
                    ++i;
                }
            } while (Thread32Next(hThreadSnap, &te32));
            result = true;
        }
        CloseHandle(hThreadSnap);
    }
    return result;
}

RF_Type::Int32 ExecuteProgram(const RF_Type::String& Executable,
	const RF_Type::String& Parameters)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	RF_Type::String cmd(Executable + " " + Parameters);
	char* p = const_cast<char*>(cmd.c_str());
	if (CreateProcessA(0, p, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) == FALSE)
		return -1;

	WaitForSingleObject(pi.hProcess, INFINITE);
	return 0;
}

RF_Type::Bool OpenWithDefaultApplication(const RF_Type::String& What)
{
    return ShellExecute(0, "open", What.c_str(), 0, 0, SW_SHOWNORMAL) != 0;
}

void RFPROC::Dispatch()
{
    GetProcessList = ::GetProcessList;
    GetCurrentProcessId = ::GetCurrentProcessIdImplementation;
    GetGeneralInfo = ::GetGeneralInfo;
    GetIOInfo = ::GetIOInfo;
    GetMemoryInfo = ::GetMemoryInfo;
    GetTimingInfo = ::GetTimingInfo;
    GetModuleInfo = ::GetModuleInfo;
    GetThreadInfo = ::GetThreadInfo;
	ExecuteProgram = ::ExecuteProgram;
    OpenWithDefaultApplication = ::OpenWithDefaultApplication;
}