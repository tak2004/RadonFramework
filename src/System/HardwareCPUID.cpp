#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware.hpp"
#include "RadonFramework/System/Hardware/CacheInfo.hpp"
/*
void cpuid(RFTYPE::Int32 code, RFTYPE::UInt32 registers[4]);
{
    __cpuid(reinterpret_cast<int*>(registers),code);
}

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

void DecodeCacheInfo(RFHDW::CacheInfo& CacheInfo, RFTYPE::UInt32 reg)
{
    reg &= 0xff;

    // Cache Size
    switch (reg)
    {
        case 0x01: case 0x03: case 0x4f: case 0x57: case 0x59: case 0x61: case 0xa0:
        case 0xb0: case 0xb2: case 0xb3: case 0xb4: case 0xb5: case 0xb6: case 0xba:
        case 0xca:
            CacheInfo.Size = 4;
            break;

        case 0x06: case 0x0a: case 0x66:
            CacheInfo.Size = 8;
            break;

        case 0x08: case 0x0c: case 0x0d: case 0x10: case 0x15: case 0x60: case 0x67:
        case 0x77:
            CacheInfo.Size = 16;
            break;

        case 0x0e:
            CacheInfo.Size = 24;
            break;

        case 0x09: case 0x2c: case 0x30: case 0x68:
            CacheInfo.Size = 32;
            break;

        case 0xd0:
            CacheInfo.Size = 64;
            break;

        case 0x1a:
            CacheInfo.Size = 96;
            break;

        case 0x1d: case 0xd9: case 0x3b: case 0x41: case 0x79: case 0x81: case 0xd1:
        case 0xd6:
            CacheInfo.Size = 128;
            break;

        case 0x3a: case 0xdc:
            CacheInfo.Size = 192;
            break;

        case 0x21: case 0x3c: case 0x42: case 0x7a: case 0x7e: case 0x82: case 0xd2:
        case 0xd7: case 0xe2:
            CacheInfo.Size = 256;
            break;

        case 0x3d: case 0xdd:
            CacheInfo.Size = 384;
            break;

        case 0x22: case 0x3e: case 0x43: case 0x7b: case 0x7f: case 0x80: case 0x83:
        case 0x86: case 0xd8: case 0xe3:
            CacheInfo.Size = 512;
            break;

        case 0xde:
            CacheInfo.Size = 768;
            break;

        case 0x23: case 0x24: case 0x44: case 0x78: case 0x7c: case 0x84: case 0x87:
        case 0xe4:
            CacheInfo.Size = 1024;
            break;

        case 0xea:
            CacheInfo.Size = 1536;
            break;

        case 0x25: case 0x45: case 0x7d: case 0x85: case 0x88:
            CacheInfo.Size = 2048;
            break;

        case 0xeb:
            CacheInfo.Size = 2304;
            break;

        case 0x48: case 0x8d: case 0xec:
            CacheInfo.Size = 3072;
            break;

        case 0x02: case 0x04: case 0x05: case 0x0b: case 0x55: case 0x56: case 0x5a:
        case 0x5b: case 0x5c: case 0x5d: case 0x76: case 0xb1: case 0xc0: case 0xc2:
        case 0x29: case 0x46: case 0x49: case 0x89:
            CacheInfo.Size = 4096;
            break;

        case 0x4a: case 0x4e:
            CacheInfo.Size = 6144;
            break;

        case 0x47: case 0x4b: case 0x8a:
            CacheInfo.Size = 8192;
            break;

        case 0x4c:
            CacheInfo.Size = 12288;
            break;

        case 0x4d:
            CacheInfo.Size = 16384;
            break;

        case 0x63:
            CacheInfo.Size = 1048576;
            break;
        
        default:
            CacheInfo.Size = 0;
            break;
    }

    // Cache line count and size
    switch (reg)
    {
        case 0x02:
            CacheInfo.LineCount = 2;
            break;

        case 0x0b: case 0x63: case 0xb1:
            CacheInfo.LineCount = 4;
            break;

        case 0x55:
            CacheInfo.LineCount = 7;
            break;

        case 0x04: case 0x76: case 0xc0:
            CacheInfo.LineCount = 8;
            break;

        case 0x56: case 0x57: case 0x59: case 0xc2:
            CacheInfo.LineCount = 16;
            break;

        case 0x01: case 0x05: case 0x4f: case 0x5a: case 0x96: case 0xa0:
            CacheInfo.LineCount = 32;
            break;

        case 0x61:
            CacheInfo.LineCount = 48;
            break;

        case 0x03: case 0x50: case 0x5b: case 0x90: case 0xb2: case 0xb5: case 0xba:
            CacheInfo.LineCount = 64;
            break;

        case 0x51: case 0x5c: case 0xb0: case 0xb3: case 0xb6:
            CacheInfo.LineCount = 128;
            break;

        case 0x52: case 0x5d: case 0xb4:
            CacheInfo.LineCount = 256;
            break;

        case 0xca:
            CacheInfo.LineCount = 512;
            break;

        case 0xc1:
            CacheInfo.LineCount = 1024;
            break;

        case 0x06: case 0x08: case 0x0a: case 0x0c: case 0x10: case 0x15: case 0x41:
        case 0x42: case 0x43: case 0x44: case 0x45: case 0x81: case 0x82: case 0x83:
        case 0x84: case 0x85:
            CacheInfo.LineSize = 32;
            break;

        case 0x09: case 0x0d: case 0x0e: case 0x1a: case 0x1d: case 0x21: case 0x22:
        case 0x23: case 0x24: case 0x25: case 0x29: case 0x2c: case 0x30: case 0x39:
        case 0x3a: case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x46: case 0x47:
        case 0x48: case 0x49: case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4e:
        case 0x60: case 0x66: case 0x67: case 0x68: case 0x77: case 0x78: case 0x79:
        case 0x7a: case 0x7b: case 0x7c: case 0x7d: case 0x7f: case 0x80: case 0x86:
        case 0x87: case 0x88: case 0x89: case 0x8a: case 0xd0: case 0xd1: case 0xd2:
        case 0xd6: case 0xd7: case 0xd8: case 0xdc: case 0xdd: case 0xde: case 0xe2:
        case 0xe3: case 0xe4: case 0xea: case 0xeb: case 0xec:
            CacheInfo.LineSize = 64;
            break;

        case 0x7e: case 0x8d:
            CacheInfo.LineSize = 128;
            break;

        default:
            CacheInfo.LineCount = 0;
            CacheInfo.LineSize = 0;
            break;
    }

    // Cache level
    switch (reg)
    {
        case 0x06: case 0x08: case 0x09: case 0x0a: case 0x0c: case 0x0d: case 0x0e:
        case 0x10: case 0x15: case 0x2c: case 0x30: case 0x60: case 0x66: case 0x67:
        case 0x68: case 0x70: case 0x71: case 0x72: case 0x73: case 0x77: case 0x96:
            CacheInfo.Level = 1;
            break;

        case 0x1a: case 0x1d: case 0x21: case 0x24: case 0x39: case 0x3a: case 0x3b:
        case 0x3c: case 0x3d: case 0x3e: case 0x41: case 0x42: case 0x43: case 0x44:
        case 0x45: case 0x48: case 0x49: case 0x4e: case 0x78: case 0x79: case 0x7a:
        case 0x7b: case 0x7c: case 0x7d: case 0x7e: case 0x7f: case 0x80: case 0x81:
        case 0x82: case 0x83: case 0x84: case 0x85: case 0x86: case 0x87: case 0x9b:
        case 0xc1: case 0xca:
            CacheInfo.Level = 2;
            break;

        case 0x22: case 0x23: case 0x25: case 0x29: case 0x46: case 0x47: case 0x4a:
        case 0x4b: case 0x4c: case 0x4d: case 0x88: case 0x89: case 0x8a: case 0x8d:
        case 0xd0: case 0xd1: case 0xd2: case 0xd6: case 0xd7: case 0xd8: case 0xdc:
        case 0xdd: case 0xde: case 0xe2: case 0xe3: case 0xe4: case 0xea: case 0xeb:
        case 0xec:
            CacheInfo.Level = 3;
            break;

        default:
            CacheInfo.Level = 0;
    }

    // Cache associativity
    switch (reg)
    {
        case 0x0a: case 0x1d: case 0x3b: case 0x7f:
            CacheInfo.Associativity = RFHDW::CacheAssociativity::_2WaySetAssociative;
            break;

        case 0x01: case 0x03: case 0x04: case 0x05: case 0x06: case 0x08: case 0x09:
        case 0x0b: case 0x0c: case 0x0d: case 0x10: case 0x15: case 0x22: case 0x39:
        case 0x3c: case 0x3e: case 0x41: case 0x42: case 0x43: case 0x44: case 0x45:
        case 0x46: case 0x56: case 0x57: case 0x5a: case 0x66: case 0x67: case 0x68:
        case 0x77: case 0x78: case 0x86: case 0x88: case 0x89: case 0x8a: case 0xb0:
        case 0xb1: case 0xb2: case 0xb3: case 0xb4: case 0xba: case 0xc0: case 0xc2:
        case 0xca: case 0xd0: case 0xd1: case 0xd2:
            CacheInfo.Associativity = RFHDW::CacheAssociativity::_4WaySetAssociative;
            break;

        case 0x0e: case 0x1a: case 0x3a: case 0x3d:
            CacheInfo.Associativity = RFHDW::CacheAssociativity::_6WaySetAssociative;
            break;

        case 0x21: case 0x23: case 0x25: case 0x29: case 0x2c: case 0x30: case 0x47:
        case 0x60: case 0x70: case 0x71: case 0x72: case 0x73: case 0x79: case 0x7a:
        case 0x7b: case 0x7c: case 0x7d: case 0x7e: case 0x80: case 0x81: case 0x82:
        case 0x83: case 0x84: case 0x85: case 0x87: case 0xb5: case 0xb6: case 0xc1:
        case 0xd6: case 0xd7: case 0xd8:
            CacheInfo.Associativity = RFHDW::CacheAssociativity::_8WaySetAssociative;
            break;

        case 0x48: case 0x4a: case 0x4c: case 0x8d: case 0xdc: case 0xdd: case 0xde:
            CacheInfo.Associativity = RFHDW::CacheAssociativity::_12WaySetAssociative;
            break;

        case 0x24: case 0x49: case 0x4b: case 0x4d: case 0xe2: case 0xe3: case 0xe4:
            CacheInfo.Associativity = RFHDW::CacheAssociativity::_16WaySetAssociative;
            break;

        case 0x4e: case 0xea: case 0xeb: case 0xec:
            CacheInfo.Associativity = RFHDW::CacheAssociativity::_24WaySetAssociative;
            break;

        case 0x02: case 0x50: case 0x51: case 0x52: case 0x55: case 0x59: case 0x5b:
        case 0x5c: case 0x5d: case 0x61: case 0x76: case 0x90: case 0x96: case 0x9b:
        case 0xa0:
            CacheInfo.Associativity = RFHDW::CacheAssociativity::FullyAssociative;
            break;

        default:
            CacheInfo.Associativity = RFHDW::CacheAssociativity::Other;
    }

    switch (reg)
    {
//        CacheInfo.UsedAs
    }

    CacheInfo.LineCount = CacheInfo.Size / CacheInfo.LineSize;
}

RFTYPE::Int32 GetCacheCount();

// Util function: use it only for internal purpose
inline void DetectCacheInfo(AutoPointerArray<RFHDW::CacheInfo>& CacheData)
{
    RFTYPE::Int32 count = ::GetCacheCount();
    CacheData = AutoPointerArray<RFHDW::CacheInfo>(new RFHDW::CacheInfo[count], count);

    RFTYPE::UInt32 reg[4]={0,0,0,0};

    // Duff device
    {
        RFTYPE::Size i = (count + 15) >> 4;
        for (; i > 0; --i)
        {
            cpuid(2, reg);
            switch (count % 16)
            {
                case 0: DecodeCacheInfo(CacheData[i+3], reg[3] >> 24);
                case 15: DecodeCacheInfo(CacheData[i+3], reg[3] >> 16);
                case 14: DecodeCacheInfo(CacheData[i+3], reg[3] >> 8);
                case 13: DecodeCacheInfo(CacheData[i+3], reg[3]);
                case 12: DecodeCacheInfo(CacheData[i+2], reg[2] >> 24);
                case 11: DecodeCacheInfo(CacheData[i+2], reg[2] >> 16);
                case 10: DecodeCacheInfo(CacheData[i+2], reg[2] >> 8);
                case 9: DecodeCacheInfo(CacheData[i+2], reg[2]);
                case 8: DecodeCacheInfo(CacheData[i+1], reg[1] >> 24);
                case 7: DecodeCacheInfo(CacheData[i+1], reg[1] >> 16);
                case 6: DecodeCacheInfo(CacheData[i+1], reg[1] >> 8);
                case 5: DecodeCacheInfo(CacheData[i+1], reg[1]);
                case 4: DecodeCacheInfo(CacheData[i], reg[0] >> 24);
                case 3: DecodeCacheInfo(CacheData[i], reg[0] >> 16);
                case 2: DecodeCacheInfo(CacheData[i], reg[0] >> 8);
                case 1: DecodeCacheInfo(CacheData[i], reg[0]);
            }
        }
    }
}

// Util function: use it only for internal purpose
RFTYPE::Int32 DetectCacheCount()
{
    static const RFTYPE::UInt32 BITSHIFT_IS_CACHE_DATA_SET = 29;
    RFTYPE::Int32 result = 0;
    RFTYPE::UInt32 reg[4]={0,0,0,0};
    cpuid(1, reg);
    RFTYPE::Size entries = reg[0] & 0xff;
    for (RFTYPE::Size i = 0; i < entries; ++i)
    {
        cpuid(1, reg);
        // If highest bit of a register is 0 then it contains 4 cache entries.
        // Negate all bits to get 1 instead of 0 at highest bit, shift by 29 bits
        // and use bitwise AND with 4 to get 0 or 4.
        result += (~reg[0] >> BITSHIFT_IS_CACHE_DATA_SET) & 0x4;
        result += (~reg[1] >> BITSHIFT_IS_CACHE_DATA_SET) & 0x4;
        result += (~reg[2] >> BITSHIFT_IS_CACHE_DATA_SET) & 0x4;
        result += (~reg[3] >> BITSHIFT_IS_CACHE_DATA_SET) & 0x4;
    }
    return result;
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
            DWORD buffer_size = 0;
            GetLogicalProcessorInformation(0, &buffer_size);
            CacheCount[pid] = buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
        }
    }
    else
    {
        RFTYPE::UInt32 LPCount = ::GetAvailableLogicalProcessorCount();
        typedef Singleton<AutoPointerArray<RFTYPE::Int32> > GlobalCacheCount;
        AutoPointerArray<RFTYPE::Int32>& cacheCount = GlobalCacheCount::GetInstance();
        cacheCount = AutoPointerArray<RFTYPE::Int32>(new RFTYPE::Int32[LPCount], LPCount);

        for (RFTYPE::Size i = 0; i < LPCount; ++i)
        {
            cacheCount[i] = -1;
        }

        DWORD buffer_size = 0;
        GetLogicalProcessorInformation(0, &buffer_size);
        cacheCount[pid] = buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
        CacheCount = cacheCount.Get();
    }
    result = CacheCount[pid];
    return result;
}
*/
void RFHDW::Dispatch()
{

}