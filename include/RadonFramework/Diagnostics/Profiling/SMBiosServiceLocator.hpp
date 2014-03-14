#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOSSERVICELOCATOR_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOSSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/Diagnostics/Profiling/SMBiosService.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            class NullSMBiosService:public SMBiosService
            {
                public:
                    NullSMBiosService(const RadonFramework::Core::Types::String &Name):SMBiosService(Name){}
                protected:
                    void LoadSMBios(){}
            };

            typedef Core::Pattern::Locator<SMBiosService,NullSMBiosService> SMBiosServiceLocator;
        }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOSSERVICELOCATOR_HPP
