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
    typedef void (*FreeCallback)(void* Data);
    static void DefaultFree(void* Data);

    void GetMaxThreads(RF_Type::UInt32& WorkerThreads,
                       RF_Type::UInt32& CompletionPortThreads);

    RF_Type::Bool SetMaxThreads(RF_Type::UInt32 WorkerThreads,
                               RF_Type::UInt32 CompletionPortThreads);

    void GetMinThreads(RF_Type::UInt32& WorkerThreads,
                       RF_Type::UInt32& CompletionPortThreads);

    RF_Type::Bool SetMinThreads(RF_Type::UInt32 WorkerThreads,
                               RF_Type::UInt32 CompletionPortThreads);

    void GetAvailableThreads(RF_Type::UInt32& WorkerThreads,
                             RF_Type::UInt32& CompletionPortThreads);

    void GetThreadCount(RF_Type::UInt32& WorkerThreads,
                        RF_Type::UInt32& CompletionPortThreads);

    RF_Type::Bool QueueUserWorkItem(WaitCallback Callback,
        TaskStrategy::Type Strategy=TaskStrategy::Concurrent,
        FreeCallback FreeData = DefaultFree);

    RF_Type::Bool QueueUserWorkItem(WaitCallback Callback,
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
    RF_Idiom::PImpl<ThreadPool> m_PImpl;
};

} }

#endif // RF_THREADING_THREADPOOL_HPP
