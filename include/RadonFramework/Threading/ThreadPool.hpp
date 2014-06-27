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
    ~ThreadPool();

    /// The function will calculate the best working thread amount
    /// for the specified processor core amount.
    static RFTYPE::UInt32 GetBestThreadAmountByProcessorCoreAmount(RFTYPE::UInt32 Amount);

    typedef Delegate1<void*> WaitCallback;
    typedef void (*FreeCallback)(void* Data);
    static void DefaultFree(void* Data);

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

    void GetThreadCount(RFTYPE::UInt32& WorkerThreads,
                        RFTYPE::UInt32& CompletionPortThreads);

    RFTYPE::Bool QueueUserWorkItem(WaitCallback Callback,
        TaskStrategy::Type Strategy=TaskStrategy::Concurrent,
        FreeCallback FreeData = DefaultFree);

    RFTYPE::Bool QueueUserWorkItem(WaitCallback Callback,
        void* State, TaskStrategy::Type Strategy=TaskStrategy::Concurrent,
        FreeCallback FreeData = DefaultFree);

    /** \brief Disable the queing of new work items and wait till all allready
      * queued items are processed and freed.
      **/
    void DisableAndWaitTillDone();

    /// Disable the queing of new work items.
    void Disable();

    /// Enable the queing of new work items.
    void Enable();

    /// Wait till all queued work items are processed and freed.
    void WaitTillDone();
private:
    Core::Idioms::PImpl<ThreadPool> m_PImpl;
};

} }

#endif // RF_THREADING_THREADPOOL_HPP
