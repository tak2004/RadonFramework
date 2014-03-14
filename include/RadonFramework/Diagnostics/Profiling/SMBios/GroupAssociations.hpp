#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_GROUPASSOCIATIONS_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_GROUPASSOCIATIONS_HPP
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
                struct HandleInformation
                {
                    HeaderType::Type Type;
                    RadonFramework::Core::Types::UInt16 Handle;
                };
                class GroupAssociations
                {
                    public:
                        GroupAssociations(Memory::AutoPointerArray<Core::Types::UInt8> Data, 
                                          Collections::AutoVector<Core::Types::String> StringList);
                    protected:
                        RadonFramework::Core::Types::String m_Name;
                        RadonFramework::Collections::AutoVector<HandleInformation> m_Item;
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_GROUPASSOCIATIONS_HPP