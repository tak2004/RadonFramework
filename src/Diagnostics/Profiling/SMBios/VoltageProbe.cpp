#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Profiling/SMBios/VoltageProbe.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/StructureHeader.hpp>

using namespace RadonFramework::Diagnostics::Profiling::SMBios;
using namespace RadonFramework;

#pragma pack(push,1)
struct VoltageProbeStructure
{
	StructureHeader Header;
	Core::Types::UInt8 Description;//string
	Core::Types::UInt8 LocationAndStatus;
	Core::Types::UInt16 MaximumValue;
	Core::Types::UInt16 MinimumValue;
	Core::Types::UInt16 Resolution;
	Core::Types::UInt16 Tolerance;
	Core::Types::UInt16 Accuracy;
	Core::Types::UInt32 OEMDefined;
	Core::Types::UInt16 NominalValue;
};
#pragma pack(pop)

VoltageProbe::VoltageProbe(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
						   Collections::AutoVector<Core::Types::String> StringList)
{
	VoltageProbeStructure* volinfo=reinterpret_cast<VoltageProbeStructure*>(Data.Get());
	m_Description=StringList[volinfo->Description-1]->TrimEnd(" ");
	m_Status=static_cast<VoltageProbeStatus::Type>(volinfo->LocationAndStatus>>5);
	m_Location=static_cast<VoltageProbeLocation::Type>(volinfo->LocationAndStatus & 31);
	m_MaximumValue=volinfo->MaximumValue==0x8000?0:volinfo->MaximumValue;
	m_MinimumValue=volinfo->MinimumValue==0x8000?0:volinfo->MinimumValue;
	m_Resolution=volinfo->Resolution==0x8000?0:volinfo->Resolution;
	m_Tolerance=volinfo->Tolerance==0x8000?0:volinfo->Tolerance;
	m_Accuracy=volinfo->Accuracy==0x8000?0:volinfo->Accuracy;
	m_OEMDefined=volinfo->OEMDefined;
	m_NominalValue=volinfo->NominalValue==0x8000?0:volinfo->NominalValue;
}
