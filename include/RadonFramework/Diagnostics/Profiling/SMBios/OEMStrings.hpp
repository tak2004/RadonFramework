#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_OEMSTRINGS_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_OEMSTRINGS_HPP
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
                class OEMStrings
                {
                    public:
                        OEMStrings(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                            Collections::AutoVector<Core::Types::String> StringList);
                        Core::Types::UInt32 OEMInformationCount()const;
                        Core::Types::String OEMInformation(const Core::Types::UInt32 Index)const;
                    protected:
                        RadonFramework::Collections::AutoVector<RadonFramework::Core::Types::String> m_OEMInformation;
                };

                inline Core::Types::UInt32 OEMStrings::OEMInformationCount()const
                {
                    return m_OEMInformation.Size();
                }
                inline Core::Types::String OEMStrings::OEMInformation(const Core::Types::UInt32 Index)const
                {
                    return *m_OEMInformation[Index];
                }
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_OEMSTRINGS_HPP