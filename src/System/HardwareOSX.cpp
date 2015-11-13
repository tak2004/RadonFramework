#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware.hpp"
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

RF_Type::Size GetPhysicalMemorySizeOSX()
{
    int mib[2];
    RF_Type::Size physical_memory;
    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;
    RF_Type::Size length = sizeof(RF_Type::Size);
    sysctl(mib, 2, &physical_memory, &length, NULL, 0);
    return physical_memory;
}

RF_Type::Size GetFreePhysicalMemorySizeOSX()
{
    RF_Type::Size result = 0;
    vm_size_t page_size;
    mach_port_t mach_port;
    mach_msg_type_number_t count;
    vm_statistics64_data_t vm_stats;

    mach_port = mach_host_self();
    count = sizeof(vm_stats) / sizeof(natural_t);
    if(KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
        KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
        (host_info64_t)&vm_stats, &count))
    {
        result = (RF_Type::Size)vm_stats.free_count * (RF_Type::Size)page_size;
    }
    return result;
}

namespace RadonFramework { namespace System { namespace Hardware {

void Dispatch_OSX()
{
    GetPhysicalMemorySize = GetPhysicalMemorySizeOSX;
    GetFreePhysicalMemorySize = GetFreePhysicalMemorySizeOSX;
}

} } }