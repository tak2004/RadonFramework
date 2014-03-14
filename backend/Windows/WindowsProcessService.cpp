#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/backend/Windows/WindowsProcessService.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ProcessTree.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ProcessInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ThreadInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ModuleInformation.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>

#include <Windows.h>
#include <psapi.h>
#include <TlHelp32.h>

using namespace RadonFramework;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Time;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Diagnostics::Profiling;
using namespace RadonFramework::Diagnostics::Profiling::Process;

WindowsProcessService::WindowsProcessService( const String &Name )
:ProcessService(Name)
{
}

AutoPointer<ProcessTree> WindowsProcessService::GetProcessTree()
{
    AutoPointer<ProcessTree> tree(new ProcessTree);

    UInt32 processcount=0;
    AutoPointerArray<UInt32> processes;
    UInt32 UsedMemory;

    do
    {
        processcount+=1024;
        processes=AutoPointerArray<UInt32>(new UInt32[processcount],processcount);
        EnumProcesses((DWORD*)processes.Get(), processcount*sizeof(UInt32), (LPDWORD)&UsedMemory );
    }while(processcount*sizeof(UInt32)==UsedMemory);
    processcount=UsedMemory/sizeof(UInt32);

    if (processcount>0)
    {
        for(UInt32 i=0;i<processcount;++i)
        {
            AutoPointer<ProcessInformation> proc=GetProcessByID(processes[i]);
            tree->Processes.PushBack(proc);
        }
    }
    return tree;
}

Memory::AutoPointer<ProcessInformation> WindowsProcessService::GetProcessByID( UInt32 ProcessID )
{
    Memory::AutoPointer<ProcessInformation> proc;
    HANDLE hProcess=NULL;
    AutoPointer<ProcessData> data(new ProcessData);
    RFMEM::Set(data.Get(),0,sizeof(ProcessData));

    PROCESS_MEMORY_COUNTERS pmc;
    hProcess=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE, ProcessID );

    if (NULL != hProcess)
    {
        data->MemoryAccessRights=true;
        if ( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc)) )
        {
            data->MemoryUsage=pmc.WorkingSetSize;
            data->PeakMemoryUsage=pmc.PeakWorkingSetSize;
            data->UsableVirtualMemory=pmc.PagefileUsage;
            data->NonPagedPool=pmc.QuotaNonPagedPoolUsage;
            data->PagedPool=pmc.QuotaPagedPoolUsage;
            data->PageFaultCount=pmc.PageFaultCount;
        }
        CloseHandle( hProcess );
        hProcess=NULL;
    }
    else
        data->MemoryAccessRights=false;

    hProcess=OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION,FALSE, ProcessID );//win vista and newer
    if (NULL==hProcess)
        hProcess=OpenProcess(PROCESS_QUERY_INFORMATION,FALSE, ProcessID );//win2k and newer
    if (NULL != hProcess)
    {
        TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
        GetProcessImageFileName(hProcess,szProcessName,sizeof(szProcessName)/sizeof(TCHAR));
        CloseHandle(hProcess);
        hProcess=NULL;
        data->BinaryName=String(szProcessName);
    }

    hProcess=OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,ProcessID);
    if (hProcess!=NULL)
    {
        HMODULE hMod;
        DWORD cbNeeded;
        if(EnumProcessModules(hProcess,&hMod,sizeof(hMod),&cbNeeded))
        {
            TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
            GetModuleBaseName(hProcess,hMod,szProcessName,sizeof(szProcessName)/sizeof(TCHAR));
            data->Name=String(szProcessName);
        }
        CloseHandle(hProcess);
        hProcess=NULL;
    }

    hProcess=OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION,FALSE, ProcessID );//win vista and newer
    if (NULL==hProcess)
        hProcess=OpenProcess(PROCESS_QUERY_INFORMATION,FALSE, ProcessID );//win2k and newer
    if (NULL != hProcess)
    {
        FILETIME ct={0,0},et={0,0},kt={0,0},ut={0,0};

        if (GetProcessTimes(hProcess,&ct,&et,&kt,&ut))
        {
            data->CreationTime=FILETIMEToDate(ct);
            data->ExitTime=FILETIMEToDate(et);
            data->KernelTime=FILETIMEToTimeSpan(kt);
            data->UserTime=FILETIMEToTimeSpan(ut);
        }
        CloseHandle(hProcess);
        hProcess=NULL;
    }

    hProcess=OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION,FALSE, ProcessID );//win vista and newer
    if (NULL==hProcess)
        hProcess=OpenProcess(PROCESS_QUERY_INFORMATION,FALSE, ProcessID );//win2k and newer
    if (NULL != hProcess)
    {
        IO_COUNTERS c;

        if (GetProcessIoCounters(hProcess,&c))
        {
            data->ReadOperationCount=c.ReadOperationCount;
            data->ReadTransferedBytes=c.ReadTransferCount;
            data->WriteOperationCount=c.WriteOperationCount;
            data->WriteTransferedBytes=c.WriteTransferCount;
            data->OtherOperationCount=c.OtherOperationCount;
            data->OtherTransferedBytes=c.OtherTransferCount;
        }
        CloseHandle(hProcess);
        hProcess=NULL;
    }

    AutoVector<ThreadInformation> Threads;
    HANDLE hThreadSnap=INVALID_HANDLE_VALUE;
    THREADENTRY32 te32;
    hThreadSnap=CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,0);
    if (hThreadSnap!=INVALID_HANDLE_VALUE)
    {
        te32.dwSize=sizeof(THREADENTRY32);
        if(Thread32First(hThreadSnap,&te32))
        {
            do
            {
                if(te32.th32OwnerProcessID==ProcessID)
                {
                    AutoPointer<ThreadData> thread(new ThreadData);
                    RFMEM::Set(thread.Get(),0,sizeof(ThreadData));

                    HANDLE hThread=NULL;
                    hThread=OpenThread(THREAD_QUERY_LIMITED_INFORMATION,false,te32.th32ThreadID);
                    if(hThread==NULL)
                        hThread=OpenThread(THREAD_QUERY_INFORMATION,false,te32.th32ThreadID);
                    if (hThread!=NULL)
                    {
                        int prio=GetThreadPriority(hThread);
                        switch(prio)
                        {
                        case THREAD_PRIORITY_ABOVE_NORMAL:
                            thread->Priority=RadonFramework::Threading::ThreadPriority::Maximal;
                            break;
                        case THREAD_PRIORITY_BELOW_NORMAL:
                            thread->Priority=RadonFramework::Threading::ThreadPriority::Minimal;
                            break;
                        case THREAD_PRIORITY_HIGHEST:
                            thread->Priority=RadonFramework::Threading::ThreadPriority::Maximal;
                            break;
                        case THREAD_PRIORITY_IDLE:
                            thread->Priority=RadonFramework::Threading::ThreadPriority::Minimal;
                            break;
                        case THREAD_PRIORITY_LOWEST:
                            thread->Priority=RadonFramework::Threading::ThreadPriority::Minimal;
                            break;
                        case THREAD_PRIORITY_NORMAL:
                            thread->Priority=RadonFramework::Threading::ThreadPriority::Normal;
                            break;
                        case THREAD_PRIORITY_TIME_CRITICAL:
                            thread->Priority=RadonFramework::Threading::ThreadPriority::Maximal;
                            break;
                        default:
                            thread->Priority=RadonFramework::Threading::ThreadPriority::Normal;
                        }
                        CloseHandle(hThread);
                        hThread=NULL;
                    }

                    hThread=OpenThread(THREAD_QUERY_LIMITED_INFORMATION,false,te32.th32ThreadID);
                    if(hThread==NULL)
                        hThread=OpenThread(THREAD_QUERY_INFORMATION,false,te32.th32ThreadID);
                    if (hThread!=NULL)
                    {
                        FILETIME ct={0,0},et={0,0},kt={0,0},ut={0,0};

                        if (GetThreadTimes(hThread,&ct,&et,&kt,&ut))
                        {
                            thread->CreationTime=FILETIMEToDate(ct);
                            thread->ExitTime=FILETIMEToDate(et);
                            thread->KernelTime=FILETIMEToTimeSpan(kt);
                            thread->UserTime=FILETIMEToTimeSpan(ut);
                        }
                        CloseHandle(hThread);
                    }

                    thread->ID=te32.th32ThreadID;
                    Threads.PushBack(AutoPointer<ThreadInformation>(new ThreadInformation(thread)));
                }
            } while (Thread32Next(hThreadSnap,&te32));
        }
        CloseHandle(hThreadSnap);
    }

    AutoVector<ModuleInformation> Modules;
    hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                            FALSE, ProcessID );
    if (hProcess)
    {
        HMODULE hMods[1024];
        DWORD cbNeeded;
        if( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
        {
            for ( UInt32 i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
            {
                TCHAR szModName[MAX_PATH];
                if ( GetModuleFileNameEx( hProcess, hMods[i], szModName,
                    sizeof(szModName) / sizeof(TCHAR)))
                {
                    String name(szModName);
                    Modules.PushBack(AutoPointer<ModuleInformation>(new ModuleInformation(name)));
                }
            }
        }
        CloseHandle( hProcess );
    }

    proc=AutoPointer<ProcessInformation>(new ProcessInformation(data,Modules,Threads));
    return proc;
}

Memory::AutoPointer<ProcessInformation> WindowsProcessService::GetCurrentProcess()
{
    Memory::AutoPointer<ProcessInformation> proc;
    proc=GetProcessByID(GetCurrentProcessID());
    return proc;
}

RadonFramework::Time::TimeSpan WindowsProcessService::FILETIMEToTimeSpan(const FILETIME &Time)
{
    UInt64 t=((UInt64)Time.dwHighDateTime)<<32;
    t+=Time.dwLowDateTime;
    return TimeSpan(t);
}

RadonFramework::Time::DateTime WindowsProcessService::FILETIMEToDate(const FILETIME &Time)
{
    UInt64 t=((UInt64)Time.dwHighDateTime)<<32;
    t+=Time.dwLowDateTime;
    t+=DateTime(1601,1,1).Ticks();
    return DateTime(t);
}

UInt32 WindowsProcessService::GetCurrentProcessID()
{
    return (UInt32)GetCurrentProcessId();
}