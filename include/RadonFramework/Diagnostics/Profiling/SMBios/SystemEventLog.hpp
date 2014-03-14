#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMEVENTLOG_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMEVENTLOG_HPP
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
                class SystemEventLog
                {
                    public:
                        SystemEventLog(Memory::AutoPointerArray<Core::Types::UInt8> Data,
                                        Collections::AutoVector<Core::Types::String> StringList);
                    protected:
                        RadonFramework::Core::Types::Bool m_IsLogAreaValid;
                        RadonFramework::Core::Types::Bool m_IsLogAreaFull;
                        RadonFramework::Core::Types::UInt32 m_LogChangeToken;
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_SYSTEMEVENTLOG_HPP