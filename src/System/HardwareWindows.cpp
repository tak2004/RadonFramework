#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware.hpp"
#include "RadonFramework/System/Hardware/CacheInfo.hpp"
#include "RadonFramework/System/Hardware/ProcessorFeatures.hpp"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace RadonFramework;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Collections;

RFTYPE::UInt32 GetAvailableLogicalProcessorCount()
{
    static RFTYPE::UInt32 NumberOfProcessors = 0;
    RFTYPE::UInt32 result;
    if (NumberOfProcessors > 0)
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

RFTYPE::UInt32 GetCurrentProcessorNumberImplementation()
{
    RFTYPE::UInt32 result;
    result = GetCurrentProcessorNumber();
    return result;
}

// Util function: use it only for internal purpose
void DetectCacheInfo(AutoPointerArray<RFHDW::CacheInfo>& CacheDataList, RFTYPE::Int32 PId)
{
    
    DWORD buffer_size = 0;
    GetLogicalProcessorInformation(0, &buffer_size);
    RFTYPE::Int32 count = buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer = new SYSTEM_LOGICAL_PROCESSOR_INFORMATION[count];
    GetLogicalProcessorInformation(&buffer[0], &buffer_size);

    RFTYPE::Int32 CacheCount = 0;
    for (RFTYPE::Size i = 0; i != count; ++i)
    {
        if (buffer[i].Relationship == RelationCache && buffer[i].ProcessorMask & PId == PId)
        {
            ++CacheCount;
        }
    }

    CacheDataList = AutoPointerArray<RFHDW::CacheInfo>(new RFHDW::CacheInfo[CacheCount], CacheCount);
    for (RFTYPE::Size i = 0, j = 0; i < count; ++i)
    {
        if (buffer[i].Relationship == RelationCache && buffer[i].ProcessorMask & PId == PId)
        {
            CacheDataList[j].Size = buffer[i].Cache.Size;
            if (buffer[i].Cache.LineSize > 0)
            {
                CacheDataList[j].LineCount = buffer[i].Cache.Size / buffer[i].Cache.LineSize;
            }
            CacheDataList[j].LineSize = buffer[i].Cache.LineSize;
            CacheDataList[j].Level = buffer[i].Cache.Level;
            switch (buffer[i].Cache.Associativity)
            {
                case 2:
                    CacheDataList[j].Associativity = RFHDW::CacheAssociativity::_2WaySetAssociative;
                    break;
                case 4:
                    CacheDataList[j].Associativity = RFHDW::CacheAssociativity::_4WaySetAssociative;
                    break;
                case 6:
                    CacheDataList[j].Associativity = RFHDW::CacheAssociativity::_6WaySetAssociative;
                    break;
                case 8:
                    CacheDataList[j].Associativity = RFHDW::CacheAssociativity::_8WaySetAssociative;
                    break;
                case 12:
                    CacheDataList[j].Associativity = RFHDW::CacheAssociativity::_12WaySetAssociative;
                    break;
                case 16:
                    CacheDataList[j].Associativity = RFHDW::CacheAssociativity::_16WaySetAssociative;
                    break;
                case 24:
                    CacheDataList[j].Associativity = RFHDW::CacheAssociativity::_24WaySetAssociative;
                    break;
                case 255:
                    CacheDataList[j].Associativity = RFHDW::CacheAssociativity::FullyAssociative;
                    break;
                default:
                    CacheDataList[j].Associativity = RFHDW::CacheAssociativity::Other;
                    break;
            }
            switch (buffer[i].Cache.Type)
            {
                case CacheUnified:
                    CacheDataList[j].UsedAs = RFHDW::CacheUseCase::CodeAndData;
                    break;
                case CacheData:
                    CacheDataList[j].UsedAs = RFHDW::CacheUseCase::Data;
                    break;
                case CacheInstruction:
                    CacheDataList[j].UsedAs = RFHDW::CacheUseCase::Data;
                    break;
                case CacheTrace:
                    CacheDataList[j].UsedAs = RFHDW::CacheUseCase::CodeAndDataTLB;
                    break;
                default:
                    CacheDataList[j].UsedAs = RFHDW::CacheUseCase::Other;
            }
            ++j;
        }
    }
    delete[] buffer;
}

RFTYPE::Bool GetCacheInfo(RFHDW::CacheInfo& Info, RFTYPE::UInt32 Index)
{
    static AutoPointerArray<RFHDW::CacheInfo>* CacheData = 0;
    typedef Singleton<AutoPointerArray<AutoPointerArray<RFHDW::CacheInfo> > > GlobalCacheData;

    RFTYPE::Bool result = false;
    RFTYPE::UInt32 pid = GetCurrentProcessorNumber();
    if (CacheData > 0)
    {
        if (CacheData[pid].Count() > Index)
        {
            RFMEM::Copy(&Info, &CacheData[pid][Index], sizeof(RFHDW::CacheInfo));
            result = true;
        }
        else
        {
            if (CacheData[pid].Count() == 0)
            {
                DetectCacheInfo(CacheData[pid], pid);
                RFMEM::Copy(&Info, &CacheData[pid][Index], sizeof(RFHDW::CacheInfo));
                result = true;
            }
        }
    }
    else
    {
        RFTYPE::UInt32 count = ::GetAvailableLogicalProcessorCount();
        AutoPointerArray<AutoPointerArray<RFHDW::CacheInfo> >& infos = GlobalCacheData::GetInstance();
        infos = AutoPointerArray<AutoPointerArray<RFHDW::CacheInfo> >(new AutoPointerArray<RFHDW::CacheInfo>[count], count);
        CacheData = infos.Get();

        DetectCacheInfo(CacheData[pid], pid);
        if (CacheData[pid].Count() > Index)
        {
            result = true;
            RFMEM::Copy(&Info, &CacheData[pid][Index], sizeof(RFHDW::CacheInfo));
        }
    }
    return result;
}

// Util function: use it only for internal purpose
RFTYPE::Int32 CacheCountFromLPInfo(RFTYPE::Int32 PId)
{
    DWORD buffer_size = 0;
    GetLogicalProcessorInformation(0, &buffer_size);
    RFTYPE::Int32 count = buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer = new SYSTEM_LOGICAL_PROCESSOR_INFORMATION[count];
    GetLogicalProcessorInformation(&buffer[0], &buffer_size);

    RFTYPE::Int32 cacheCount = 0;
    for (RFTYPE::Size i = 0; i != count; ++i)
    {
        if (buffer[i].Relationship == RelationCache && buffer[i].ProcessorMask & PId == PId)
        {
            ++cacheCount;
        }
    }
    delete[] buffer;
    return cacheCount;
}

RFTYPE::Int32 GetCacheCount()
{
    static RFTYPE::Int32* CacheCount = 0;

    RFTYPE::Int32 result = -1;
    RFTYPE::UInt32 pid = GetCurrentProcessorNumber();
    if (CacheCount > 0)
    {
        if (CacheCount[pid] > -1)
        {
        }
        else
        {
            CacheCount[pid] = CacheCountFromLPInfo(pid);
        }
    }
    else
    {
        RFTYPE::UInt32 LPCount = ::GetAvailableLogicalProcessorCount();
        typedef Singleton<AutoPointerArray<RFTYPE::Int32> > GlobalCacheCount;
        AutoPointerArray<RFTYPE::Int32>& cacheCountList = GlobalCacheCount::GetInstance();
        cacheCountList = AutoPointerArray<RFTYPE::Int32>(new RFTYPE::Int32[LPCount], LPCount);

        for (RFTYPE::Size i = 0; i < LPCount; ++i)
        {
            cacheCountList[i] = -1;
        }

        CacheCount = cacheCountList.Get();
        CacheCount[pid] = CacheCountFromLPInfo(pid);
    }
    result = CacheCount[pid];
    return result;
}

namespace RadonFramework { namespace System { namespace Hardware {

void DispatchWindows()
{
    GetAvailableLogicalProcessorCount = ::GetAvailableLogicalProcessorCount;
    GetCurrentProcessorNumber = ::GetCurrentProcessorNumberImplementation;
    GetCacheInfo = ::GetCacheInfo;
    GetCacheCount = ::GetCacheCount;
}

} } }