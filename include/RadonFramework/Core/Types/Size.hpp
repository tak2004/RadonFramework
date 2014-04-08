#ifndef RF_CORE_TYPES_SIZE_HPP
#define RF_CORE_TYPES_SIZE_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdlib.h>

namespace RadonFramework { namespace Core { namespace Types {

/// The size of Size can vary by compiler and system but it's always unsigned.
typedef size_t Size;

/// The maximum value which can be contained by a Size.
extern const Size SizeMax;

/// The minimum value which can be contained by a Size.
extern const Size SizeMin;

} } }

#endif // RF_CORE_TYPES_SIZE_HPP
