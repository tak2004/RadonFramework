#ifndef RF_SYSTEM_ENDIAN_HPP
#define RF_SYSTEM_ENDIAN_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace System {

enum class Endian
{ 
    Little=1, 
    Big, 
    Both 
}; 

} }

#ifndef RF_SHORTHAND_NAMESPACE_SYS
#define RF_SHORTHAND_NAMESPACE_SYS
namespace RF_Sys = RadonFramework::System;
#endif

#endif // RF_SYSTEM_ENDIAN_HPP