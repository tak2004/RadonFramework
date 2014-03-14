#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_MEMORYCONTROLLERINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_MEMORYCONTROLLERINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/Information.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
	    namespace Profiling
	    {
		    namespace SMBios
		    {
			    namespace MemoryControllerErrorDetectingMethod
			    {
				    enum Type
				    {
					    Other=1,
					    Unknown=2,
					    None=3,
					    _8BitParity=4,
					    _32BitECC=5,
					    _64BitECC=6,
					    _128BitECC=7,
					    CRC=8
				    };
			    }

			    namespace MemoryControllerErrorCorrectingCapability
			    {
				    enum Type
				    {
					    Other=1,
					    Unknown=2,
					    None=4,
					    SingleBitErrorCorrecting=8,
					    DoubleBitErrorCorrecting=16,
					    ErrorScrubbing=32
				    };
			    }

			    namespace MemoryControllerInformationInterleaveSupport
			    {
				    enum Type
				    {
					    Other=1,
					    Unknown=2,
					    OneWayInterleave=4,
					    TwoWayInterleave=8,
					    FourWayInterleave=16,
					    EightWayInterleave=32,
					    SixteenWayInterleave=64
				    };
			    }

			    namespace MemoryControllerInformationMemorySpeeds
			    {
				    enum Type
				    {
					    Other=1,
					    Unknown=2,
					    _70ns=4,
					    _60ns=8,
					    _50ns=16
					    //5-15 Reserved, must be zero
				    };
			    }

			    class MemoryControllerInformation
			    {
				    public:
					    MemoryControllerInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
												    Collections::AutoVector<Core::Types::String> StringList,
												    Collections::AutoVector<SMBios::Information> ContainedElements);
			    };
		    }
	    }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_MEMORYCONTROLLERINFORMATION_HPP