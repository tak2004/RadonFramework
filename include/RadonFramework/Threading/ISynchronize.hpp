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
                virtual Core::Types::Bool TryLock(Core::Types::UInt64 TimeInMicroSec)=0;
                virtual void Unlock()=0;
                // signals
                virtual void Wait()=0;
                virtual Core::Types::Bool Wait(Core::Types::UInt64 TimeInMicroSec)=0;
                virtual void Pulse()=0;
                virtual void PulseAll()=0;
        };
    }
}

#endif // RF_THREADING_ISYNCHRONIZE_HPP