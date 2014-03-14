#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_BASEBOARDINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_BASEBOARDINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/Information.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/SystemEnclosure.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace SMBios
            {
                namespace FeatureFlagsField
                {
                    enum Type
                    {
                        IsHostingBoard=1,
                        RequiresAtLeastOneDaughterBoard=2,
                        IsRemoveable=4,
                        IsReplaceable=8,
                        IsHotSwappable=16
                        //5-7 reserved for future use
                    };
                }

                namespace BoardTypeField
                {
                    enum Type
                    {
                        Unknown=1,
                        Other=2,
                        ServerBlade=3,
                        ConnectivitySwitch=4,
                        SystemManagmentModule=5,
                        ProcessorModule=6,
                        IOModule=7,
                        MemoryModule=8,
                        DaughterBoard=9,
                        Motherboard=10,
                        ProcessorOrMemoryModule=11,
                        ProcessorOrIOModule=12,
                        InterconnectBoard=13
                    };
                }

                class BaseBoardInformation
                {
                    public:
                        BaseBoardInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                            Collections::AutoVector<Core::Types::String> StringList,
                            Collections::AutoVector<SMBios::Information> ContainedElements);
                        Core::Types::String Manufacturer()const;
                        Core::Types::String Product()const;
                        Core::Types::String Version()const;
                        Core::Types::String SerialNumber()const;
                        Core::Types::String AssetTag()const;
                        FeatureFlagsField::Type FeatureFlags()const;
                        Core::Types::String LocationInChassis()const;
                        BoardTypeField::Type BoardType()const;
                        Core::Types::String BoardTypeAsString()const;
                        const SystemEnclosureInformation& Chassi()const;
                        Core::Types::UInt32 ContainedObjectCount()const;
                        const SystemEnclosureInformation& ContainedObject(Core::Types::UInt32 Index)const;
                    protected:
                        RadonFramework::Core::Types::String m_Manufacturer;
                        RadonFramework::Core::Types::String m_Product;
                        RadonFramework::Core::Types::String m_Version;
                        RadonFramework::Core::Types::String m_SerialNumber;
                        RadonFramework::Core::Types::String m_AssetTag;
                        FeatureFlagsField::Type m_FeatureFlags;
                        RadonFramework::Core::Types::String m_LocationInChassis;
                        BoardTypeField::Type m_BoardType;
                        RadonFramework::Collections::AutoVector<SystemEnclosureInformation> m_ContainedObjects;
                        RadonFramework::Memory::AutoPointer<SystemEnclosureInformation> m_Chassi;
                };

                inline Core::Types::String BaseBoardInformation::Manufacturer()const{
                    return m_Manufacturer;
                }
                inline Core::Types::String BaseBoardInformation::Product()const{
                    return m_Product;
                }
                inline Core::Types::String BaseBoardInformation::Version()const{
                    return m_Version;
                }
                inline Core::Types::String BaseBoardInformation::SerialNumber()const{
                    return m_SerialNumber;
                }
                inline Core::Types::String BaseBoardInformation::AssetTag()const{
                    return m_AssetTag;
                }
                inline FeatureFlagsField::Type BaseBoardInformation::FeatureFlags()const{
                    return m_FeatureFlags;
                }
                inline Core::Types::String BaseBoardInformation::LocationInChassis()const{
                    return m_LocationInChassis;
                }
                inline BoardTypeField::Type BaseBoardInformation::BoardType()const{
                    return m_BoardType;
                }
                inline const SystemEnclosureInformation& BaseBoardInformation::Chassi()const{
                    Assert(m_Chassi.Get(),"Illegal usage of null pointer.");
                    return *m_Chassi.Get();
                }
                inline Core::Types::UInt32 BaseBoardInformation::ContainedObjectCount()const{
                    return m_ContainedObjects.Size();
                }
                inline const SystemEnclosureInformation& BaseBoardInformation::ContainedObject(Core::Types::UInt32 Index)const{
                    return *m_ContainedObjects[Index];
                }
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_BASEBOARDINFORMATION_HPP