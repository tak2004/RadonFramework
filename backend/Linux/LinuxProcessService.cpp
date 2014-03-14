#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/backend/Linux/LinuxProcessService.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ProcessTree.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ProcessInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ThreadInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/Process/ModuleInformation.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>

#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <sys/time.h>
#include <unistd.h>

// stl
#include <ios>
#include <fstream>

using namespace std;

using namespace RadonFramework;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Time;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Diagnostics::Profiling;
using namespace RadonFramework::Diagnostics::Profiling::Process;
using namespace RadonFramework::Threading;

namespace Stat
{
    enum Type
    {
        ProcessID=0,
        Executable,
        State,//one of following modes R,S,D,Z,T,W
        ParentProcessID,
        ProcessGroupID,
        SessionID,
        TTY,
        ProcessGroupIDOfTTYOwner,
        KernelFlags,
        MinorFaultsNotRequiredLoadingFromDisk,
        MinorFaultsWaitForChildren,
        MajorFaultsNotRequiredLoadingFromDisk,
        MajorFaultsWaitForChildren,
        UserTime,
        KernelTime,
        ChildrenUserTime,
        ChildrenKernelTime,
        Priority,
        Nice,
        Reserved,
        StartTime,
        VirtualMemorySize,
        ResidentSetSize,
        RSSLimit,
        StartCode,
        EndCode,
        StartStack,
        CurrentESPValue,
        CurrentInstructionPointer,
        PendingSignals,
        BlockedSignals,
        IgnoredSignals,
        CaughtedSignals,
        WaitingChannel,
        PagecountSwapped,
        ChildPagecountSwapped,
        ExitSignal,
        Processor,
        RealtimePriority,
        SchedulingPolicy
    };
}

AutoVector<String> LinuxProcessService::GetProcessIDsByFolder(const String& Path)
{
    DIR *dp;
    struct dirent *dirp;
    AutoVector<String> ids;
    if((dp=opendir(Path.c_str())))
    {
        while ((dirp=readdir(dp)))
        {
            if (dirp->d_type==DT_DIR)
            {
                AutoPointer<String> name(new String(dirp->d_name));
                if(name->IsNumber())
                    ids.PushBack(name);
            }
        }
        closedir(dp);
    }
    return ids;
}

AutoVector<String> LinuxProcessService::ReadProcFile(const String& Path)
{
    AutoPointerArray<String> vec;
    AutoVector<String> res;
    Int32 length = 0;//proc files are stored in the memory there is no filesize
    Int32 len=0;

    ifstream proc_stream(Path.c_str(),ios_base::in);
    if (proc_stream.is_open())
    {
        RadonFramework::Memory::AutoPointerArray<char> buf;
        do
        {
            length+=1024;
            buf=RadonFramework::Memory::AutoPointerArray<char>(new char[length],length);
            len=length;
            proc_stream.read(buf.Get(),len);
        }while(len>length);
        String str(buf.Get());
        vec=str.Split(" \n");
        proc_stream.close();
    }

    for (UInt32 i=0;i<vec.Count();++i)
    {
        AutoPointer<String> str(new String(vec[i]));
        res.PushBack(str);
    }

    return res;
}

AutoPointer<ProcessTree> LinuxProcessService::GetProcessTree()
{
    String path("/proc/");
    Memory::AutoPointer<ProcessTree> tree(new ProcessTree);
    AutoVector<String> processes=GetProcessIDsByFolder(path);
    UInt32 id;
    if (processes.Size()>0)
        for (UInt32 i=0;i<processes.Size();++i)
            if (Convert::ToUInt32(*processes[i], id))
                tree->Processes.PushBack(GetProcessByID(id));
    return tree;
}

AutoPointer<ProcessInformation> LinuxProcessService::GetProcessByID(UInt32 ProcessID)
{
    String loc;
    String path("/proc/");
    String procpath(path);
    procpath+=Convert::ToString(ProcessID)+"/";

    //get overall infos
    loc=path+"stat";
    ifstream overall_stat_stream(loc.c_str(),ios_base::in);
    string cputag;
    UInt64 usermode,pnice,systemmode,idle,waitio,irqtime,softirqtime;
    overall_stat_stream>>cputag>>usermode>>pnice>>systemmode>>idle>>waitio>>irqtime>>softirqtime;
    overall_stat_stream.close();
    UInt64 totalcputime=usermode+pnice+systemmode+idle+waitio+irqtime+softirqtime;

    //process information
    loc=procpath+"stat";
    AutoVector<String> stats=ReadProcFile(loc);
    uid_t loginuid=0;
    String username;
    UInt32 pid;
    UInt64 majflt,cmajflt,cutime=0,cstime=0,starttime;//,utime,stime;

    if (stats.Size())
    {
        Convert::ToUInt32(*stats[Stat::ProcessID], pid);
        Convert::ToUInt64(*stats[Stat::MajorFaultsNotRequiredLoadingFromDisk], majflt);
        Convert::ToUInt64(*stats[Stat::MajorFaultsWaitForChildren], cmajflt);
        //utime=*stats[Stat::UserTime];
        //stime=*stats[Stat::KernelTime];
        Convert::ToUInt64(*stats[Stat::ChildrenUserTime], cutime);
        Convert::ToUInt64(*stats[Stat::ChildrenKernelTime], cstime);
        Convert::ToUInt64(*stats[Stat::StartTime], starttime);
    }

    UInt64 totalprocesscputime=cutime+cstime;

    //get uid of the user which execute the process
    loc=procpath+"loginuid";
    AutoVector<String> loginuids=ReadProcFile(loc);
    UInt64 tmpLoginUID=0;
    if (loginuids.Size())
        Convert::ToUInt64(*loginuids[0], tmpLoginUID);
    loginuid=tmpLoginUID;
    //try to find the name of the uid
    struct passwd *pws;
    pws=getpwuid(loginuid);
    if (pws)
        username=pws->pw_name;
    else//there is no username use the uid as name
        username<<static_cast<UInt32>(loginuid);

    //get binary location
    char buf[1024];
    loc=procpath+"exe";
    ssize_t len=readlink(loc.c_str(),buf,1023);
    String bin;
    if (-1==len)
    {//here you can place alternativ ways

    }
    else
        bin=String(buf,len);

    //get io infos
    string rchar,wchar,syscr,syscw,readbytes,writebytes;
    UInt64 rchar_value,wchar_value,syscr_value,syscw_value,
           readbytes_value,writebytes_value;
    loc=procpath+"io";
    AutoVector<String> ios=ReadProcFile(loc);

    ifstream io_stream(loc.c_str(),ios_base::in);
    io_stream>>rchar>>rchar_value>>wchar>>wchar_value>>syscr>>syscr_value>>
               syscw>>syscw_value>>readbytes>>readbytes_value>>writebytes>>
               writebytes_value;
    io_stream.close();

    //get memory infos
    UInt64 size,resident,shared,trs,lrs,drs,dt;
    loc=procpath+"statm";
    AutoVector<String> statms=ReadProcFile(loc);
    ifstream mem_stream(loc.c_str(),ios_base::in);
    mem_stream>>size>>resident>>shared>>trs>>lrs>>drs>>dt;
    mem_stream.close();

    AutoPointer<ProcessData> proc(new ProcessData);
    proc->ID=pid;
    String name;
    if (stats.Size())
        name=stats[Stat::Executable]->SubString(1,stats[Stat::Executable]->Length()-2);
    proc->BinaryName=bin;
    proc->Name=name;
    proc->MemoryAccessRights=true;//on linux always true
    proc->MemoryUsage=size;
    // TODO : /proc/[pid]/statm is a possible place for this information
    proc->PeakMemoryUsage=0;
    proc->UsableVirtualMemory=0;
    // TODO : /proc/[pid]/statm is a possible place for this information
    proc->NonPagedPool=0;
    // TODO : /proc/[pid]/statm is a possible place for this information
    proc->PagedPool=0;
    //process+child pagefaults which need to read from disk
    proc->PageFaultCount=majflt+cmajflt;
    proc->CreationTime=starttime;
    proc->ExitTime=0;
    proc->KernelTime=cstime*TimeSpan::TicksPerMillisecond*4;
    proc->UserTime=cutime*TimeSpan::TicksPerMillisecond*4;
    //linux don't track the operation count, each byte count as operation
    proc->ReadOperationCount=readbytes_value;
    proc->WriteOperationCount=writebytes_value;
    //sum of read and write bytes, which not belong to process
    proc->OtherOperationCount=(readbytes_value-(rchar_value+syscr_value))+
                              (writebytes_value-(wchar_value+syscw_value));
    proc->ReadTransferedBytes=proc->ReadOperationCount;
    proc->WriteTransferedBytes=proc->WriteOperationCount;
    proc->OtherTransferedBytes=proc->OtherTransferedBytes;
    proc->CPUUsage=(Float32)100*(Float32)totalprocesscputime/(Float32)totalcputime;
    proc->ExecutedByUser=username;

    //thread information
    loc=path+ProcessID+"/task/";
    AutoVector<String> threadids=GetProcessIDsByFolder(loc);
    AutoVector<ThreadInformation> threads;
    if (threadids.Size()>0)
    {
        for (UInt32 j=0;j<threadids.Size();++j)
        {
            AutoPointer<ThreadData> thread(new ThreadData);
            loc=path+ProcessID+"/task/"+*threadids[j]+"/stat";
            AutoVector<String> tstats=ReadProcFile(loc);
            UInt32 tpid;
            UInt64 tutime,tstime,tcutime,tcstime,tstarttime;
            Int32 tnice,tprio;
            if (tstats.Size())
            {
                Convert::ToUInt32(*tstats[Stat::ProcessID], tpid);
                Convert::ToInt32(*tstats[Stat::Priority], tprio);
                Convert::ToInt32(*tstats[Stat::Nice], tnice);
                Convert::ToUInt64(*tstats[Stat::UserTime], tutime);
                Convert::ToUInt64(*tstats[Stat::KernelTime], tstime);
                Convert::ToUInt64(*tstats[Stat::ChildrenUserTime], tcutime);
                Convert::ToUInt64(*tstats[Stat::ChildrenKernelTime], tcstime);
                Convert::ToUInt64(*tstats[Stat::StartTime], tstarttime);
            }
            else
                continue;
            thread->ID=tpid;
            thread->Priority=tnice!=tprio?
                                tnice>tprio?
                                    ThreadPriority::Maximal:
                                ThreadPriority::Minimal:
                             ThreadPriority::Normal;
            thread->CreationTime=tstarttime;
            thread->ExitTime=0;
            //this times are in jiffy which is 4ms since linux kernel 2.6.13
            thread->KernelTime=(tstime+tcstime)*TimeSpan::TicksPerMillisecond*4;
            thread->UserTime=(tutime+tcutime)*TimeSpan::TicksPerMillisecond*4;
            threads.PushBack(AutoPointer<ThreadInformation>(new ThreadInformation(thread)));
        }
    }

    //module information
    AutoVector<String> modules;
    AutoVector<ModuleInformation> mods;
    // TODO : /proc/[pid]/maps is a possible place but how to extract

    return AutoPointer<ProcessInformation>(new ProcessInformation(proc,mods,threads));
}

LinuxProcessService::LinuxProcessService(const String &Name)
:ProcessService(Name)
{

}

AutoPointer<ProcessInformation> LinuxProcessService::GetCurrentProcess()
{
    Memory::AutoPointer<ProcessInformation> proc;
    proc=GetProcessByID(GetCurrentProcessID());
    return proc;
}

UInt32 LinuxProcessService::GetCurrentProcessID()
{
    return getpid();
}
