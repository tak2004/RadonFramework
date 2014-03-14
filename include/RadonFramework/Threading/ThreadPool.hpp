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

namespace RadonFramework
{
    namespace Threading
    {
        class PoolTask;

        class PoolThread:public System::Threading::Thread
        {
            public:
                void Run();
        };

        void InitializeThreadPool(RFTYPE::UInt32 LogicalProcessourCount);
        void ShutdownThreadPool();

        struct ThreadPool
        {
            friend class PoolThread;

            typedef Delegate1<void*> WaitCallback;
            typedef Delegate2<void*,RFTYPE::Bool> WaitOrTimerCallback;

            static void GetMaxThreads(RFTYPE::UInt32& WorkerThreads,
                                        RFTYPE::UInt32& CompletionPortThreads);

            static RFTYPE::Bool SetMaxThreads(RFTYPE::UInt32 WorkerThreads,
                                            RFTYPE::UInt32 CompletionPortThreads);

            static void GetMinThreads(RFTYPE::UInt32& WorkerThreads,
                                        RFTYPE::UInt32& CompletionPortThreads);

            static RFTYPE::Bool SetMinThreads(RFTYPE::UInt32 WorkerThreads,
                                            RFTYPE::UInt32 CompletionPortThreads);

            static void GetAvailableThreads(RFTYPE::UInt32& WorkerThreads,
                                            RFTYPE::UInt32& CompletionPortThreads);

            //static CT::Bool BindHandle(ISafeHandle* OSHandle);

            static RFTYPE::Bool QueueUserWorkItem(WaitCallback Callback,
                TaskStrategy::Type Strategy=TaskStrategy::Concurrent,
                RFTYPE::Bool AutoCleanup=true);

            static RFTYPE::Bool QueueUserWorkItem(WaitCallback Callback,
                void* State, TaskStrategy::Type Strategy=TaskStrategy::Concurrent,
                RFTYPE::Bool AutoCleanup=true);
            /*
            static RegisteredWaitHandle RegisterWaitForSingleObject(
                IWaitHandle* WaitObject, WaitOrTimerCallback Callback,
                void* Sate, CT::Int32 MilisecondsTimeOutInterval,
                CT::Bool ExecuteOnlyOnce);
                */
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
    }
}

#endif // RF_THREADING_THREADPOOL_HPP
