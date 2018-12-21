#ifndef RF_THREADING_SCOPELOCK_HPP
#define RF_THREADING_SCOPELOCK_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::System::Threading
{
class Mutex;
}

namespace RadonFramework::Threading
{
class Scopelock
{
public:
  Scopelock(System::Threading::Mutex& Ref);
  ~Scopelock();

protected:
  System::Threading::Mutex* m_Mutex;
  Scopelock() = default;
  Scopelock(const Scopelock& Other);
  Scopelock& operator=(const Scopelock& Other);
};

}  // namespace RadonFramework::Threading

#ifndef RF_SHORTHAND_NAMESPACE_THREAD
#define RF_SHORTHAND_NAMESPACE_THREAD
namespace RF_Thread = RadonFramework::Threading;
#endif  // !RF_SHORTHAND_NAMESPACE_THREAD

#endif  // RF_THREADING_SCOPELOCK_HPP
