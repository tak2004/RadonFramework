#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/SystemSlotInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Profiling::SMBios;

#pragma pack(push,1)
struct SystemSlotsStructure
{
    StructureHeader Header;
    UInt8 SlotDesignation;//string
    UInt8 SlotType;
    UInt8 SlotDataBusWidth;
    UInt8 CurrentUsage;
    UInt8 SlotLength;
    UInt16 SlotID;
    UInt8 SlotCharacteristics1;
    UInt8 SlotCharacteristics2;
};
#pragma pack(pop)

SystemSlotInformation::SystemSlotInformation( Memory::AutoPointerArray<UInt8> Data, 
                                              Collections::AutoVector<String> StringList )
{
    SystemSlotsStructure* info=reinterpret_cast<SystemSlotsStructure*>(Data.Get());
    m_Designation=StringList[info->SlotDesignation-1]->TrimEnd(" ");
    m_Type=(SlotType::Type)info->SlotType;
    m_DataBusWidth=static_cast<SlotDataBusWidth::Type>(info->SlotDataBusWidth);
    m_CurrentUsage=static_cast<SlotCurrentUsage::Type>(info->CurrentUsage);
    m_Length=static_cast<SlotLength::Type>(info->SlotLength);
    m_Characteristisc=static_cast<SlotCharacteristics::Type>(*(reinterpret_cast<UInt16*>(&info->SlotCharacteristics1)));
}

const String& SystemSlotInformation::Designation()const
{
    return m_Designation;
}

SlotType::Type SystemSlotInformation::Type()const
{
    return m_Type;
}

String SystemSlotInformation::TypeAsString()const
{
    String str;
    switch (m_Type)
    {
        case SMBios::SlotType::VLVESA:str="VL VESA";break;
        case SMBios::SlotType::Unknown:str="Unknown";break;
        case SMBios::SlotType::ProprietaryMemoryCardSlot:str="Proprietary memory card slot";break;
        case SMBios::SlotType::Proprietary:str="Proprietary";break;
        case SMBios::SlotType::ProcessorCardSlot:str="Processor card slot";break;
        case SMBios::SlotType::PCIX:str="PCI-X";break;
        case SMBios::SlotType::PCIExpressX8:str="PCI-Express x8";break;
        case SMBios::SlotType::PCIExpressX4:str="PCI-Express x4";break;
        case SMBios::SlotType::PCIExpressX2:str="PCI-Express x2";break;
        case SMBios::SlotType::PCIExpressX16:str="PCI-Express x16";break;
        case SMBios::SlotType::PCIExpressX1:str="PCI-Express x1";break;
        case SMBios::SlotType::PCIExpressGeneration2X8:str="PCI-Express generation2 x8";break;
        case SMBios::SlotType::PCIExpressGeneration2X4:str="PCI-Express generation2 x4";break;
        case SMBios::SlotType::PCIExpressGeneration2X2:str="PCI-Express generation2 x2";break;
        case SMBios::SlotType::PCIExpressGeneration2X16:str="PCI-Express generation2 x16";break;
        case SMBios::SlotType::PCIExpressGeneration2X1:str="PCI-Express generation2 x1";break;
        case SMBios::SlotType::PCIExpressGeneration2:str="PCI-Express generation2";break;
        case SMBios::SlotType::PCIExpress:str="PCI-Express";break;
        case SMBios::SlotType::PCI66MHzCapable:str="PCI 66MHz capable";break;
        case SMBios::SlotType::PCI:str="PCI";break;
        case SMBios::SlotType::PCCard:str="PC card";break;
        case SMBios::SlotType::PC98LocalBus:str="PC-98 local bus";break;
        case SMBios::SlotType::PC98E:str="PC-98E";break;
        case SMBios::SlotType::PC98Card:str="PC-98 card";break;
        case SMBios::SlotType::PC98C24:str="PC-98 C24";break;
        case SMBios::SlotType::PC98C20:str="PC-98 C20";break;
        case SMBios::SlotType::Other:str="Other";break;
        case SMBios::SlotType::NuBus:str="Nu bus";break;
        case SMBios::SlotType::MCA:str="MCA";break;
        case SMBios::SlotType::ISA3:str="ISA 3";break;
        case SMBios::SlotType::IORiserCardSlot:str="IO riser card slot";break;
        case SMBios::SlotType::EISA:str="EISA";break;
        case SMBios::SlotType::AGP8x:str="AGP 8x";break;
        case SMBios::SlotType::AGP4x:str="AGP 4x";break;
        case SMBios::SlotType::AGP2x:str="AGP 2x";break;
        case SMBios::SlotType::AGP:str="AGP";break;
    }
    return str;
}

SlotDataBusWidth::Type SystemSlotInformation::DataBusWidth()const
{
    return m_DataBusWidth;
}

String SystemSlotInformation::DataBusWidthAsString()const
{
    String str;
    switch (m_DataBusWidth)
    {
        case SlotDataBusWidth::_8Bit:str="8Bit";break;
        case SlotDataBusWidth::_64Bit:str="64Bit";break;
        case SlotDataBusWidth::_32Bit:str="32Bit";break;
        case SlotDataBusWidth::_16Bit:str="16Bit";break;
        case SlotDataBusWidth::_128Bit:str="128Bit";break;
        case SlotDataBusWidth::x8:str="x8";break;
        case SlotDataBusWidth::x4:str="x4";break;
        case SlotDataBusWidth::x32:str="x32";break;
        case SlotDataBusWidth::x2:str="x2";break;
        case SlotDataBusWidth::x16:str="x16";break;
        case SlotDataBusWidth::x12:str="x12";break;
        case SlotDataBusWidth::x1:str="x1";break;
        case SlotDataBusWidth::Unknown:str="Unknown";break;
        case SlotDataBusWidth::Other:str="Other";break;
    }
    return str;
}

SlotCurrentUsage::Type SystemSlotInformation::CurrentUsage()const
{
    return m_CurrentUsage;
}

String SystemSlotInformation::CurrentUsageAsString()const
{
    String str;
    switch (m_CurrentUsage)
    {
        case SlotCurrentUsage::Unknown:str="Unknown";break;
        case SlotCurrentUsage::Other:str="Other";break;
        case SlotCurrentUsage::InUse:str="In use";break;
        case SlotCurrentUsage::Available:str="Available";break;
    }
    return str;
}

SlotLength::Type SystemSlotInformation::Length()const
{
    return m_Length;
}

String SystemSlotInformation::LengthAsString()const
{
    String str;
    switch (m_Length)
    {
        case SlotLength::Unknown:str="Unknown";break;
        case SlotLength::ShortLength:str="Short length";break;
        case SlotLength::Other:str="Other";break;
        case SlotLength::LongLength:str="Long length";break;
    }
    return str;
}

SlotCharacteristics::Type SystemSlotInformation::Characteristisc()const
{
    return m_Characteristisc;
}