#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMINFORMATION_HPP
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
                namespace WakeupTypeField
                {
                    enum Type
                    {
                        Reserved=0,
                        Other=1,
                        Unknown=2,
                        APMTimer=3,
                        ModemRing=4,
                        LANRemote=5,
                        PowerSwitch=6,
                        PCIPME=7,
                        ACPowerRestored=8
                    };
                }

                class SystemInformation
                {
                    public:
                        typedef RadonFramework::Memory::AutoPointerArray<RadonFramework::Core::Types::UInt8> UUID;
                        SystemInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                            Collections::AutoVector<Core::Types::String> StringList);
                        Core::Types::String Manufacturer();
                        Core::Types::String ProductName();
                        Core::Types::String Version();
                        Core::Types::String SerialNumber();
                        UUID GetUUID();
                        WakeupTypeField::Type WakeupType();
                        Core::Types::String WakeupTypeAsString();
                        Core::Types::String SKUNumber();
                        Core::Types::String Family();
                    protected:
                        Core::Types::String m_Manufacturer;
                        Core::Types::String m_ProductName;
                        Core::Types::String m_Version;
                        Core::Types::String m_SerialNumber;
                        UUID m_UUID;
                        WakeupTypeField::Type m_WakeupType;
                        Core::Types::String m_SKUNumber;
                        Core::Types::String m_Family;
                };
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMINFORMATION_HPP