#ifndef RF_SYSTEM_SIMD_HPP
#define RF_SYSTEM_SIMD_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::System::SIMD {

/// This function will be called by RadonFramework_Init function.
void Dispatch();

/** This function will be called by RadonFraemwork_Init function to
  * check if the dispatching was successfully.
  **/
RFTYPE::Bool IsSuccessfullyDispatched();
    
/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(Collections::List<RFTYPE::String>& Result);

}

#endif // RF_SYSTEM_SIMD_HPP