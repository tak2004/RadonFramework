#ifndef RF_DIAGNOSTICS_DEBUGGING_FRAMEWORKDIAGNOSTICS_HPP
#define RF_DIAGNOSTICS_DEBUGGING_FRAMEWORKDIAGNOSTICS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::Diagnostics::Debugging {

struct FrameworkDiagnostics 
{
    static void GetAllMissingSystemFunctions(RF_Collect::List<RF_Type::String>& Result);
};

}

#ifndef RF_SHORTHAND_NAMESPACE_DEBUG
#define RF_SHORTHAND_NAMESPACE_DEBUG
namespace RF_Debug = RadonFramework::Diagnostics::Debugging;
#endif

#endif // RF_DIAGNOSTICS_DEBUGGING_FRAMEWORKDIAGNOSTICS_HPP
