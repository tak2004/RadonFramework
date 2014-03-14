#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_MEMORYDEVICE_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_MEMORYDEVICE_HPP
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
                namespace FormFactorField
                {
                    enum Type
                    {
                        Other=1,
                        Unknown,
                        SIMM,
                        SIP,
                        Chip,
                        DIP,
                        ZIP,
                        ProprietaryCard,
                        DIMM,
                        TSOP,
                        RowOfChips,
                        RIMM,
                        SODIMM,
                        SRIMM,
                        FBDIMM
                    };
                }

                namespace MemoryDeviceType
                {
                    enum Type
                    {
                        Other=1,
                        Unknown,
                        DRAM,
                        EDRAM,
                        VRAM,
                        SRAM,
                        RAM,
                        ROM,
                        FLASH,
                        EEPROM,
                        FEPROM,
                        EPROM,
                        CDRAM,
                        _3DRAM,
                        SDRAM,
                        SGRAM,
                        RDRAM,
                        DDR,
                        DDR2,
                        DDR2FBDIMM,
                        DDR3=0x18,
                        FBD2
                    };
                }

                namespace MemoryDeviceTypeDetailField
                {
                    enum Type
                    {
                        Other=2,
                        Unknown=4,
                        FastPage=8,
                        StaticColumn=0x10,
                        PseudoStatic=0x20,
                        RAMBUS=0x40,
                        Synchronous=0x80,
                        CMOS=0x100,
                        EDO=0x200,
                        WindowDRAM=0x400,
                        CacheDRAM=0x800,
                        NonVolatile=0x1000,
                        Registered=0x2000,
                        Unregistered=0x4000
                    };
                }

                class MemoryDevice
                {
                    public:
                        MemoryDevice(Memory::AutoPointerArray<Core::Types::UInt8> Data,
                            Collections::AutoVector<Core::Types::String> StringList);
                        RadonFramework::Core::Types::UInt16 PhysicalMemoryArrayHandle()const;
                        RadonFramework::Core::Types::UInt32 TotalBandwidth()const;
                        RadonFramework::Core::Types::UInt32 DataBandwidth()const;
                        RadonFramework::Core::Types::UInt32 Size()const;
                        RadonFramework::Core::Types::UInt32 DeviceSet()const;
                        RadonFramework::Core::Types::String DeviceLocator()const;
                        RadonFramework::Core::Types::String BankLocator()const;
                        FormFactorField::Type FormFactor()const;
                        RadonFramework::Core::Types::String FormFactorAsString()const;
                        MemoryDeviceType::Type Type()const;
                        RadonFramework::Core::Types::String TypeAsString()const;
                        MemoryDeviceTypeDetailField::Type  TypeDetail()const;
                    protected:
                        RadonFramework::Core::Types::UInt16 m_PhysicalMemoryArrayHandle;
                        RadonFramework::Core::Types::UInt32 m_TotalBandwidth;
                        RadonFramework::Core::Types::UInt32 m_DataBandwidth;
                        RadonFramework::Core::Types::UInt32 m_Size;
                        FormFactorField::Type m_FormFactor;
                        RadonFramework::Core::Types::UInt32 m_DeviceSet;
                        RadonFramework::Core::Types::String m_DeviceLocator;
                        RadonFramework::Core::Types::String m_BankLocator;
                        MemoryDeviceType::Type m_Type;
                        MemoryDeviceTypeDetailField::Type m_TypeDetail;
                };
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_MEMORYDEVICE_HPP