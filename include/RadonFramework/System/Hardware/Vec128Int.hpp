#ifndef RF_SYSTEM_HARDWARE_VEC128INT_HPP
#define RF_SYSTEM_HARDWARE_VEC128INT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace System { namespace Hardware {

/// This function will be called by RadonFramework_Init function.
void Dispatch();

/** This function will be called by RadonFraemwork_Init function to
* check if the dispatching was successfully.
**/
RF_Type::Bool IsSuccessfullyDispatched();

/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(Collections::List<RF_Type::String>& Result);

using LoadCallback = void(*)(RF_Type::Vec128Int32* Destination, 
    const RF_Type::Vec128Int32* Source,  const RF_Type::Size Elements);

using SetInt32Callback = void(*)(RF_Type::Vec128Int32* Destination, 
    const RF_Type::Int32 Source, const RF_Type::Size Elements);

using CompareInt32Callback = void(*)(RF_Type::Vec128Int32* Destination, 
    const RF_Type::Vec128Int32* SourceA, const RF_Type::Vec128Int32* SourceB,
    const RF_Type::Size Elements);

using MaskInt8Callback = void(*)(RF_Type::Int32* Masks,
    const RF_Type::Vec128Int32* Source, const RF_Type::Size Elements);

extern LoadCallback Load;
extern SetInt32Callback SetInt32;
extern CompareInt32Callback CompareInt32;
extern MaskInt8Callback MaskInt8;

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SYSHARDWARE
#define RF_SHORTHAND_NAMESPACE_SYSHARDWARE
namespace RF_SysHardware = RadonFramework::System::Hardware;
#endif

#endif