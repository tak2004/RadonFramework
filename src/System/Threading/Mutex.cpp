#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Threading/Mutex.hpp"

using namespace RadonFramework::System::Threading;

#if defined(RF_WINDOWS)
#include <windows.h>

void* MutImplementationInit()
{
    HANDLE* result=new HANDLE;
    *result=CreateMutex(
        NULL,              // default security attributes
        FALSE,             // initially not owned
        NULL);
    return static_cast<void*>(result);
}

void MutImplementationFree(void* Data)
{
    CloseHandle(*static_cast<HANDLE*>(Data));
    delete Data;
}

UInt32 MutImplementationLock(void* Data)
{
    WaitForSingleObject(*static_cast<HANDLE*>(Data),INFINITE);
    return GetCurrentThreadId();
}

void MutImplementationUnlock(void* Data)
{    
    ReleaseMutex(*static_cast<HANDLE*>(Data));
}
#endif

#if defined(RF_UNIX)
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>

void* MutImplementationInit()
{
    pthread_mutex_t* result=new pthread_mutex_t;
    pthread_mutex_init(result,0);
    return static_cast<void*>(result);
}

void MutImplementationFree(void* Data)
{
    pthread_mutex_destroy(static_cast<pthread_mutex_t*>(Data));
    delete Data;
}

UInt32 MutImplementationLock(void* Data)
{
    pthread_mutex_lock(static_cast<pthread_mutex_t*>(Data));
    return syscall(SYS_gettid);
}

void MutImplementationUnlock(void* Data)
{    
    pthread_mutex_unlock(static_cast<pthread_mutex_t*>(Data));
}
#endif


Mutex::Mutex()
:m_IsLogicLock(false)
{
    m_ImplData=MutImplementationInit();
}

Mutex::~Mutex()
{
    MutImplementationFree(m_ImplData);
}

void Mutex::Lock()
{
  m_ThreadID=MutImplementationLock(m_ImplData);
  m_IsLogicLock=true;
}

void Mutex::Unlock()
{
    m_IsLogicLock=false;
    m_ThreadID=0;
    MutImplementationUnlock(m_ImplData);
}

Bool Mutex::IsLocked()
{
    return m_IsLogicLock;
}

UInt32 Mutex::LockedByThreadID()
{
    return m_ThreadID;
}
