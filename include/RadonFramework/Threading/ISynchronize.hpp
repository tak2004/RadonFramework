#ifndef RF_THREADING_ISYNCHRONIZE_HPP
#define RF_THREADING_ISYNCHRONIZE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Threading
    {
        class ISynchronize
        {
            public:
                // lock based mechanic
                virtual void Lock()=0;
                virtual RFTYPE::Bool TryLock(RFTYPE::UInt64 TimeInMicroSec)=0;
                virtual void Unlock()=0;
                // signals
                virtual void Wait()=0;
                virtual RFTYPE::Bool Wait(RFTYPE::UInt64 TimeInMicroSec)=0;
                virtual void Pulse()=0;
                virtual void PulseAll()=0;
        };
    }
}

#endif // RF_THREADING_ISYNCHRONIZE_HPP