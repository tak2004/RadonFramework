#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware/Hardware.hpp"
#include "RadonFramework/System/Hardware/CacheInfo.hpp"
#include "RadonFramework/System/Hardware/ProcessorFeatures.hpp"
#include "RadonFramework/Memory/AutoPointerArray.hpp"
#include "RadonFramework/Core/Pattern/Singleton.hpp"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace RadonFramework;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Collections;

namespace RadonFramework::System::Hardware::Windows {

RF_Type::UInt32 GetAvailableLogicalProcessorCount()
{
    static RF_Type::UInt32 NumberOfProcessors = 0;
    RF_Type::UInt32 result;
    if(NumberOfProcessors > 0)
    {
        result = NumberOfProcessors;
    }
    else
    {
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        result = sysInfo.dwNumberOfProcessors;
        NumberOfProcessors = sysInfo.dwNumberOfProcessors;
    }
    return result;
}

RF_Type::UInt32 GetCurrentProcessorNumber()
{
    RF_Type::UInt32 result;
    result = ::GetCurrentProcessorNumber();
    return result;
}

RF_Type::UInt32 GetCurrentUniqueProcessorNumber()
{
    static RF_Type::UInt32 MAX_GROUP_COUNT = 64;
    RF_Type::UInt32 result;
    PROCESSOR_NUMBER value;
    ::GetCurrentProcessorNumberEx(&value);
    result = value.Group * MAX_GROUP_COUNT + value.Number;
    return result;
}

// Util function: use it only for internal purpose
void DetectCacheInfo(AutoPointerArray<CacheInfo>& CacheDataList, RF_Type::Int32 PId)
{

    DWORD buffer_size = 0;
    GetLogicalProcessorInformation(0, &buffer_size);
    RF_Type::Int32 count = buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer = new SYSTEM_LOGICAL_PROCESSOR_INFORMATION[count];
    GetLogicalProcessorInformation(&buffer[0], &buffer_size);

    RF_Type::Int32 CacheCount = 0;
    for(RF_Type::Size i = 0; i != count; ++i)
    {
        if(buffer[i].Relationship == RelationCache && (buffer[i].ProcessorMask & PId) == PId)
        {
            ++CacheCount;
        }
    }

    CacheDataList = AutoPointerArray<CacheInfo>(CacheCount);
    for(RF_Type::Size i = 0, j = 0; i < count; ++i)
    {
        if(buffer[i].Relationship == RelationCache && (buffer[i].ProcessorMask & PId) == PId)
        {
            CacheDataList[j].Size = buffer[i].Cache.Size;
            if(buffer[i].Cache.LineSize > 0)
            {
                CacheDataList[j].LineCount = buffer[i].Cache.Size / buffer[i].Cache.LineSize;
            }
            CacheDataList[j].LineSize = buffer[i].Cache.LineSize;
            CacheDataList[j].Level = buffer[i].Cache.Level;
            switch(buffer[i].Cache.Associativity)
            {
            case 2:
                CacheDataList[j].Associativity = CacheAssociativity::_2WaySetAssociative;
                break;
            case 4:
                CacheDataList[j].Associativity = CacheAssociativity::_4WaySetAssociative;
                break;
            case 6:
                CacheDataList[j].Associativity = CacheAssociativity::_6WaySetAssociative;
                break;
            case 8:
                CacheDataList[j].Associativity = CacheAssociativity::_8WaySetAssociative;
                break;
            case 12:
                CacheDataList[j].Associativity = CacheAssociativity::_12WaySetAssociative;
                break;
            case 16:
                CacheDataList[j].Associativity = CacheAssociativity::_16WaySetAssociative;
                break;
            case 24:
                CacheDataList[j].Associativity = CacheAssociativity::_24WaySetAssociative;
                break;
            case 255:
                CacheDataList[j].Associativity = CacheAssociativity::FullyAssociative;
                break;
            default:
                CacheDataList[j].Associativity = CacheAssociativity::Other;
                break;
            }
            switch(buffer[i].Cache.Type)
            {
            case CacheUnified:
                CacheDataList[j].UsedAs = CacheUseCase::CodeAndData;
                break;
            case CacheData:
                CacheDataList[j].UsedAs = CacheUseCase::Data;
                break;
            case CacheInstruction:
                CacheDataList[j].UsedAs = CacheUseCase::Code;
                break;
            case CacheTrace:
                CacheDataList[j].UsedAs = CacheUseCase::CodeAndDataTLB;
                break;
            default:
                CacheDataList[j].UsedAs = CacheUseCase::Other;
            }
            ++j;
        }
    }
    delete[] buffer;
}

RF_Type::Bool GetCacheInfo(CacheInfo& Info, RF_Type::UInt32 Index)
{
    static AutoPointerArray<CacheInfo>* CacheData = 0;
    typedef RF_Pattern::Singleton<AutoPointerArray<AutoPointerArray<CacheInfo> > > GlobalCacheData;

    RF_Type::Bool result = false;
    RF_Type::UInt32 pid = GetCurrentProcessorNumber();
    if(CacheData)
    {
        if(CacheData[pid].Count() > Index)
        {
            RF_SysMem::Copy(&Info, &CacheData[pid][Index], sizeof(CacheInfo));
            result = true;
        }
    }
    else
    {
        RF_Type::UInt32 count = GetAvailableLogicalProcessorCount();
        AutoPointerArray<AutoPointerArray<CacheInfo> >& infos = GlobalCacheData::GetInstance();
        infos = AutoPointerArray<AutoPointerArray<CacheInfo> >(count);
        CacheData = infos.Get();

        DetectCacheInfo(CacheData[pid], pid);
        if(CacheData[pid].Count() > Index)
        {
            result = true;
            RF_SysMem::Copy(&Info, &CacheData[pid][Index], sizeof(CacheInfo));
        }
    }
    return result;
}

// Util function: use it only for internal purpose
RF_Type::Int32 CacheCountFromLPInfo(RF_Type::Int32 PId)
{
    DWORD buffer_size = 0;
    GetLogicalProcessorInformation(0, &buffer_size);
    RF_Type::Int32 count = buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer = new SYSTEM_LOGICAL_PROCESSOR_INFORMATION[count];
    GetLogicalProcessorInformation(&buffer[0], &buffer_size);

    RF_Type::Int32 cacheCount = 0;
    for(RF_Type::Size i = 0; i != count; ++i)
    {
        if(buffer[i].Relationship == RelationCache && (buffer[i].ProcessorMask & PId) == PId)
        {
            ++cacheCount;
        }
    }
    delete[] buffer;
    return cacheCount;
}

RF_Type::Int32 GetCacheCount()
{
    static RF_Type::Int32* CacheCount = 0;

    RF_Type::Int32 result = -1;
    RF_Type::UInt32 pid = GetCurrentProcessorNumber();
    if(CacheCount > 0)
    {
        if(CacheCount[pid] > -1)
        {
        }
        else
        {
            CacheCount[pid] = CacheCountFromLPInfo(pid);
        }
    }
    else
    {
        RF_Type::UInt32 LPCount = GetAvailableLogicalProcessorCount();
        typedef RF_Pattern::Singleton<AutoPointerArray<RF_Type::Int32> > GlobalCacheCount;
        AutoPointerArray<RF_Type::Int32>& cacheCountList = GlobalCacheCount::GetInstance();
        cacheCountList = AutoPointerArray<RF_Type::Int32>(LPCount);

        for(RF_Type::Size i = 0; i < LPCount; ++i)
        {
            cacheCountList[i] = -1;
        }

        CacheCount = cacheCountList.Get();
        CacheCount[pid] = CacheCountFromLPInfo(pid);
    }
    result = CacheCount[pid];
    return result;
}

RF_Type::Size GetPhysicalMemorySizeWindows()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    return memInfo.ullTotalPhys;
}

RF_Type::Size GetFreePhysicalMemorySizeWindows()
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    return memInfo.ullAvailPhys;
}

}

namespace RadonFramework::System::Hardware {

void Dispatch_Windows()
{
    GetAvailableLogicalProcessorCount = Windows::GetAvailableLogicalProcessorCount;
    GetCurrentProcessorNumber = Windows::GetCurrentProcessorNumber;
    GetCurrentUniqueProcessorNumber = Windows::GetCurrentUniqueProcessorNumber;
    GetCacheInfo = Windows::GetCacheInfo;
    GetCacheCount = Windows::GetCacheCount;
    GetPhysicalMemorySize = Windows::GetPhysicalMemorySizeWindows;
    GetFreePhysicalMemorySize = Windows::GetFreePhysicalMemorySizeWindows;
}

}