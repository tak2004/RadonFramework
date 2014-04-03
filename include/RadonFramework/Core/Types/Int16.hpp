#ifndef RF_CORE_TYPES_INT16_HPP
#define RF_CORE_TYPES_INT16_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace RadonFramework { namespace Core { namespace Types {

/// A Int16 have always the size of 2 byte and represent a signed number.
typedef short int Int16;

/// The maximum value which can be contained by a Int16.
extern const Int16 Int16Max;

/// The minimum value which can be contained by a Int16.
extern const Int16 Int16Min;

} } }

#endif // RF_CORE_TYPES_INT16_HPP
