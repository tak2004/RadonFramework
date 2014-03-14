#ifndef RF_THREADING_IRUNNABLE_HPP
#define RF_THREADING_IRUNNABLE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Threading
    {
        class IRunnable
        {
            public:
                virtual ~IRunnable() {}
                virtual void Run()=0;
        };
    }
}

#endif // RF_THREADING_IRUNNABLE_HPP
