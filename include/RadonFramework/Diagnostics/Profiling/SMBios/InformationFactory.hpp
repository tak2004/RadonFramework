#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_INFORMATIONFACTORY_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_INFORMATIONFACTORY_HPP

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/HeaderType.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/Information.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
	    namespace Profiling
	    {
		    namespace SMBios
		    {
			    class InformationFactory
			    {
				    public:
					    static Memory::AutoPointer<SMBios::Information> Create(
                            const SMBios::HeaderType::Type Type, 
                            Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                            Collections::AutoVector<Core::Types::String>& StringList);
			    };
		    }
	    }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_INFORMATIONFACTORY_HPP