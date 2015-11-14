#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Threading/Thread.hpp"
#include "RadonFramework/System/Threading/Thread.hpp"
#include "RadonFramework/System/Threading/Condition.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <sys/prctl.h>

namespace RadonFramework { namespace System { namespace Threading {

namespace Linux {

void Rename(void* Data, const RF_Type::String& Name)
{
    prctl(PR_SET_NAME, Name.c_str(), 0, 0, 0, 0);
}

RF_Type::Bool GetAffinityMask(void* Data, RF_Collect::BitArray<>& Mask)
{
    RF_Type::Bool result = false;
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    if(pthread_getaffinity_np(p->ID, sizeof(cpuset), &cpuset) == 0)
    {
        Mask.Resize(CPU_SETSIZE);
        Mask.Reset();
        for(RF_Type::Size i = 0; i < CPU_SETSIZE; ++i)
        {
            if(CPU_ISSET(i, &cpuset))
                Mask.Set(i);
        }
        result = true;
    }
    return result;
}

RF_Type::Bool SetAffinityMask(void* Data, const RF_Collect::BitArray<>& NewValue)
{
    ThreadHelper* p = static_cast<ThreadHelper*>(Data);
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    for(RF_Type::Size i = 0; i < NewValue.Count(); ++i)
    {
        if(NewValue[i])
            CPU_SET(i, &cpuset);
    }
    return pthread_setaffinity_np(p->ID, sizeof(cpu_set_t), &cpuset) == 0;
}

}

void Dispatch_Linux()
{
    Rename = Linux::Rename;
    GetAffinityMask = Linux::GetAffinityMask;
    SetAffinityMask = Linux::SetAffinityMask;
}

} } }