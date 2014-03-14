#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/OEMStrings.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Diagnostics::Profiling::SMBios;

#pragma pack(push,1)
struct OEMStringsStructure
{
	StructureHeader Header;
	RadonFramework::Core::Types::UInt8 StringCount;
};
#pragma pack(pop)

OEMStrings::OEMStrings( Memory::AutoPointerArray<Core::Types::UInt8> Data, Collections::AutoVector<Core::Types::String> StringList )
{
	OEMStringsStructure* info=(OEMStringsStructure*)Data.Get();
	Memory::AutoPointer<RadonFramework::Core::Types::String> str;
	for (RadonFramework::Core::Types::UInt32 i=0;i<info->StringCount;++i)
	{
		str=Memory::AutoPointer<Core::Types::String>(new Core::Types::String(StringList[i]->TrimEnd(" ")));
		m_OEMInformation.PushBack(str);
	}
}
