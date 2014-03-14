#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_VOLTAGEPROBE_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_VOLTAGEPROBE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
	    namespace Profiling
	    {
		    namespace SMBios
		    {
			    namespace VoltageProbeStatus
			    {
				    enum Type
				    {
					    Other,
					    Unknown,
					    Ok,
					    NonCritical,
					    Critical,
					    NonRecoverable
				    };
			    }

			    namespace VoltageProbeLocation
			    {
				    enum Type
				    {
					    Other,
					    Unknown,
					    Processor,
					    Disk,
					    PeripheralBay,
					    SystemManagmentModule,
					    Motherboard,
					    MemoryModule,
					    ProcessorModule,
					    PowerUnit,
					    AddInCard
				    };
			    }

			    class VoltageProbe
			    {
				    public:
					    VoltageProbe(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
								     Collections::AutoVector<Core::Types::String> StringList);
				    protected:
					    Core::Types::String m_Description;
					    VoltageProbeStatus::Type m_Status;
					    VoltageProbeLocation::Type m_Location;
					    Core::Types::UInt16 m_MaximumValue;
					    Core::Types::UInt16 m_MinimumValue;
					    Core::Types::UInt16 m_Resolution;
					    Core::Types::UInt16 m_Tolerance;
					    Core::Types::UInt16 m_Accuracy;
					    Core::Types::UInt32 m_OEMDefined;
					    Core::Types::UInt16 m_NominalValue;
			    };
		    }
	    }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_VOLTAGEPROBE_HPP