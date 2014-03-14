#ifndef RF_SYSTEM_THREADING_MUTEX_HPP
#define RF_SYSTEM_THREADING_MUTEX_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>

namespace RadonFramework
{
    namespace Time
    {
        class TimeSpan;
    }
    namespace System
    {
        namespace Threading
        {
            class Mutex
            {
                friend void CondImplementationWait(void*, Mutex&);
                friend void CondImplementationTimeWait(void*, Mutex&, const RadonFramework::Time::TimeSpan&);                                
                public:
                    Mutex();
                    ~Mutex();
                    void Lock();
                    void Unlock();
                    Core::Types::Bool IsLocked();
                    /// Return 0 if the resource isn't locked else the thread id.
                    Core::Types::UInt32 LockedByThreadID();
                protected:
                    Core::Types::Bool m_IsLogicLock;
                    Core::Types::UInt32 m_ThreadID;
                    void* m_ImplData;
            };
        }
    }    
}

#endif // RF_SYSTEM_THREADING_MUTEX_HPP
