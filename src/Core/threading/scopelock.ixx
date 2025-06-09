export module rf.core.threading:scopelock;
import :mutex;

export namespace rf {
class Scopelock {
public:
  Scopelock(Mutex &Ref);
  ~Scopelock();

protected:
  Mutex *mutex;
  Scopelock() = default;
  Scopelock(const Scopelock &Other);
  Scopelock &operator=(const Scopelock &Other);
};

Scopelock::Scopelock(const Scopelock &Other) {}

Scopelock::Scopelock(Mutex &Ref) : mutex(&Ref) { this->mutex->lock(); }

Scopelock::~Scopelock() { this->mutex->unlock(); }

Scopelock &Scopelock::operator=(const Scopelock &Other) { return *this; }
} // namespace rf