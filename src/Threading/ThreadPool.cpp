#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Threading/ThreadPool.hpp"
#include "RadonFramework/System/Hardware/Hardware.hpp"
#include "RadonFramework/Time/ScopeTimer.hpp"

using namespace RadonFramework;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Threading;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Idioms;
using namespace RadonFramework::System::Threading;
using namespace RadonFramework::System;

class PoolTask
{
public:
    PoolTask();
    ~PoolTask();
    PoolTask(ThreadPool::WaitCallback Callback, void* Data,
             ThreadPool::FreeCallback CustomFree);
    PoolTask(const PoolTask& Copy) = delete;
    PoolTask& operator=(PoolTask& Other);
    PoolTask& operator=(const PoolTask& Other)=delete;

    ThreadPool::WaitCallback Callback;
    void* Data;
    ThreadPool::FreeCallback FreeData;
};

class PoolThread : public Thread
{
public:
    virtual ~PoolThread();
    void Run();
    PImpl<ThreadPool>::Data* Pool;
    volatile bool shutdown;
};

namespace RadonFramework { namespace Core { namespace Idioms {
template<class T>
class PImpl<T>::Data
{
public:
    Data()
    :MaxWorkerThreads(1)
    ,MinWorkerThreads(0)
    ,Latency(10000)
    ,IsQueingAllowed(true)
    ,Running(true)
    {
        UInt32 lps = Hardware::GetAvailableLogicalProcessorCount();
        MaxWorkerThreads = lps;//ThreadPool::GetBestThreadAmountByProcessorCoreAmount(lps);
        SerialTaskLists = AutoPointerArray<Queue<PoolTask> >(MaxWorkerThreads);
        WorkerThreads.Resize(MaxWorkerThreads);
        BitArray<> mask(lps);
        for (UInt32 i=0; i < WorkerThreads.Count(); ++i)
        {
            WorkerThreads(i)=AutoPointer<PoolThread>(new PoolThread());
            WorkerThreads(i)->Pool = this;
            WorkerThreads(i)->shutdown = false;
            mask.Reset();
            mask.Set(i % lps);
            WorkerThreads(i)->SetAffinityMask(mask);
            WorkerThreads(i)->Start();
        }
    }

    ~Data()
    {
        IsQueingAllowed=false;
        Running = false;
        MaxWorkerThreads = 0;
        MinWorkerThreads = 0;

        // signal all threads to cancel
        for (UInt32 i=0; i < WorkerThreads.Count(); ++i)
            WorkerThreads(i)->shutdown = true;
        
        // clean up the list and trigger a change that the threads can leave Wait()
        ConcurrentTaskList.Clear();
        for (RF_Type::Size i = 0; i < SerialTaskLists.Count(); ++i)
        {
            SerialTaskLists[i].Clear();
        }

        // wait till all threads are finished
        for (UInt32 i=0; i < WorkerThreads.Count(); ++i)
            WorkerThreads(i)->Join();

        // clean up threads
        WorkerThreads.Resize(0);
        // destroy per-thread task collector
        SerialTaskLists.Reset();
    }

    void UpdatePoolSize()
    {
        // shrink worker threads
        if (MaxWorkerThreads < WorkerThreads.Count())
        {
            // trigger exit routine in specified thread
            for (Size i = MaxWorkerThreads - 1; i < WorkerThreads.Count(); ++i)
            {
                WorkerThreads(i)->Interrupt();
            }
            // wait till each triggered thread is no longer working
            for (Size i = MaxWorkerThreads - 1; i < WorkerThreads.Count(); ++i)
            {
                WorkerThreads(i)->Join();
            }

            WorkerThreads.Resize(MaxWorkerThreads);
        }

        // grow worker threads
        if (MinWorkerThreads > WorkerThreads.Count())
        {
            Size currentSize = WorkerThreads.Count();
            WorkerThreads.Resize(MinWorkerThreads);
            for (Size i = currentSize - 1; i < MinWorkerThreads; ++i)
            {
                WorkerThreads(i)=AutoPointer<PoolThread>(new PoolThread());
                WorkerThreads(i)->Pool = this;
                WorkerThreads(i)->Start();
            }
        }
    }

    Array<AutoPointer<PoolThread> > WorkerThreads;
    Queue<PoolTask> ConcurrentTaskList;
    AutoPointerArray<Queue<PoolTask> > SerialTaskLists;
    UInt32 MaxWorkerThreads;
    UInt32 MinWorkerThreads;
    RF_Time::TimeValue Latency;
    AtomicInt32 WorkingThreads;
    Bool IsQueingAllowed;
    Bool Running;
};
} } }

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
}

RF_Type::UInt32 ThreadPool::GetBestThreadAmountByProcessorCoreAmount(RF_Type::UInt32 Amount)
{
    // twice more as logical processor count
    return Math::Integer<UInt32>::Max(Amount, 1) << 1;
}

void ThreadPool::GetMaxThreads(UInt32& WorkerThreads)
{
    WorkerThreads = m_PImpl->MaxWorkerThreads;
}

Bool ThreadPool::SetMaxThreads(UInt32 WorkerThreads)
{
    if (m_PImpl->MinWorkerThreads <= WorkerThreads)
    {
        m_PImpl->MaxWorkerThreads = WorkerThreads;
        m_PImpl->UpdatePoolSize();
        return true;
    }
    return false;
}

void ThreadPool::GetMinThreads(UInt32& WorkerThreads)
{
    WorkerThreads = m_PImpl->MinWorkerThreads;
}

Bool ThreadPool::SetMinThreads(UInt32 WorkerThreads)
{
    if (m_PImpl->MaxWorkerThreads >= WorkerThreads)
    {
        m_PImpl->MinWorkerThreads = WorkerThreads;
        m_PImpl->UpdatePoolSize();
        return true;
    }
    return false;
}

void ThreadPool::GetAvailableThreads(UInt32& WorkerThreads)
{
    WorkerThreads = m_PImpl->MaxWorkerThreads - m_PImpl->WorkerThreads.Count();
}

Bool ThreadPool::QueueUserWorkItem(WaitCallback Callback, TaskStrategy::Type Strategy, 
    FreeCallback FreeData)
{
    return QueueUserWorkItem(Callback, 0, Strategy, FreeData);
}

Bool ThreadPool::QueueUserWorkItem(WaitCallback Callback, void* State,
    TaskStrategy::Type Strategy, FreeCallback FreeData)
{
    if (m_PImpl->IsQueingAllowed)
    {
        PoolTask task(Callback, State, FreeData);
        if (Strategy==TaskStrategy::Concurrent)
        {
            m_PImpl->ConcurrentTaskList.Enqueue(task); 
        }
        else
        {
            Int64 serialGrp=RF_SysHardware::GetCurrentUniqueProcessorNumber() % m_PImpl->WorkerThreads.Count();
            m_PImpl->SerialTaskLists[static_cast<UInt32>(serialGrp)].Enqueue(task);
        }   
        return true;
    }
    return false;
}

void ThreadPool::DisableAndWaitTillDone()
{
    m_PImpl->IsQueingAllowed = false;
    WaitTillQueueIsEmpty();
    m_PImpl->Running = false;

    while(m_PImpl->WorkingThreads > 0)
    {
        Thread::Sleep(Time::TimeSpan::CreateByTicks(Time::TimeSpan::TicksPerMillisecond));
    }

    m_PImpl->Running = true;
}

void ThreadPool::DisableQueing()
{
    m_PImpl->IsQueingAllowed = false;
}

void ThreadPool::EnableQueing()
{
    m_PImpl->IsQueingAllowed = true;
}

void ThreadPool::DisableProcessing()
{
    m_PImpl->Running = false;
}

void ThreadPool::EnableProcessing()
{
    m_PImpl->Running = true;
}

void ThreadPool::WaitTillQueueIsEmpty()
{
    Time::TimeSpan delta = Time::TimeSpan::CreateByTime(0, 0, 1);
    Bool idle;
    do
    {
        idle = true;
        for(Size i = 0, end = m_PImpl->SerialTaskLists.Count(); i < end; ++i)
            idle = idle && m_PImpl->SerialTaskLists[static_cast<UInt32>(i)].IsEmpty();
        idle = idle && m_PImpl->ConcurrentTaskList.IsEmpty();

        if(!idle)
            Thread::Sleep(Time::TimeSpan::CreateByTicks(Time::TimeSpan::TicksPerMillisecond));
    } while(!idle);
}

void ThreadPool::GetThreadCount(UInt32& WorkerThreads)
{
    WorkerThreads = m_PImpl->WorkerThreads.Count();
}

void ThreadPool::DefaultFree(void* Data)
{
    delete Data;
}

void ThreadPool::LowLatencyPool()
{
    m_PImpl->Latency = 0;
}

void ThreadPool::HighLatencyPool()
{
    m_PImpl->Latency = 10000;
}

bool ThreadPool::IsLowLatencyPool()
{
    return m_PImpl->Latency == 0;
}

RF_Type::Bool RadonFramework::Threading::ThreadPool::CanQueue() const
{
    return m_PImpl->IsQueingAllowed;
}

void RadonFramework::Threading::ThreadPool::WaitTillDoneWithInactiveQueue()
{
    DisableAndWaitTillDone();
    EnableQueing();
}

void PoolThread::Run()
{
    PoolTask task;
    Bool result=false;
    Int64 serialGrp = RF_SysHardware::GetCurrentUniqueProcessorNumber() % Pool->WorkerThreads.Count();
    while(!shutdown)
    {
        result = false;
        Pool->WorkingThreads.Increment();
        result = Pool->SerialTaskLists[static_cast<UInt32>(serialGrp)].Dequeue(task);
        if (false == result)
        {
            result = Pool->ConcurrentTaskList.Dequeue(task);
            
            if(result == false)
            {// task pool is empty
                Pool->WorkingThreads.Decrement();
                Thread::Sleep(Time::TimeSpan::CreateByTicks(Pool->Latency));
                Pool->WorkingThreads.Increment();
            }
        }

        if (result)
        {
            task.Callback(task.Data);

            if (task.Data && task.FreeData)
            {
                task.FreeData(task.Data);
                task.Data = nullptr;
                task.FreeData = nullptr;
            }
        }
        Pool->WorkingThreads.Decrement();

        while(!Pool->Running && !shutdown)
        {
            Thread::Sleep(Time::TimeSpan::CreateByTicks(Pool->Latency));
        }
    }
}

PoolThread::~PoolThread()
{
    shutdown = true;
}

PoolTask::PoolTask()
:Data(0)
{
}

PoolTask::~PoolTask()
{

}

PoolTask::PoolTask(ThreadPool::WaitCallback Callback, void* Data,
    ThreadPool::FreeCallback FreeData)
:Callback(Callback)
,Data(Data)
,FreeData(FreeData)
{
}


PoolTask& PoolTask::operator=(PoolTask& Other)
{
    Callback=Other.Callback;
    Data=Other.Data;
    Other.Data=nullptr;
    FreeData=Other.FreeData;
    Other.FreeData = nullptr;
    return *this;
}
