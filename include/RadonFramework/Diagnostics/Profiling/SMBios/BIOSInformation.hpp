#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_BIOSINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_BIOSINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace SMBios
            {
                namespace BIOSCharacteristics
                {
                    enum Type
                    {
                        BIOSCharacteristicsAreNotSupported,
                        ISA,
                        MCA,
                        EISA,
                        PCI,
                        PCMCIA,
                        PlugAndPlay,
                        APM,
                        BIOSIsUpgradeable,
                        BIOSShadowing,
                        VL_VESA,
                        ESCD,
                        BootFromCD,
                        SelectableBoot,
                        BIOSROM,
                        BootFromPCMCIA,
                        EDDSpecification,
                        JapaneseFloppyForNEC9800,
                        JapaneseFloppyForToshiba,
                        FloppyServicesFor5Point25Inch_360KB,
                        FloppyServicesFor5Point25Inch_1Point2MB,
                        FloppyServicesFor3Point5Inch_720KB,
                        FloppyServicesFor3Point5Inch_2Point88MB,
                        PrintScreenService,
                        KeyboardServicesFor8042,
                        SerialServices,
                        PrinterServices,
                        CGA_MonoVideoServices,
                        NECPC_98,
                        ACPI,
                        USBLegacy,
                        AGP,
                        I2OBoot,
                        LS120SuperDiskBoot,
                        ATAPIZipDriveBoot,
                        IEEE1394,
                        SmartBattery,
                        BIOSBootSpecification,
                        KeyInitiatedNetworkServiceBoot,
                        EnableTargetedContentDistribution,
                        UEFISpecification,
                        TheSMBIOSTableDescribesAVirtualMachine,
                        MAX
                    };
                }

                class BIOSInformation
                {
                    public:
                        BIOSInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                            Collections::AutoVector<Core::Types::String> StringList);
                        const RadonFramework::Core::Types::String& Vendor()const;
                        const RadonFramework::Core::Types::String& Version()const;
                        const RadonFramework::Core::Types::UInt16 Address()const;
                        const RadonFramework::Core::Types::String& ReleaseDate()const;
                        const RadonFramework::Core::Types::UInt32 ROMSize()const;
                        const RadonFramework::Core::Types::Bool Characteristiscs(BIOSCharacteristics::Type Value)const;
                        const RadonFramework::Core::Types::UInt8 MajorRevision()const;
                        const RadonFramework::Core::Types::UInt8 MinorRevision()const;
                        const RadonFramework::Core::Types::UInt8 EmbeddedControllerFirmwareMajorRevision()const;
                        const RadonFramework::Core::Types::UInt8 EmbeddedControllerFirmwareMinorRevision()const;
                    protected:
                        RadonFramework::Core::Types::String m_Vendor;
                        RadonFramework::Core::Types::String m_Version;
                        RadonFramework::Core::Types::UInt16 m_Address;
                        RadonFramework::Core::Types::String m_ReleaseDate;
                        RadonFramework::Core::Types::UInt32 m_ROMSize;
                        RadonFramework::Core::Types::Bool m_Characteristics[BIOSCharacteristics::MAX];
                        RadonFramework::Core::Types::UInt8 m_MajorRevision;
                        RadonFramework::Core::Types::UInt8 m_MinorRevision;
                        RadonFramework::Core::Types::UInt8 m_EmbeddedControllerFirmwareMajorRevision;
                        RadonFramework::Core::Types::UInt8 m_EmbeddedControllerFirmwareMinorRevision;
                };

                inline const RadonFramework::Core::Types::String& BIOSInformation::Vendor()const{
                    return m_Vendor;
                }
                inline const RadonFramework::Core::Types::String& BIOSInformation::Version()const{
                    return m_Version;
                }
                inline const RadonFramework::Core::Types::UInt16 BIOSInformation::Address()const{
                    return m_Address;
                }
                inline const RadonFramework::Core::Types::String& BIOSInformation::ReleaseDate()const{
                    return m_ReleaseDate;
                }
                inline const RadonFramework::Core::Types::UInt32 BIOSInformation::ROMSize()const{
                    return m_ROMSize;
                }
                inline const RadonFramework::Core::Types::Bool BIOSInformation::Characteristiscs(BIOSCharacteristics::Type Value)const{
                    return m_Characteristics[Value];
                }
                inline const RadonFramework::Core::Types::UInt8 BIOSInformation::MajorRevision()const{
                    return m_MajorRevision;
                }
                inline const RadonFramework::Core::Types::UInt8 BIOSInformation::MinorRevision()const{
                    return m_MinorRevision;
                }
                inline const RadonFramework::Core::Types::UInt8 BIOSInformation::EmbeddedControllerFirmwareMajorRevision()const{
                    return m_EmbeddedControllerFirmwareMajorRevision;
                }
                inline const RadonFramework::Core::Types::UInt8 BIOSInformation::EmbeddedControllerFirmwareMinorRevision()const{
                    return m_EmbeddedControllerFirmwareMinorRevision;
                }
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_BIOSINFORMATION_HPP