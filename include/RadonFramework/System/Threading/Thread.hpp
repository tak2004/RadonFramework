#ifndef RF_SYSTEM_THREADING_THREAD_HPP
#define RF_SYSTEM_THREADING_THREAD_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/System/Threading/Mutex.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Pattern/Signal.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Threading/ThreadPriority.hpp>
#include <RadonFramework/Threading/ThreadError.hpp>
#include <RadonFramework/Threading/IRunnable.hpp>

namespace RadonFramework
{
    namespace Time{
        struct TimeSpan;
    }

    namespace System
    {
        namespace Threading
        {
            class Thread:public RadonFramework::Threading::IRunnable,public SignalReceiver
            {
                public:
                    Thread();
                    Thread(RadonFramework::Threading::IRunnable* Target);
                    virtual ~Thread();
                    /// The code in this method is executed by the thread.
                    virtual void Run();
                    /// This method will start the thread.
                    void Start();
                    /// This method will stop the thread and wait till it's done.
                    void Exit();
                    /// This method will stop the thread and return immediately.
                    void Interrupt();
                    /** Check if the thread was stopped by Exit() or Interrupt().
                      * Use this in Run().
                      **/
                    void CheckCancel();

                    /// Wait till the thread is dead.
                    void Join();
                    void Join(const RadonFramework::Time::TimeSpan& Delta);
                    /// Return the thread priority.
                    RadonFramework::Threading::ThreadPriority::Type Priority();
                    /// Set a new thread priority.
                    void Priority(RadonFramework::Threading::ThreadPriority::Type Value);
                    /// Return the affinity mask.
                    //const Collections::BitArray& GetAffinityMask();
                    /// Set the affinity mask.
                    //void SetAffinityMask(const Collections::BitArray& NewValue);

                    /// Is the thread is running.
                    RFTYPE::Bool IsAlive();

                    /// Return true if the backend is working.
                    RFTYPE::Bool Working();

                    /// Assign a name to the thread, to make debugging easier.
                    const RFTYPE::String& Name()const;
                    void Name(const RFTYPE::String& NewName);

                    /// ProcessID
                    RFTYPE::Int64 Pid()const;

                    /// Will be called after the processing cursor left the Run methode scope.
                    Signal OnFinished;

                    static void Sleep(const RadonFramework::Time::TimeSpan& Delta);
            
                    /// Allocate memory and assign it to the Thread.
                    /// If the tread die and the memory isn't freed till yet then it will
                    /// be cleaned up by the destructor.
                    void* MemAlloc(const RFTYPE::UInt64 Bytes);
            
                    /// Free allocated memory, if it was generated by an instance of this
                    /// Thread class.
                    void FreeMem(const void* Ptr);

                    /// Return true if the pointer is part of the allocated memory of
                    /// a Thread instances.
                    RFTYPE::Bool MemAccess(const void* Ptr);

                    /// Return the Process ID of the current thread or main process.
                    static RFTYPE::Int64 CurrentPid();
                protected:
                    RadonFramework::Threading::ThreadPriority::Type m_Priority;
                    IRunnable* m_Target;
                    RFTYPE::Bool m_Alive;
                    RFTYPE::Bool m_CreateSuccessful;
                    Collections::AutoVector<RFTYPE::UInt8> m_ThreadAllocatedMemory;
                    Mutex m_ThreadBarrier;
                    RFTYPE::String m_Name;
                    RFTYPE::Int64 m_Pid;
                    void* m_ImplData;
                    void Finished();
            };
        }
    }
}

#endif // RF_SYSTEM_THREADING_THREAD_HPP
