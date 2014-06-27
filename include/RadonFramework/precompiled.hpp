#ifndef PRECOMPILED_HPP
#define PRECOMPILED_HPP

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Defines.hpp>
#include <RadonFramework/Compiler.hpp>

// allow to raise compile time assertion
#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>

#include <RadonFramework/Core/Types/CompilerConfig.hpp>
// Basic types
#include <stdint.h>
// 1 byte size
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/Int8.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/Char.hpp>
// 2 byte size
#include <RadonFramework/Core/Types/Int16.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
// 4 byte size
#include <RadonFramework/Core/Types/Float32.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
// 8 byte size
#include <RadonFramework/Core/Types/Float64.hpp>
#include <RadonFramework/Core/Types/Int64.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>

#include <RadonFramework/Core/Types/Size.hpp>
#include <RadonFramework/Core/Types/MemoryRange.hpp>

namespace RFTYPE=RadonFramework::Core::Types;

// Information about types
#include <RadonFramework/Core/Types/CompilerConfig.hpp>
#include <RadonFramework/Core/Types/TypeCode.hpp>

#include <RadonFramework/Core/Common/DataManagment.hpp>

#include <RadonFramework/Memory/Allocator.hpp>

#if defined(RF_PRECOMPILED_PIMPL)
#include <RadonFramework/Core/Idioms/PImpl.hpp>
namespace RFIDIOM = RadonFramework::Core::Idioms;
#endif
#include <RadonFramework/Core/Pattern/Singleton.hpp>

//--------- depending on upper includes -----------

#include <RadonFramework/System/String.hpp>
namespace RFSTR = RadonFramework::System::String;

#include <RadonFramework/System/Memory.hpp>
namespace RFMEM = RadonFramework::System::Memory;

// Random size
#include <RadonFramework/Core/Types/Vec.hpp>

// Special types
// 4 byte size
#include <RadonFramework/Core/Types/AtomicInt32.hpp>
// 8 byte size
#include <RadonFramework/Core/Types/Vec64Int.hpp>
#include <RadonFramework/Core/Types/Vec64UInt.hpp>
// 16 byte size
#include <RadonFramework/Core/Types/Vec128Int.hpp>
#include <RadonFramework/Core/Types/Vec128UInt.hpp>
#include <RadonFramework/Core/Types/Vec128Float.hpp>

// more safety memory usage
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Memory/PointerID.hpp>

// lockfree functions
#include <RadonFramework/System/Threading/Interlocked.hpp>

// Random size
#include <RadonFramework/Core/Types/FixString.hpp>
#include <RadonFramework/Core/Types/DynamicString.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/AtomicPointer.hpp>

// Util classes for types
#include <RadonFramework/Core/Types/Convert.hpp>

// Each compiler can implement it on it's own way.
#include <stdarg.h>

#endif // PRECOMPILED_HPP