module;
#include <windows.h>
export module rf.core.os:threading_implementation;
import rf.core.types;

export namespace rf {
enum class ThreadError { TooManyThreads, InvalidArgument, Unknown };
using AffinityBitMask = u64;
using ThreadID = u64;
using GroupID = u64;
using TimerCallback = void (*)(void *);
using Callback = void (*)(void *UserData);
using ErrorCallback = void (*)(void *UserData, const ThreadError Error);

// System timer
ptr createTimerQueue(TimerCallback Callback, ptr Parameter, i32 DueTime,
                     i32 Period);
void destroyTimerQueue(ptr &Handle);

// system mutex
struct MutexHandler;
MutexHandler createMutex();
void destroyMutex(MutexHandler &AMutex);
void lockMutex(MutexHandler &AMutex);
void unlockMutex(MutexHandler &AMutex);
bool isMutexLocked(MutexHandler &AMutex);
ThreadID lockedByThreadID(MutexHandler &AMutex);

// system threads
struct ThreadHandler;
void shortestPause();
void sleep(timeval Timespan);
bool setThreadAffinityMask(ThreadHandler &AThread, const GroupID NewGroup,
                           const AffinityBitMask NewMask);
ThreadHandler *createThread(void *UserData, Callback OnRun, Callback OnFinished,
                           ErrorCallback OnError);
void postThreadConfigurationComplete(ThreadHandler &AThread);

// system conditions
struct ConditionHandler;
ConditionHandler createCondition();
void destroyCondition(ConditionHandler &ACondition);
void waitForCondition(ConditionHandler &ACondition, MutexHandler &Lock);
void waitForConditionWithTimeout(ConditionHandler &ACondition,
                                 MutexHandler &Lock,
                                 const u64 Miliseconds);
void conditionNotify(ConditionHandler &ACondition);
void conditionNotifyAll(ConditionHandler &ACondition);

// Implementation
void shortestPause() { YieldProcessor(); }

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

struct ConditionHandler {
  HANDLE semaphore;
  HANDLE waiters_done;
  long waiters_count;
  size_t was_broadcast;
};

struct MutexHandler {
  HANDLE mutex;
  ThreadID threadID;
  bool isLogicLock;
};

struct ThreadHandler {
  ConditionHandler aliveChanged;
  HANDLE thread;
  HANDLE mutexIsAlive;
  MutexHandler mutex;
  DWORD ID;
  Callback OnFinished;
  Callback OnRun;
  ErrorCallback OnError;
  void *UserData;
  bool alive;
  bool cancel;
  bool postConfigurationComplete;
};

MutexHandler createMutex() {
  MutexHandler result;
  result.mutex = ::CreateMutexA(NULL,  // default security attributes
                                FALSE, // initially not owned
                                NULL);
  result.threadID = 0;
  result.isLogicLock = false;
  return result;
}

void destroyMutex(MutexHandler &AMutex) { CloseHandle(AMutex.mutex); }

void lockMutex(MutexHandler &AMutex) {
  WaitForSingleObject(AMutex.mutex, INFINITE);
  AMutex.threadID = GetCurrentThreadId();
  AMutex.isLogicLock = true;
}

void unlockMutex(MutexHandler &AMutex) {
  AMutex.isLogicLock = false;
  AMutex.threadID = 0;
  ReleaseMutex(AMutex.mutex);
}
bool isMutexLocked(MutexHandler &AMutex) { return AMutex.isLogicLock; }
ThreadID lockedByThreadID(MutexHandler &AMutex) { return AMutex.threadID; }

void setAlive(ThreadHandler &AThread, bool Value) {
  ::WaitForSingleObject(AThread.mutexIsAlive, INFINITE);
  if (Value != AThread.alive) {
    AThread.alive = Value;
    ::ReleaseMutex(AThread.mutexIsAlive);

    lockMutex(AThread.mutex);
    conditionNotifyAll(AThread.aliveChanged);
    unlockMutex(AThread.mutex);
  } else
    ::ReleaseMutex(AThread.mutexIsAlive);
}

DWORD WINAPI threadFunction(void *userdata) {
  ThreadHandler *p = static_cast<ThreadHandler *>(userdata);
  setAlive(*p, true);
  while (!p->postConfigurationComplete) {
    ::Sleep(0);
  }
  if (p->OnRun)
    p->OnRun(p->UserData);
  setAlive(*p, false);
  if (p->OnFinished)
  p->OnFinished(p->UserData);
  ::ExitThread(0);
  return 0;
}

ThreadHandler *createThread(void *UserData, Callback OnRun, Callback OnFinished,
                            ErrorCallback OnError) {
  ThreadHandler *p = new ThreadHandler;

  p->OnFinished = OnFinished;
  p->OnRun = OnRun;
  p->OnError = OnError;
  p->UserData = UserData;
  p->ID = 0;
  p->alive = false;
  p->cancel = false;
  p->postConfigurationComplete = false;
  p->thread = 0;
  p->mutex = createMutex();
  p->aliveChanged = createCondition();

  lockMutex(p->mutex);
  p->thread = (HANDLE)::CreateThread(NULL, 0, threadFunction, p, 0, &p->ID);

  if (!p->thread) {
    unlockMutex(p->mutex);
    delete p;
    switch (errno) {
    case EAGAIN:
      p->OnError(p->UserData, ThreadError::TooManyThreads);
      break;
    case EINVAL:
      p->OnError(p->UserData, ThreadError::InvalidArgument);
      break;
    default:
      p->OnError(p->UserData, ThreadError::Unknown);
      break;
    }
  } else {
    waitForCondition(p->aliveChanged, p->mutex);
    unlockMutex(p->mutex);
  }
  return p;
}

void destroyThread(ThreadHandler *AThread) {
  if (AThread->alive) {
    setAlive(*AThread, false);
    ::WaitForSingleObject(AThread->thread, INFINITE);
  }

  if (AThread->thread)
    ::CloseHandle(AThread->thread);

  delete AThread;
}

bool setThreadAffinityMask(ThreadHandler &AThread, const GroupID NewGroup,
                           const AffinityBitMask NewMask) {
  GROUP_AFFINITY groupAffinity;
  groupAffinity.Group = static_cast<WORD>(NewGroup);
  groupAffinity.Mask = NewMask;
  return ::SetThreadSelectedCpuSetMasks(AThread.thread, &groupAffinity, 1);
}

void postThreadConfigurationComplete(ThreadHandler &AThread) {
  AThread.postConfigurationComplete = true;
}

ConditionHandler createCondition() {
  ConditionHandler result;
  result.waiters_count = 0;
  result.was_broadcast = 0;
  result.semaphore = CreateSemaphore(nullptr, 0, 0x7ffffff, nullptr);
  result.waiters_done = CreateEvent(nullptr, false, false, nullptr);
  return result;
}

void destroyCondition(ConditionHandler &ACondition) {
  CloseHandle(ACondition.waiters_done);
  CloseHandle(ACondition.semaphore);
}

void waitForCondition(ConditionHandler &ACondition, MutexHandler &Lock) {
  InterlockedIncrement(&ACondition.waiters_count);

  int res = 0;
  unlockMutex(Lock);
  DWORD dwres = WaitForSingleObject(ACondition.semaphore, INFINITE);
  if (dwres != WAIT_OBJECT_0)
    res = (int)dwres;

  InterlockedDecrement(&ACondition.waiters_count);
  long w = InterlockedExchangeAdd(&ACondition.waiters_count, 0);
  int last_waiter = ACondition.was_broadcast && w == 0;

  if (res != -1 && last_waiter)
    SetEvent(ACondition.waiters_done);

  lockMutex(Lock);
}

void waitForConditionWithTimeout(ConditionHandler &ACondition,
                                 MutexHandler &Lock,
                                 const u64 Miliseconds) {
  if (Miliseconds == 0)
    waitForCondition(ACondition, Lock);
  else {
    InterlockedIncrement(&ACondition.waiters_count);

    int res = 0;
    lockMutex(Lock);
    DWORD dwres = WaitForSingleObject(ACondition.semaphore,
                                      static_cast<DWORD>(Miliseconds));
    if (dwres != WAIT_OBJECT_0)
      res = (int)dwres;

    InterlockedDecrement(&ACondition.waiters_count);
    long w = InterlockedExchangeAdd(&ACondition.waiters_count, 0);
    int last_waiter = ACondition.was_broadcast && w == 0;

    if (res != -1 && last_waiter)
      SetEvent(ACondition.waiters_done);
    lockMutex(Lock);
  }
}

void conditionNotify(ConditionHandler &ACondition) {
  long w = InterlockedExchangeAdd(&ACondition.waiters_count, 0);
  int have_waiters = w > 0;

  if (have_waiters)
    ReleaseSemaphore(ACondition.semaphore, 1, 0);
}

void conditionNotifyAll(ConditionHandler &ACondition) {
  int have_waiters = 0;
  long w = InterlockedExchangeAdd(&ACondition.waiters_count, 0);

  if (w > 0) {
    ACondition.was_broadcast = 1;
    have_waiters = 1;
  }

  if (have_waiters) {
    ReleaseSemaphore(ACondition.semaphore, ACondition.waiters_count, 0);
    WaitForSingleObject(ACondition.waiters_done, INFINITE);
    ACondition.was_broadcast = 0;
  }
}
} // namespace rf