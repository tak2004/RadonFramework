#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/MemoryControllerInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Diagnostics::Profiling::SMBios;

#pragma pack(push,1)
struct MemoryControllerInformationStructure
{
	StructureHeader Header;
	RadonFramework::Core::Types::UInt8 ErrorDetectingMethod;
	RadonFramework::Core::Types::UInt8 ErrorCorrectingCapability;
	RadonFramework::Core::Types::UInt8 SupportedInterleave;
	RadonFramework::Core::Types::UInt8 CurrentInterleave;
	RadonFramework::Core::Types::UInt8 MaximumMemoryModuleSize;
	RadonFramework::Core::Types::UInt16 SupportedSpeeds;
	RadonFramework::Core::Types::UInt16 SupportedMemoryTypes;
	RadonFramework::Core::Types::UInt8 MemoryModuleVoltage;
	RadonFramework::Core::Types::UInt8 NumberOfAssociatedMemorySlots;
	//WORD MemoryModuleConfigurationHandles[NumberOfAssociatedMemorySlots];
	//BYTE EnabledErrorCorrectingCapabilities[NumberOfAssociatedMemorySlots];
};
#pragma pack(pop)

MemoryControllerInformation::MemoryControllerInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data,
														 Collections::AutoVector<Core::Types::String> StringList,
														 Collections::AutoVector<Information> ContainedElements )
{

}
