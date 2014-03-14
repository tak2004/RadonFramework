#ifndef RF_THREADING_TASKSTRATEGY_HPP
#define RF_THREADING_TASKSTRATEGY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Threading
    {
        namespace TaskStrategy
        {
            enum Type
            {
                SerialPerThread,
                Concurrent
            };
        }
    }
}

#endif // RF_THREADING_TASKSTRATEGY_HPP