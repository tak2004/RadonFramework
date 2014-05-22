#ifndef RF_SYSTEM_THREADING_MUTEX_HPP
#define RF_SYSTEM_THREADING_MUTEX_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework {
    namespace Time {
        struct TimeSpan;
    }

    namespace System { namespace Threading {

    class Mutex
    {
    friend void CondImplementationWait(void*, Mutex&);
    friend void CondImplementationTimeWait(void*, Mutex&, const Time::TimeSpan&);
    public:
        Mutex();
        ~Mutex();
        void Lock();
        void Unlock();
        RFTYPE::Bool IsLocked();
        /// Return 0 if the resource isn't locked else the thread id.
        RFTYPE::UInt32 LockedByThreadID();
    protected:
        RFTYPE::Bool m_IsLogicLock;
        RFTYPE::UInt32 m_ThreadID;
        void* m_ImplData;
    };

} } }

#endif // RF_SYSTEM_THREADING_MUTEX_HPP
