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
RF_Type::Bool IsSuccessfullyDispatched();
    
/// This function is for debugging purpose and return all unassigned functions.
void GetNotDispatchedFunctions(Collections::List<RF_Type::String>& Result);

/** @brief Return the count of logical processors available by the OS.
  * There are cases where some cores or whole cpu's are not accessable by the OS.
  *
  * @return Return the count of the available logical processor.
  **/
using GetAvailableLogicalProcessorCountCallback = RF_Type::UInt32(*)();

/** @brief Return the logical processor number on which this call is executed.
  *
  * @return Return the logical processor number.
  **/
using GetCurrentProcessorNumberCallback = RF_Type::UInt32(*)();

/** \brief If successfull this function return the cache information of the logical processor
  * on which the call was executed. The call can return different values on different
  * logical processor. This can happen if the code run on a multi cpu system with
  * different cpu's.
  *
  * @param Info Specify the destination where to write the information.
  * @return Return true if data where written to Info else false.
  **/
using GetCacheInfoCallback = RF_Type::Bool(*)(CacheInfo& Info, RF_Type::UInt32 Index);

/** \brief This function obtains how many caches are available on the logical
  * processor unit this call is running on.
  *
  * @return Return -1 if an error occured else the number of available caches.
  **/
using GetCacheCountCallback = RF_Type::Int32(*)();

/** \brief This function obtains which processor features are available on the
  * logical processor unit this call is running on.
  *
  * @param Features Specify the destination where the to write the processor features.
  * @return Return true if data where written to Features else false.
  **/
using GetLogicalProcessorFeaturesCallback = RF_Type::Bool(*)(ProcessorFeatureMask& Features);

/// Returns the amount of physical memory(in bytes) accessible by the OS.
using GetPhysicalMemorySizeCallback = RF_Type::Size (*)();

/// Returns the amount of free physical memory in bytes.
using GetFreePhysicalMemorySizeCallback = RF_Type::Size(*)();

extern GetAvailableLogicalProcessorCountCallback GetAvailableLogicalProcessorCount;
extern GetCurrentProcessorNumberCallback GetCurrentProcessorNumber;
extern GetCacheInfoCallback GetCacheInfo;
extern GetCacheCountCallback GetCacheCount;
extern GetLogicalProcessorFeaturesCallback GetLogicalProcessorFeatures;
extern GetPhysicalMemorySizeCallback GetPhysicalMemorySize;
extern GetFreePhysicalMemorySizeCallback GetFreePhysicalMemorySize;

CacheInfo& GetLevel1DataCache();
CacheInfo& GetLevel1InstructionCache();
CacheInfo& GetLevel2DataCache();

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SYSHARDWARE
#define RF_SHORTHAND_NAMESPACE_SYSHARDWARE
namespace RF_SysHardware = RadonFramework::System::Hardware;
#endif

#endif // RF_SYSTEM_HARDWARE_HPP