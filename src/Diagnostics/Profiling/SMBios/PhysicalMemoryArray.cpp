#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/PhysicalMemoryArray.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Diagnostics::Profiling::SMBios;

#pragma pack(push,1)
//smbios 2.1
struct PhysicalMemoryArrayStructure
{
    StructureHeader Header;
    RadonFramework::Core::Types::UInt8 Location;
    RadonFramework::Core::Types::UInt8 Use;
    RadonFramework::Core::Types::UInt8 MemoryErrorCorrection;
    RadonFramework::Core::Types::UInt32 MaximumCapacity;
    RadonFramework::Core::Types::UInt16 MemoryErrorInformationHandle;
    RadonFramework::Core::Types::UInt16 NumberOfMemoryDevices;
};

//smbios 2.7
struct PhysicalMemoryArray2_7Structure
{
    PhysicalMemoryArrayStructure PhysicalMemoryArray2_1;
    RadonFramework::Core::Types::UInt64 ExtendedMaximumCapacity;
};
#pragma pack(pop)

PhysicalMemoryArray::PhysicalMemoryArray(Memory::AutoPointerArray<Core::Types::UInt8> Data,
                                         Collections::AutoVector<Core::Types::String> StringList,
                                         Collections::AutoVector<Information> MemoryDevices )
{
    PhysicalMemoryArrayStructure* info=(PhysicalMemoryArrayStructure*)Data.Get();
    m_Location=(Location::Type)info->Location;
    m_Use=(Use::Type)info->Use;
    m_ErrorCorrectionType=(ErrorCorrectionType::Type)info->MemoryErrorCorrection;
    if(info->MaximumCapacity==0x80000000)
        m_MaximumCapacity=((PhysicalMemoryArray2_7Structure*)info)->ExtendedMaximumCapacity;
    else
        m_MaximumCapacity=info->MaximumCapacity;
    if (info->MemoryErrorInformationHandle==0xfffe ||
        info->MemoryErrorInformationHandle==0xffff)
        m_ErrorInformationHandle=0;
    else
        m_ErrorInformationHandle=info->MemoryErrorInformationHandle;
    m_HasError=m_ErrorInformationHandle!=0?true:false;
    m_NumberOfDevices=info->NumberOfMemoryDevices;

    for (Collections::AutoVector<Information>::Iterator it=MemoryDevices.Begin();it!=MemoryDevices.End();++it)
    {
        if ((*it)->Type==HeaderType::MemoryDevice)
        {
            Memory::AutoPointer<MemoryDevice> memory(new MemoryDevice((*it)->Data,(*it)->StringList));
            if (memory->PhysicalMemoryArrayHandle()==info->Header.Handle)
            {
                m_MemoryDevices.PushBack(memory);
            }
        }
    }
}

const MemoryDevice& PhysicalMemoryArray::Device(const RadonFramework::Core::Types::UInt32 Index)const
{
    return *m_MemoryDevices[Index];
}

RadonFramework::Core::Types::UInt32 PhysicalMemoryArray::DeviceCount()const
{
    return m_MemoryDevices.Size();
}

RadonFramework::Core::Types::Bool PhysicalMemoryArray::HasError()const
{
    return m_HasError;
}

RadonFramework::Core::Types::UInt64 PhysicalMemoryArray::MaximumCapacity()const
{
    return m_MaximumCapacity;
}

ErrorCorrectionType::Type PhysicalMemoryArray::ErrorCorrectionType()const
{
    return m_ErrorCorrectionType;
}

RadonFramework::Core::Types::String PhysicalMemoryArray::ErrorCorrectionTypeAsString()const
{
    RadonFramework::Core::Types::String str;
    switch (m_ErrorCorrectionType)
    {
        case ErrorCorrectionType::Unknown:str="Unknown";break;
        case ErrorCorrectionType::SingleBitECC:str="Single Bit ECC";break;
        case ErrorCorrectionType::Parity:str="Parity";break;
        case ErrorCorrectionType::Other:str="Other";break;
        case ErrorCorrectionType::None:str="None";break;
        case ErrorCorrectionType::MultiBitECC:str="Multi Bit ECC";break;
        case ErrorCorrectionType::CRC:str="CRC";break;
    }
    return str;
}

Use::Type PhysicalMemoryArray::Use()const
{
    return m_Use;
}

RadonFramework::Core::Types::String PhysicalMemoryArray::UseAsString()const
{
    RadonFramework::Core::Types::String str;
    switch (m_Use)
    {
        case Use::VideoMemory:str="Video Memory";break;
        case Use::Unknown:str="Unknown";break;
        case Use::SystemMemory:str="System Memory";break;
        case Use::Other:str="Other";break;
        case Use::NonVolatileRAM:str="Non volatile RAM";break;
        case Use::FlashMemory:str="Flash Memory";break;
        case Use::CacheMemory:str="Cache Memory";break;
    }
    return str;
}

Location::Type PhysicalMemoryArray::Location()const
{
    return m_Location;
}

RadonFramework::Core::Types::String PhysicalMemoryArray::LocationAsString()const
{
    RadonFramework::Core::Types::String str;
    switch (m_Location)
    {
        case Location::Unknown:str="Unkown";break;
        case Location::SystemBoardOrMotherboard:str="System board or motherboard";break;
        case Location::ProprietaryAddonCard:str="Proprietary addon card";break;
        case Location::PCMCIAAddonCard:str="PCMCIA addon card";break;
        case Location::PCIAddonCard:str="PCI addon card";break;
        case Location::PC98LocalBusAddonCard:str="PC-98 local bus addon card";break;
        case Location::PC98EAddonCard:str="PC-98 addon card";break;
        case Location::PC98C24AddonCard:str="PC-98 C24 addon card";break;
        case Location::PC98C20AddonCard:str="PC-98 C20 addon card";break;
        case Location::Other:str="Other";break;
        case Location::NuBus:str="NuBus";break;
        case Location::MCAAddonCard:str="MCA addon card";break;
        case Location::ISAAddOnCard:str="ISA addon card";break;
        case Location::EISAAddonCard:str="EISA addon card";break;
    }
    return str;
}