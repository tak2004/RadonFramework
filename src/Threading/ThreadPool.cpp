#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Threading/ThreadPool.hpp>
#include "RadonFramework/Math/Math.hpp"

using namespace RadonFramework;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Threading;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Idioms;
using namespace RadonFramework::System::Threading;
using namespace RadonFramework::System;

class PoolThread : public System::Threading::Thread
{
public:
    void Run();
    PImpl<ThreadPool>::Data* Pool;
};

template<>
class PImpl<ThreadPool>::Data
{
public:
    Data()
    :MaxWorkerThreads(1)
    ,MaxCompletionPortThreads(0)
    ,MinWorkerThreads(0)
    ,MinCompletionPortThreads(0)
    ,Running(true)
    {
        SerialTaskLists.Resize(MaxWorkerThreads);
        WorkerThreads.Resize(MaxWorkerThreads);
        for (UInt32 i=0; i < WorkerThreads.Count(); ++i)
        {
            WorkerThreads(i)=AutoPointer<PoolThread>(new PoolThread());
            WorkerThreads(i)->Pool = this;
            WorkerThreads(i)->Start();
        }
    }

    virtual ~Data()
    {
        Running=false;
        MaxWorkerThreads = 0;
        MaxCompletionPortThreads = 0;
        MinWorkerThreads = 0;
        MinCompletionPortThreads = 0;

        // signal all threads to cancel
        for (UInt32 i=0; i < WorkerThreads.Count(); ++i)
            WorkerThreads(i)->Interrupt();
        
        {// clean up the list and trigger a change that the threads can leave Wait()
            Scopelock lock(Busy);
            ConcurrentTaskList.Clear();
            SerialTaskLists.Resize(0);
            TaskListChanged.NotifyAll();
        }

        // wait till all threads are finished
        for (UInt32 i=0; i < WorkerThreads.Count(); ++i)
            WorkerThreads(i)->Join();

        // clean up threads
        WorkerThreads.Resize(0);
    }

    Array<AutoPointer<PoolThread> > WorkerThreads;
    Array<AutoPointer<Thread> > CompletionPortThreads;
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

ThreadPool::ThreadPool()
{
}

ThreadPool::~ThreadPool()
{
}

RFTYPE::UInt32 ThreadPool::GetBestThreadAmountByProcessorCoreAmount(RFTYPE::UInt32 Amount)
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
    m_PImpl->MaxWorkerThreads=WorkerThreads;
    m_PImpl->MaxCompletionPortThreads=CompletionPortThreads;
    return true;
}

void ThreadPool::GetMinThreads(UInt32& WorkerThreads, UInt32& CompletionPortThreads)
{
    WorkerThreads = m_PImpl->MinWorkerThreads;
    CompletionPortThreads = m_PImpl->MinCompletionPortThreads;
}

Bool ThreadPool::SetMinThreads(UInt32 WorkerThreads, UInt32 CompletionPortThreads)
{
    m_PImpl->MinWorkerThreads=WorkerThreads;
    m_PImpl->MinCompletionPortThreads=CompletionPortThreads;
    return true;
}

void ThreadPool::GetAvailableThreads(UInt32& WorkerThreads, UInt32& CompletionPortThreads)
{
    WorkerThreads = m_PImpl->MaxWorkerThreads - m_PImpl->WorkerThreads.Count();
    CompletionPortThreads = m_PImpl->MaxCompletionPortThreads - m_PImpl->CompletionPortThreads.Count();
}

Bool ThreadPool::QueueUserWorkItem(WaitCallback Callback, TaskStrategy::Type Strategy, 
                                   Bool AutoCleanup)
{
    return QueueUserWorkItem(Callback, 0, Strategy, AutoCleanup);
}

Bool ThreadPool::QueueUserWorkItem(WaitCallback Callback, void* State,
                                   TaskStrategy::Type Strategy, Bool AutoCleanup)
{
    if (m_PImpl->Running)
    {
        PoolTask task(Callback,State,AutoCleanup);
        Scopelock lock(m_PImpl->Busy);
        if (Strategy==TaskStrategy::Concurrent)
            m_PImpl->ConcurrentTaskList.Enqueue(task);
        else
        {
            Int64 serialGrp=Thread::CurrentPid() % m_PImpl->WorkerThreads.Count();
            m_PImpl->SerialTaskLists(static_cast<UInt32>(serialGrp)).Enqueue(task);
        }   
        m_PImpl->TaskListChanged.NotifyAll();
        return true;
    }
    return false;
}

void PoolThread::Run()
{
    PoolTask task;
    Bool result=false;
    Int64 serialGrp = Thread::CurrentPid() % Pool->WorkerThreads.Count();
    while(true)
    {
        {
            Scopelock lock(Pool->Busy);
            result = Pool->SerialTaskLists(static_cast<UInt32>(serialGrp)).Dequeue(task);
        }
        if (false == result)
        {
            {
                Scopelock lock(Pool->Busy);
                result = Pool->ConcurrentTaskList.Dequeue(task);
            }
            if (false == result)
                Pool->TaskListChanged.Wait(Pool->Busy);
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
    *this = Copy;
}

PoolTask& PoolTask::operator=(const PoolTask& Other)
{
    Callback=Other.Callback;
    Data=Other.Data;
    Other.Data=0;
    AutoCleanup=Other.AutoCleanup;
    return *this;
}
