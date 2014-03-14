#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMENCLOSURE_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMENCLOSURE_HPP
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
                namespace SystemEnclosureOrChassisType
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        Desktop=3,
                        LowProfileDesktop=4,
                        PizzaBox=5,
                        MiniTower=6,
                        Tower=7,
                        Portable=8,
                        Laptop=9,
                        Notebook=10,
                        HandHeld=11,
                        DockingStation=12,
                        AllInOne=13,
                        SubNotebook=14,
                        SpaceSaving=15,
                        LunchBox=16,
                        MainServerChassis=17,
                        ExpansionChassis=18,
                        SubChassis=19,
                        BusExpansionChassis=20,
                        PeripheralChassis=21,
                        RAIDChassis=22,
                        RackMountChassis=23,
                        SealedCasePC=24,
                        MultiSystemChassi=25,
                        CompactPCI=26,
                        AdvancedTCA=27
                    };
                }

                namespace SystemEnclosureOrChassisState
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        Safe=3,
                        Warning=4,
                        Critical=5,
                        NonRecoverable=6
                    };
                }

                namespace SystemEnclosureOrChassisSecurityStatus
                {
                    enum Type
                    {
                        Other=1,
                        Unknown=2,
                        None=3,
                        ExternalInterfaceLockedOut=4,
                        ExternalInterfaceEnabled=5
                    };
                }

                class SystemEnclosureInformation
                {
                    public:
                        SystemEnclosureInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                            Collections::AutoVector<Core::Types::String>& StringList);
                        Core::Types::String Manufacturer()const;
                        SystemEnclosureOrChassisType::Type Type()const;
                        Core::Types::String TypeAsString()const;
                        Core::Types::Bool IsChassisLockPresent()const;
                        Core::Types::String Version()const;
                        Core::Types::String SerialNumber()const;
                        Core::Types::String AssetTagNumber()const;
                        SystemEnclosureOrChassisState::Type BootUpSate()const;
                        Core::Types::String BootUpStateAsString()const;
                        SystemEnclosureOrChassisState::Type PowerSupplyState()const;
                        Core::Types::String PowerSupplyStateAsString()const;
                        SystemEnclosureOrChassisState::Type ThermalState()const;
                        Core::Types::String ThermalStateAsString()const;
                        SystemEnclosureOrChassisSecurityStatus::Type SecurityStatus()const;
                        Core::Types::String SecurityStatusAsString()const;
                        Core::Types::UInt32 OEMDefined()const;
                        /// In U=1.75inch or 4,445cm
                        Core::Types::UInt8 Height()const;
                        Core::Types::UInt8 NumberOfPowerCords()const;
                    protected:
                        RadonFramework::Core::Types::String m_Manufacturer;
                        SystemEnclosureOrChassisType::Type m_Type;
                        RadonFramework::Core::Types::Bool m_IsChassisLockPresent;
                        RadonFramework::Core::Types::String m_Version;
                        RadonFramework::Core::Types::String m_SerialNumber;
                        RadonFramework::Core::Types::String m_AssetTagNumber;
                        SystemEnclosureOrChassisState::Type m_BootUpState;
                        SystemEnclosureOrChassisState::Type m_PowerSupplyState;
                        SystemEnclosureOrChassisState::Type m_ThermalState;
                        SystemEnclosureOrChassisSecurityStatus::Type m_SecurityStatus;
                        RadonFramework::Core::Types::UInt32 m_OEMDefined;
                        RadonFramework::Core::Types::UInt8 m_Height;
                        RadonFramework::Core::Types::UInt8 m_NumberOfPowerCords;
                };
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMENCLOSURE_HPP