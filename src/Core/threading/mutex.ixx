export module rf.core.threading:mutex;

import rf.core.types;
import rf.core.os;
import rf.core.time;

export namespace rf {
class Mutex {
  friend void CondImplementationWait(ptr, Mutex &);
  friend void CondImplementationTimeWait(ptr, Mutex &, const TimeSpan &);

public:
  Mutex();
  ~Mutex();
  void lock();
  void unlock();
  bool isLocked();
  /// Return 0 if the resource isn't locked else the thread id.
  u32 lockedByThreadID();

protected:
  bool isLogicLock;
  u32 threadID;
  ptr handle;
};
Mutex::Mutex() : isLogicLock(false) { this->handle = createMutex(); }

Mutex::~Mutex() { destroyMutex(this->handle); }

void Mutex::lock() {
  this->threadID = lockMutex(this->handle);
  this->isLogicLock = true;
}

void Mutex::unlock() {
  this->isLogicLock = false;
  this->threadID = 0;
  unlockMutex(this->handle);
}

bool Mutex::isLocked() { return this->isLogicLock; }

u32 Mutex::lockedByThreadID() { return this->threadID; }
} // namespace rf