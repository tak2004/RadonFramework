#ifndef RF_CORE_TYPES_CHAR_HPP
#define RF_CORE_TYPES_CHAR_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework::Core::Types {

/// A Char have always the size of 1 byte and represent the ASCII charset.
typedef char Char;

/// The minimum value which can be contained by a Char.
extern const Char CharMin;

/// The maximum value which can be contained by a Char.
extern const Char CharMax;

}

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif // RF_CORE_TYPES_CHAR_HPP
