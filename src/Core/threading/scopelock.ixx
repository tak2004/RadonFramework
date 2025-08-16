export module rf.core.threading:scopelock;
import rf.core.os;

export namespace rf {
/*
class ScopeLock {
public:
  ScopeLock()=delete;
  ScopeLock(MutexHandler &Ref);
  ScopeLock(const ScopeLock &Other)=delete;
  ~ScopeLock();
    
  ScopeLock &operator=(const ScopeLock &Other)=delete;
protected:
  MutexHandler &mutex;
};

ScopeLock::ScopeLock(MutexHandler &Ref) : mutex(Ref) { lockMutex(this->mutex); }

ScopeLock::~ScopeLock() { unlockMutex(this->mutex); }

*/} // namespace rf