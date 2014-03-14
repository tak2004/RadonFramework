#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/SystemEventLog.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Diagnostics::Profiling::SMBios;

#pragma pack(push,1)
struct SupportedEventLogTypeDescriptors
{
    RadonFramework::Core::Types::UInt8 LogType;
    RadonFramework::Core::Types::UInt8 VariableDataFormatType;
};

#ifdef RF_VISUALCPP
    #pragma warning(push)
    #pragma warning(disable:4200)//silence vc++ to warn about "array of size 0"
#endif
struct SystemEventLogStructure
{
    StructureHeader Header;
    RadonFramework::Core::Types::UInt16 AreaLength;
    RadonFramework::Core::Types::UInt16 HeaderStartOffset;
    RadonFramework::Core::Types::UInt16 DataStartOffset;
    RadonFramework::Core::Types::UInt8 AccessMethod;
    RadonFramework::Core::Types::UInt8 Status;
    RadonFramework::Core::Types::UInt16 ChangeToken;
    RadonFramework::Core::Types::UInt16 AccessMethodAddress;
    RadonFramework::Core::Types::UInt8 HeaderFormat;
    RadonFramework::Core::Types::UInt8 NumberOfSupportedLogTypeDescriptors;
    RadonFramework::Core::Types::UInt8 LengthOfEachLogTypeDescriptor;
    SupportedEventLogTypeDescriptors ListOfSupportedEventLogTypeDescriptors[];
};
#ifdef RF_VISUALCPP
    #pragma warning(pop)
#endif
#pragma pack(pop)

SystemEventLog::SystemEventLog( Memory::AutoPointerArray<Core::Types::UInt8> Data, Collections::AutoVector<Core::Types::String> StringList )
{
    SystemEventLogStructure* info=(SystemEventLogStructure*)Data.Get();
    m_IsLogAreaValid=(info->Status & 1)!=0;
    m_IsLogAreaFull=(info->Status & 2)!=0;
    m_LogChangeToken=info->ChangeToken;
//	info->AreaLength;
//	info->HeaderStartOffset;
}
