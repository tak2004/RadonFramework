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

namespace RadonFramework { namespace System { namespace Hardware {

namespace Linux {

RF_Type::UInt32 GetAvailableLogicalProcessorCount()
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

RF_Type::UInt32 GetCurrentProcessorNumber()
{
    RF_Type::UInt32 result = 0;
    int cpu = sched_getcpu();
    if(cpu >= 0)
    {
        result = cpu;
    }
    return result;
}

RF_Type::UInt32 GetCurrentUniqueProcessorNumber()
{
    return GetCurrentProcessorNumber();
}

RF_Type::Size GetPhysicalMemorySize()
{
    struct sysinfo memInfo;    
    sysinfo(&memInfo);
    RF_Type::Size totalVirtualMem = memInfo.totalram;
    totalVirtualMem *= memInfo.mem_unit;
    return totalVirtualMem;
}

RF_Type::Size GetFreePhysicalMemorySize()
{
    struct sysinfo memInfo;
    sysinfo(&memInfo);
    RF_Type::Size totalVirtualMem = memInfo.freeram;
    totalVirtualMem *= memInfo.mem_unit;
    return totalVirtualMem;
}

#ifndef RF_BUILD_INTRINSIC_CPUID
#if __ARMEL__
#include <sys/auxv.h>
#include <asm/hwcap.h>
RF_Type::Bool GetLogicalProcessorFeatures(ProcessorFeatureMask& Features)
{
    Features.None();
    long hwcaps = getauxval(AT_HWCAP);
    long hwcaps2 = getauxval(AT_HWCAP2);
    Features[ProcessorFeatures::NEON] = hwcaps & HWCAP_NEON;
    Features[ProcessorFeatures::AES] = hwcaps2 & HWCAP2_AES;
    Features[ProcessorFeatures::SHA1] = hwcaps2 & HWCAP2_SHA1;
    Features[ProcessorFeatures::SHA2] = hwcaps2 & HWCAP2_SHA2;
    Features[ProcessorFeatures::CRC32] = hwcaps2 & HWCAP2_CRC32;
    return true;
}
#endif
#endif

}

void Dispatch_Linux()
{
    GetAvailableLogicalProcessorCount = Linux::GetAvailableLogicalProcessorCount;
    GetCurrentProcessorNumber = Linux::GetCurrentProcessorNumber;
    GetCurrentUniqueProcessorNumber = Linux::GetCurrentUniqueProcessorNumber;
    GetPhysicalMemorySize = Linux::GetPhysicalMemorySize;
    GetFreePhysicalMemorySize = Linux::GetFreePhysicalMemorySize;
#ifndef RF_BUILD_INTRINSIC_CPUID
#if __ARMEL__
    GetLogicalProcessorFeatures = Linux::GetLogicalProcessorFeatures;
#endif
#endif
}

} } }