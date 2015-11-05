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

RF_Type::Size GetPhysicalMemorySize_SystemAPIDispatcher()
{
    GetPhysicalMemorySize = 0;
    Dispatch();
    Assert(GetPhysicalMemorySize != GetPhysicalMemorySize_SystemAPIDispatcher &&
           GetPhysicalMemorySize != 0,
           "Funtion was called and couldn't be dispatched");
    return GetPhysicalMemorySize();
}

RF_Type::Size GetFreePhysicalMemorySize_SystemAPIDispatcher()
{
    GetFreePhysicalMemorySize = 0;
    Dispatch();
    Assert(GetFreePhysicalMemorySize != GetFreePhysicalMemorySize_SystemAPIDispatcher &&
        GetFreePhysicalMemorySize != 0,
        "Funtion was called and couldn't be dispatched");
    return GetFreePhysicalMemorySize();
}

RFHDW::GetAvailableLogicalProcessorCountCallback RFHDW::GetAvailableLogicalProcessorCount = GetAvailableLogicalProcessorCount_SystemAPIDispatcher;
RFHDW::GetCurrentProcessorNumberCallback RFHDW::GetCurrentProcessorNumber = GetCurrentProcessorNumber_SystemAPIDispatcher;
RFHDW::GetCacheInfoCallback RFHDW::GetCacheInfo = GetCacheInfo_SystemAPIDispatcher;
RFHDW::GetCacheCountCallback RFHDW::GetCacheCount = GetCacheCount_SystemAPIDispatcher;
RFHDW::GetLogicalProcessorFeaturesCallback RFHDW::GetLogicalProcessorFeatures = GetLogicalProcessorFeatures_SystemAPIDispatcher;
RFHDW::GetPhysicalMemorySizeCallback RFHDW::GetPhysicalMemorySize = GetPhysicalMemorySize_SystemAPIDispatcher;
RFHDW::GetFreePhysicalMemorySizeCallback RFHDW::GetFreePhysicalMemorySize = GetFreePhysicalMemorySize_SystemAPIDispatcher;

RF_Type::Bool RFHDW::IsSuccessfullyDispatched()
{
    RF_Type::Bool result = true;
    result = result && GetAvailableLogicalProcessorCount != GetAvailableLogicalProcessorCount_SystemAPIDispatcher && GetAvailableLogicalProcessorCount != 0;
    result = result && GetCurrentProcessorNumber != GetCurrentProcessorNumber_SystemAPIDispatcher && GetCurrentProcessorNumber != 0;
    result = result && GetCacheInfo != GetCacheInfo_SystemAPIDispatcher && GetCacheInfo != 0;
    result = result && GetCacheCount != GetCacheCount_SystemAPIDispatcher && GetCacheCount != 0;
    result = result && GetLogicalProcessorFeatures != GetLogicalProcessorFeatures_SystemAPIDispatcher && GetLogicalProcessorFeatures != 0;
    result = result && GetPhysicalMemorySize != GetPhysicalMemorySize_SystemAPIDispatcher && GetPhysicalMemorySize != 0;
    result = result && GetFreePhysicalMemorySize != GetFreePhysicalMemorySize_SystemAPIDispatcher && GetFreePhysicalMemorySize != 0;
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
    if(GetPhysicalMemorySize == GetPhysicalMemorySize_SystemAPIDispatcher || GetPhysicalMemorySize == 0)
        Result.AddLast(RF_Type::String("GetPhysicalMemorySize", sizeof("GetPhysicalMemorySize")));
    if(GetFreePhysicalMemorySize == GetFreePhysicalMemorySize_SystemAPIDispatcher || GetFreePhysicalMemorySize == 0)
        Result.AddLast(RF_Type::String("GetFreePhysicalMemorySize", sizeof("GetFreePhysicalMemorySize")));
}

struct MostWantedCacheInfos
{
    void InitData()
    {
        CacheInfo tmp;
        RF_Type::Int32 count = GetCacheCount();
        for(RF_Type::Int32 i = 0; i < count; ++i)
        {
            if(GetCacheInfo(tmp, i))
            {
                if(tmp.Level == 1 && tmp.UsedAs == CacheUseCase::Data)
                {
                    RF_SysMem::Copy(&L1Data, &tmp, sizeof(CacheInfo));
                }
                if(tmp.Level == 2 && tmp.UsedAs == CacheUseCase::Data)
                {
                    RF_SysMem::Copy(&L2Data, &tmp, sizeof(CacheInfo));
                }
                if(tmp.Level == 1 && tmp.UsedAs == CacheUseCase::Code)
                {
                    RF_SysMem::Copy(&L1Instruction, &tmp, sizeof(CacheInfo));
                }
            }
        }
        // hardwired fallback which should fit to the majority
        if(SharedCacheInfo.L1Data.Level == 0)
        {
            L1Data.Associativity = CacheAssociativity::Unknown;
            L1Data.Level = 1;
            L1Data.LineCount = 512;
            L1Data.LineSize = 64;
            L1Data.Size = 32768;
            L1Data.UsedAs = CacheUseCase::Data;
        }

        if(SharedCacheInfo.L2Data.Level == 0)
        {
            L2Data.Associativity = CacheAssociativity::Unknown;
            L2Data.Level = 2;
            L2Data.LineCount = 4096;
            L2Data.LineSize = 64;
            L2Data.Size = 262144;
            L2Data.UsedAs = CacheUseCase::Data;
        }

        if(SharedCacheInfo.L1Instruction.Level == 0)
        {
            L1Data.Associativity = CacheAssociativity::Unknown;
            L1Data.Level = 1;
            L1Data.LineCount = 512;
            L1Data.LineSize = 64;
            L1Data.Size = 32768;
            L1Data.UsedAs = CacheUseCase::Code;
        }
    }
    RFHDW::CacheInfo L1Data;
    RFHDW::CacheInfo L2Data;
    RFHDW::CacheInfo L1Instruction;
} SharedCacheInfo = {0};

RFHDW::CacheInfo& RFHDW::GetLevel1DataCache()
{
    if(SharedCacheInfo.L1Data.Level == 0)
    {
        SharedCacheInfo.InitData();
    }
    return SharedCacheInfo.L1Data;
}

RFHDW::CacheInfo& RFHDW::GetLevel1InstructionCache()
{
    if(SharedCacheInfo.L1Instruction.Level == 0)
    {
        SharedCacheInfo.InitData();
    }
    return SharedCacheInfo.L1Instruction;
}

RFHDW::CacheInfo& RFHDW::GetLevel2DataCache()
{
    if(SharedCacheInfo.L2Data.Level == 0)
    {
        SharedCacheInfo.InitData();
    }
    return SharedCacheInfo.L2Data;
}