#ifndef RF_SYSTEM_HARDWARE_HPP
#define RF_SYSTEM_HARDWARE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace System { namespace Hardware {

// forward decleration
struct CacheInfo;
class ProcessorFeatureMask;

/// This function will be called by RadonFramework_Init function.
void Dispatch();

/** This function will be called by RadonFraemwork_Init function to
  * check if the dispatching was successfully.
  **/
RFTYPE::Bool IsSuccessfullyDispatched();
    
/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(Collections::List<RFTYPE::String>& Result);

/** @brief Return the count of logical processors available by the OS.
  * There are cases where some cores or whole cpu's are not accessable by the OS.
  *
  * @return Return the count of the available logical processor.
  **/
typedef RFTYPE::UInt32 (*GetAvailableLogicalProcessorCountCallback)();

/** @brief Return the logical processor number on which this call is executed.
  *
  * @return Return the logical processor number.
  **/
typedef RFTYPE::UInt32 (*GetCurrentProcessorNumberCallback)();

/** \brief If successfull this function return the cache information of the logical processor
  * on which the call was executed. The call can return different values on different
  * logical processor. This can happen if the code run on a multi cpu system with
  * different cpu's.
  *
  * @param Info Specify the destination where to write the information.
  * @return Return true if data where written to Info else false.
  **/
typedef RFTYPE::Bool (*GetCacheInfoCallback)(CacheInfo& Info, RFTYPE::UInt32 Index);

/** \brief This function obtain how many caches are available on the logical
  * processor unit this call is running on.
  *
  * @return Return -1 if an error occured else the number of available caches.
  **/
typedef RFTYPE::Int32 (*GetCacheCountCallback)();

/** \brief This function obtain which processor features are available on the
  * logical processor unit this call is running on.
  *
  * @param Features Specify the destition where the to write the processor features.
  * @return Return true if data where written to Features else false.
  **/
typedef RFTYPE::Bool (*GetLogicalProcessorFeaturesCallback)(ProcessorFeatureMask& Features);

extern GetAvailableLogicalProcessorCountCallback GetAvailableLogicalProcessorCount;
extern GetCurrentProcessorNumberCallback GetCurrentProcessorNumber;
extern GetCacheInfoCallback GetCacheInfo;
extern GetCacheCountCallback GetCacheCount;
extern GetLogicalProcessorFeaturesCallback GetLogicalProcessorFeatures;

} } }

namespace RFHDW = RadonFramework::System::Hardware;

#endif // RF_SYSTEM_HARDWARE_HPP