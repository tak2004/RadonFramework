#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_INFORMATION_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_INFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Profiling/SMBios/HeaderType.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Profiling
        {
            namespace SMBios
            {
                struct Information
                {
                    HeaderType::Type Type;
                    Collections::AutoVector<Core::Types::String> StringList;
                    Memory::AutoPointerArray<Core::Types::UInt8> Data;
                    Core::Types::UInt16 Handle;
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_INFORMATION_HPP