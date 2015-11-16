#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware/Hardware.hpp"
#include "RadonFramework/System/Hardware/CacheInfo.hpp"
#include "RadonFramework/System/Hardware/ProcessorFeatures.hpp"

#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/sysinfo.h>

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

RF_Type::Size GetPhysicalMemorySizeLinux()
{
    struct sysinfo memInfo;    
    sysinfo(&memInfo);
    RF_Type::Size totalVirtualMem = memInfo.totalram;
    totalVirtualMem *= memInfo.mem_unit;
    return totalVirtualMem;
}

RF_Type::Size GetFreePhysicalMemorySizeLinux()
{
    struct sysinfo memInfo;
    sysinfo(&memInfo);
    RF_Type::Size totalVirtualMem = memInfo.freeram;
    totalVirtualMem *= memInfo.mem_unit;
    return totalVirtualMem;
}

namespace RadonFramework { namespace System { namespace Hardware {

void Dispatch_Linux()
{
    GetAvailableLogicalProcessorCount = GetAvailableLogicalProcessorCountLinux;
    GetCurrentProcessorNumber = GetCurrentProcessorNumberLinux;
    GetPhysicalMemorySize = GetPhysicalMemorySizeLinux;
    GetFreePhysicalMemorySize = GetFreePhysicalMemorySizeLinux;
}

} } }