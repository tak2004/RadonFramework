#ifndef RF_SYSTEM_MEMORY_HPP
#define RF_SYSTEM_MEMORY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework {

// forward declarations
namespace Collections {
    template<class T>
    class List;
}
namespace Core { namespace Types {
    class String;
} }

namespace System { namespace Memory {

/// This function will be called by RadonFramework_Init function.
void Dispatch();

/** This function will be called by RadonFraemwork_Init function to
    * check if the dispatching was successfully.
    **/
RF_Type::Bool IsSuccessfullyDispatched();
    
/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(Collections::List<RF_Type::String>& Result);
    
typedef RF_Type::UInt32 (*GetPageSizeCallback)();
typedef void (*EnableTerminationOnHeapCorruptionCallback)();
typedef void* (*AllocateCallback)(const RF_Type::UInt32 Bytes);
typedef void (*FreeCallback)(void* FirstPage);

typedef RF_Type::Int32 (*CompareCallback)(const void* P1, const void* P2,
                                        RF_Type::Size Bytes);
typedef void (*CopyCallback)(void* Destination, const void* Source,
                                RF_Type::Size Bytes);
typedef void (*MoveCallback)(void* Destination, const void* Source,
                                RF_Type::Size Bytes);
typedef void (*SetCallback)(void* Pointer, RF_Type::Int32 Value,
                            RF_Type::Size Bytes);

extern GetPageSizeCallback GetPageSize;
extern EnableTerminationOnHeapCorruptionCallback EnableTerminationOnHeapCorruption;
extern AllocateCallback Allocate;
extern FreeCallback Free;

extern CompareCallback Compare;
extern CopyCallback Copy;
extern MoveCallback Move;
extern SetCallback Set;

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SYSMEM
#define RF_SHORTHAND_NAMESPACE_SYSMEM
namespace RF_SysMem = RadonFramework::System::Memory;
#endif

#endif // RF_SYSTEM_MEMORY_HPP