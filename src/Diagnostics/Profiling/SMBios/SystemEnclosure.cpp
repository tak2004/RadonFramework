#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/SystemEnclosure.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework::Diagnostics::Profiling::SMBios;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;

#pragma pack(push,1)
struct SystemEnclosureOrChassisContainedElementStructure
{
    RadonFramework::Core::Types::UInt8 ContainedElementType;
    RadonFramework::Core::Types::UInt8 ContainedElementMinimum;
    RadonFramework::Core::Types::UInt8 ContainedElementMaximum;
};

#ifdef RF_VISUALCPP
    #pragma warning(push)
    #pragma warning(disable:4200)//silence vc++ to warn about "array of size 0"
#endif
struct SystemEnclosureOrChassisStructure
{
    StructureHeader Header;
    RadonFramework::Core::Types::UInt8 Manufacturer;
    RadonFramework::Core::Types::UInt8 Type;
    RadonFramework::Core::Types::UInt8 Version;
    RadonFramework::Core::Types::UInt8 SerialNumber;
    RadonFramework::Core::Types::UInt8 AssetTagNumber;
    RadonFramework::Core::Types::UInt8 BootUpState;
    RadonFramework::Core::Types::UInt8 PowerSupplyState;
    RadonFramework::Core::Types::UInt8 ThermalState;
    RadonFramework::Core::Types::UInt8 SecurityStatus;
    RadonFramework::Core::Types::UInt32 OEMDefined;
    RadonFramework::Core::Types::UInt8 Height;
    RadonFramework::Core::Types::UInt8 NumberOfPowerCords;
    RadonFramework::Core::Types::UInt8 ContainedElementCount;
    RadonFramework::Core::Types::UInt8 ContainedElementRecordLength;
    SystemEnclosureOrChassisContainedElementStructure ContainedElements[];
    //BYTE ContainedElements[ContainedElementCount*ContainedElementRecordLength]
};
#ifdef RF_VISUALCPP
    #pragma warning(pop)
#endif
#pragma pack(pop)

SystemEnclosureInformation::SystemEnclosureInformation(AutoPointerArray<UInt8> Data,
                                                       AutoVector<String>& StringList )
{
    SystemEnclosureOrChassisStructure* info=(SystemEnclosureOrChassisStructure*)Data.Get();
    m_Manufacturer=StringList[info->Manufacturer-1]->TrimEnd(" ");
    m_Type=(SystemEnclosureOrChassisType::Type)(info->Type & 127);
    m_IsChassisLockPresent=(info->Type & 128)!=0;
    m_Version=StringList[info->Version-1]->TrimEnd(" ");
    m_SerialNumber=StringList[info->SerialNumber-1]->TrimEnd(" ");
    m_AssetTagNumber=StringList[info->AssetTagNumber-1]->TrimEnd(" ");
    m_BootUpState=(SystemEnclosureOrChassisState::Type)(info->BootUpState);
    m_PowerSupplyState=(SystemEnclosureOrChassisState::Type)(info->PowerSupplyState);
    m_ThermalState=(SystemEnclosureOrChassisState::Type)(info->ThermalState);
    m_SecurityStatus=(SystemEnclosureOrChassisSecurityStatus::Type)(info->SecurityStatus);
    m_OEMDefined=info->OEMDefined;
    m_Height=info->Height;
    m_NumberOfPowerCords=info->NumberOfPowerCords;
}

RadonFramework::Core::Types::String SystemEnclosureInformation::Manufacturer()const
{
    return m_Manufacturer;
}

SystemEnclosureOrChassisType::Type SystemEnclosureInformation::Type()const
{
    return m_Type;
}

RadonFramework::Core::Types::String SystemEnclosureInformation::TypeAsString()const
{
    RadonFramework::Core::Types::String str;
    switch (m_Type)
    {
        case SystemEnclosureOrChassisType::AdvancedTCA:
            str="Advanced TCA";
            break;
        case SystemEnclosureOrChassisType::AllInOne:
            str="All in one";
            break;
        case SystemEnclosureOrChassisType::BusExpansionChassis:
            str="Bus expansion chassis";
            break;
        case SystemEnclosureOrChassisType::CompactPCI:
            str="Compact PCI";
            break;
        case SystemEnclosureOrChassisType::Desktop:
            str="Desktop";
            break;
        case SystemEnclosureOrChassisType::DockingStation:
            str="Docking station";
            break;
        case SystemEnclosureOrChassisType::ExpansionChassis:
            str="Expansion chassis";
            break;
        case SystemEnclosureOrChassisType::HandHeld:
            str="Handheld";
            break;
        case SystemEnclosureOrChassisType::Laptop:
            str="Laptop";
            break;
        case SystemEnclosureOrChassisType::LowProfileDesktop:
            str="Low profile desktop";
            break;
        case SystemEnclosureOrChassisType::LunchBox:
            str="Lunch box";
            break;
        case SystemEnclosureOrChassisType::MainServerChassis:
            str="Main server chassis";
            break;
        case SystemEnclosureOrChassisType::MiniTower:
            str="Mini tower";
            break;
        case SystemEnclosureOrChassisType::MultiSystemChassi:
            str="Multi system chassi";
            break;
        case SystemEnclosureOrChassisType::Notebook:
            str="Notebook";
            break;
        case SystemEnclosureOrChassisType::Other:
            str="Other";
            break;
        case SystemEnclosureOrChassisType::PeripheralChassis:
            str="Peripheral chassis";
            break;
        case SystemEnclosureOrChassisType::PizzaBox:
            str="Pizza box";
            break;
        case SystemEnclosureOrChassisType::Portable:
            str="Portable";
            break;
        case SystemEnclosureOrChassisType::RackMountChassis:
            str="Rack mount chassis";
            break;
        case SystemEnclosureOrChassisType::RAIDChassis:
            str="RAID chassis";
            break;
        case SystemEnclosureOrChassisType::SealedCasePC:
            str="Sealed case PC";
            break;
        case SystemEnclosureOrChassisType::SpaceSaving:
            str="Space saving";
            break;
        case SystemEnclosureOrChassisType::SubChassis:
            str="Sub chassis";
            break;
        case SystemEnclosureOrChassisType::SubNotebook:
            str="Sub notebook";
            break;
        case SystemEnclosureOrChassisType::Tower:
            str="Tower";
            break;
        case SystemEnclosureOrChassisType::Unknown:
            str="Unknown";
            break;
    }
    return str;
}

RadonFramework::Core::Types::Bool SystemEnclosureInformation::IsChassisLockPresent()const
{
    return m_IsChassisLockPresent;
}

RadonFramework::Core::Types::String SystemEnclosureInformation::Version()const
{
    return m_Version;
}

RadonFramework::Core::Types::String SystemEnclosureInformation::SerialNumber()const
{
    return m_SerialNumber;
}

RadonFramework::Core::Types::String SystemEnclosureInformation::AssetTagNumber()const
{
    return m_AssetTagNumber;
}

SystemEnclosureOrChassisState::Type SystemEnclosureInformation::BootUpSate()const
{
    return m_BootUpState;
}

RadonFramework::Core::Types::String SystemEnclosureInformation::BootUpStateAsString()const
{
    RadonFramework::Core::Types::String str;
    switch (m_BootUpState)
    {
        case SystemEnclosureOrChassisState::Critical:
            str="Critical";
            break;
        case SystemEnclosureOrChassisState::NonRecoverable:
            str="Non recoverable";
            break;
        case SystemEnclosureOrChassisState::Other:
            str="Other";
            break;
        case SystemEnclosureOrChassisState::Safe:
            str="Safe";
            break;
        case SystemEnclosureOrChassisState::Unknown:
            str="Unknown";
            break;
        case SystemEnclosureOrChassisState::Warning:
            str="Warning";
            break;
    }
    return str;
}

SystemEnclosureOrChassisState::Type SystemEnclosureInformation::PowerSupplyState()const
{
    return m_PowerSupplyState;
}

RadonFramework::Core::Types::String SystemEnclosureInformation::PowerSupplyStateAsString()const
{
    RadonFramework::Core::Types::String str;
    switch (m_BootUpState)
    {
        case SystemEnclosureOrChassisState::Critical:
            str="Critical";
            break;
        case SystemEnclosureOrChassisState::NonRecoverable:
            str="Non recoverable";
            break;
        case SystemEnclosureOrChassisState::Other:
            str="Other";
            break;
        case SystemEnclosureOrChassisState::Safe:
            str="Safe";
            break;
        case SystemEnclosureOrChassisState::Unknown:
            str="Unknown";
            break;
        case SystemEnclosureOrChassisState::Warning:
            str="Warning";
            break;
    }
    return str;
}

SystemEnclosureOrChassisState::Type SystemEnclosureInformation::ThermalState()const
{
    return m_ThermalState;
}

RadonFramework::Core::Types::String SystemEnclosureInformation::ThermalStateAsString()const
{
    RadonFramework::Core::Types::String str;
    switch (m_BootUpState)
    {
        case SystemEnclosureOrChassisState::Critical:
            str="Critical";
            break;
        case SystemEnclosureOrChassisState::NonRecoverable:
            str="Non recoverable";
            break;
        case SystemEnclosureOrChassisState::Other:
            str="Other";
            break;
        case SystemEnclosureOrChassisState::Safe:
            str="Safe";
            break;
        case SystemEnclosureOrChassisState::Unknown:
            str="Unknown";
            break;
        case SystemEnclosureOrChassisState::Warning:
            str="Warning";
            break;
    }
    return str;
}

SystemEnclosureOrChassisSecurityStatus::Type SystemEnclosureInformation::SecurityStatus()const
{
    return m_SecurityStatus;
}

RadonFramework::Core::Types::String SystemEnclosureInformation::SecurityStatusAsString()const
{
    RadonFramework::Core::Types::String str;
    switch (m_SecurityStatus)
    {
        case SystemEnclosureOrChassisSecurityStatus::ExternalInterfaceEnabled:
            str="External interface enabled";
            break;
        case SystemEnclosureOrChassisSecurityStatus::ExternalInterfaceLockedOut:
            str="External interface locked out";
            break;
        case SystemEnclosureOrChassisSecurityStatus::None:
            str="None";
            break;
        case SystemEnclosureOrChassisSecurityStatus::Other:
            str="Other";
            break;
        case SystemEnclosureOrChassisSecurityStatus::Unknown:
            str="Unknown";
            break;
    }
    return str;
}

RadonFramework::Core::Types::UInt32 SystemEnclosureInformation::OEMDefined()const
{
    return m_OEMDefined;
}

RadonFramework::Core::Types::UInt8 SystemEnclosureInformation::Height()const
{
    return m_Height;
}

RadonFramework::Core::Types::UInt8 SystemEnclosureInformation::NumberOfPowerCords()const
{
    return m_NumberOfPowerCords;
}