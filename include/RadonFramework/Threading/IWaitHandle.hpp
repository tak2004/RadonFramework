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
        namespace CT=RadonFramework::Core::Types;

        class IWaitHandle
        {
            public:
                static const CT::Int32 WaitTimeout;

                static CT::Bool SignalAndWait(IWaitHandle* toSignal,
                                              IWaitHandle* toWaitOn);

                static CT::Bool SignalAndWait(IWaitHandle* toSignal,
                                              IWaitHandle* toWaitOn,
                                              CT::Int32 MillisecondsTimeout,
                                              CT::Bool ExitContext);

                static CT::Bool SignalAndWait(IWaitHandle* toSignal,
                                              IWaitHandle* toWaitOn,
                                              Time::TimeSpan& Timeout,
                                              CT::Bool ExitContext);

                static CT::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles);

                static CT::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles,
                                        CT::Int32 MillisecondsTimeout);

                static CT::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles,
                                        Time::TimeSpan Timeout);

                static CT::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles,
                                        CT::Int32 MillisecondsTimeout,
                                        CT::Bool ExitContext);

                static CT::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles,
                                        Time::TimeSpan Timeout,
                                        CT::Bool ExitContext);

                static CT::Int32 WaitAny(Collections::Array<IWaitHandle>& WaitHandles);

                static CT::Int32 WaitAny(Collections::Array<IWaitHandle>& WaitHandles,
                                         CT::Int32 MillisecondsTimeout);

                static CT::Bool WaitAny(Collections::Array<IWaitHandle>& WaitHandles,
                                        Time::TimeSpan Timeout);

                static CT::Bool WaitAny(Collections::Array<IWaitHandle>& WaitHandles,
                                        CT::Int32 MillisecondsTimeout,
                                        CT::Bool ExitContext);

                static CT::Bool WaitAny(Collections::Array<IWaitHandle>& WaitHandles,
                                        Time::TimeSpan Timeout,
                                        CT::Bool ExitContext);

                //SafeWaitHandle SafeWaitHandle();
                //void SafeWaitHandle(SafeWaitHandle NewValue);

                virtual void Close()=0;

                virtual CT::Bool WaitOne()=0;

                virtual CT::Bool WaitOne(CT::Int32 MillisecondsTimeout)=0;

                virtual CT::Bool WaitOne(Time::TimeSpan& Timeout)=0;

                virtual CT::Bool WaitOne(CT::Int32 MillisecondsTimeout,
                                         CT::Bool ExitContext)=0;

                virtual CT::Bool WaitOne(Time::TimeSpan& Timeout,
                                         CT::Bool ExitContext)=0;
            protected:
                static const Memory::PointerID InvalidHandle;
        };
    }
}

#endif // RF_THREADING_IWAITHANDLE_HPP