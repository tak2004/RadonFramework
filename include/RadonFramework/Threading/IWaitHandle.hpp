#ifndef RF_THREADING_IWAITHANDLE_HPP
#define RF_THREADING_IWAITHANDLE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Memory/PointerID.hpp>
#include <RadonFramework/Time/TimeSpan.hpp>
#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework
{
    namespace Threading
    {
        class IWaitHandle
        {
            public:
                static const RFTYPE::Int32 WaitTimeout;

                static RFTYPE::Bool SignalAndWait(IWaitHandle* toSignal,
                                              IWaitHandle* toWaitOn);

                static RFTYPE::Bool SignalAndWait(IWaitHandle* toSignal,
                                              IWaitHandle* toWaitOn,
                                              RFTYPE::Int32 MillisecondsTimeout,
                                              RFTYPE::Bool ExitContext);

                static RFTYPE::Bool SignalAndWait(IWaitHandle* toSignal,
                                              IWaitHandle* toWaitOn,
                                              Time::TimeSpan& Timeout,
                                              RFTYPE::Bool ExitContext);

                static RFTYPE::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles);

                static RFTYPE::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles,
                                        RFTYPE::Int32 MillisecondsTimeout);

                static RFTYPE::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles,
                                        Time::TimeSpan Timeout);

                static RFTYPE::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles,
                                        RFTYPE::Int32 MillisecondsTimeout,
                                        RFTYPE::Bool ExitContext);

                static RFTYPE::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles,
                                        Time::TimeSpan Timeout,
                                        RFTYPE::Bool ExitContext);

                static RFTYPE::Int32 WaitAny(Collections::Array<IWaitHandle>& WaitHandles);

                static RFTYPE::Int32 WaitAny(Collections::Array<IWaitHandle>& WaitHandles,
                                         RFTYPE::Int32 MillisecondsTimeout);

                static RFTYPE::Bool WaitAny(Collections::Array<IWaitHandle>& WaitHandles,
                                        Time::TimeSpan Timeout);

                static RFTYPE::Bool WaitAny(Collections::Array<IWaitHandle>& WaitHandles,
                                        RFTYPE::Int32 MillisecondsTimeout,
                                        RFTYPE::Bool ExitContext);

                static RFTYPE::Bool WaitAny(Collections::Array<IWaitHandle>& WaitHandles,
                                        Time::TimeSpan Timeout,
                                        RFTYPE::Bool ExitContext);

                //SafeWaitHandle SafeWaitHandle();
                //void SafeWaitHandle(SafeWaitHandle NewValue);

                virtual void Close()=0;

                virtual RFTYPE::Bool WaitOne()=0;

                virtual RFTYPE::Bool WaitOne(RFTYPE::Int32 MillisecondsTimeout)=0;

                virtual RFTYPE::Bool WaitOne(Time::TimeSpan& Timeout)=0;

                virtual RFTYPE::Bool WaitOne(RFTYPE::Int32 MillisecondsTimeout,
                                         RFTYPE::Bool ExitContext)=0;

                virtual RFTYPE::Bool WaitOne(Time::TimeSpan& Timeout,
                                         RFTYPE::Bool ExitContext)=0;
            protected:
                static const Memory::PointerID InvalidHandle;
        };
    }
}

#endif // RF_THREADING_IWAITHANDLE_HPP