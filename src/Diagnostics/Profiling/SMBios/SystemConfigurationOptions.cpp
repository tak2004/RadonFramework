#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/SystemConfigurationOptions.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Diagnostics::Profiling::SMBios;

#pragma pack(push,1)
struct SystemConfigurationOptionsStructure
{
    StructureHeader Header;
    RadonFramework::Core::Types::UInt8 StringCount;
};
#pragma pack(pop)

SystemConfigurationOptions::SystemConfigurationOptions(Memory::AutoPointerArray<Core::Types::UInt8> Data,
                                                       Collections::AutoVector<Core::Types::String> StringList)
{
    SystemConfigurationOptionsStructure* info=(SystemConfigurationOptionsStructure*)Data.Get();
    Memory::AutoPointer<RadonFramework::Core::Types::String> str;
    for (RadonFramework::Core::Types::UInt32 i=0;i<info->StringCount;++i)
    {
        str=Memory::AutoPointer<Core::Types::String>(new Core::Types::String(StringList[i]->TrimEnd(" ")));
        m_ConfigurationInformation.PushBack(str);
    }
}

Core::Types::UInt32 SystemConfigurationOptions::OptionCount()const
{
    return m_ConfigurationInformation.Size();
}

const RadonFramework::Core::Types::String& SystemConfigurationOptions::Option(const Core::Types::UInt32 Index)const
{
    return *m_ConfigurationInformation[Index];
}