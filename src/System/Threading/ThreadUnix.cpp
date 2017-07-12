#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Threading/Thread.hpp"
#include "RadonFramework/System/Threading/Condition.hpp"
#include "RadonFramework/IO/Log.hpp"
#include "RadonFramework/System/Threading/ThreadUnix.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>

namespace RadonFramework::System::Threading::Unix {

void SetAlive(void* Data, RF_Type::Bool Value)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    pthread_mutex_lock(&p->mutexIsAlive);
    if(Value != p->alive)
    {
        p->alive = Value;
        pthread_mutex_unlock(&p->mutexIsAlive);

        pthread_mutex_lock(&p->mutex);
        pthread_cond_broadcast(&p->aliveChanged);
        pthread_mutex_unlock(&p->mutex);
    }
    else
        pthread_mutex_unlock(&p->mutexIsAlive);
}

RF_Type::UInt64 GetProcessId()
{
    return getpid();
}

void* ThreadFunction(void *userdata)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(userdata);
    if(userdata == 0)
    {
        RF_IO::LogError("Parameter is empty.");
        return 0;
    }
    *p->PID = GetProcessId();
    SetAlive(p, true);
    while(!p->postConfigurationComplete)
    {
        usleep(0);
    }
    p->OnRun();
    SetAlive(p, false);

    p->OnFinished();
    pthread_exit(NULL);
    return 0;
}

void* Create(RF_Thread::Thread& Instance, RF_Type::UInt64& PID)
{
    ThreadHelper* p = new ThreadHelper;
    void* result = 0;

    p->OnFinished = MakeDelegate(&Instance, &RF_Thread::Thread::Finished);
    p->OnRun = MakeDelegate(&Instance, &RF_Thread::Thread::Run);
    p->ID = 0;
    p->PID = &PID;
    p->alive = false;
    p->cancel = false;
    p->postConfigurationComplete = false;
    pthread_attr_init(&p->attr);
    pthread_mutex_init(&p->mutex, NULL);
    pthread_mutex_init(&p->mutexIsAlive, NULL);
    pthread_cond_init(&p->aliveChanged, NULL);

    pthread_mutex_lock(&p->mutex);
    pthread_attr_setdetachstate(&p->attr, PTHREAD_CREATE_JOINABLE);

    int res = pthread_create(&p->ID, &p->attr, ThreadFunction, p);
    if(res != 0)
    {
        pthread_mutex_unlock(&p->mutex);
        delete p;
        switch(errno)
        {
            case EAGAIN:
                RF_IO::LogError("Can't create thread because of following error. %s", strerror(errno));
                break;
            case EINVAL:
            case EPERM:
                break;
            default:
                RF_IO::LogError("An unhandled error occured.");
                break;
        }
    }
    else
    {
        pthread_cond_wait(&p->aliveChanged, &p->mutex);
        result = static_cast<void*>(p);
    }
    pthread_mutex_unlock(&p->mutex);
    return result;
}

void Destroy(void* Data)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    if(p->ID)
    {
        p->cancel = true;
        pthread_detach(p->ID);
        pthread_cancel(p->ID);
        pthread_join(p->ID, 0);
    }

    delete Data;
}

void Sleep(const RF_Time::TimeSpan& Delta)
{
    usleep((unsigned int)(Delta.TotalMicroseconds()));
}

void Wait(void* Data, const RF_Time::TimeSpan& Delta)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    pthread_mutex_lock(&p->mutexIsAlive);
    RF_Type::Bool val = p->alive;
    pthread_mutex_unlock(&p->mutexIsAlive);

    if(val)
    {
        if(Delta.Ticks() != 0)
        {
            pthread_mutex_lock(&p->mutex);
            struct timespec ts;
            ts.tv_sec = (unsigned int)(Delta.TotalSeconds());
            ts.tv_nsec = Delta.Microseconds() * 100 + Delta.Milliseconds() * 100000;
            pthread_cond_timedwait(&p->aliveChanged, &p->mutex, &ts);
            pthread_mutex_unlock(&p->mutex);
            return;
        }
        else
            pthread_join(p->ID, 0);
    }
}

void Join(void* Data)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    pthread_mutex_lock(&p->mutexIsAlive);
    RF_Type::Bool val = p->alive;
    pthread_mutex_unlock(&p->mutexIsAlive);

    if(val)
    {
        pthread_join(p->ID, 0);
    }
}

RF_Type::Bool IsAlive(void* Data)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    pthread_mutex_lock(&p->mutexIsAlive);
    RF_Type::Bool val = p->alive;
    pthread_mutex_unlock(&p->mutexIsAlive);
    return val;
}

RF_Type::Int32 ConvertPriority(RF_Thread::ThreadPriority::Type Prio, 
    RF_Type::Int32 policy)
{
    RF_Type::Int32 p = 0;
    switch(Prio)
    {
    default:
        RF_IO::LogError("The priority wasn't expected.");
        break;
    case RF_Thread::ThreadPriority::Minimal:
        p = (sched_get_priority_min(policy) + sched_get_priority_max(policy)) / 2; 
        break;
    case RF_Thread::ThreadPriority::Normal:
        p = sched_get_priority_min(policy); 
        break;
    case RF_Thread::ThreadPriority::Maximal:
        p = sched_get_priority_max(policy); 
        break;
    }
    return p;
}

void SetPriority(void* Data, RF_Thread::ThreadPriority::Type Value)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    if(p->ID)
    {
        if(p->alive)
        {
            pthread_mutex_lock(&p->mutex);
            struct sched_param param;
            RF_Type::Int32 policy = SCHED_OTHER;
            if(0 != pthread_getschedparam(p->ID, reinterpret_cast<int*>(&policy), &param))
                RF_IO::LogError("Can't access the priority of the thread.");

            param.sched_priority = ConvertPriority(Value, policy);

            if(0 != pthread_setschedparam(p->ID, policy, &param))
                RF_IO::LogError("Can't set the priority of the thread.");
            pthread_mutex_unlock(&p->mutex);
        }
    }
}

RF_Type::Bool IsRunning(void* Data)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    return !p->cancel && p->alive;
}

void PostConfigurationComplete(void* Data)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    p->postConfigurationComplete = true;
}

void Stop(void* Data)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    p->cancel = true;
}

}

namespace RadonFramework::System::Threading {

void Dispatch()
{
    Create = Unix::Create;
    Destroy = Unix::Destroy;
    Sleep = Unix::Sleep;
    GetProcessId = Unix::GetProcessId;
    Wait = Unix::Wait;
    Join = Unix::Join;
    IsAlive = Unix::IsAlive;
    SetPriority = Unix::SetPriority;
    IsRunning = Unix::IsRunning;
    PostConfigurationComplete = Unix::PostConfigurationComplete;
    Stop = Unix::Stop;
#ifdef RF_LINUX
    extern void Dispatch_Linux();
    Dispatch_Linux();
#else
#ifdef RF_OSX
    extern void Dispatch_OSX();
    Dispatch_OSX();
#endif
#endif
}

}