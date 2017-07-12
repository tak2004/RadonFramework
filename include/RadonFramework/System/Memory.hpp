#ifndef RF_SYSTEM_MEMORY_HPP
#define RF_SYSTEM_MEMORY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Collections {

template<class T>
class List;

}

namespace RadonFramework::Core::Types {

class String;

}

namespace RadonFramework::System::Memory {

/// This function will be called by RadonFramework_Init function.
void Dispatch();

/** This function will be called by RadonFraemwork_Init function to
    * check if the dispatching was successfully.
    **/
RF_Type::Bool IsSuccessfullyDispatched();
    
/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(Collections::List<RF_Type::String>& Result);
    
/// Return the granularity(in bytes) of memory allocation and validation.
using GetPageSizeCallback = RF_Type::UInt32(*)();

/// Return the granularity(in byteS) of minimal allocated chunks of the OS.
using GetBlockSizeCallback = RF_Type::UInt32(*)();

using EnableTerminationOnHeapCorruptionCallback = void(*)();

using PageAllocationSizeCallback = RF_Type::Size (*)(const void* FirstPage);

using PageAllocateCallback = void* (*)(RF_Type::Size& Bytes);

using PageFreeCallback = void (*)(void* FirstPage);

using AllocateCallback = void* (*)(const RF_Type::Size Bytes, const RF_Type::Size Alignment);

using FreeCallback = void(*)(void* FirstPage);

using CompareCallback = RF_Type::Int32(*)(const void* P1, const void* P2,
                                          RF_Type::Size Bytes);

using CopyCallback = void(*)(void* Destination, const void* Source,
                             RF_Type::Size Bytes);

using MoveCallback = void (*)(void* Destination, const void* Source,
                              RF_Type::Size Bytes);

using SetCallback = void(*)(void* Pointer, RF_Type::Int32 Value,
                            RF_Type::Size Bytes);

using SwapCallback = void(*)(void* P1, void* P2, RF_Type::Size Bytes);

using FillCallback = RF_Type::Size(*)(void* Pointer, const void* PatternData,
                                      RF_Type::Size PatternSize, RF_Type::Size BufferSize);

extern GetPageSizeCallback GetPageSize;
extern GetBlockSizeCallback GetBlockSize;
extern EnableTerminationOnHeapCorruptionCallback EnableTerminationOnHeapCorruption;
extern PageAllocationSizeCallback PageAllocationSize;
extern PageAllocateCallback PageAllocate;
extern PageFreeCallback PageFree;
extern AllocateCallback Allocate;
extern FreeCallback Free;
extern CompareCallback Compare;
extern CopyCallback Copy;
extern MoveCallback Move;
extern SetCallback Set;
extern SwapCallback Swap;
extern FillCallback Fill;

}

#ifndef RF_SHORTHAND_NAMESPACE_SYSMEM
#define RF_SHORTHAND_NAMESPACE_SYSMEM
namespace RF_SysMem = RadonFramework::System::Memory;
#endif

#endif // RF_SYSTEM_MEMORY_HPP