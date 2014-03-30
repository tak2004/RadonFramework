#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/System/Hardware/CacheInfo.hpp"
#include "RadonFramework/System/Hardware/ProcessorFeatures.hpp"

using namespace RadonFramework::System::Hardware;
using namespace RadonFramework::Collections;

RFTYPE::UInt32 GetAvailableLogicalProcessorCount_SystemAPIDispatcher()
{
    RFHDW::Dispatch();
    Assert(RFHDW::GetAvailableLogicalProcessorCount != GetAvailableLogicalProcessorCount_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFHDW::GetAvailableLogicalProcessorCount();
}

RFTYPE::UInt32 GetCurrentProcessorNumber_SystemAPIDispatcher()
{
    RFHDW::Dispatch();
    Assert(RFHDW::GetCurrentProcessorNumber != GetCurrentProcessorNumber_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFHDW::GetCurrentProcessorNumber();
}

RFTYPE::Bool GetCacheInfo_SystemAPIDispatcher(CacheInfo& Info, RFTYPE::UInt32 Index)
{
    RFHDW::Dispatch();
    Assert(RFHDW::GetCacheInfo != GetCacheInfo_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFHDW::GetCacheInfo(Info, Index);
}

RFTYPE::Int32 GetCacheCount_SystemAPIDispatcher()
{
    RFHDW::Dispatch();
    Assert(RFHDW::GetCacheCount != GetCacheCount_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFHDW::GetCacheCount();
}

RFTYPE::Bool GetLogicalProcessorFeatures_SystemAPIDispatcher(ProcessorFeatureMask& Features)
{
    RFHDW::Dispatch();
    Assert(RFHDW::GetLogicalProcessorFeatures != GetLogicalProcessorFeatures_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFHDW::GetLogicalProcessorFeatures(Features);
}

RFHDW::GetAvailableLogicalProcessorCountCallback RFHDW::GetAvailableLogicalProcessorCount = GetAvailableLogicalProcessorCount_SystemAPIDispatcher;
RFHDW::GetCurrentProcessorNumberCallback RFHDW::GetCurrentProcessorNumber = GetCurrentProcessorNumber_SystemAPIDispatcher;
RFHDW::GetCacheInfoCallback RFHDW::GetCacheInfo = GetCacheInfo_SystemAPIDispatcher;
RFHDW::GetCacheCountCallback RFHDW::GetCacheCount = GetCacheCount_SystemAPIDispatcher;
RFHDW::GetLogicalProcessorFeaturesCallback RFHDW::GetLogicalProcessorFeatures = GetLogicalProcessorFeatures_SystemAPIDispatcher;

RFTYPE::Bool IsSuccessfullyDispatched()
{
    RFTYPE::Bool result = true;
    result = result && GetAvailableLogicalProcessorCount != GetAvailableLogicalProcessorCount_SystemAPIDispatcher;
    result = result && GetCurrentProcessorNumber != GetCurrentProcessorNumber_SystemAPIDispatcher;
    result = result && GetCacheInfo != GetCacheInfo_SystemAPIDispatcher;
    result = result && GetCacheCount != GetCacheCount_SystemAPIDispatcher;
    result = result && GetLogicalProcessorFeatures != GetLogicalProcessorFeatures_SystemAPIDispatcher;
    return result;
}

void GetNotDispatchedFunctions( List<RFTYPE::String>& Result )
{
    if (GetAvailableLogicalProcessorCount == GetAvailableLogicalProcessorCount_SystemAPIDispatcher) 
        Result.AddLast("GetAvailableLogicalProcessorCount");
    if (GetCurrentProcessorNumber == GetCurrentProcessorNumber_SystemAPIDispatcher) 
        Result.AddLast("GetCurrentProcessorNumber");
    if (GetCacheInfo == GetCacheInfo_SystemAPIDispatcher) 
        Result.AddLast("GetCacheInfo");
    if (GetCacheCount == GetCacheCount_SystemAPIDispatcher) 
        Result.AddLast("GetCacheCount");
    if (GetLogicalProcessorFeatures == GetLogicalProcessorFeatures_SystemAPIDispatcher) 
        Result.AddLast("GetLogicalProcessorFeatures");
}