#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/BaseBoardInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework::Diagnostics::Profiling::SMBios;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;

#ifdef RF_VISUALCPP
    #pragma warning(push)
    #pragma warning(disable:4200)//silence vc++ to warn about "array of size 0"
#endif
#pragma pack(push,1)
struct BaseBoardInformationStructure
{
    StructureHeader Header;
    RadonFramework::Core::Types::UInt8 Manufacturer;//string
    RadonFramework::Core::Types::UInt8 Product;//string
    RadonFramework::Core::Types::UInt8 Version;//string
    RadonFramework::Core::Types::UInt8 SerialNumber;//string
    RadonFramework::Core::Types::UInt8 AssetTag;//string
    RadonFramework::Core::Types::UInt8 FeatureFlags;
    RadonFramework::Core::Types::UInt8 LocationInChassis;//string
    RadonFramework::Core::Types::UInt16 ChassisHandle;
    RadonFramework::Core::Types::UInt8 BoardType;
    RadonFramework::Core::Types::UInt8 NumberOfContainedObjectHandles;
    RadonFramework::Core::Types::UInt16 ContainedObjectHandles[];
};
#pragma pack(pop)
#ifdef RF_VISUALCPP
    #pragma warning(pop)
#endif

BaseBoardInformation::BaseBoardInformation(AutoPointerArray<UInt8> Data,
                                           AutoVector<String> StringList,
                                           AutoVector<Information> ContainedElements)
{
    BaseBoardInformationStructure* bbinfo=(BaseBoardInformationStructure*)Data.Get();
    m_Manufacturer=StringList[bbinfo->Manufacturer-1]->TrimEnd(" ");
    m_Product=StringList[bbinfo->Product-1]->TrimEnd(" ");
    m_Version=StringList[bbinfo->Version-1]->TrimEnd(" ");
    m_SerialNumber=StringList[bbinfo->SerialNumber-1]->TrimEnd(" ");
    if(bbinfo->Header.Length > 8)
    {
        m_AssetTag=bbinfo->AssetTag!=0?StringList[bbinfo->AssetTag-1]->TrimEnd(" "):"";
        m_FeatureFlags=(FeatureFlagsField::Type)bbinfo->FeatureFlags;
        m_LocationInChassis=bbinfo->LocationInChassis!=0?StringList[bbinfo->LocationInChassis-1]->TrimEnd(" "):"";
        m_BoardType=(BoardTypeField::Type)bbinfo->BoardType;

        for (UInt32 i=0;i<bbinfo->NumberOfContainedObjectHandles;++i)
            for (AutoVector<SMBios::Information>::Iterator it=ContainedElements.Begin();it!=ContainedElements.End();++it)
            {
                if ((*it)->Handle==bbinfo->ContainedObjectHandles[i])
                {
                    AutoPointer<SystemEnclosureInformation> chassi(new SystemEnclosureInformation((*it)->Data,(*it)->StringList));
                    m_ContainedObjects.PushBack(chassi);
                }
                else
                    if((*it)->Handle==bbinfo->ChassisHandle)
                    {
                        m_Chassi=AutoPointer<SystemEnclosureInformation>(new SystemEnclosureInformation((*it)->Data,(*it)->StringList));
                    }
            }

            for (Collections::AutoVector<SMBios::Information>::Iterator it=ContainedElements.Begin();it!=ContainedElements.End();++it)
            {
                if((*it)->Handle==bbinfo->ChassisHandle)
                {
                    m_Chassi=AutoPointer<SystemEnclosureInformation>(new SystemEnclosureInformation((*it)->Data,(*it)->StringList));
                }
            }
    }

}

String BaseBoardInformation::BoardTypeAsString()const
{
    String str;
    switch (m_BoardType)
    {
        case BoardTypeField::ConnectivitySwitch:
            str="Connectivity switch";
            break;
        case BoardTypeField::DaughterBoard:
            str="Daughter board";
            break;
        case BoardTypeField::InterconnectBoard:
            str="Interconnect board";
            break;
        case BoardTypeField::IOModule:
            str="IO module";
            break;
        case BoardTypeField::MemoryModule:
            str="Memory module";
            break;
        case BoardTypeField::Motherboard:
            str="Motherboard";
            break;
        case BoardTypeField::Other:
            str="Other";
            break;
        case BoardTypeField::ProcessorModule:
            str="Processor module";
            break;
        case BoardTypeField::ProcessorOrIOModule:
            str="Processor or IO module";
            break;
        case BoardTypeField::ProcessorOrMemoryModule:
            str="Processor or memory module";
            break;
        case BoardTypeField::ServerBlade:
            str="Server blade";
            break;
        case BoardTypeField::SystemManagmentModule:
            str="System managment module";
            break;
        case BoardTypeField::Unknown:
            str="Unknown";
            break;
    }
    return str;
}
