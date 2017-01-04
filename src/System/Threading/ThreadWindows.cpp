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
    DWORD ID;
    Delegate<void()> OnFinished;
    Delegate<void()> OnRun;
    RF_Type::Bool alive;
    RF_Type::Bool cancel;
    RF_Type::Bool postConfigurationComplete;
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
    SetAlive(p, true);
    while(!p->postConfigurationComplete)
    {
        ::Sleep(0);
    }
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

void* Create(RF_Thread::Thread& Instance, RF_Type::UInt64& PID)
{
    ThreadHelper* p = new ThreadHelper;
    void* result = 0;

    p->OnFinished = MakeDelegate(&Instance, &RF_Thread::Thread::Finished);
    p->OnRun = MakeDelegate(&Instance, &RF_Thread::Thread::Run);
    p->ID = 0;
    p->alive = false;
    p->cancel = false;
    p->postConfigurationComplete = false;
    p->thread = 0;

    p->mutex.Lock();
    p->thread = (HANDLE)CreateThread(NULL, 0, ThreadFunction, p, 0, &p->ID);

    if(!p->thread)
    {
        p->mutex.Unlock();
        delete p;
        switch(errno)
        {
        case EAGAIN:
            RF_IO::LogError("There are to many threads.");
            break;
        case EINVAL:
            RF_IO::LogError("The argument is invalid or the stack size is incorrect.");
            break;
        default:
            RF_IO::LogError("An unhandled error occurred.");
            break;
        }
    }
    else
    {
        p->aliveChanged.Wait(p->mutex);
        result = static_cast<void*>(p);
        PID = p->ID;
        p->mutex.Unlock();
    }
    return result;
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

    __try
    {
        RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR*)&info);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {}
}

void Sleep(const RF_Time::TimeSpan& Delta)
{
    unsigned int timeInMiliseconds = Delta.TotalMilliseconds();
    ::Sleep(timeInMiliseconds);
}

RF_Type::UInt64 GetProcessId()
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
    if(p)
    {
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
}

RF_Type::Bool SetAffinityMask(void* Data, const RF_Collect::BitArray<>& NewMask)
{
    RF_Type::Bool result = false;
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    if (p)
    {
        DWORD_PTR threadAffinityMask;
        threadAffinityMask = 0;

        RF_Type::Size end = RadonFramework::Math::Integer<RF_Type::Size>::Min(
            sizeof(DWORD_PTR) << 3,
            NewMask.Count()
        );
        for(RF_Type::Size i = 0; i < end; ++i)
        {
            threadAffinityMask |= static_cast<DWORD_PTR>(NewMask.Test(i)) << i;
        }

        result = SetThreadAffinityMask(p->thread, threadAffinityMask);
    }
    return result;
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

void PostConfigurationComplete(void* Data)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    p->postConfigurationComplete = true;
}

void ShortestPause()
{
    YieldProcessor();
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
    PostConfigurationComplete = Windows::PostConfigurationComplete;
    ShortestPause = Windows::ShortestPause;
}

} } }