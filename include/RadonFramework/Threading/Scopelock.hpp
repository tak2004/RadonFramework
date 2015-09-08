#ifndef RF_THREADING_SCOPELOCK_HPP
#define RF_THREADING_SCOPELOCK_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace System { namespace Threading {

class Mutex;

} } }

namespace RadonFramework { namespace Threading {

class Scopelock
{
public:
    Scopelock(System::Threading::Mutex& Ref);
    ~Scopelock();
protected:
    System::Threading::Mutex* m_Mutex;
    Scopelock();
    Scopelock(const Scopelock& Other);
    Scopelock& operator=(const Scopelock& Other);
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_THREAD
#define RF_SHORTHAND_NAMESPACE_THREAD
namespace RF_Thread = RadonFramework::Threading;
#endif // !RF_SHORTHAND_NAMESPACE_THREAD


#endif // RF_THREADING_SCOPELOCK_HPP
