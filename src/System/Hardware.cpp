#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/System/Hardware/CacheInfo.hpp"
#include "RadonFramework/System/Hardware/ProcessorFeatures.hpp"

using namespace RadonFramework::System::Hardware;
using namespace RadonFramework::Collections;

RF_Type::UInt32 GetAvailableLogicalProcessorCount_SystemAPIDispatcher()
{
    GetAvailableLogicalProcessorCount = 0;
    Dispatch();
    Assert(GetAvailableLogicalProcessorCount != GetAvailableLogicalProcessorCount_SystemAPIDispatcher &&
           GetAvailableLogicalProcessorCount != 0,
           "Funtion was called and couldn't be dispatched");
    return GetAvailableLogicalProcessorCount();
}

RF_Type::UInt32 GetCurrentProcessorNumber_SystemAPIDispatcher()
{
    GetCurrentProcessorNumber = 0;
    Dispatch();
    Assert(GetCurrentProcessorNumber != GetCurrentProcessorNumber_SystemAPIDispatcher &&
           GetCurrentProcessorNumber != 0,
           "Funtion was called and couldn't be dispatched");
    return GetCurrentProcessorNumber();
}

RF_Type::Bool GetCacheInfo_SystemAPIDispatcher(CacheInfo& Info, RF_Type::UInt32 Index)
{
    GetCacheInfo = 0;
    Dispatch();
    Assert(GetCacheInfo != GetCacheInfo_SystemAPIDispatcher &&
           GetCacheInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetCacheInfo(Info, Index);
}

RF_Type::Int32 GetCacheCount_SystemAPIDispatcher()
{
    GetCacheCount = 0;
    Dispatch();
    Assert(GetCacheCount != GetCacheCount_SystemAPIDispatcher &&
           GetCacheCount != 0,
           "Funtion was called and couldn't be dispatched");
    return GetCacheCount();
}

RF_Type::Bool GetLogicalProcessorFeatures_SystemAPIDispatcher(ProcessorFeatureMask& Features)
{
    GetLogicalProcessorFeatures = 0;
    Dispatch();
    Assert(GetLogicalProcessorFeatures != GetLogicalProcessorFeatures_SystemAPIDispatcher &&
           GetLogicalProcessorFeatures != 0,
           "Funtion was called and couldn't be dispatched");
    return GetLogicalProcessorFeatures(Features);
}

RFHDW::GetAvailableLogicalProcessorCountCallback RFHDW::GetAvailableLogicalProcessorCount = GetAvailableLogicalProcessorCount_SystemAPIDispatcher;
RFHDW::GetCurrentProcessorNumberCallback RFHDW::GetCurrentProcessorNumber = GetCurrentProcessorNumber_SystemAPIDispatcher;
RFHDW::GetCacheInfoCallback RFHDW::GetCacheInfo = GetCacheInfo_SystemAPIDispatcher;
RFHDW::GetCacheCountCallback RFHDW::GetCacheCount = GetCacheCount_SystemAPIDispatcher;
RFHDW::GetLogicalProcessorFeaturesCallback RFHDW::GetLogicalProcessorFeatures = GetLogicalProcessorFeatures_SystemAPIDispatcher;

RF_Type::Bool RFHDW::IsSuccessfullyDispatched()
{
    RF_Type::Bool result = true;
    result = result && GetAvailableLogicalProcessorCount != GetAvailableLogicalProcessorCount_SystemAPIDispatcher && GetAvailableLogicalProcessorCount != 0;
    result = result && GetCurrentProcessorNumber != GetCurrentProcessorNumber_SystemAPIDispatcher && GetCurrentProcessorNumber != 0;
    result = result && GetCacheInfo != GetCacheInfo_SystemAPIDispatcher && GetCacheInfo != 0;
    result = result && GetCacheCount != GetCacheCount_SystemAPIDispatcher && GetCacheCount != 0;
    result = result && GetLogicalProcessorFeatures != GetLogicalProcessorFeatures_SystemAPIDispatcher && GetLogicalProcessorFeatures != 0;
    return result;
}

void RFHDW::GetNotDispatchedFunctions( List<RF_Type::String>& Result )
{
    if (GetAvailableLogicalProcessorCount == GetAvailableLogicalProcessorCount_SystemAPIDispatcher || GetAvailableLogicalProcessorCount == 0) 
        Result.AddLast(RF_Type::String("GetAvailableLogicalProcessorCount", sizeof("GetAvailableLogicalProcessorCount")));
    if (GetCurrentProcessorNumber == GetCurrentProcessorNumber_SystemAPIDispatcher || GetCurrentProcessorNumber == 0) 
        Result.AddLast(RF_Type::String("GetCurrentProcessorNumber", sizeof("GetCurrentProcessorNumber")));
    if (GetCacheInfo == GetCacheInfo_SystemAPIDispatcher || GetCacheInfo == 0) 
        Result.AddLast(RF_Type::String("GetCacheInfo", sizeof("GetCacheInfo")));
    if (GetCacheCount == GetCacheCount_SystemAPIDispatcher || GetCacheCount == 0) 
        Result.AddLast(RF_Type::String("GetCacheCount", sizeof("GetCacheCount")));
    if (GetLogicalProcessorFeatures == GetLogicalProcessorFeatures_SystemAPIDispatcher || GetLogicalProcessorFeatures == 0) 
        Result.AddLast(RF_Type::String("GetLogicalProcessorFeatures", sizeof("GetLogicalProcessorFeatures")));
}