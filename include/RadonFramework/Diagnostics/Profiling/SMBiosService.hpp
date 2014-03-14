#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOSSERVICE_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOSSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Memory/ReadBuffer.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/Information.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBios/HeaderType.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
	    namespace Profiling
	    {
		    class SMBiosService:public Core::Pattern::Service
		    {
			    public:
				    SMBiosService(const RadonFramework::Core::Types::String &Name);
				    /** @brief This method read the SMBios from memory and return the new buffer.
				      * 
				      */
				    const Memory::ReadBuffer& ReadSMBios();
				    /** @brief This method return the last read SMBios buffer.
				      *
				      */
				    const Memory::ReadBuffer& GetSMBios()const;
				    /** @brief This method return the major version number of the SMBios.
				      *
				      */
				    Core::Types::UInt8 MajorVersion()const;
				    /** @brief This method return the minor version number of the SMBios.
				      *
				      */
				    Core::Types::UInt8 MinorVersion()const;

				    Collections::AutoVector<SMBios::Information> GetInformation(
                        const SMBios::HeaderType::Type OfType, 
                        Memory::ReadBuffer& Buffer);
			    protected:
				    virtual void LoadSMBios()=0;
				    Memory::ReadBuffer m_SMBios;
				    Core::Types::UInt8 m_MajorVersion;
				    Core::Types::UInt8 m_MinorVersion;
		    };
	    }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOSSERVICE_HPP