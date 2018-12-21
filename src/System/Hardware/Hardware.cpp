#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware/Hardware.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/System/Hardware/CacheInfo.hpp"
#include "RadonFramework/System/Hardware/ProcessorFeatures.hpp"
#include "RadonFramework/System/Hardware/Vec128Int.hpp"

using namespace RadonFramework::Collections;

namespace RadonFramework::System::Hardware {

RF_Type::UInt32 GetAvailableLogicalProcessorCount_SystemAPIDispatcher()
{
    GetAvailableLogicalProcessorCount = 0;
    Dispatch();
    RF_ASSERT(GetAvailableLogicalProcessorCount != GetAvailableLogicalProcessorCount_SystemAPIDispatcher &&
           GetAvailableLogicalProcessorCount != 0,
           "Funtion was called and couldn't be dispatched");
    return GetAvailableLogicalProcessorCount();
}

RF_Type::UInt32 GetCurrentProcessorNumber_SystemAPIDispatcher()
{
    GetCurrentProcessorNumber = 0;
    Dispatch();
    RF_ASSERT(GetCurrentProcessorNumber != GetCurrentProcessorNumber_SystemAPIDispatcher &&
           GetCurrentProcessorNumber != 0,
           "Funtion was called and couldn't be dispatched");
    return GetCurrentProcessorNumber();
}

RF_Type::UInt32 GetCurrentUniqueProcessorNumber_SystemAPIDispatcher()
{
    GetCurrentUniqueProcessorNumber = 0;
    Dispatch();
    RF_ASSERT(GetCurrentUniqueProcessorNumber != GetCurrentUniqueProcessorNumber_SystemAPIDispatcher &&
        GetCurrentUniqueProcessorNumber != 0,
        "Funtion was called and couldn't be dispatched");
    return GetCurrentUniqueProcessorNumber();
}

RF_Type::Bool GetCacheInfo_SystemAPIDispatcher(CacheInfo& Info, RF_Type::UInt32 Index)
{
    GetCacheInfo = 0;
    Dispatch();
    RF_ASSERT(GetCacheInfo != GetCacheInfo_SystemAPIDispatcher &&
           GetCacheInfo != 0,
           "Funtion was called and couldn't be dispatched");
    return GetCacheInfo(Info, Index);
}

RF_Type::Int32 GetCacheCount_SystemAPIDispatcher()
{
    GetCacheCount = 0;
    Dispatch();
    RF_ASSERT(GetCacheCount != GetCacheCount_SystemAPIDispatcher &&
           GetCacheCount != 0,
           "Funtion was called and couldn't be dispatched");
    return GetCacheCount();
}

RF_Type::Bool GetLogicalProcessorFeatures_SystemAPIDispatcher(ProcessorFeatureMask& Features)
{
    GetLogicalProcessorFeatures = 0;
    Dispatch();
    RF_ASSERT(GetLogicalProcessorFeatures != GetLogicalProcessorFeatures_SystemAPIDispatcher &&
           GetLogicalProcessorFeatures != 0,
           "Funtion was called and couldn't be dispatched");
    return GetLogicalProcessorFeatures(Features);
}

RF_Type::Size GetPhysicalMemorySize_SystemAPIDispatcher()
{
    GetPhysicalMemorySize = 0;
    Dispatch();
    RF_ASSERT(GetPhysicalMemorySize != GetPhysicalMemorySize_SystemAPIDispatcher &&
           GetPhysicalMemorySize != 0,
           "Funtion was called and couldn't be dispatched");
    return GetPhysicalMemorySize();
}

RF_Type::Size GetFreePhysicalMemorySize_SystemAPIDispatcher()
{
    GetFreePhysicalMemorySize = 0;
    Dispatch();
    RF_ASSERT(GetFreePhysicalMemorySize != GetFreePhysicalMemorySize_SystemAPIDispatcher &&
        GetFreePhysicalMemorySize != 0,
        "Funtion was called and couldn't be dispatched");
    return GetFreePhysicalMemorySize();
}

GetAvailableLogicalProcessorCountCallback GetAvailableLogicalProcessorCount = GetAvailableLogicalProcessorCount_SystemAPIDispatcher;
GetCurrentProcessorNumberCallback GetCurrentProcessorNumber = GetCurrentProcessorNumber_SystemAPIDispatcher;
GetCurrentUniqueProcessorNumberCallback GetCurrentUniqueProcessorNumber = GetCurrentUniqueProcessorNumber_SystemAPIDispatcher;
GetCacheInfoCallback GetCacheInfo = GetCacheInfo_SystemAPIDispatcher;
GetCacheCountCallback GetCacheCount = GetCacheCount_SystemAPIDispatcher;
GetLogicalProcessorFeaturesCallback GetLogicalProcessorFeatures = GetLogicalProcessorFeatures_SystemAPIDispatcher;
GetPhysicalMemorySizeCallback GetPhysicalMemorySize = GetPhysicalMemorySize_SystemAPIDispatcher;
GetFreePhysicalMemorySizeCallback GetFreePhysicalMemorySize = GetFreePhysicalMemorySize_SystemAPIDispatcher;

RF_Type::Bool IsSuccessfullyDispatched()
{
    RF_Type::Bool result = true;
    result = result && GetAvailableLogicalProcessorCount != GetAvailableLogicalProcessorCount_SystemAPIDispatcher && GetAvailableLogicalProcessorCount != 0;
    result = result && GetCurrentProcessorNumber != GetCurrentProcessorNumber_SystemAPIDispatcher && GetCurrentProcessorNumber != 0;
    result = result && GetCurrentUniqueProcessorNumber != GetCurrentUniqueProcessorNumber_SystemAPIDispatcher && GetCurrentUniqueProcessorNumber != 0;
    result = result && GetCacheInfo != GetCacheInfo_SystemAPIDispatcher && GetCacheInfo != 0;
    result = result && GetCacheCount != GetCacheCount_SystemAPIDispatcher && GetCacheCount != 0;
    result = result && GetLogicalProcessorFeatures != GetLogicalProcessorFeatures_SystemAPIDispatcher && GetLogicalProcessorFeatures != 0;
    result = result && GetPhysicalMemorySize != GetPhysicalMemorySize_SystemAPIDispatcher && GetPhysicalMemorySize != 0;
    result = result && GetFreePhysicalMemorySize != GetFreePhysicalMemorySize_SystemAPIDispatcher && GetFreePhysicalMemorySize != 0;
    result = result && IsVec128IntSuccessfullyDispatched();
    return result;
}

void GetNotDispatchedFunctions( List<RF_Type::String>& Result )
{
    if (GetAvailableLogicalProcessorCount == GetAvailableLogicalProcessorCount_SystemAPIDispatcher || GetAvailableLogicalProcessorCount == 0) 
        Result.AddLast("GetAvailableLogicalProcessorCount"_rfs);
    if (GetCurrentProcessorNumber == GetCurrentProcessorNumber_SystemAPIDispatcher || GetCurrentProcessorNumber == 0) 
        Result.AddLast("GetCurrentProcessorNumber"_rfs);
    if(GetCurrentUniqueProcessorNumber == GetCurrentUniqueProcessorNumber_SystemAPIDispatcher || GetCurrentUniqueProcessorNumber == 0)
        Result.AddLast("GetCurrentUniqueProcessorNumber"_rfs);
    if (GetCacheInfo == GetCacheInfo_SystemAPIDispatcher || GetCacheInfo == 0) 
        Result.AddLast("GetCacheInfo"_rfs);
    if (GetCacheCount == GetCacheCount_SystemAPIDispatcher || GetCacheCount == 0) 
        Result.AddLast("GetCacheCount"_rfs);
    if (GetLogicalProcessorFeatures == GetLogicalProcessorFeatures_SystemAPIDispatcher || GetLogicalProcessorFeatures == 0) 
        Result.AddLast("GetLogicalProcessorFeatures"_rfs);
    if(GetPhysicalMemorySize == GetPhysicalMemorySize_SystemAPIDispatcher || GetPhysicalMemorySize == 0)
        Result.AddLast("GetPhysicalMemorySize"_rfs);
    if(GetFreePhysicalMemorySize == GetFreePhysicalMemorySize_SystemAPIDispatcher || GetFreePhysicalMemorySize == 0)
        Result.AddLast("GetFreePhysicalMemorySize"_rfs);
    GetNotDispatchedVec128IntFunctions(Result);
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
        if(L1Data.Level == 0)
        {
            L1Data.Associativity = CacheAssociativity::Unknown;
            L1Data.Level = 1;
            L1Data.LineCount = 512;
            L1Data.LineSize = 64;
            L1Data.Size = 32768;
            L1Data.UsedAs = CacheUseCase::Data;
        }

        if(L2Data.Level == 0)
        {
            L2Data.Associativity = CacheAssociativity::Unknown;
            L2Data.Level = 2;
            L2Data.LineCount = 4096;
            L2Data.LineSize = 64;
            L2Data.Size = 262144;
            L2Data.UsedAs = CacheUseCase::Data;
        }

        if(L1Instruction.Level == 0)
        {
            L1Data.Associativity = CacheAssociativity::Unknown;
            L1Data.Level = 1;
            L1Data.LineCount = 512;
            L1Data.LineSize = 64;
            L1Data.Size = 32768;
            L1Data.UsedAs = CacheUseCase::Code;
        }
    }
    CacheInfo L1Data;
    CacheInfo L2Data;
    CacheInfo L1Instruction;
} SharedCacheInfo = {0};

CacheInfo& GetLevel1DataCache()
{
    if(SharedCacheInfo.L1Data.Level == 0)
    {
        SharedCacheInfo.InitData();
    }
    return SharedCacheInfo.L1Data;
}

CacheInfo& GetLevel1InstructionCache()
{
    if(SharedCacheInfo.L1Instruction.Level == 0)
    {
        SharedCacheInfo.InitData();
    }
    return SharedCacheInfo.L1Instruction;
}

CacheInfo& GetLevel2DataCache()
{
    if(SharedCacheInfo.L2Data.Level == 0)
    {
        SharedCacheInfo.InitData();
    }
    return SharedCacheInfo.L2Data;
}

}