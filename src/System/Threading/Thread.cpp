#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Threading/Thread.hpp"
#include "RadonFramework/Threading/Scopelock.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"
#include "RadonFramework/Defines.hpp"
#include "RadonFramework/IO/Log.hpp"
#include "RadonFramework/Math/Integer.hpp"
#include <errno.h>

namespace RFT=RadonFramework::Threading;

using namespace RadonFramework::Time;
using namespace RadonFramework::System::Threading;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Collections;
using namespace RadonFramework::IO;

#if defined(RF_WINDOWS)
#include <windows.h>
#include <process.h>
#include "RadonFramework/System/Threading/Condition.hpp"

struct ThreadHelper
{
    Condition aliveChanged;
    HANDLE thread;
    HANDLE mutexIsAlive;
    Mutex mutex;
    Bool alive;
    Bool cancel;
    DWORD ID;
    Int64* PID;
    RFT::IRunnable* run;
    Delegate<> OnFinished;
};

void ThrImplementationAlive(void* Data, Bool Value)
{
    ThreadHelper* p=static_cast<ThreadHelper*>(Data);
    WaitForSingleObject(p->mutexIsAlive,INFINITE);
    if (Value!=p->alive)
    {
        p->alive=Value;
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
    ThreadHelper* p=static_cast<ThreadHelper*>(userdata);
    if (userdata==0)
    {
        LogError("Parameter is empty.");
        return 1;
    }
    *p->PID=GetCurrentProcessId();
    ThrImplementationAlive(p,true);
    p->run->Run();
    ThrImplementationAlive(p,false);
    p->OnFinished();
    ExitThread(0);
    return 0;
}

RFT::ThreadError::Type ThrImplementationInit(void*& Data, RFT::IRunnable *Job, 
    Thread* Instance, void(Thread::*Callback)(), Int64& PID)
{
    ThreadHelper* p=new ThreadHelper;
    Data=static_cast<void*>(p);

    p->OnFinished=MakeDelegate(Instance,Callback);
    p->ID=0;
    p->PID=&PID;
    p->alive=false;
    p->cancel=false;
    p->thread=0;

    p->run=Job;
    p->mutex.Lock();
    if (p->run)
        p->thread = (HANDLE)CreateThread(NULL, 0, ThreadFunction, p, 0, &p->ID);

    if (!p->thread)
    {
        p->mutex.Unlock();
        Data=0;
        delete p;
        switch (errno)
        {
            case EAGAIN:
                LogError("There are to many threads.");
                return RFT::ThreadError::ThreadLimitReached;
            case EINVAL:
                LogError("The argument is invalid or the stacksize is incorrect.");
                return RFT::ThreadError::InvalidArgument;
            default:
                LogError("An unhandled error ocurred.");
                return RFT::ThreadError::InternalError;
        }
    }
    else
        p->aliveChanged.Wait(p->mutex);

    p->mutex.Unlock();
    return RFT::ThreadError::NoError;
}

void ThrImplementationFree(void* Data)
{
    ThreadHelper* p=static_cast<ThreadHelper*>(Data);
    if (p->alive)
    {
        ThrImplementationAlive(p,false);
        WaitForSingleObject(p->thread, 1000);
    }

    if (p->thread)
        CloseHandle(p->thread);

    delete Data;
}

const DWORD MS_VC_EXCEPTION=0x406D1388;

#pragma pack(push,8)
typedef struct tagTHREADNAME_INFO
{
   DWORD dwType; // Must be 0x1000.
   LPCSTR szName; // Pointer to name (in user addr space).
   DWORD dwThreadID; // Thread ID (-1=caller thread).
   DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma pack(pop)

void ThrImplementationSetName(void* Data, const String& Name)
{
    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = Name.c_str();
    info.dwThreadID = static_cast<ThreadHelper*>(Data)->ID;
    info.dwFlags = 0;
    /*
    __try
    {
        RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info );
    }
    __except (EXCEPTION_CONTINUE_EXECUTION)
    {
    }*/
}

inline void ThrImplementationSleep(const TimeSpan& Delta)
{
    ::Sleep((unsigned int)(Delta.TotalMilliseconds()));
}

inline Int64 ThrImplementationPid()
{
    return GetCurrentProcessId();
}

void ThrImplementationJoin(void* Data, const TimeSpan& Delta)
{
    if (Delta.Microseconds()==0)
        WaitForSingleObject(static_cast<ThreadHelper*>(Data)->thread,INFINITE);
    else
        WaitForSingleObject(static_cast<ThreadHelper*>(Data)->thread, Delta.Milliseconds() );
}

Bool ThrImplementationIsAlive(void* Data)
{
    ThreadHelper* p=static_cast<ThreadHelper*>(Data);
    WaitForSingleObject(p->mutexIsAlive,INFINITE);
    Bool val=p->alive;
    ReleaseMutex(p->mutexIsAlive);
    return val;
}

inline void ThrImplementationCheckCancel(void* Data)
{
	if (static_cast<ThreadHelper*>(Data)->cancel)
		ExitThread(0);
}

void ThrImplementationPriority(void* Data, RFT::ThreadPriority::Type Value)
{
    ThreadHelper* p=static_cast<ThreadHelper*>(Data);
    if (p->ID)
    {
        if (p->alive)
        {
            SuspendThread(p->thread);
            int prio=0;
            switch (Value)
            {
                case RFT::ThreadPriority::Normal:prio=THREAD_PRIORITY_NORMAL; break;
                case RFT::ThreadPriority::Minimal:prio=THREAD_PRIORITY_BELOW_NORMAL; break;
                case RFT::ThreadPriority::Maximal:prio=THREAD_PRIORITY_ABOVE_NORMAL; break;
                default:prio=THREAD_PRIORITY_NORMAL;
            }
            SetThreadPriority(p->thread,prio);
            ResumeThread(p->thread);
        }
    }
}

inline void ThrImplementationDestroy(void* Data)
{
	static_cast<ThreadHelper*>(Data)->cancel=true;
	ThrImplementationJoin(Data,RadonFramework::Time::TimeSpan());
}

inline void ThrImplementationCancel(void* Data)
{
	static_cast<ThreadHelper*>(Data)->cancel=true;
}

inline Bool ThrImplementationGetAffinityMask(void* Data, BitArray<>& Mask)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    DWORD_PTR threadAffinityMask, testAffinityMask = 1;
    // a successfully SetThreadAffinityMask call return the old mask 
    threadAffinityMask = SetThreadAffinityMask(p->thread, testAffinityMask);
    // recover the old mask
    SetThreadAffinityMask(p->thread, threadAffinityMask);
    Mask.Resize(sizeof(DWORD_PTR) << 3);
    Mask.Reset();
    for(Size i = 0; i < sizeof(DWORD_PTR) << 3; ++i)
    {
        if((threadAffinityMask >> i) & 1)
            Mask.Set(i);
    }
    return true;
}

inline Bool ThrImplementationSetAffinityMask(void* Data, const BitArray<>& NewValue)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    DWORD_PTR threadAffinityMask;
    threadAffinityMask = 0;
    
    Size end = RadonFramework::Math::Integer<Size>::ClampUpperBound(
        sizeof(DWORD_PTR) << 3,
        NewValue.Count()
    );
    for (Size i = 0; i < end; ++i)
    {
        threadAffinityMask |= static_cast<DWORD_PTR>(NewValue.Test(i)) << i;
    }
    return SetThreadAffinityMask(p->thread, threadAffinityMask);
}
#endif

#if defined(RF_UNIX)
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#if defined(RF_LINUX)
    #include <sys/prctl.h>
#endif

struct ThreadHelper
{
    pthread_t ID;
    pthread_mutex_t mutex;
    pthread_mutex_t mutexIsAlive;
    pthread_cond_t aliveChanged;
    pthread_attr_t attr;
    Delegate<> OnFinished;
    RFT::IRunnable* run;
    Int64* PID;
    Bool alive;
};

void ThrImplementationAlive(void* Data, Bool Value)
{
    ThreadHelper* p=static_cast<ThreadHelper*>(Data);
    pthread_mutex_lock(&p->mutexIsAlive);
    if (Value!=p->alive)
    {
        p->alive=Value;
        pthread_mutex_unlock(&p->mutexIsAlive);

        pthread_mutex_lock(&p->mutex);
        pthread_cond_broadcast(&p->aliveChanged);
        pthread_mutex_unlock(&p->mutex);
    }
    else
        pthread_mutex_unlock(&p->mutexIsAlive);
}

void* ThreadFunction(void *userdata)
{
    ThreadHelper* p=static_cast<ThreadHelper*>(userdata);
    if (userdata==0)
    {
        LogError("Parameter is empty.");
        return 0;
    }
    *p->PID=getpid();
    ThrImplementationAlive(p,true);
    p->run->Run();
    ThrImplementationAlive(p,false);
    
    p->OnFinished();
    pthread_exit(NULL);
    return 0;
}

RFT::ThreadError::Type ThrImplementationInit(void*& Data, RFT::IRunnable* Job, Thread* Instance, void(Thread::*Callback)(),Int64& PID)
{
    ThreadHelper* p=new ThreadHelper;
    Data=static_cast<void*>(p);

    p->OnFinished=MakeDelegate(Instance,Callback);
    p->ID=0;
    p->PID=&PID;
    p->alive=false;
    pthread_attr_init(&p->attr);
    pthread_mutex_init(&p->mutex,NULL);
    pthread_mutex_init(&p->mutexIsAlive,NULL);
    pthread_cond_init(&p->aliveChanged,NULL);

    p->run=Job;
    pthread_mutex_lock(&p->mutex);
    pthread_attr_setdetachstate(&p->attr, PTHREAD_CREATE_JOINABLE);

    int res=pthread_create(&p->ID,&p->attr,ThreadFunction,p);
    if (res!=0)
    {
        pthread_mutex_unlock(&p->mutex);
        Data=0;
        delete p;
        switch (errno)
        {
            case EAGAIN:
                LogError("Can't create thread because of following error. %s",strerror(errno));
                return RFT::ThreadError::ThreadLimitReached;
            case EINVAL:
            case EPERM:
                break;
            default:
                LogError("An unhandled error occured.");
                return RFT::ThreadError::InternalError;
        }
    }
    else
        pthread_cond_wait(&p->aliveChanged,&p->mutex);
    pthread_mutex_unlock(&p->mutex);
    return RFT::ThreadError::NoError;
}

void ThrImplementationDestroy(void* Data)
{
    ThreadHelper* p=static_cast<ThreadHelper*>(Data);
    if (p->ID)
    {
        pthread_detach(p->ID);
        pthread_cancel(p->ID);
        pthread_join(p->ID,0);
    }
}

void ThrImplementationCancel(void* Data)
{
    ThreadHelper* p=static_cast<ThreadHelper*>(Data);
    if (p->ID)
    {
        pthread_detach(p->ID);
        pthread_cancel(p->ID);
    }
}

void ThrImplementationFree(void* Data)
{
    ThrImplementationDestroy(Data);
    delete Data;
}

void ThrImplementationSetName(void* Data, const String& Name)
{
#if defined(RF_OSX)
    String shortName(Name);
    if (shortName.Size() > 63)
        shortName = shortName.SubString(0,63);
    pthread_setname_np(shortName.c_str());
#else
    prctl(PR_SET_NAME, Name.c_str(), 0, 0, 0, 0);
#endif
}

void ThrImplementationSleep(const TimeSpan& Delta)
{
    usleep((unsigned int)(Delta.TotalMicroseconds()));
}

Int64 ThrImplementationPid()
{
    return getpid();
}

void ThrImplementationJoin(void* Data, const TimeSpan& Delta)
{
    ThreadHelper* p=static_cast<ThreadHelper*>(Data);
    pthread_mutex_lock(&p->mutexIsAlive);
    Bool val=p->alive;
    pthread_mutex_unlock(&p->mutexIsAlive);

    if (val)
    {
        if (Delta.Ticks()!=0)
        {
            pthread_mutex_lock(&p->mutex);
            struct timespec ts;
            ts.tv_sec=(unsigned int)(Delta.TotalSeconds());
            ts.tv_nsec=Delta.Microseconds()*100+Delta.Milliseconds()*100000;
            pthread_cond_timedwait(&p->aliveChanged,&p->mutex,&ts);
            pthread_mutex_unlock(&p->mutex);
            return;
        }
        else
            pthread_join(p->ID,0);
    }
}

Bool ThrImplementationIsAlive(void* Data)
{
    ThreadHelper* p=static_cast<ThreadHelper*>(Data);
    pthread_mutex_lock(&p->mutexIsAlive);
    Bool val=p->alive;
    pthread_mutex_unlock(&p->mutexIsAlive);
    return val;
}

void ThrImplementationCheckCancel(void* Data)
{
    pthread_testcancel();
}

Int32 ThrImplementationConvertPriority(RFT::ThreadPriority::Type Prio, Int32 policy)
{
    Int32 p=0;
    switch (Prio)
    {
        default:LogError("The priority wasn't exspected.");
        case RFT::ThreadPriority::Minimal:p=(sched_get_priority_min(policy)+sched_get_priority_max(policy))/2;break;
        case RFT::ThreadPriority::Normal:p = sched_get_priority_min(policy); break;
        case RFT::ThreadPriority::Maximal:p = sched_get_priority_max(policy); break;
    }
    return p;
}

void ThrImplementationPriority(void* Data, RFT::ThreadPriority::Type Value)
{
    ThreadHelper* p=static_cast<ThreadHelper*>(Data);
    if (p->ID)
    {
        if (p->alive)
        {
            pthread_mutex_lock(&p->mutex);
            struct sched_param param;
            Int32 policy=SCHED_OTHER;
            if(0!=pthread_getschedparam(p->ID, reinterpret_cast<int*>(&policy), &param))
                LogError("Can't access the priority of the thread.");

            param.sched_priority=ThrImplementationConvertPriority(Value,policy);

            if (0!=pthread_setschedparam(p->ID,policy,&param))
                LogError("Can't set the priority of the thread.");
            pthread_mutex_unlock(&p->mutex);
        }
    }
}
#endif

Thread::Thread()
:m_Priority(RFT::ThreadPriority::Normal)
,m_CreateSuccessful(false)
,m_Pid(-1)
,m_ImplData(0)
{
    m_Target=this;
}

Thread::Thread(IRunnable* Target)
:m_Priority(RFT::ThreadPriority::Normal)
,m_Target(Target)
,m_CreateSuccessful(false)
,m_Pid(-1)
,m_ImplData(0)
{
    
}

Thread::~Thread()
{
    if (m_ImplData)
        ThrImplementationFree(m_ImplData);
}

void Thread::Run()
{
}

void Thread::Start()
{
    RFT::ThreadError::Type res=ThrImplementationInit(m_ImplData,m_Target,this,&Thread::Finished,m_Pid);
    m_CreateSuccessful=(res==RFT::ThreadError::NoError);

    if (m_CreateSuccessful)
        ThrImplementationPriority(m_ImplData,m_Priority);
}

void Thread::Exit()
{
    ThrImplementationDestroy(m_ImplData);
}

void Thread::Interrupt()
{
    ThrImplementationCancel(m_ImplData);
}

void Thread::CheckCancel()
{
    ThrImplementationCheckCancel(m_ImplData);
}

RFT::ThreadPriority::Type Thread::Priority()
{
    return m_Priority;
}

void Thread::Priority(RFT::ThreadPriority::Type Value)
{
    if (Value!=m_Priority)
    {
        m_Priority=Value;
        ThrImplementationPriority(m_ImplData,m_Priority);
    }
}

void Thread::Join()
{
    Time::TimeSpan t;
    ThrImplementationJoin(m_ImplData,t);
}

void Thread::Join(const RadonFramework::Time::TimeSpan& Delta)
{
    ThrImplementationJoin(m_ImplData,Delta);
}

void Thread::Sleep(const RadonFramework::Time::TimeSpan& Delta)
{
    ThrImplementationSleep(Delta);
}

Bool Thread::IsAlive()
{
    return ThrImplementationIsAlive(m_ImplData);
}

Bool Thread::Working()
{
    return m_CreateSuccessful;
}

void Thread::Finished()
{
    OnFinished.Notify();
}

const String& Thread::Name()const
{
    return m_Name;
}

void Thread::Name(const class String& NewName)
{
    m_Name=NewName;
    return ThrImplementationSetName(m_ImplData,NewName);
}

Int64 Thread::Pid()const
{
    return m_Pid;
}

void* Thread::MemAlloc(const UInt64 Bytes)
{
    RFT::Scopelock lock(m_ThreadBarrier);
    AutoPointerArray<UInt8> m(new UInt8[Bytes],static_cast<UInt32>(Bytes));
    UInt8* p=m.Get();
    m_ThreadAllocatedMemory.PushBack(m);
    return p;
}

void Thread::FreeMem(const void* Ptr)
{
    RFT::Scopelock lock(m_ThreadBarrier);
    Collections::AutoVector<UInt8>::Iterator it=m_ThreadAllocatedMemory.Begin();
    for (;it!=m_ThreadAllocatedMemory.End();++it)
        if ((*it)==Ptr)
        {
            m_ThreadAllocatedMemory.Erase(it);
            break;
        }
}

Bool Thread::MemAccess(const void* Ptr)
{
    RFT::Scopelock lock(m_ThreadBarrier);
    Collections::AutoVector<UInt8>::Iterator it=m_ThreadAllocatedMemory.Begin();
    for (;it!=m_ThreadAllocatedMemory.End();++it)
        if ((*it)==Ptr)
            return true;
    return false;
}

Int64 Thread::CurrentPid()
{
    return ThrImplementationPid();
}

Bool Thread::GetAffinityMask(BitArray<>& Mask)const
{
    return ThrImplementationGetAffinityMask(m_ImplData, Mask);
}

Bool Thread::SetAffinityMask(const BitArray<>& NewValue)const
{
    return ThrImplementationSetAffinityMask(m_ImplData, NewValue);
}
