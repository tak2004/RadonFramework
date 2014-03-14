#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_MEMORYMODULEINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_MEMORYMODULEINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace SMBios
            {
                namespace MemoryTypesField
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        Standard=4,
                        FastPageMode=8,
                        EDO=16,
                        Parity=32,
                        ECC=64,
                        SIMM=128,
                        DIMM=256,
                        BurstEDO=512,
                        SDRAM=1024
                        //11-15 reserved, must be zero
                    };
                }

                namespace MemorySizeField
                {
                    enum Type
                    {
                        //0-124=2^n MB
                        NotDeterminable=125,
                        IsInstalledButMemoryIsDisabled=126,
                        NotInstalled=127,
                        IsDoubleBank=128//1=yes,0=single-bank
                    };
                }

                class MemoryModuleInformation
                {
                    public:
                        MemoryModuleInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                                                Collections::AutoVector<Core::Types::String> StringList);
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_MEMORYMODULEINFORMATION_HPP