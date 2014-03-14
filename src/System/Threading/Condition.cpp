#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Threading/Condition.hpp"
#include "RadonFramework/System/Threading/Mutex.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"

using namespace RadonFramework::System::Threading;
using namespace RadonFramework::Time;
using namespace RadonFramework::Core::Types;

namespace RadonFramework
{
    namespace System
    {
        namespace Threading
        {
#if defined(RF_WINDOWS)
#include <windows.h>

struct CondHelper
{
    HANDLE semaphore;
    HANDLE waiters_done;
    long waiters_count;
    size_t was_broadcast;
};

void* CondImplementationInit()
{
    CondHelper* result=new CondHelper;
    result->waiters_count=0;
    result->was_broadcast=0;
    result->semaphore=CreateSemaphore(NULL,0,0x7fffffff,NULL);
    result->waiters_done=CreateEvent(NULL,FALSE,FALSE,NULL);
    return static_cast<void*>(result);
}

void CondImplementationFree(void* Data)
{
    CondHelper* p=static_cast<CondHelper*>(Data);
    CloseHandle(p->waiters_done);
    CloseHandle(p->semaphore);
    delete p;
}

void CondImplementationWait(void* Data, Mutex& Lock)
{
    CondHelper* p=static_cast<CondHelper*>(Data);
    InterlockedIncrement(&p->waiters_count);

    int res=0;
    Lock.Unlock();
    DWORD dwres=WaitForSingleObject(p->semaphore, INFINITE);
    if (dwres!=WAIT_OBJECT_0)
        res=(int)dwres;

    InterlockedDecrement(&p->waiters_count);
    long w=InterlockedExchangeAdd(&p->waiters_count,0);
    int last_waiter = p->was_broadcast && w == 0;

    if (res!=-1 && last_waiter)
        SetEvent(p->waiters_done);

    Lock.Lock();
}

void CondImplementationTimeWait(void* Data, Mutex& Lock, const TimeSpan& Delta)
{
    CondHelper* p=static_cast<CondHelper*>(Data);
    if (Delta.Ticks()==0)
        CondImplementationWait(Data,Lock);
    else
    {
        InterlockedIncrement(&p->waiters_count);

        int res=0;
        Lock.Unlock();
        DWORD dwres=WaitForSingleObject(p->semaphore,(DWORD)Delta.TotalMilliseconds());
        if (dwres!=WAIT_OBJECT_0)
            res=(int)dwres;

        InterlockedDecrement(&p->waiters_count);
        long w=InterlockedExchangeAdd(&p->waiters_count,0);
        int last_waiter = p->was_broadcast && w == 0;

        if (res!=-1 && last_waiter)
            SetEvent(p->waiters_done);
        Lock.Lock();
    }
}

void CondImplementationNotify(void* Data)
{
    CondHelper* p=static_cast<CondHelper*>(Data);
    long w=InterlockedExchangeAdd(&p->waiters_count,0);
    int have_waiters = w > 0;

    if (have_waiters)
        ReleaseSemaphore (p->semaphore, 1, 0);
}

void CondImplementationNotifyAll(void* Data)
{
    CondHelper* p=static_cast<CondHelper*>(Data);
    int have_waiters = 0;
    long w=InterlockedExchangeAdd(&p->waiters_count,0);

    if (w> 0) 
    {
        p->was_broadcast = 1;
        have_waiters = 1;
    }

    if (have_waiters) 
    {
        ReleaseSemaphore (p->semaphore, p->waiters_count, 0);
        WaitForSingleObject(p->waiters_done,INFINITE);
        p->was_broadcast = 0;
    }
}
#endif

#if defined(RF_UNIX)
#include <pthread.h>
#include <sys/time.h>

void* CondImplementationInit()
{
    pthread_cond_t* result=new pthread_cond_t;
    pthread_cond_init(result,0);
    return static_cast<void*>(result);
}

void CondImplementationFree(void* Data)
{
    pthread_cond_destroy(static_cast<pthread_cond_t*>(Data));
    delete Data;
}

void CondImplementationWait(void* Data, RadonFramework::System::Threading::Mutex& Lock)
{
    pthread_cond_wait(static_cast<pthread_cond_t*>(Data),
                      static_cast<pthread_mutex_t*>(Lock.m_ImplData));
}

void CondImplementationTimeWait(void* Data, RadonFramework::System::Threading::Mutex& Lock, const RadonFramework::Time::TimeSpan& Delta)
{
    if (Delta.Ticks()==0)
        ::CondImplementationWait(Data,Lock);
    else
    {
        timeval t;
        gettimeofday(&t,0);
        UInt64 end = t.tv_sec*10000000llu+t.tv_usec*10llu+Delta.Ticks();
        timespec time;
        time.tv_sec = end / TimeSpan::TicksPerSecond;
        time.tv_nsec = end - time.tv_sec * TimeSpan::TicksPerSecond;
        pthread_cond_timedwait(static_cast<pthread_cond_t*>(Data),
                               static_cast<pthread_mutex_t*>(Lock.m_ImplData),&time);
    }
}

void CondImplementationNotify(void* Data)
{
    pthread_cond_signal(static_cast<pthread_cond_t*>(Data));
}

void CondImplementationNotifyAll(void* Data)
{
    pthread_cond_broadcast(static_cast<pthread_cond_t*>(Data));
}
#endif
        }
    }
}

Condition::Condition()
{
    m_ImplData=CondImplementationInit();
}

Condition::~Condition()
{
    CondImplementationFree(m_ImplData);
}

void Condition::Wait(Mutex& Lock)
{
    ::CondImplementationWait(m_ImplData,Lock);
}

void Condition::TimedWait(Mutex& Lock, const RadonFramework::Time::TimeSpan& Delta)
{
    ::CondImplementationTimeWait(m_ImplData,Lock,Delta);
}

void Condition::Notify()
{
    CondImplementationNotify(m_ImplData);
}

void Condition::NotifyAll()
{
    CondImplementationNotifyAll(m_ImplData);
}
