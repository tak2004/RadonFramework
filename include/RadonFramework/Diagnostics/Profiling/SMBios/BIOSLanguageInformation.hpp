#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_BIOSLANGUAGEINFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_BIOSLANGUAGEINFORMATION_HPP
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
                class BIOSLanguageInformation
                {
                    public:
                        BIOSLanguageInformation(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                            Collections::AutoVector<Core::Types::String> StringList);
                        Core::Types::Bool IsLongFormat()const;
                        Core::Types::String CurrentLanguage()const;
                        Core::Types::UInt32 AvailableLanguageCount()const;
                        Core::Types::String AvailableLanguage(const Core::Types::UInt32 Index)const;
                    protected:
                        Core::Types::Bool m_IsLongFormat;
                        Core::Types::String m_CurrentLanguage;
                        Collections::AutoVector<Core::Types::String> m_AvailableLanguages;
                };
                inline Core::Types::Bool BIOSLanguageInformation::IsLongFormat()const
                {
                    return m_IsLongFormat;
                }
                inline Core::Types::String BIOSLanguageInformation::CurrentLanguage()const
                {
                    return m_CurrentLanguage;
                }
                inline Core::Types::UInt32 BIOSLanguageInformation::AvailableLanguageCount()const
                {
                    return m_AvailableLanguages.Size();
                }
                inline Core::Types::String BIOSLanguageInformation::AvailableLanguage(const Core::Types::UInt32 Index)const
                {
                    return *m_AvailableLanguages[Index];
                }
            }
        }
    }    
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_BIOSLANGUAGEINFORMATION_HPP