#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/BIOSLanguageInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Diagnostics::Profiling::SMBios;

#pragma pack(push,1)
struct BIOSLanguageInformationStructure
{
	StructureHeader Header;
	RadonFramework::Core::Types::UInt8 InstallabledLanguages;//string count
	RadonFramework::Core::Types::UInt8 Flags;
	RadonFramework::Core::Types::UInt8 Reserved[15];
	RadonFramework::Core::Types::UInt8 CurrentLanguage;//string
};
#pragma pack(pop)

BIOSLanguageInformation::BIOSLanguageInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
												 Collections::AutoVector<Core::Types::String> StringList )
{
	BIOSLanguageInformationStructure* info=(BIOSLanguageInformationStructure*)Data.Get();
	m_IsLongFormat=(info->Flags & 1)==0;
	m_CurrentLanguage=StringList[info->CurrentLanguage-1]->TrimEnd(" ");
	for (RadonFramework::Core::Types::UInt32 i=0;i<info->InstallabledLanguages;++i)
		m_AvailableLanguages.PushBack(Memory::AutoPointer<Core::Types::String>(new Core::Types::String(StringList[i]->TrimEnd(" "))));
}
