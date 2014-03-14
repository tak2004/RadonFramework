#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/MemoryDevice.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Diagnostics::Profiling::SMBios;

#pragma pack(push,1)
//smbios 2.1
struct MemoryDevice2_1Structure
{
	StructureHeader Header;
	RadonFramework::Core::Types::UInt16 PhysicalMemoryArrayHandle;
	RadonFramework::Core::Types::UInt16 MemoryErrorInformationHandle;
	RadonFramework::Core::Types::UInt16 TotalWidth;
	RadonFramework::Core::Types::UInt16 DataWidth;
	RadonFramework::Core::Types::UInt16 Size;
	RadonFramework::Core::Types::UInt8 FormFactor;
	RadonFramework::Core::Types::UInt8 DeviceSet;
	RadonFramework::Core::Types::UInt8 DeviceLocator;
	RadonFramework::Core::Types::UInt8 BankLocator;
	RadonFramework::Core::Types::UInt8 MemoryType;
	RadonFramework::Core::Types::UInt16 TypeDetail;
};

//smbios 2.3
struct MemoryDevice2_3Structure
{
	StructureHeader Header;
	RadonFramework::Core::Types::UInt16 PhysicalMemoryArrayHandle;
	RadonFramework::Core::Types::UInt16 MemoryErrorInformationHandle;
	RadonFramework::Core::Types::UInt16 TotalWidth;
	RadonFramework::Core::Types::UInt16 DataWidth;
	RadonFramework::Core::Types::UInt16 Size;
	RadonFramework::Core::Types::UInt8 FormFactor;
	RadonFramework::Core::Types::UInt8 DeviceSet;
	RadonFramework::Core::Types::UInt8 DeviceLocator;
	RadonFramework::Core::Types::UInt8 BankLocator;
	RadonFramework::Core::Types::UInt8 MemoryType;
	RadonFramework::Core::Types::UInt16 TypeDetail;

	RadonFramework::Core::Types::UInt16 Speed;
	RadonFramework::Core::Types::UInt8 Manufacturer;
	RadonFramework::Core::Types::UInt8 SerialNumber;
	RadonFramework::Core::Types::UInt8 AssetTag;
	RadonFramework::Core::Types::UInt8 PartNumber;
};

//smbios 2.6
struct MemoryDevice2_6Structure
{
	StructureHeader Header;
	RadonFramework::Core::Types::UInt16 PhysicalMemoryArrayHandle;
	RadonFramework::Core::Types::UInt16 MemoryErrorInformationHandle;
	RadonFramework::Core::Types::UInt16 TotalWidth;
	RadonFramework::Core::Types::UInt16 DataWidth;
	RadonFramework::Core::Types::UInt16 Size;
	RadonFramework::Core::Types::UInt8 FormFactor;
	RadonFramework::Core::Types::UInt8 DeviceSet;
	RadonFramework::Core::Types::UInt8 DeviceLocator;
	RadonFramework::Core::Types::UInt8 BankLocator;
	RadonFramework::Core::Types::UInt8 MemoryType;
	RadonFramework::Core::Types::UInt16 TypeDetail;

	RadonFramework::Core::Types::UInt16 Speed;
	RadonFramework::Core::Types::UInt8 Manufacturer;
	RadonFramework::Core::Types::UInt8 SerialNumber;
	RadonFramework::Core::Types::UInt8 AssetTag;
	RadonFramework::Core::Types::UInt8 PartNumber;

	RadonFramework::Core::Types::UInt8 Attributes;
};

//smbios 2.7
struct MemoryDevice2_7Structure
{
	StructureHeader Header;
	RadonFramework::Core::Types::UInt16 PhysicalMemoryArrayHandle;
	RadonFramework::Core::Types::UInt16 MemoryErrorInformationHandle;
	RadonFramework::Core::Types::UInt16 TotalWidth;
	RadonFramework::Core::Types::UInt16 DataWidth;
	RadonFramework::Core::Types::UInt16 Size;
	RadonFramework::Core::Types::UInt8 FormFactor;
	RadonFramework::Core::Types::UInt8 DeviceSet;
	RadonFramework::Core::Types::UInt8 DeviceLocator;
	RadonFramework::Core::Types::UInt8 BankLocator;
	RadonFramework::Core::Types::UInt8 MemoryType;
	RadonFramework::Core::Types::UInt16 TypeDetail;

	RadonFramework::Core::Types::UInt16 Speed;
	RadonFramework::Core::Types::UInt8 Manufacturer;
	RadonFramework::Core::Types::UInt8 SerialNumber;
	RadonFramework::Core::Types::UInt8 AssetTag;
	RadonFramework::Core::Types::UInt8 PartNumber;

	RadonFramework::Core::Types::UInt8 Attributes;

	RadonFramework::Core::Types::UInt32 ExtendedSize;
	RadonFramework::Core::Types::UInt16 ConfiguredMemoryClockSpeed;
};
#pragma pack(pop)

MemoryDevice::MemoryDevice(Memory::AutoPointerArray<Core::Types::UInt8> Data,
						   Collections::AutoVector<Core::Types::String> StringList)
{
	MemoryDevice2_1Structure *info=(MemoryDevice2_1Structure*)Data.Get();
	m_PhysicalMemoryArrayHandle=info->PhysicalMemoryArrayHandle;
	m_TotalBandwidth=info->TotalWidth;
	m_DataBandwidth=info->DataWidth;
	//memory size
	if ((info->Size & 0x8000)!=0)
	{
		if (info->Size==0xffff)
			m_Size=0;
		else
			m_Size=info->Size;
	}
	else
	{
		if(info->Size==0x7fff)//smbios 2.7
			m_Size=((MemoryDevice2_7Structure*)info)->ExtendedSize*1024;
		else
			m_Size=info->Size*1024;
	}
	m_FormFactor=(FormFactorField::Type)info->FormFactor;
	m_DeviceSet=info->DeviceSet;
	m_DeviceLocator=StringList[info->DeviceLocator-1]->TrimEnd(" ");
	m_BankLocator=StringList[info->BankLocator-1]->TrimEnd(" ");
	m_Type=(MemoryDeviceType::Type)info->MemoryType;
	m_TypeDetail=(MemoryDeviceTypeDetailField::Type)info->TypeDetail;
}

RadonFramework::Core::Types::UInt16 MemoryDevice::PhysicalMemoryArrayHandle()const
{
	return m_PhysicalMemoryArrayHandle;
}

RadonFramework::Core::Types::UInt32 MemoryDevice::TotalBandwidth()const
{
    return m_TotalBandwidth;
}

RadonFramework::Core::Types::UInt32 MemoryDevice::DataBandwidth()const
{
    return m_DataBandwidth;
}

RadonFramework::Core::Types::UInt32 MemoryDevice::Size()const
{
    return m_Size;
}

RadonFramework::Core::Types::UInt32 MemoryDevice::DeviceSet()const
{
    return m_DeviceSet;
}

RadonFramework::Core::Types::String MemoryDevice::DeviceLocator()const
{
    return m_DeviceLocator;
}

RadonFramework::Core::Types::String MemoryDevice::BankLocator()const
{
    return m_BankLocator;
}

FormFactorField::Type MemoryDevice::FormFactor()const
{
    return m_FormFactor;
}

RadonFramework::Core::Types::String MemoryDevice::FormFactorAsString()const
{
    Core::Types::String str;
    switch (m_FormFactor)
    {
        case FormFactorField::ZIP:str="ZIP";break;
        case FormFactorField::Unknown:str="Unknown";break;
        case FormFactorField::TSOP:str="TSOP";break;
        case FormFactorField::SRIMM:str="SRIMM";break;
        case FormFactorField::SODIMM:str="SODIMM";break;
        case FormFactorField::SIP:str="SIP";break;
        case FormFactorField::SIMM:str="SIMM";break;
        case FormFactorField::RowOfChips:str="Row of chips";break;
        case FormFactorField::RIMM:str="RIMM";break;
        case FormFactorField::ProprietaryCard:str="Propritary card";break;
        case FormFactorField::Other:str="Other";break;
        case FormFactorField::FBDIMM:str="FBDIMM";break;
        case FormFactorField::DIP:str="DIP";break;
        case FormFactorField::DIMM:str="DIMM";break;
        case FormFactorField::Chip:str="Chip";break;
    }
    return str;
}

MemoryDeviceType::Type MemoryDevice::Type()const
{
    return m_Type;
}

RadonFramework::Core::Types::String MemoryDevice::TypeAsString()const
{
    Core::Types::String str;
    switch (m_Type)
    {
        case MemoryDeviceType::_3DRAM:str="3D RAM";break;
        case MemoryDeviceType::VRAM:str="VRAM";break;
        case MemoryDeviceType::Unknown:str="Unknown";break;
        case MemoryDeviceType::SRAM:str="SRAM";break;
        case MemoryDeviceType::SGRAM:str="SGRAM";break;
        case MemoryDeviceType::SDRAM:str="SDRAM";break;
        case MemoryDeviceType::RAM:str="RAM";break;
        case MemoryDeviceType::Other:str="Other";break;
        case MemoryDeviceType::FLASH:str="Flash";break;
        case MemoryDeviceType::FEPROM:str="FEPROM";break;
        case MemoryDeviceType::FBD2:str="FBD2";break;
        case MemoryDeviceType::EPROM:str="EPROM";break;
        case MemoryDeviceType::EEPROM:str="EEPROM";break;
        case MemoryDeviceType::EDRAM:str="EDRAM";break;
        case MemoryDeviceType::DRAM:str="DRAM";break;
        case MemoryDeviceType::DDR3:str="DDR3";break;
        case MemoryDeviceType::DDR2FBDIMM:str="DDR2 DBDIM";break;
        case MemoryDeviceType::DDR2:str="DDR2";break;
        case MemoryDeviceType::DDR:str="DDR";break;
        case MemoryDeviceType::CDRAM:str="CDRAM";break;
        case MemoryDeviceType::ROM:str="ROM";break;
        case MemoryDeviceType::RDRAM:str="RDRAM";break;
    }
    return str;
}

MemoryDeviceTypeDetailField::Type MemoryDevice::TypeDetail()const
{
    return m_TypeDetail;
}
