#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/GroupAssociations.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Diagnostics::Profiling::SMBios;

#pragma pack(push,1)
struct ItemStructure
{
    RadonFramework::Core::Types::UInt8 Type;
    RadonFramework::Core::Types::UInt16 Handle;
};

#ifdef RF_VISUALCPP
    #pragma warning(push)
    #pragma warning(disable:4200)//silence vc++ to warn about "array of size 0"
#endif
struct GroupAssociationsStructure
{
    StructureHeader Header;
    RadonFramework::Core::Types::UInt8 GroupName;//string
    ItemStructure Items[];
};
#ifdef RF_VISUALCPP
    #pragma warning(pop)
#endif
#pragma pack(pop)

GroupAssociations::GroupAssociations(Memory::AutoPointerArray<Core::Types::UInt8> Data,
                                     Collections::AutoVector<Core::Types::String> StringList)
{
    GroupAssociationsStructure* info=(GroupAssociationsStructure*)Data.Get();
    m_Name=StringList[info->GroupName-1]->TrimEnd(" ");
    Core::Types::UInt32 itemcount=(info->Header.Length-5)/3;
    Memory::AutoPointer<Information> item;
    for (Core::Types::UInt32 i=0;i<itemcount;++i)
    {
        item=Memory::AutoPointer<Information>(new Information);
        item->Type=(HeaderType::Type)info->Items[i].Type;
        item->Handle=info->Items[i].Handle;
    }
}
