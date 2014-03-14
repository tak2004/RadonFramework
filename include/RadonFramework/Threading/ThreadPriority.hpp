#ifndef RF_THREADING_THREADPRIORITY_HPP
#define RF_THREADING_THREADPRIORITY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Threading
    {
        namespace ThreadPriority
        {
            enum Type
            {
                Minimal,
                Normal,
                Maximal
            };
        }
    }
}

#endif // RF_THREADING_THREADPRIORITY_HPP