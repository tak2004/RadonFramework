#ifndef RF_SYSTEM_THREADING_MUTEX_HPP
#define RF_SYSTEM_THREADING_MUTEX_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Time {

struct TimeSpan;

}

namespace RadonFramework::System::Threading {

class Mutex
{
friend void CondImplementationWait(void*, Mutex&);
friend void CondImplementationTimeWait(void*, Mutex&, 
    const RadonFramework::Time::TimeSpan&);
public:
    Mutex();
    ~Mutex();
    void Lock();
    void Unlock();
    RF_Type::Bool IsLocked();
    /// Return 0 if the resource isn't locked else the thread id.
    RF_Type::UInt32 LockedByThreadID();
protected:
    RF_Type::Bool m_IsLogicLock;
    RF_Type::UInt32 m_ThreadID;
    void* m_ImplData;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_SYSTHREAD
#define RF_SHORTHAND_NAMESPACE_SYSTHREAD
namespace RF_SysThread = RadonFramework::System::Threading;
#endif

#endif // RF_SYSTEM_THREADING_MUTEX_HPP
