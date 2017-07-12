#ifndef RF_SYSTEM_HARDWARE_VEC128INT_HPP
#define RF_SYSTEM_HARDWARE_VEC128INT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::System::Hardware {

/// This function will be called by RadonFramework_Init function.
void DispatchVec128Int();

/** This function will be called by RadonFraemwork_Init function to
* check if the dispatching was successfully.
**/
RF_Type::Bool IsVec128IntSuccessfullyDispatched();

/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedVec128IntFunctions(Collections::List<RF_Type::String>& Result);

using Vec128IntLoadCallback = void(*)(RF_Type::Vec128Int32* Destination, 
    const RF_Type::Vec128Int32* Source,  const RF_Type::Size Elements);

using Vec128IntSetInt32Callback = void(*)(RF_Type::Vec128Int32* Destination,
    const RF_Type::Int32 Source, const RF_Type::Size Elements);

using Vec128IntCompareInt32Callback = void(*)(RF_Type::Vec128Int32* Destination,
    const RF_Type::Vec128Int32* SourceA, const RF_Type::Vec128Int32* SourceB,
    const RF_Type::Size Elements);

using Vec128IntMaskInt8Callback = void(*)(RF_Type::Int32* Masks,
    const RF_Type::Vec128Int32* Source, const RF_Type::Size Elements);

using Vec128IntFindInt32Callback = RF_Type::Int32(*)(
    const RF_Type::Vec128Int32* Source, RF_Type::Int32 Value);

extern Vec128IntLoadCallback Vec128IntLoad;
extern Vec128IntSetInt32Callback Vec128IntSetInt32;
extern Vec128IntCompareInt32Callback Vec128IntCompareInt32;
extern Vec128IntMaskInt8Callback Vec128IntMaskInt8;
extern Vec128IntFindInt32Callback Vec128IntFindInt32;

}

#ifndef RF_SHORTHAND_NAMESPACE_SYSHARDWARE
#define RF_SHORTHAND_NAMESPACE_SYSHARDWARE
namespace RF_SysHardware = RadonFramework::System::Hardware;
#endif

#endif