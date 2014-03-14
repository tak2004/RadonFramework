#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_ONBOARDDEVICESINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_ONBOARDDEVICESINFORMATION_HPP
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
                namespace OnBoardDeviceType
                {
                    enum Type
                    {
                        Other=1,
                        Unknown,
                        Video,
                        SCSIController,
                        Ethernet,
                        TokenRing,
                        Sound,
                        PATAController,
                        SATAController,
                        SASController
                    };
                }

                struct OnBoardDevice 
                {
                    RadonFramework::Core::Types::Bool IsEnabled;
                    OnBoardDeviceType::Type Type;
                    RadonFramework::Core::Types::String Description;
                    RadonFramework::Core::Types::String TypeAsString()const;
                };

                class OnBoardDevicesInformation
                {
                    public:
                        OnBoardDevicesInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                            Collections::AutoVector<Core::Types::String> StringList);
                        const OnBoardDevice& Device(const Core::Types::UInt32 Index)const;
                        Core::Types::UInt32 DeviceCount()const;
                    protected:
                        RadonFramework::Collections::AutoVector<OnBoardDevice> m_Devices;
                };
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_ONBOARDDEVICESINFORMATION_HPP