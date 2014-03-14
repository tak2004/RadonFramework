#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMSLOTINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMSLOTINFORMATION_HPP
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
                namespace SlotType
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        ISA3,
                        MCA=4,
                        EISA=5,
                        PCI=6,
                        PCCard=7,
                        VLVESA=8,
                        Proprietary=9,
                        ProcessorCardSlot=10,
                        ProprietaryMemoryCardSlot=11,
                        IORiserCardSlot=12,
                        NuBus=13,
                        PCI66MHzCapable=14,
                        AGP=15,
                        AGP2x=16,
                        AGP4x=17,
                        PCIX=18,
                        AGP8x=19,
                        PC98C20=160,
                        PC98C24=161,
                        PC98E=162,
                        PC98LocalBus=163,
                        PC98Card=164,
                        PCIExpress=165,
                        PCIExpressX1=166,
                        PCIExpressX2=167,
                        PCIExpressX4=168,
                        PCIExpressX8=169,
                        PCIExpressX16=170,
                        PCIExpressGeneration2=171,
                        PCIExpressGeneration2X1=172,
                        PCIExpressGeneration2X2=173,
                        PCIExpressGeneration2X4=174,
                        PCIExpressGeneration2X8=175,
                        PCIExpressGeneration2X16=176
                    };
                }

                namespace SlotDataBusWidth
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        _8Bit=3,
                        _16Bit=4,
                        _32Bit=5,
                        _64Bit=6,
                        _128Bit=7,
                        x1=8,
                        x2=9,
                        x4=10,
                        x8=11,
                        x12=12,
                        x16=13,
                        x32=14
                    };
                }

                namespace SlotCurrentUsage
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        Available=3,
                        InUse=4
                    };
                }

                namespace SlotLength
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        ShortLength=3,
                        LongLength=4
                    };
                }

                namespace SlotCharacteristics
                {
                    enum Type
                    {
                        Unknown=1,
                        Provides5Volts=2,
                        Provides3_3Volts=4,
                        SharedSlot=8,
                        PC_Card16=0x10,
                        CardBus=0x20,
                        ZoomVideo=0x40,
                        ModemRingResume=0x80,
                        PowerManagmentEvent=0x100,
                        HotPlug=0x200,
                        SMBiosSignal=0x400,
                    };
                }

                class SystemSlotInformation
                {
                    public:
                        SystemSlotInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data,
                            Collections::AutoVector<Core::Types::String> StringList);
                        const RadonFramework::Core::Types::String& Designation()const;
                        SlotType::Type Type()const;
                        RadonFramework::Core::Types::String TypeAsString()const;
                        SlotDataBusWidth::Type DataBusWidth()const;
                        RadonFramework::Core::Types::String DataBusWidthAsString()const;
                        SlotCurrentUsage::Type CurrentUsage()const;
                        RadonFramework::Core::Types::String CurrentUsageAsString()const;
                        SlotLength::Type Length()const;
                        RadonFramework::Core::Types::String LengthAsString()const;
                        SlotCharacteristics::Type Characteristisc()const;
                    protected:
                        RadonFramework::Core::Types::String m_Designation;
                        SlotType::Type m_Type;
                        SlotDataBusWidth::Type m_DataBusWidth;
                        SlotCurrentUsage::Type m_CurrentUsage;
                        SlotLength::Type m_Length;
                        SlotCharacteristics::Type m_Characteristisc;
                };
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMSLOTINFORMATION_HPP