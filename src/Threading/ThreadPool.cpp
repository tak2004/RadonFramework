#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Threading/ThreadPool.hpp"
#include "RadonFramework/Math/Math.hpp"
#include "RadonFramework/System/Hardware.hpp"
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
    PoolTask(const PoolTask& Copy);
    PoolTask& operator=(const PoolTask& Other);

    ThreadPool::WaitCallback Callback;
    mutable void* Data;
    ThreadPool::FreeCallback FreeData;
};

class PoolThread : public System::Threading::Thread
{
public:
    void Run();
    PImpl<ThreadPool>::Data* Pool;
    volatile bool shutdown;
};

template<class T>
class PImpl<T>::Data
{
public:
    Data()
    :MaxWorkerThreads(1)
    ,MaxCompletionPortThreads(0)
    ,MinWorkerThreads(0)
    ,MinCompletionPortThreads(0)
    ,Running(true)
    {
        UInt32 lps = Hardware::GetAvailableLogicalProcessorCount();
        MaxWorkerThreads = lps;//ThreadPool::GetBestThreadAmountByProcessorCoreAmount(lps);
        SerialTaskLists = AutoPointerArray<Queue<PoolTask> >(new Queue<PoolTask>[MaxWorkerThreads], MaxWorkerThreads);
        WorkerThreads.Resize(MaxWorkerThreads);
        BitArray<> mask(lps);
        for (UInt32 i=0; i < WorkerThreads.Count(); ++i)
        {
            WorkerThreads(i)=AutoPointer<PoolThread>(new PoolThread());
            WorkerThreads(i)->Pool = this;
            WorkerThreads(i)->shutdown = false;
            WorkerThreads(i)->Start();
            mask.Reset();
            mask.Set(i % lps);
            WorkerThreads(i)->SetAffinityMask(mask);
        }
    }

    ~Data()
    {
        Running=false;
        MaxWorkerThreads = 0;
        MaxCompletionPortThreads = 0;
        MinWorkerThreads = 0;
        MinCompletionPortThreads = 0;

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
        if (MaxWorkerThreads > WorkerThreads.Count())
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

        // shrink completion ports
        if (MaxCompletionPortThreads > CompletionPortThreads.Count())
        {
            // trigger exit routine in specified thread
            for (Size i = MaxCompletionPortThreads - 1; i < CompletionPortThreads.Count(); ++i)
            {
                CompletionPortThreads(i)->Interrupt();
            }
            // wait till each triggered thread is no longer working
            for (Size i = MaxCompletionPortThreads - 1; i < CompletionPortThreads.Count(); ++i)
            {
                CompletionPortThreads(i)->Join();
            }

            CompletionPortThreads.Resize(MaxCompletionPortThreads);
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

        // grow completion port
        if (MinCompletionPortThreads > CompletionPortThreads.Count())
        {/*
            Size currentSize = CompletionPortThreads.Count();
            CompletionPortThreads.Resize(MinCompletionPortThreads);
            for (Size i = currentSize - 1; i < MinCompletionPortThreads; ++i)
            {
                CompletionPortThreads(i)=AutoPointer<PoolThread>(new PoolThread());
                CompletionPortThreads(i)->Start();
            }*/
        }
    }

    Array<AutoPointer<PoolThread> > WorkerThreads;
    Array<AutoPointer<Thread> > CompletionPortThreads;
    Queue<PoolTask> ConcurrentTaskList;
    AutoPointerArray<Queue<PoolTask> > SerialTaskLists;
    UInt32 MaxWorkerThreads;
    UInt32 MaxCompletionPortThreads;
    UInt32 MinWorkerThreads;
    UInt32 MinCompletionPortThreads;
    Bool Running;
};

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
}

RF_Type::UInt32 ThreadPool::GetBestThreadAmountByProcessorCoreAmount(RF_Type::UInt32 Amount)
{
    // twice more as logical processor count
    return Math::Math<UInt32>::Max(Amount, 1) << 1;
}

void ThreadPool::GetMaxThreads(UInt32& WorkerThreads, UInt32& CompletionPortThreads)
{
    WorkerThreads = m_PImpl->MaxWorkerThreads;
    CompletionPortThreads = m_PImpl->MaxCompletionPortThreads;
}

Bool ThreadPool::SetMaxThreads(UInt32 WorkerThreads, UInt32 CompletionPortThreads)
{
    if (m_PImpl->MinWorkerThreads <= WorkerThreads &&
        m_PImpl->MinCompletionPortThreads <= CompletionPortThreads)
    {
        m_PImpl->MaxWorkerThreads = WorkerThreads;
        m_PImpl->MaxCompletionPortThreads = CompletionPortThreads;
        m_PImpl->UpdatePoolSize();
        return true;
    }
    return false;
}

void ThreadPool::GetMinThreads(UInt32& WorkerThreads, UInt32& CompletionPortThreads)
{
    WorkerThreads = m_PImpl->MinWorkerThreads;
    CompletionPortThreads = m_PImpl->MinCompletionPortThreads;
}

Bool ThreadPool::SetMinThreads(UInt32 WorkerThreads, UInt32 CompletionPortThreads)
{
    if (m_PImpl->MaxWorkerThreads >= WorkerThreads &&
        m_PImpl->MaxCompletionPortThreads >= CompletionPortThreads)
    {
        m_PImpl->MinWorkerThreads = WorkerThreads;
        m_PImpl->MinCompletionPortThreads = CompletionPortThreads;
        m_PImpl->UpdatePoolSize();
        return true;
    }
    return false;
}

void ThreadPool::GetAvailableThreads(UInt32& WorkerThreads, UInt32& CompletionPortThreads)
{
    WorkerThreads = m_PImpl->MaxWorkerThreads - m_PImpl->WorkerThreads.Count();
    CompletionPortThreads = m_PImpl->MaxCompletionPortThreads - m_PImpl->CompletionPortThreads.Count();
}

Bool ThreadPool::QueueUserWorkItem(WaitCallback Callback, TaskStrategy::Type Strategy, 
    FreeCallback FreeData)
{
    return QueueUserWorkItem(Callback, 0, Strategy, FreeData);
}

Bool ThreadPool::QueueUserWorkItem(WaitCallback Callback, void* State,
    TaskStrategy::Type Strategy, FreeCallback FreeData)
{
    if (m_PImpl->Running)
    {
        PoolTask task(Callback, State, FreeData);
        if (Strategy==TaskStrategy::Concurrent)
        {
            m_PImpl->ConcurrentTaskList.Enqueue(task); 
        }
        else
        {
            Int64 serialGrp=Thread::CurrentPid() % m_PImpl->WorkerThreads.Count();
            m_PImpl->SerialTaskLists[static_cast<UInt32>(serialGrp)].Enqueue(task);
        }   
        return true;
    }
    return false;
}

void ThreadPool::DisableAndWaitTillDone()
{
    m_PImpl->Running = false;
    WaitTillDone();
}

void ThreadPool::Disable()
{
    m_PImpl->Running = false;
}

void ThreadPool::Enable()
{
    m_PImpl->Running = true;
}

void ThreadPool::WaitTillDone()
{
        Time::TimeSpan delta = Time::TimeSpan::CreateByTime(0,0,1);
        Bool idle;
        do
        {
            idle = true;
            {
                for(Size i = 0, end = m_PImpl->SerialTaskLists.Count(); i < end; ++i)
                    idle = idle && m_PImpl->SerialTaskLists[static_cast<UInt32>(i)].IsEmpty();
                idle = idle && m_PImpl->ConcurrentTaskList.IsEmpty();
            }

            if(!idle)
                Thread::Sleep(Time::TimeSpan::CreateByTicks(Time::TimeSpan::TicksPerMillisecond));
        } while(!idle);
}

void ThreadPool::GetThreadCount(UInt32& WorkerThreads, UInt32& CompletionPortThreads)
{
    WorkerThreads = m_PImpl->WorkerThreads.Count();
    CompletionPortThreads = m_PImpl->CompletionPortThreads.Count();
}

void ThreadPool::DefaultFree(void* Data)
{
    delete Data;
}


void PoolThread::Run()
{
    PoolTask task;
    Bool result=false;
    Int64 serialGrp = Thread::CurrentPid() % Pool->WorkerThreads.Count();
    while(!shutdown)
    {
        result = Pool->SerialTaskLists[static_cast<UInt32>(serialGrp)].Dequeue(task);
        if (false == result)
        {
            result = Pool->ConcurrentTaskList.Dequeue(task);

            Thread::Sleep(Time::TimeSpan::CreateByTicks(0));
        }

        if (result)
        {
            task.Callback(task.Data);

            if (task.Data && task.FreeData)
            {
                task.FreeData(task.Data);
                task.Data=0;
            }
        }
    }
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

PoolTask::PoolTask(const PoolTask& Copy)
{
    *this = Copy;
}

PoolTask& PoolTask::operator=(const PoolTask& Other)
{
    Callback=Other.Callback;
    Data=Other.Data;
    Other.Data=0;
    FreeData=Other.FreeData;
    return *this;
}
