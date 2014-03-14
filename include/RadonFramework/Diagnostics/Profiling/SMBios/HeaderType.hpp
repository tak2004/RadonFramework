#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_HEADERTYPE_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_HEADERTYPE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace SMBios
            {
                namespace HeaderType
                {
                    enum Type
                    {
                        BIOSInformation=0,
                        SystemInformation=1,
                        BaseBoardInformation=2,
                        SystemEnclosure=3,
                        ProcessorInformation=4,
                        MemoryController=5,
                        MemoryModule=6,
                        CacheInformation=7,
                        PortConnector=8,
                        SystemSlot=9,
                        OnBoardDevice=10,
                        OEMStrings=11,
                        SystemConfigurationOptions=12,
                        BIOSLanguageInformation=13,
                        GroupAssociations=14,
                        SystemEventLog=15,
                        PhysicalMemoryArray=16,
                        MemoryDevice=17,
                        MemoryArrayMappedAddress=19,
                        VoltageProbe=26,
                        SystemBootInformation=32,
                        Inactive=126,
                        EndOfTable=127
                    };
                }
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_HEADERTYPE_HPP