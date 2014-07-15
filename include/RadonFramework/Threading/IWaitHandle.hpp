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
                static const RF_Type::Int32 WaitTimeout;

                static RF_Type::Bool SignalAndWait(IWaitHandle* toSignal,
                                              IWaitHandle* toWaitOn);

                static RF_Type::Bool SignalAndWait(IWaitHandle* toSignal,
                                              IWaitHandle* toWaitOn,
                                              RF_Type::Int32 MillisecondsTimeout,
                                              RF_Type::Bool ExitContext);

                static RF_Type::Bool SignalAndWait(IWaitHandle* toSignal,
                                              IWaitHandle* toWaitOn,
                                              Time::TimeSpan& Timeout,
                                              RF_Type::Bool ExitContext);

                static RF_Type::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles);

                static RF_Type::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles,
                                        RF_Type::Int32 MillisecondsTimeout);

                static RF_Type::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles,
                                        Time::TimeSpan Timeout);

                static RF_Type::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles,
                                        RF_Type::Int32 MillisecondsTimeout,
                                        RF_Type::Bool ExitContext);

                static RF_Type::Bool WaitAll(Collections::Array<IWaitHandle>& WaitHandles,
                                        Time::TimeSpan Timeout,
                                        RF_Type::Bool ExitContext);

                static RF_Type::Int32 WaitAny(Collections::Array<IWaitHandle>& WaitHandles);

                static RF_Type::Int32 WaitAny(Collections::Array<IWaitHandle>& WaitHandles,
                                         RF_Type::Int32 MillisecondsTimeout);

                static RF_Type::Bool WaitAny(Collections::Array<IWaitHandle>& WaitHandles,
                                        Time::TimeSpan Timeout);

                static RF_Type::Bool WaitAny(Collections::Array<IWaitHandle>& WaitHandles,
                                        RF_Type::Int32 MillisecondsTimeout,
                                        RF_Type::Bool ExitContext);

                static RF_Type::Bool WaitAny(Collections::Array<IWaitHandle>& WaitHandles,
                                        Time::TimeSpan Timeout,
                                        RF_Type::Bool ExitContext);

                //SafeWaitHandle SafeWaitHandle();
                //void SafeWaitHandle(SafeWaitHandle NewValue);

                virtual void Close()=0;

                virtual RF_Type::Bool WaitOne()=0;

                virtual RF_Type::Bool WaitOne(RF_Type::Int32 MillisecondsTimeout)=0;

                virtual RF_Type::Bool WaitOne(Time::TimeSpan& Timeout)=0;

                virtual RF_Type::Bool WaitOne(RF_Type::Int32 MillisecondsTimeout,
                                         RF_Type::Bool ExitContext)=0;

                virtual RF_Type::Bool WaitOne(Time::TimeSpan& Timeout,
                                         RF_Type::Bool ExitContext)=0;
            protected:
                static const Memory::PointerID InvalidHandle;
        };
    }
}

#endif // RF_THREADING_IWAITHANDLE_HPP