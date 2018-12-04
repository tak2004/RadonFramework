#ifndef RF_CORE_TYPES_BOOL_HPP
#define RF_CORE_TYPES_BOOL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Core::Types {

using Bool = bool;

}

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#ifndef RF_DISABLE_USING_TYPES
using RadonFramework::Core::Types::Bool;
#endif

#endif // RF_CORE_TYPES_BOOL_HPP
