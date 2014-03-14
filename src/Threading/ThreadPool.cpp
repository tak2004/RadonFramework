#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Threading/ThreadPool.hpp>
#include "RadonFramework/Math/Math.hpp"

using namespace RadonFramework;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Threading;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Threading;
using namespace RadonFramework::System;

struct ThreadPoolData
{
    ThreadPoolData()
    :MaxWorkerThreads(0)
    ,MaxCompletionPortThreads(0)
    ,MinWorkerThreads(0)
    ,MinCompletionPortThreads(0)
    ,Running(true)
    {
    }

    Array<AutoPointer<PoolThread> > WorkerThreads;
    //Array<AutoPointer<Thread> > CompletionPortThreads;
    Queue<PoolTask> ConcurrentTaskList;
    Array<Queue<PoolTask> > SerialTaskLists;
    Mutex Busy;
    Condition TaskListChanged;
    UInt32 MaxWorkerThreads;
    UInt32 MaxCompletionPortThreads;
    UInt32 MinWorkerThreads;
    UInt32 MinCompletionPortThreads;
    Bool Running;
};

static ThreadPoolData* Data=0;

void RadonFramework::Threading::InitializeThreadPool(UInt32 LogicalProcessorCount)
{
    if (Data==0)
    {
        Data=new ThreadPoolData();
        UInt32 lp=Math::Math<UInt32>::Max(LogicalProcessorCount,1)<<1;// twice more as logical processor count
        Data->SerialTaskLists.Resize(lp);
        Data->WorkerThreads.Resize(lp);
        for (UInt32 i=0;i<Data->WorkerThreads.Count();++i)
        {
            Data->WorkerThreads(i)=AutoPointer<PoolThread>(new PoolThread());
            Data->WorkerThreads(i)->Start();
        }
    }
}

void RadonFramework::Threading::ShutdownThreadPool()
{
    Data->Running=false;
    ThreadPool::SetMaxThreads(0,0);
    ThreadPool::SetMinThreads(0,0);

    // signal all threads to cancel
    for (UInt32 i=0;i<Data->WorkerThreads.Count();++i)
        Data->WorkerThreads(i)->Interrupt();
        
    {// clean up the list and trigger a change that the threads can leave Wait()
        Scopelock lock(Data->Busy);
        Data->ConcurrentTaskList.Clear();
        Data->SerialTaskLists.Resize(0);
        Data->TaskListChanged.NotifyAll();
    }

    // wait till all threads are finished
    for (UInt32 i=0;i<Data->WorkerThreads.Count();++i)
        Data->WorkerThreads(i)->Join();

    // clean up threads
    Data->WorkerThreads.Resize(0);
}

void ThreadPool::GetMaxThreads(UInt32& WorkerThreads, UInt32& CompletionPortThreads)
{
    WorkerThreads=Data->MaxWorkerThreads;
    CompletionPortThreads=Data->MaxCompletionPortThreads;
}

Bool ThreadPool::SetMaxThreads(UInt32 WorkerThreads, UInt32 CompletionPortThreads)
{
    Data->MaxWorkerThreads=WorkerThreads;
    Data->MaxCompletionPortThreads=CompletionPortThreads;
    return true;
}

void ThreadPool::GetMinThreads(UInt32& WorkerThreads, UInt32& CompletionPortThreads)
{
    WorkerThreads=Data->MinWorkerThreads;
    CompletionPortThreads=Data->MinCompletionPortThreads;
}

Bool ThreadPool::SetMinThreads(UInt32 WorkerThreads, UInt32 CompletionPortThreads)
{
    Data->MinWorkerThreads=WorkerThreads;
    Data->MinCompletionPortThreads=CompletionPortThreads;
    return true;
}

void ThreadPool::GetAvailableThreads(UInt32& WorkerThreads, UInt32& CompletionPortThreads)
{
    //WorkerThreads=Data->MaxWorkerThreads-Data->WorkerThreads.Count();
    //CompletionPortThreads=Data->MaxCompletionPortThreads-Data->CompletionPortThreads.Count();
}
/*
Bool ThreadPool::BindHandle(ISafeHandle* OSHandle)
{
    return false;
}*/

Bool ThreadPool::QueueUserWorkItem(WaitCallback Callback, TaskStrategy::Type Strategy, 
                                   Bool AutoCleanup)
{
    return QueueUserWorkItem(Callback, 0, Strategy, AutoCleanup);
}

Bool ThreadPool::QueueUserWorkItem(WaitCallback Callback, void* State,
                                   TaskStrategy::Type Strategy, Bool AutoCleanup)
{
    if (Data->Running)
    {
        PoolTask task(Callback,State,AutoCleanup);
        Scopelock lock(Data->Busy);
        if (Strategy==TaskStrategy::Concurrent)
            Data->ConcurrentTaskList.Enqueue(task);
        else
        {
            Int64 serialGrp=Thread::CurrentPid()%Data->WorkerThreads.Count();
            Data->SerialTaskLists(static_cast<UInt32>(serialGrp)).Enqueue(task);
        }   
        Data->TaskListChanged.NotifyAll();
        return true;
    }
    return false;
}

/*
RegistersedWaitHandle ThreadPool::RegistersWaitForSingleObject(IWaitHandle* WaitObject, 
    WaitOrTimerCallback Callback, void* Sate, Int32 MilisecondsTimeOutInterval,
    Bool ExecuteOnlyOnce)
{
    return RegistersedWaitHandle();
}*/

void PoolThread::Run()
{
    PoolTask task;
    Bool result=false;
    Int64 serialGrp=Thread::CurrentPid()%Data->WorkerThreads.Count();
    while(true)
    {
        {
            Scopelock lock(Data->Busy);            
            result=Data->SerialTaskLists(static_cast<UInt32>(serialGrp)).Dequeue(task);
        }
        if (false==result)
        {
            {
                Scopelock lock(Data->Busy);            
                result=Data->ConcurrentTaskList.Dequeue(task);
            }
            if (false==result)
                Data->TaskListChanged.Wait(Data->Busy);
        }

        if (result)
        {
            task.Callback(task.Data);

            if (task.Data && task.AutoCleanup)
            {
                delete task.Data;
                task.Data=0;
            }
        }
        
        CheckCancel();
    }
}

PoolTask::PoolTask()
:Data(0)
{
}

PoolTask::~PoolTask()
{
    if (Data)
        delete Data;
}

PoolTask::PoolTask(ThreadPool::WaitCallback Callback, void* Data, Bool AutoCleanup)
:Callback(Callback)
,Data(Data)
,AutoCleanup(AutoCleanup)
{
}

PoolTask::PoolTask(const PoolTask& Copy)
{
    *this=Copy;
}

PoolTask& PoolTask::operator=(const PoolTask& Other)
{
    Callback=Other.Callback;
    Data=Other.Data;
    Other.Data=0;
    AutoCleanup=Other.AutoCleanup;
    return *this;
}
