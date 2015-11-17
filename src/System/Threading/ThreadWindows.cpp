#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Threading/Thread.hpp"
#include "RadonFramework/System/Threading/Condition.hpp"
#include "RadonFramework/IO/Log.hpp"
#include <windows.h>
#include <process.h>
#include <errno.h>

namespace RadonFramework { namespace System { namespace Threading {

namespace Windows {

struct ThreadHelper
{
    Condition aliveChanged;
    HANDLE thread;
    HANDLE mutexIsAlive;
    Mutex mutex;
    RF_Type::Bool alive;
    RF_Type::Bool cancel;
    DWORD ID;
    RF_Type::Int64* PID;
    Delegate<void()> OnFinished;
    Delegate<void()> OnRun;
};

const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
    DWORD dwType; // Must be 0x1000.
    LPCSTR szName; // Pointer to name (in user addr space).
    DWORD dwThreadID; // Thread ID (-1=caller thread).
    DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

void SetAlive(void* Data, RF_Type::Bool Value)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    WaitForSingleObject(p->mutexIsAlive, INFINITE);
    if(Value != p->alive)
    {
        p->alive = Value;
        ReleaseMutex(p->mutexIsAlive);

        p->mutex.Lock();
        p->aliveChanged.NotifyAll();
        p->mutex.Unlock();
    }
    else
        ReleaseMutex(p->mutexIsAlive);
}

DWORD WINAPI ThreadFunction(void *userdata)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(userdata);
    if(userdata == 0)
    {
        RF_IO::LogError("Parameter is empty.");
        return 1;
    }
    *p->PID = GetCurrentProcessId();
    SetAlive(p, true);
    p->OnRun();
    SetAlive(p, false);
    p->OnFinished();
    ExitThread(0);
    return 0;
}

RF_Type::Bool IsAlive(void* Data)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    WaitForSingleObject(p->mutexIsAlive, INFINITE);
    RF_Type::Bool val = p->alive;
    ReleaseMutex(p->mutexIsAlive);
    return val;
}

RF_Type::Bool IsRunning(void* Data)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    return !p->cancel && p->alive;
}

RF_Thread::ThreadError::Type Create(void*& Data,
    RF_Thread::Thread* Instance, RF_Type::Int64& PID)
{
    ThreadHelper* p = new ThreadHelper;
    Data = static_cast<void*>(p);

    p->OnFinished = MakeDelegate(Instance, &RF_Thread::Thread::Finished);
    p->OnRun = MakeDelegate(Instance, &RF_Thread::Thread::Run);
    p->ID = 0;
    p->PID = &PID;
    p->alive = false;
    p->cancel = false;
    p->thread = 0;

    p->mutex.Lock();
    p->thread = (HANDLE)CreateThread(NULL, 0, ThreadFunction, p, 0, &p->ID);

    if(!p->thread)
    {
        p->mutex.Unlock();
        Data = 0;
        delete p;
        switch(errno)
        {
        case EAGAIN:
            RF_IO::LogError("There are to many threads.");
            return RF_Thread::ThreadError::ThreadLimitReached;
        case EINVAL:
            RF_IO::LogError("The argument is invalid or the stack size is incorrect.");
            return RF_Thread::ThreadError::InvalidArgument;
        default:
            RF_IO::LogError("An unhandled error occurred.");
            return RF_Thread::ThreadError::InternalError;
        }
    }
    else
        p->aliveChanged.Wait(p->mutex);

    p->mutex.Unlock();
    return RF_Thread::ThreadError::NoError;
}

void Destroy(void* Data)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    if(p->alive)
    {
        SetAlive(p, false);
        WaitForSingleObject(p->thread, INFINITE);
    }

    if(p->thread)
        CloseHandle(p->thread);

    delete Data;
}

void Rename(void* Data, const RF_Type::String& Name)
{
    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = Name.c_str();
    info.dwThreadID = static_cast<ThreadHelper*>(Data)->ID;
    info.dwFlags = 0;
}

void Sleep(const RF_Time::TimeSpan& Delta)
{
    unsigned int timeInMiliseconds = Delta.TotalMilliseconds();
    ::Sleep(timeInMiliseconds);
}

RF_Type::Int64 GetProcessId()
{
    return GetCurrentProcessId();
}

void Wait(void* Data, const RF_Time::TimeSpan& Delta)
{
    if(Delta.Ticks() > 0)
        WaitForSingleObject(static_cast<ThreadHelper*>(Data)->thread, Delta.Milliseconds());
}

void Join(void* Data)
{
    WaitForSingleObject(static_cast<ThreadHelper*>(Data)->thread, INFINITE);
}

void SetPriority(void* Data, RF_Thread::ThreadPriority::Type Value)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    if(p->ID)
    {
        if(p->alive)
        {
            SuspendThread(p->thread);
            int prio = 0;
            switch(Value)
            {
            case RF_Thread::ThreadPriority::Normal:
                prio = THREAD_PRIORITY_NORMAL; break;
            case RF_Thread::ThreadPriority::Minimal:
                prio = THREAD_PRIORITY_BELOW_NORMAL; break;
            case RF_Thread::ThreadPriority::Maximal:
                prio = THREAD_PRIORITY_ABOVE_NORMAL; break;
            default:
                prio = THREAD_PRIORITY_NORMAL;
            }
            SetThreadPriority(p->thread, prio);
            ResumeThread(p->thread);
        }
    }
}

RF_Type::Bool SetAffinityMask(void* Data, const RF_Collect::BitArray<>& NewMask)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    DWORD_PTR threadAffinityMask;
    threadAffinityMask = 0;

    RF_Type::Size end = RadonFramework::Math::Integer<RF_Type::Size>::ClampUpperBound(
        sizeof(DWORD_PTR) << 3,
        NewMask.Count()
    );
    for(RF_Type::Size i = 0; i < end; ++i)
    {
        threadAffinityMask |= static_cast<DWORD_PTR>(NewMask.Test(i)) << i;
    }
    return SetThreadAffinityMask(p->thread, threadAffinityMask);
}

RF_Type::Bool GetAffinityMask(void* Data, RF_Collect::BitArray<>& Mask)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    DWORD_PTR threadAffinityMask, testAffinityMask = 1;
    // a successfully SetThreadAffinityMask call return the old mask 
    threadAffinityMask = SetThreadAffinityMask(p->thread, testAffinityMask);
    // recover the old mask
    SetThreadAffinityMask(p->thread, threadAffinityMask);
    Mask.Resize(sizeof(DWORD_PTR) << 3);
    Mask.Reset();
    for(RF_Type::Size i = 0; i < sizeof(DWORD_PTR) << 3; ++i)
    {
        if((threadAffinityMask >> i) & 1)
            Mask.Set(i);
    }
    return true;
}

}

void Dispatch()
{
    IsAlive = Windows::IsAlive;
    IsRunning = Windows::IsRunning;
    Create = Windows::Create;
    Destroy = Windows::Destroy;
    Rename = Windows::Rename;
    Sleep = Windows::Sleep;
    GetProcessId = Windows::GetProcessId;
    Wait = Windows::Wait;
    Join = Windows::Join;
    SetPriority = Windows::SetPriority;
    SetAffinityMask = Windows::SetAffinityMask;
    GetAffinityMask = Windows::GetAffinityMask;
}

} } }