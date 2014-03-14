#ifndef RF_DIAGNOSTICS_DEBUGGING_FRAMEWORKDIAGNOSTICS_HPP
#define RF_DIAGNOSTICS_DEBUGGING_FRAMEWORKDIAGNOSTICS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework
{
    namespace Diagnostics
    {
        namespace Debugging
        {
            namespace FrameworkDiagnostics
            {
                void GetAllMissingSystemFunctions(Collections::List<Core::Types::String>& Result);
            }
        }
    }
}

#endif // RF_DIAGNOSTICS_DEBUGGING_FRAMEWORKDIAGNOSTICS_HPP
