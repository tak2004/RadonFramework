module;
#include <windows.h>
export module rf.core.os:threading;
import rf.core.types;

export namespace rf {
using TimerCallback = void (*)(void *);

void sleep(timeval Timespan);
ptr createTimerQueue(TimerCallback Callback, ptr Parameter, i32 DueTime,
                     i32 Period);
void destroyTimerQueue(ptr &Handle);
ptr createMutex();
void destroyMutex(ptr &Handle);
u32 lockMutex(ptr Handle);
void unlockMutex(ptr Handle);

void sleep(timeval Timespan) { ::Sleep(Timespan); }

struct TimerWrapper {
  TimerCallback Callback;
  void *Parameter;
  HANDLE Handle;
};

void CALLBACK timerCallbackWrapper(PVOID lpParameter,
                                   BOOLEAN TimerOrWaitFired) {
  TimerWrapper *wrapper = reinterpret_cast<TimerWrapper *>(lpParameter);
  wrapper->Callback(wrapper->Parameter);
}

ptr createTimerQueue(TimerCallback Callback, ptr Parameter, i32 DueTime,
                     i32 Period) {
  TimerWrapper *wrapper = new TimerWrapper();
  wrapper->Callback = Callback;
  wrapper->Parameter = Parameter;
  ptr result = wrapper;
  CreateTimerQueueTimer(&wrapper->Handle, 0, timerCallbackWrapper, wrapper,
                        DueTime, Period, WT_EXECUTEINTIMERTHREAD);
  return result;
}

void destroyTimerQueue(ptr &Handle) {
  if (Handle) {
    TimerWrapper *pimpl = reinterpret_cast<TimerWrapper *>(Handle);
    // msdn say call it again till DeleteTimerQueueTimer succeed or error is
    // ERROR_IO_PENDING
    for (; DeleteTimerQueueTimer(0, pimpl->Handle, 0) == 0 &&
           GetLastError() != ERROR_IO_PENDING;) {
    }
    delete pimpl;
    Handle = nullptr;
  }
}

ptr createMutex() {
  HANDLE result = nullptr;
  result = ::CreateMutex(NULL,  // default security attributes
                         FALSE, // initially not owned
                         NULL);
  return static_cast<ptr>(result);
}

void destroyMutex(ptr& Handle) {
  CloseHandle(*static_cast<HANDLE *>(Handle));
  Handle = nullptr;
}

u32 lockMutex(ptr Handle) {
  ::WaitForSingleObject(*static_cast<HANDLE *>(Handle), INFINITE);
  return ::GetCurrentThreadId();
}

void unlockMutex(ptr Handle) {
  ::ReleaseMutex(*static_cast<HANDLE *>(Handle));
}
} // namespace rf