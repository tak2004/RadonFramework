#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware.hpp"
#include "RadonFramework/System/Hardware/CacheInfo.hpp"
#include "RadonFramework/System/Hardware/ProcessorFeatures.hpp"

#include <unistd.h>
#include <sched.h>

using namespace RadonFramework;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Collections;

RF_Type::UInt32 GetAvailableLogicalProcessorCountLinux()
{
    static RF_Type::UInt32 NumberOfProcessors = 0;
    RF_Type::UInt32 result;
    if (NumberOfProcessors > 0)
    {
        result = NumberOfProcessors;
    }
    else
    {
        NumberOfProcessors = sysconf(_SC_NPROCESSORS_ONLN);
    }
    return result;
}

RF_Type::UInt32 GetCurrentProcessorNumberLinux()
{
    RF_Type::UInt32 result = 0;
    int cpu = sched_getcpu();
    if(cpu >= 0)
    {
        result = cpu;
    }
    return result;
}

namespace RadonFramework { namespace System { namespace Hardware {

void DispatchLinux()
{
    GetAvailableLogicalProcessorCount = GetAvailableLogicalProcessorCountLinux;
    GetCurrentProcessorNumber = GetCurrentProcessorNumberLinux;
}

} } }