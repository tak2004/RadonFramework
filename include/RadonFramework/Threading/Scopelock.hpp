#ifndef RF_THREADING_SCOPELOCK_HPP
#define RF_THREADING_SCOPELOCK_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace System
    {
        namespace Threading
        {
            class Mutex;
        }
    }
    namespace Threading
    {
        class Scopelock
        {
            public:
                Scopelock(System::Threading::Mutex& Ref);
                ~Scopelock();
            protected:
                System::Threading::Mutex* m_Mutex;
                Scopelock();
                Scopelock(const Scopelock& Other);
        };
    }
}

#endif // RF_THREADING_SCOPELOCK_HPP
