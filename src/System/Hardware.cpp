#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/System/Hardware/CacheInfo.hpp"
#include "RadonFramework/System/Hardware/ProcessorFeatures.hpp"

using namespace RadonFramework::System::Hardware;
using namespace RadonFramework::Collections;

RFTYPE::UInt32 GetAvailableLogicalProcessorCount_SystemAPIDispatcher()
{
    RFHDW::GetAvailableLogicalProcessorCount = 0;
    RFHDW::Dispatch();
    Assert(RFHDW::GetAvailableLogicalProcessorCount != GetAvailableLogicalProcessorCount_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFHDW::GetAvailableLogicalProcessorCount();
}

RFTYPE::UInt32 GetCurrentProcessorNumber_SystemAPIDispatcher()
{
    RFHDW::GetCurrentProcessorNumber = 0;
    RFHDW::Dispatch();
    Assert(RFHDW::GetCurrentProcessorNumber != GetCurrentProcessorNumber_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFHDW::GetCurrentProcessorNumber();
}

RFTYPE::Bool GetCacheInfo_SystemAPIDispatcher(CacheInfo& Info, RFTYPE::UInt32 Index)
{
    RFHDW::GetCacheInfo = 0;
    RFHDW::Dispatch();
    Assert(RFHDW::GetCacheInfo != GetCacheInfo_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFHDW::GetCacheInfo(Info, Index);
}

RFTYPE::Int32 GetCacheCount_SystemAPIDispatcher()
{
    RFHDW::GetCacheCount = 0;
    RFHDW::Dispatch();
    Assert(RFHDW::GetCacheCount != GetCacheCount_SystemAPIDispatcher,
        "Funtion was called and couldn't be dispatched");
    return RFHDW::GetCacheCount();
}

RFTYPE::Bool GetLogicalProcessorFeatures_SystemAPIDispatcher(ProcessorFeatureMask& Features)
{
    RFHDW::GetLogicalProcessorFeatures = 0;
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

RFTYPE::Bool RFHDW::IsSuccessfullyDispatched()
{
    RFTYPE::Bool result = true;
    result = result && GetAvailableLogicalProcessorCount != GetAvailableLogicalProcessorCount_SystemAPIDispatcher && GetAvailableLogicalProcessorCount != 0;
    result = result && GetCurrentProcessorNumber != GetCurrentProcessorNumber_SystemAPIDispatcher && GetCurrentProcessorNumber != 0;
    result = result && GetCacheInfo != GetCacheInfo_SystemAPIDispatcher && GetCacheInfo != 0;
    result = result && GetCacheCount != GetCacheCount_SystemAPIDispatcher && GetCacheCount != 0;
    result = result && GetLogicalProcessorFeatures != GetLogicalProcessorFeatures_SystemAPIDispatcher && GetLogicalProcessorFeatures != 0;
    return result;
}

void RFHDW::GetNotDispatchedFunctions( List<RFTYPE::String>& Result )
{
    if (GetAvailableLogicalProcessorCount == GetAvailableLogicalProcessorCount_SystemAPIDispatcher || GetAvailableLogicalProcessorCount == 0) 
        Result.AddLast("GetAvailableLogicalProcessorCount");
    if (GetCurrentProcessorNumber == GetCurrentProcessorNumber_SystemAPIDispatcher || GetCurrentProcessorNumber == 0) 
        Result.AddLast("GetCurrentProcessorNumber");
    if (GetCacheInfo == GetCacheInfo_SystemAPIDispatcher || GetCacheInfo == 0) 
        Result.AddLast("GetCacheInfo");
    if (GetCacheCount == GetCacheCount_SystemAPIDispatcher || GetCacheCount == 0) 
        Result.AddLast("GetCacheCount");
    if (GetLogicalProcessorFeatures == GetLogicalProcessorFeatures_SystemAPIDispatcher || GetLogicalProcessorFeatures == 0) 
        Result.AddLast("GetLogicalProcessorFeatures");
}