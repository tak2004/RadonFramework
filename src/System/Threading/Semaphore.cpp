#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Threading/Semaphore.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"

using namespace RadonFramework::System::Threading;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Time;

#if defined(RF_WINDOWS)
#include <windows.h>

void* SemaImplementationInit(UInt32 value)
{
    HANDLE* result=new HANDLE;
    *result=CreateSemaphore(NULL, value, 256000, NULL);
    return result;
}

void SemaImplementationFree(void* Data)
{
    CloseHandle(*static_cast<HANDLE*>(Data));
    delete Data;
}

void SemaImplementationRelease(void* Data)
{
    ReleaseSemaphore(*static_cast<HANDLE*>(Data), 1, NULL);
}

void SemaImplementationWait(void* Data)
{
    WaitForSingleObject(*static_cast<HANDLE*>(Data), INFINITE);
}

Bool SemaImplementationTimedWait(void* Data, const TimeSpan& timeout)
{
    DWORD state = WaitForSingleObject(*static_cast<HANDLE*>(Data), 
                                      timeout.Milliseconds());
    return state == 0;
}
#endif

#if defined(RF_UNIX)
#include <semaphore.h>
#include <sys/time.h>
#ifdef RF_OSX
#include <unistd.h>
#include <time.h>
#endif

void* SemaImplementationInit(UInt32 value)
{
    sem_t* result=new sem_t;
    sem_init(result, 0, value);
    return static_cast<void*>(result);
}

void SemaImplementationFree(void* Data)
{
    sem_destroy(static_cast<sem_t*>(Data));
    delete Data;
}

void SemaImplementationRelease(void* Data)
{
    sem_post(static_cast<sem_t*>(Data));
}

void SemaImplementationWait(void* Data)
{
    sem_wait(static_cast<sem_t*>(Data));
}

Bool SemaImplementationTimedWait(void* Data, const TimeSpan& timeout)
{
    timeval t;
    gettimeofday(&t,0);
    UInt64 end = t.tv_sec*10000000llu+t.tv_usec*10llu+timeout.Ticks();
    timespec atTime;
    atTime.tv_sec = end / TimeSpan::TicksPerSecond;
    atTime.tv_nsec = end - atTime.tv_sec * TimeSpan::TicksPerSecond;
    
#ifdef RF_OSX
    time_t timer = time(NULL) * 1000 + end;
    int res = 0;
    do {
        res = sem_trywait(static_cast<sem_t*>(Data));
        if (res == 0) break;
        sleep(1);
    } while(time(NULL) * 1000 < timer);
#else
    int res = sem_timedwait(static_cast<sem_t*>(Data), &atTime);
#endif
    return res == 0;
}
#endif

Semaphore::Semaphore(UInt32 value)
{
    SemaImplementationInit(value);
}

Semaphore::~Semaphore()
{
    SemaImplementationFree(m_ImplData);
}

void Semaphore::Release()
{
    SemaImplementationRelease(m_ImplData);
}

void Semaphore::Wait()
{
    SemaImplementationWait(m_ImplData);
}

Bool Semaphore::TimedWait( const TimeSpan& timeout )
{
    return SemaImplementationTimedWait(m_ImplData,timeout);
}
