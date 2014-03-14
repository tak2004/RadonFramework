#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Time.hpp"

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <windows.h>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::System::Time;

struct TimerWrapper
{
    TimerCallback Callback;
    void* Parameter;
    HANDLE Handle;
};

void CALLBACK TimerCallbackWrapper(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{
    TimerWrapper* wrapper = reinterpret_cast<TimerWrapper*>(lpParameter);
    wrapper->Callback(wrapper->Parameter);
}

TimerHandle CreateTimerQueueCallback(TimerCallback Callback, void* Parameter, 
                                     Int32 DueTime, Int32 Period)
{
    TimerWrapper* wrapper = new TimerWrapper();
    wrapper->Callback = Callback;
    wrapper->Parameter = Parameter;
    TimerHandle result = TimerHandle::GenerateFromPointer(wrapper);
    CreateTimerQueueTimer(&wrapper->Handle, 0, TimerCallbackWrapper, wrapper, DueTime, Period, WT_EXECUTEINTIMERTHREAD);
    return result;
}

void DeleteTimerQueueCallback(TimerHandle& Handle)
{
    if (Handle.GetPointer())
    {
        TimerWrapper* pimpl=reinterpret_cast<TimerWrapper*>(Handle.GetPointer());
        DeleteTimerQueueTimer(0, pimpl->Handle, 0);
        delete pimpl;
        Handle=TimerHandle::Zero();
    }
}

void RadonFramework::System::Time::Dispatch()
{
    CreateTimerQueue=::CreateTimerQueueCallback;
    DeleteTimerQueue=::DeleteTimerQueueCallback;
}