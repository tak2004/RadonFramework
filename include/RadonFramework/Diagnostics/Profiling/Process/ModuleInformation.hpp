#ifndef RF_DIAGNOSTICS_PROFILING_PROCESS_MODULEINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_PROCESS_MODULEINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace Process
            {
                class ModuleInformation
                {
                    public:
                        ModuleInformation();
                        ModuleInformation(const ModuleInformation& Copy);
                        ModuleInformation(RadonFramework::Core::Types::String& Name);
                        const Core::Types::String& Name()const;
                    protected:
                        RadonFramework::Core::Types::String m_Name;
                };
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_PROCESS_MODULEINFORMATION_HPP