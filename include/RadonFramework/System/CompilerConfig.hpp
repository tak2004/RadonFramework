#ifndef RF_SYSTEM_COMPILERCONFIG_HPP
#define RF_SYSTEM_COMPILERCONFIG_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/System/MemoryArchitecture.hpp>
#include <RadonFramework/System/Endian.hpp>
#include <RadonFramework/Core/Common/Version.hpp>

namespace RadonFramework
{
    namespace System
    {
        struct CompilerConfig
        {
            static const Endian::Type Endianness;
            static const MemoryArchitecture::Type CompiledForArchitecture;
            static const Core::Common::Version FrameworkVersion;
        };
    }
}

#endif // RF_SYSTEM_COMPILERCONFIG_HPP