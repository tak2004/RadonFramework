#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/BIOSInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework::Diagnostics::Profiling::SMBios;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;

//SMBIOS 2.4 and later
#pragma pack(push,1)
struct BiosInformation
{
	StructureHeader Header;
	RadonFramework::Core::Types::UInt8 Vendor;//string
	RadonFramework::Core::Types::UInt8 BIOSVersion;//string
	RadonFramework::Core::Types::UInt16 BIOSStartingAddressSegment;
	RadonFramework::Core::Types::UInt8 BIOSReleaseDate;//string
	RadonFramework::Core::Types::UInt8 BIOSROMSize;
	RadonFramework::Core::Types::UInt32 BIOSCharacteristics;
	RadonFramework::Core::Types::UInt16 BIOSCharacteristicsExtensionBytes;
	RadonFramework::Core::Types::UInt8 SystemBIOSMajorRelease;
	RadonFramework::Core::Types::UInt8 SystemBIOSMinorRelease;
	RadonFramework::Core::Types::UInt8 EmbeddedControllerFirmwareMajorRelease;
	RadonFramework::Core::Types::UInt8 EmbeddedControllerFirmwareMinorRelease;
};
#pragma pack(pop)

BIOSInformation::BIOSInformation(AutoPointerArray<UInt8> Data,
								 AutoVector<String> StringList )
{
	BiosInformation* biosinfo=(BiosInformation*)Data.Get();
	m_Vendor=StringList[biosinfo->Vendor-1]->TrimEnd(" ");
	m_Version=StringList[biosinfo->BIOSVersion-1]->TrimEnd(" ");
	m_Address=biosinfo->BIOSStartingAddressSegment;
	m_ReleaseDate=StringList[biosinfo->BIOSReleaseDate-1]->TrimEnd(" ");
	m_ROMSize=(biosinfo->BIOSROMSize+1)*65536;
	m_MajorRevision=biosinfo->SystemBIOSMajorRelease;
	m_MinorRevision=biosinfo->SystemBIOSMinorRelease;
	m_EmbeddedControllerFirmwareMajorRevision=biosinfo->EmbeddedControllerFirmwareMajorRelease;
	m_EmbeddedControllerFirmwareMinorRevision=biosinfo->EmbeddedControllerFirmwareMinorRelease;

	m_Characteristics[BIOSCharacteristics::BIOSCharacteristicsAreNotSupported]=(biosinfo->BIOSCharacteristics & 0x8)!=0;
	m_Characteristics[BIOSCharacteristics::ISA]=(biosinfo->BIOSCharacteristics & 0x10)!=0;
	m_Characteristics[BIOSCharacteristics::MCA]=(biosinfo->BIOSCharacteristics & 0x20)!=0;
	m_Characteristics[BIOSCharacteristics::EISA]=(biosinfo->BIOSCharacteristics & 0x40)!=0;
	m_Characteristics[BIOSCharacteristics::PCI]=(biosinfo->BIOSCharacteristics & 0x80)!=0;
	m_Characteristics[BIOSCharacteristics::PCMCIA]=(biosinfo->BIOSCharacteristics & 0x100)!=0;
	m_Characteristics[BIOSCharacteristics::PlugAndPlay]=(biosinfo->BIOSCharacteristics & 0x200)!=0;
	m_Characteristics[BIOSCharacteristics::APM]=(biosinfo->BIOSCharacteristics & 0x400)!=0;
	m_Characteristics[BIOSCharacteristics::BIOSIsUpgradeable]=(biosinfo->BIOSCharacteristics & 0x800)!=0;
	m_Characteristics[BIOSCharacteristics::BIOSShadowing]=(biosinfo->BIOSCharacteristics & 0x1000)!=0;
	m_Characteristics[BIOSCharacteristics::VL_VESA]=(biosinfo->BIOSCharacteristics & 0x2000)!=0;
	m_Characteristics[BIOSCharacteristics::ESCD]=(biosinfo->BIOSCharacteristics & 0x4000)!=0;
	m_Characteristics[BIOSCharacteristics::BootFromCD]=(biosinfo->BIOSCharacteristics & 0x8000)!=0;
	m_Characteristics[BIOSCharacteristics::SelectableBoot]=(biosinfo->BIOSCharacteristics & 0x10000)!=0;
	m_Characteristics[BIOSCharacteristics::BIOSROM]=(biosinfo->BIOSCharacteristics & 0x20000)!=0;
	m_Characteristics[BIOSCharacteristics::BootFromPCMCIA]=(biosinfo->BIOSCharacteristics & 0x40000)!=0;
	m_Characteristics[BIOSCharacteristics::EDDSpecification]=(biosinfo->BIOSCharacteristics & 0x80000)!=0;
	m_Characteristics[BIOSCharacteristics::JapaneseFloppyForNEC9800]=(biosinfo->BIOSCharacteristics & 0x100000)!=0;
	m_Characteristics[BIOSCharacteristics::JapaneseFloppyForToshiba]=(biosinfo->BIOSCharacteristics & 0x200000)!=0;
	m_Characteristics[BIOSCharacteristics::FloppyServicesFor5Point25Inch_360KB]=(biosinfo->BIOSCharacteristics & 0x400000)!=0;
	m_Characteristics[BIOSCharacteristics::FloppyServicesFor5Point25Inch_1Point2MB]=(biosinfo->BIOSCharacteristics & 0x800000)!=0;
	m_Characteristics[BIOSCharacteristics::FloppyServicesFor3Point5Inch_720KB]=(biosinfo->BIOSCharacteristics & 0x1000000)!=0;
	m_Characteristics[BIOSCharacteristics::FloppyServicesFor3Point5Inch_2Point88MB]=(biosinfo->BIOSCharacteristics & 0x2000000)!=0;
	m_Characteristics[BIOSCharacteristics::PrintScreenService]=(biosinfo->BIOSCharacteristics & 0x4000000)!=0;
	m_Characteristics[BIOSCharacteristics::KeyboardServicesFor8042]=(biosinfo->BIOSCharacteristics & 0x8000000)!=0;
	m_Characteristics[BIOSCharacteristics::SerialServices]=(biosinfo->BIOSCharacteristics & 0x10000000)!=0;
	m_Characteristics[BIOSCharacteristics::PrinterServices]=(biosinfo->BIOSCharacteristics & 0x20000000)!=0;
	m_Characteristics[BIOSCharacteristics::CGA_MonoVideoServices]=(biosinfo->BIOSCharacteristics & 0x40000000)!=0;
	m_Characteristics[BIOSCharacteristics::NECPC_98]=(biosinfo->BIOSCharacteristics & 0x80000000)!=0;
	m_Characteristics[BIOSCharacteristics::ACPI]=(biosinfo->BIOSCharacteristicsExtensionBytes & 0x01)!=0;
	m_Characteristics[BIOSCharacteristics::USBLegacy]=(biosinfo->BIOSCharacteristicsExtensionBytes & 0x02)!=0;
	m_Characteristics[BIOSCharacteristics::AGP]=(biosinfo->BIOSCharacteristicsExtensionBytes & 0x04)!=0;
	m_Characteristics[BIOSCharacteristics::I2OBoot]=(biosinfo->BIOSCharacteristicsExtensionBytes & 0x08)!=0;
	m_Characteristics[BIOSCharacteristics::LS120SuperDiskBoot]=(biosinfo->BIOSCharacteristicsExtensionBytes & 0x10)!=0;
	m_Characteristics[BIOSCharacteristics::ATAPIZipDriveBoot]=(biosinfo->BIOSCharacteristicsExtensionBytes & 0x20)!=0;
	m_Characteristics[BIOSCharacteristics::IEEE1394]=(biosinfo->BIOSCharacteristicsExtensionBytes & 0x40)!=0;
	m_Characteristics[BIOSCharacteristics::SmartBattery]=(biosinfo->BIOSCharacteristicsExtensionBytes & 0x80)!=0;
	m_Characteristics[BIOSCharacteristics::BIOSBootSpecification]=(biosinfo->BIOSCharacteristicsExtensionBytes & 0x100)!=0;
	m_Characteristics[BIOSCharacteristics::KeyInitiatedNetworkServiceBoot]=(biosinfo->BIOSCharacteristicsExtensionBytes & 0x200)!=0;
	m_Characteristics[BIOSCharacteristics::EnableTargetedContentDistribution]=(biosinfo->BIOSCharacteristicsExtensionBytes & 0x400)!=0;
	m_Characteristics[BIOSCharacteristics::UEFISpecification]=(biosinfo->BIOSCharacteristicsExtensionBytes & 0x800)!=0;
	m_Characteristics[BIOSCharacteristics::TheSMBIOSTableDescribesAVirtualMachine]=(biosinfo->BIOSCharacteristicsExtensionBytes & 0x1000)!=0;
}
