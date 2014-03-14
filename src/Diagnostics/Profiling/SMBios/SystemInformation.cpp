#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Profiling/SMBios/SystemInformation.hpp"
#include "RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp"

using namespace RadonFramework::Diagnostics::Profiling::SMBios;
using namespace RadonFramework;

#pragma pack(push,1)
struct SystemInformationStructure
{
    StructureHeader Header;
    Core::Types::UInt8 Manufacturer;//string
    Core::Types::UInt8 ProductName;//string
    Core::Types::UInt8 Version;//string
    Core::Types::UInt8 SerialNumber;//string
    Core::Types::UInt8 UUID[16];
    Core::Types::UInt8 WakeupType;
    Core::Types::UInt8 SKUNumber;//string
    Core::Types::UInt8 Family;//string
};
#pragma pack(pop)

SystemInformation::SystemInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                                                                        Collections::AutoVector<Core::Types::String> StringList )
{
    SystemInformationStructure* sysinfo=(SystemInformationStructure*)Data.Get();
    m_Manufacturer=StringList[sysinfo->Manufacturer-1]->TrimEnd(" ");
    m_ProductName=StringList[sysinfo->ProductName-1]->TrimEnd(" ");
    m_Version=StringList[sysinfo->Version-1]->TrimEnd(" ");
    m_SerialNumber=StringList[sysinfo->SerialNumber-1]->TrimEnd(" ");
    m_UUID=UUID(new Core::Types::UInt8[16],16);
    RFMEM::Copy(m_UUID.Get(),sysinfo->UUID,16);
    m_WakeupType=(WakeupTypeField::Type)sysinfo->WakeupType;
    if(sysinfo->SKUNumber > 0)
        m_SKUNumber=StringList[sysinfo->SKUNumber-1]->TrimEnd(" ");
    if(sysinfo->Family > 0)
        m_Family=StringList[sysinfo->Family-1]->TrimEnd(" ");
}

Core::Types::String SystemInformation::Manufacturer()
{
    return m_Manufacturer;
}

Core::Types::String SystemInformation::ProductName()
{
    return m_ProductName;
}

Core::Types::String SystemInformation::Version()
{
    return m_Version;
}

Core::Types::String SystemInformation::SerialNumber()
{
    return m_SerialNumber;
}

SystemInformation::UUID SystemInformation::GetUUID()
{
    return m_UUID.Clone();
}

WakeupTypeField::Type SystemInformation::WakeupType()
{
    return m_WakeupType;
}

Core::Types::String SystemInformation::WakeupTypeAsString()
{
    Core::Types::String str;
    switch (m_WakeupType)
    {
        case WakeupTypeField::ACPowerRestored:
            str="AC power restored";
            break;
        case WakeupTypeField::APMTimer:
            str="APM timer";
            break;
        case WakeupTypeField::LANRemote:
            str="LAN remote";
            break;
        case WakeupTypeField::ModemRing:
            str="Modem ring";
            break;
        case WakeupTypeField::Other:
            str="Other";
            break;
        case WakeupTypeField::PCIPME:
            str="PCI power managment event";
            break;
        case WakeupTypeField::PowerSwitch:
            str="Power switch";
            break;
        case WakeupTypeField::Reserved:
            str="Reserved";
            break;
        case WakeupTypeField::Unknown:
            str="Unknown";
            break;
    }
    return str;
}

Core::Types::String SystemInformation::SKUNumber()
{
    return m_SKUNumber;
}

Core::Types::String SystemInformation::Family()
{
    return m_Family;
}
