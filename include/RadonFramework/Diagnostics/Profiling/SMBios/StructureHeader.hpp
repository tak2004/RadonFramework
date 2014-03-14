#ifndef RF_DIAGNOSTICS_PROFILING_SMBIOS_STRUCTUREHEADER_HPP
#define RF_DIAGNOSTICS_PROFILING_SMBIOS_STRUCTUREHEADER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

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
                struct StructureHeader
                {
                    RadonFramework::Core::Types::UInt8 Type;
                    RadonFramework::Core::Types::UInt8 Length;
                    RadonFramework::Core::Types::UInt16 Handle;
                };
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_PROFILING_SMBIOS_STRUCTUREHEADER_HPP