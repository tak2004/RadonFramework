#ifndef RF_THREADING_THREADPRIORITY_HPP
#define RF_THREADING_THREADPRIORITY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Threading::ThreadPriority {

enum Type
{
    Minimal,
    Normal,
    Maximal
};

}

namespace RF_Thread = RadonFramework::Threading;

#endif // RF_THREADING_THREADPRIORITY_HPP