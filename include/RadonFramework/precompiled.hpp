#if defined(RF_SKIP_PRECOMPILED_HEADER)
#define PRECOMPILED_HPP
#endif
#ifndef PRECOMPILED_HPP
#define PRECOMPILED_HPP

#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER > 1000

#include <RadonFramework/Defines.hpp>
#include <RadonFramework/System/CompilerConfig.hpp>

// type traits
#include <type_traits>

#include <RadonFramework/Core/DataManagment.hpp>

// Basic types
#include <stdint.h>
// 1 byte size
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/Char.hpp>
#include <RadonFramework/Core/Types/Int8.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
// 2 byte size
#include <RadonFramework/Core/Types/AtomicInt16.hpp>
#include <RadonFramework/Core/Types/AtomicUInt16.hpp>
#include <RadonFramework/Core/Types/Int16.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
// 4 byte size
#include <RadonFramework/Core/Types/AtomicInt32.hpp>
#include <RadonFramework/Core/Types/AtomicUInt32.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
// 8 byte size
#include <RadonFramework/Core/Types/AtomicInt64.hpp>
#include <RadonFramework/Core/Types/AtomicUInt64.hpp>
#include <RadonFramework/Core/Types/Float64.hpp>
#include <RadonFramework/Core/Types/Int64.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>

#include <RadonFramework/Core/Types/AtomicPointer.hpp>
#include <RadonFramework/Core/Types/MemoryRange.hpp>
#include <RadonFramework/Core/Types/Size.hpp>

// Information about types
#include <RadonFramework/Core/Types/TypeCode.hpp>

#include <RadonFramework/Core/Idioms/PImpl.hpp>
#include <RadonFramework/Core/Pattern/Singleton.hpp>

//--------- depending on upper includes -----------

#include <RadonFramework/System/Memory.hpp>
#include <RadonFramework/System/String.hpp>

// Random size
#include <RadonFramework/Core/Types/Vec.hpp>

// Special types
// 4 byte size
#include <RadonFramework/Core/Types/AtomicInt32.hpp>
// 8 byte size
#include <RadonFramework/Core/Types/Vec64Int.hpp>
#include <RadonFramework/Core/Types/Vec64UInt.hpp>
// 16 byte size
#include <RadonFramework/Core/Types/Vec128Float.hpp>
#include <RadonFramework/Core/Types/Vec128Int.hpp>
#include <RadonFramework/Core/Types/Vec128UInt.hpp>

// more safety memory usage
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Memory/ObserverPointer.hpp>
#include <RadonFramework/Memory/PointerID.hpp>

// lockfree functions
#include <RadonFramework/System/Threading/Interlocked.hpp>

// Random size
#include <RadonFramework/Core/Types/AtomicPointer.hpp>
#include <RadonFramework/Core/Types/DynamicString.hpp>
#include <RadonFramework/Core/Types/FixString.hpp>
#include <RadonFramework/Core/Types/String.hpp>

#include <RadonFramework/Core/Types/UUID.hpp>

// Util classes for types
#include <RadonFramework/Core/Types/Convert.hpp>
#include <RadonFramework/Core/Types/Utils/StringOperators.hpp>

// floating point math
#include <RadonFramework/Math/Float32.hpp>
#include <RadonFramework/Math/Float64.hpp>
// integer math
#include <RadonFramework/Math/Integer.hpp>

#include <RadonFramework/Core/Common/Assert.hpp>

// Each compiler can implement it on it's own way.
#include <stdarg.h>

#endif  // PRECOMPILED_HPP