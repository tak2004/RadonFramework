#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMCONFIGURATIONOPTIONS_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMCONFIGURATIONOPTIONS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace SMBios
            {
                class SystemConfigurationOptions
                {
                    public:
                        SystemConfigurationOptions(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                            Collections::AutoVector<Core::Types::String> StringList);
                        Core::Types::UInt32 OptionCount()const;
                        const RadonFramework::Core::Types::String& Option(const Core::Types::UInt32 Index)const;
                    protected:
                        RadonFramework::Collections::AutoVector<RadonFramework::Core::Types::String> m_ConfigurationInformation;
                };
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMCONFIGURATIONOPTIONS_HPP