#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/OnBoardDevicesInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Diagnostics::Profiling::SMBios;

#ifdef RF_VISUALCPP
    #pragma warning(push)
    #pragma warning(disable:4200)//silence vc++ to warn about "array of size 0"
#endif
#pragma pack(push,1)
struct OnBoardDevicesInformationStructure
{
    StructureHeader Header;
    RadonFramework::Core::Types::UInt8 Data[];//stupid structure
};
#pragma pack(pop)
#ifdef RF_VISUALCPP
    #pragma warning(pop)
#endif

OnBoardDevicesInformation::OnBoardDevicesInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data,
                                                     Collections::AutoVector<Core::Types::String> StringList )
{
    OnBoardDevicesInformationStructure* info=(OnBoardDevicesInformationStructure*)Data.Get();
    RadonFramework::Core::Types::UInt32 elements=(info->Header.Length-4)/2;
    for (RadonFramework::Core::Types::UInt32 i=0;i<elements;++i)
    {
        Memory::AutoPointer<OnBoardDevice> dev(new OnBoardDevice);
        dev->IsEnabled=(info->Data[i] & 128)!=0;
        dev->Type=(OnBoardDeviceType::Type)(info->Data[i] & 127);
        dev->Description=StringList[info->Data[i+elements]-1]->TrimEnd(" ");
        m_Devices.PushBack(dev);
    }
}

const OnBoardDevice& OnBoardDevicesInformation::Device(const Core::Types::UInt32 Index)const
{
    return *m_Devices[Index];
}

Core::Types::UInt32 OnBoardDevicesInformation::DeviceCount()const
{
    return m_Devices.Size();
}

RadonFramework::Core::Types::String OnBoardDevice::TypeAsString()const
{
    RadonFramework::Core::Types::String str;
    switch (Type)
    {
        case OnBoardDeviceType::Video:str="Video";break;
        case OnBoardDeviceType::Unknown:str="Unknown";break;
        case OnBoardDeviceType::TokenRing:str="Token ring";break;
        case OnBoardDeviceType::Sound:str="Sound";break;
        case OnBoardDeviceType::SCSIController:str="SCSI controller";break;
        case OnBoardDeviceType::SATAController:str="SATA controller";break;
        case OnBoardDeviceType::SASController:str="SAS controller";break;
        case OnBoardDeviceType::PATAController:str="PATA controller";break;
        case OnBoardDeviceType::Other:str="Other";break;
        case OnBoardDeviceType::Ethernet:str="Ethernet";break;
    }
    return str;
}