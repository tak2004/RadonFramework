#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Process.hpp"
#include "RadonFramework/System/Process/GeneralInfo.hpp"
#include "RadonFramework/System/Process/IOInfo.hpp"
#include "RadonFramework/System/Process/MemoryInfo.hpp"
#include "RadonFramework/System/Process/TimingInfo.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"
#include "RadonFramework/Time/DateTime.hpp"
#include <Windows.h>
#include <psapi.h>

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Time;

AutoPointerArray<RFTYPE::UInt32> GetProcessList()
{
    AutoPointerArray<RFTYPE::UInt32> result;
    
    RFTYPE::UInt32 processcount=0;
    AutoPointerArray<RFTYPE::UInt32> processes;
    RFTYPE::UInt32 UsedMemory;

    do
    {
        processcount += 1024;
        processes = AutoPointerArray<RFTYPE::UInt32>(new RFTYPE::UInt32[processcount], processcount);
        EnumProcesses((DWORD*)processes.Get(), processcount*sizeof(RFTYPE::UInt32),
                      (LPDWORD)&UsedMemory);
    } while (processcount * sizeof(RFTYPE::UInt32) == UsedMemory);
    processcount = UsedMemory / sizeof(RFTYPE::UInt32);
    result = AutoPointerArray<RFTYPE::UInt32>(new RFTYPE::UInt32[processcount], processcount);
    RFMEM::Copy(result.Get(), processes.Get(), UsedMemory);

    return result;
}

// Append "Implementation" at function name to avoid name collision with windows.
RFTYPE::UInt32 GetCurrentProcessIdImplementation()
{
    return static_cast<RFTYPE::UInt32>(GetCurrentProcessId());
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

RFTYPE::Bool GetGeneralInfo(RFTYPE::UInt32 PId, RFPROC::GeneralInfo& Info)
{
    RFTYPE::Bool result = false;
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
        Info.BinaryName = String(szProcessName);
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
            Info.Name = String(szProcessName);
        }
        CloseHandle(hProcess);
        hProcess=NULL;
        result = true;
    }
    return result;
}

RFTYPE::Bool GetIOInfo(RFTYPE::UInt32 PId, RFPROC::IOInfo& Info)
{
    RFTYPE::Bool result = false;

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

RFTYPE::Bool GetMemoryInfo(RFTYPE::UInt32 PId, RFPROC::MemoryInfo& Info)
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

RFTYPE::Bool GetTimingInfo(RFTYPE::UInt32 PId, RFPROC::TimingInfo& Info)
{
    RFTYPE::Bool result = false;
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

void RFPROC::Dispatch()
{
    GetProcessList = ::GetProcessList;
    GetCurrentProcessId = ::GetCurrentProcessIdImplementation;
    GetGeneralInfo = ::GetGeneralInfo;
    GetIOInfo = ::GetIOInfo;
    GetMemoryInfo = ::GetMemoryInfo;
    GetTimingInfo = ::GetTimingInfo;
}