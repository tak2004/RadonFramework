#ifndef RF_THREADING_THREADPOOL_HPP
#define RF_THREADING_THREADPOOL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/System/Threading/Thread.hpp>
#include <RadonFramework/System/Threading/Mutex.hpp>
#include <RadonFramework/System/Threading/Condition.hpp>
#include <RadonFramework/Threading/TaskStrategy.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Collections/Queue.hpp>
#include <RadonFramework/Core/Idioms/PImpl.hpp>

namespace RadonFramework { namespace Threading {

class ThreadPool
{
public:
    ThreadPool();
    ~ThreadPool();

    /// The function will calculate the best working thread amount
    /// for the specified processor core amount.
    static RF_Type::UInt32 GetBestThreadAmountByProcessorCoreAmount(RF_Type::UInt32 Amount);

    typedef Delegate1<void(void*)> WaitCallback;
    using FreeCallback = void(*)(void* Data);
    static void DefaultFree(void* Data);

    void GetMaxThreads(RF_Type::UInt32& WorkerThreads);

    RF_Type::Bool SetMaxThreads(RF_Type::UInt32 WorkerThreads);

    void GetMinThreads(RF_Type::UInt32& WorkerThreads);

    RF_Type::Bool SetMinThreads(RF_Type::UInt32 WorkerThreads);

    void GetAvailableThreads(RF_Type::UInt32& WorkerThreads);

    void GetThreadCount(RF_Type::UInt32& WorkerThreads);

    RF_Type::Bool QueueUserWorkItem(WaitCallback Callback,
        TaskStrategy::Type Strategy=TaskStrategy::Concurrent,
        FreeCallback FreeData = DefaultFree);

    RF_Type::Bool QueueUserWorkItem(WaitCallback Callback,
        void* State, TaskStrategy::Type Strategy=TaskStrategy::Concurrent,
        FreeCallback FreeData = DefaultFree);

    /** \brief Disable the queuing of new work items and wait till all already
      * queued items are processed and freed.
      **/
    void DisableAndWaitTillDone();

    /// Disable the queing of new work items.
    void DisableQueing();

    /// Enable the queing of new work items.
    void EnableQueing();

    RF_Type::Bool CanQueue()const;

    /// Disable the processing of work items.
    void DisableProcessing();

    /// Enable the processing of work items.
    void EnableProcessing();

    /// Wait till all queued work items are processed or in processing state.
    void WaitTillQueueIsEmpty();

    /// Same as DisableAndWaitTillDone followed by EnableQueing.
    void WaitTillDoneWithInactiveQueue();

    /// The task scheduler lower the latency but rise the cpu power
    /// consumption if there are not enough tasks.
    void LowLatencyPool();

    /// The task scheduler rise the latency but lower the cpu power consumption.
    void HighLatencyPool();

    /// Returns true if the task scheduler work in low latency mode else false.
    bool IsLowLatencyPool();
private:
    RF_Idiom::PImpl<ThreadPool> m_PImpl;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_THREAD
#define RF_SHORTHAND_NAMESPACE_THREAD
namespace RF_Thread = RadonFramework::Threading;
#endif

#endif // RF_THREADING_THREADPOOL_HPP
