#ifndef RF_THREADING_TASKSTRATEGY_HPP
#define RF_THREADING_TASKSTRATEGY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Threading::TaskStrategy {

enum Type
{
    SerialPerThread,
    Concurrent
};

}

#ifndef RF_SHORTHAND_NAMESPACE_THREAD
#define RF_SHORTHAND_NAMESPACE_THREAD
namespace RF_Thread = RadonFramework::Threading;
#endif

#endif // RF_THREADING_TASKSTRATEGY_HPP