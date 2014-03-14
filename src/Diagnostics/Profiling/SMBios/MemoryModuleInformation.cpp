#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/MemoryModuleInformation.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Diagnostics::Profiling::SMBios;

#pragma pack(push,1)
struct MemoryModuleInformationStructure
{
	StructureHeader Header;
	RadonFramework::Core::Types::UInt8 SocketDesignation;
	RadonFramework::Core::Types::UInt8 BankConnections;
	RadonFramework::Core::Types::UInt8 CurrentSpeed;
	RadonFramework::Core::Types::UInt16 CurrentMemoryType;
	RadonFramework::Core::Types::UInt8 InstalledSize;
	RadonFramework::Core::Types::UInt8 EnabledSize;
	RadonFramework::Core::Types::UInt8 ErrorStatus;
};
#pragma pack(pop)

MemoryModuleInformation::MemoryModuleInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data,
												 Collections::AutoVector<Core::Types::String> StringList)
{

}
