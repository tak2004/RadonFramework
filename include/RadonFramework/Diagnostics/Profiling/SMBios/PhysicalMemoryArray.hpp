#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_PHYSICALMEMORYARRAY_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_PHYSICALMEMORYARRAY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/Information.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/MemoryDevice.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace SMBios
            {
                namespace Location
                {
                    enum Type
                    {
                        Other=1,
                        Unknown,
                        SystemBoardOrMotherboard,
                        ISAAddOnCard,
                        EISAAddonCard,
                        PCIAddonCard,
                        MCAAddonCard,
                        PCMCIAAddonCard,
                        ProprietaryAddonCard,
                        NuBus,
                        PC98C20AddonCard=0xA0,
                        PC98C24AddonCard=0xA1,
                        PC98EAddonCard=0xA2,
                        PC98LocalBusAddonCard=0xA3
                    };
                }

                namespace Use
                {
                    enum Type
                    {
                        Other=1,
                        Unknown,
                        SystemMemory,
                        VideoMemory,
                        FlashMemory,
                        NonVolatileRAM,
                        CacheMemory
                    };
                }

                namespace ErrorCorrectionType
                {
                    enum Type
                    {
                        Other=1,
                        Unknown,
                        None,
                        Parity,
                        SingleBitECC,
                        MultiBitECC,
                        CRC
                    };
                }

                class PhysicalMemoryArray
                {
                    public:
                        PhysicalMemoryArray(Memory::AutoPointerArray<Core::Types::UInt8> Data,
                            Collections::AutoVector<Core::Types::String> StringList,
                            Collections::AutoVector<SMBios::Information> MemoryDevices);
                        const MemoryDevice& Device(const RadonFramework::Core::Types::UInt32 Index)const;
                        RadonFramework::Core::Types::UInt32 DeviceCount()const;
                        RadonFramework::Core::Types::Bool HasError()const;
                        RadonFramework::Core::Types::UInt64 MaximumCapacity()const;
                        ErrorCorrectionType::Type ErrorCorrectionType()const;
                        RadonFramework::Core::Types::String ErrorCorrectionTypeAsString()const;
                        Use::Type Use()const;
                        RadonFramework::Core::Types::String UseAsString()const;
                        Location::Type Location()const;
                        RadonFramework::Core::Types::String LocationAsString()const;
                    protected:
                        Location::Type m_Location;
                        Use::Type m_Use;
                        ErrorCorrectionType::Type m_ErrorCorrectionType;
                        RadonFramework::Core::Types::UInt64 m_MaximumCapacity;
                        RadonFramework::Core::Types::UInt16 m_NumberOfDevices;
                        RadonFramework::Core::Types::UInt16 m_ErrorInformationHandle;
                        RadonFramework::Core::Types::Bool m_HasError;
                        Collections::AutoVector<MemoryDevice> m_MemoryDevices;
                };
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_PHYSICALMEMORYARRAY_HPP