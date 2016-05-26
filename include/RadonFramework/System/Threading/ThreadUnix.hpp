#ifndef RF_SYSTEM_THREADING_THREADUNIX_HPP
#define RF_SYSTEM_THREADING_THREADUNIX_HPP

#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <pthread.h>

namespace RadonFramework { namespace System { namespace Threading { namespace Unix {

struct ThreadHelper
{
    pthread_t ID;
    pthread_mutex_t mutex;
    pthread_mutex_t mutexIsAlive;
    pthread_cond_t aliveChanged;
    pthread_attr_t attr;
    Delegate<void()> OnFinished;
    Delegate<void()> OnRun;
    RF_Type::UInt64* PID;
    RF_Type::Bool alive;
    RF_Type::Bool cancel;
    RF_Type::Bool postConfigurationComplete;
};

} } } }

#endif // !RF_SYSTEM_THREADING_THREADUNIX_HPP