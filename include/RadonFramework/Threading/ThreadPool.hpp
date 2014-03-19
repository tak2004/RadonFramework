#ifndef RF_THREADING_THREADPOOL_HPP
#define RF_THREADING_THREADPOOL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/System/Threading/Thread.hpp>
#include <RadonFramework/System/Threading/Mutex.hpp>
#include <RadonFramework/System/Threading/Condition.hpp>
#include <RadonFramework/Threading/RegisteredWaitHandle.hpp>
#include <RadonFramework/Threading/IWaitHandle.hpp>
#include <RadonFramework/Threading/TaskStrategy.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Collections/Queue.hpp>

namespace RadonFramework { namespace Threading {

class ThreadPool
{
public:
    ThreadPool();
    virtual ~ThreadPool();

    /// The function will calculate the best working thread amount
    /// for the specified processor core amount.
    static RFTYPE::UInt32 GetBestThreadAmountByProcessorCoreAmount(RFTYPE::UInt32 Amount);

    typedef Delegate1<void*> WaitCallback;

    void GetMaxThreads(RFTYPE::UInt32& WorkerThreads,
                       RFTYPE::UInt32& CompletionPortThreads);

    RFTYPE::Bool SetMaxThreads(RFTYPE::UInt32 WorkerThreads,
                               RFTYPE::UInt32 CompletionPortThreads);

    void GetMinThreads(RFTYPE::UInt32& WorkerThreads,
                       RFTYPE::UInt32& CompletionPortThreads);

    RFTYPE::Bool SetMinThreads(RFTYPE::UInt32 WorkerThreads,
                               RFTYPE::UInt32 CompletionPortThreads);

    void GetAvailableThreads(RFTYPE::UInt32& WorkerThreads,
                             RFTYPE::UInt32& CompletionPortThreads);

    RFTYPE::Bool QueueUserWorkItem(WaitCallback Callback,
        TaskStrategy::Type Strategy=TaskStrategy::Concurrent,
        RFTYPE::Bool AutoCleanup=true);

    RFTYPE::Bool QueueUserWorkItem(WaitCallback Callback,
        void* State, TaskStrategy::Type Strategy=TaskStrategy::Concurrent,
        RFTYPE::Bool AutoCleanup=true);
private:
    Core::Idioms::PImpl<ThreadPool> m_PImpl;
};

class PoolTask
{
public:
    PoolTask();
    ~PoolTask();
    PoolTask(ThreadPool::WaitCallback Callback, void* Data,
             RFTYPE::Bool AutoCleanup);
    PoolTask(const PoolTask& Copy);
    PoolTask& operator=(const PoolTask& Other);

    ThreadPool::WaitCallback Callback;
    mutable void* Data;
    RFTYPE::Bool AutoCleanup;
};

} }

#endif // RF_THREADING_THREADPOOL_HPP
