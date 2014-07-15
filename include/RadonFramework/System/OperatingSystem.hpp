#ifndef RF_SYSTEM_OPERATINGSYSTEM_HPP
#define RF_SYSTEM_OPERATINGSYSTEM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/System/PlatformID.hpp>
#include <RadonFramework/Core/Common/Version.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
    namespace System
    {
        class OperatingSystem
        {
            public:
                OperatingSystem();
                OperatingSystem(const PlatformID::Type Platform, 
                                const Core::Common::Version& VersionNumber);

                PlatformID::Type Platform()const;
                RF_Type::String PlatformString()const;
                RF_Type::String VersionString()const;
                const Core::Common::Version& VersionNumber()const;
            protected:
                PlatformID::Type m_Platform;
                Core::Common::Version m_VersionNumber;
        };
    }
}

#endif // RF_SYSTEM_OPERATINGSYSTEM_HPP