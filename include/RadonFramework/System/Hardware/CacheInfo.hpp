#ifndef RF_SYSTEM_HARDWARE_CACHEINFO_HPP
#define RF_SYSTEM_HARDWARE_CACHEINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace System { namespace Hardware {

namespace CacheAssociativity
{
    enum Type : RFTYPE::UInt8
    {
        Unknown,
        _2WaySetAssociative,
        _4WaySetAssociative,
        _6WaySetAssociative,
        _8WaySetAssociative,
        _12WaySetAssociative,
        _16WaySetAssociative,
        _24WaySetAssociative,
        FullyAssociative,
        Other
    };
}

namespace CacheUseCase
{
    enum Type : RFTYPE::UInt8
    {
        Unknown,
        Data,
        Code,
        CodeAndData,
        CodeTLB,
        DataTLB,
        CodeAndDataTLB,
        Other
    };
}

struct ALIGN(16) CacheInfo
{
    /// Cache size.
    RFTYPE::UInt32 Size;
    /// Cache line count.
    RFTYPE::UInt32 LineCount;
    /// Cache line size in bytes.
    RFTYPE::UInt32 LineSize;
    /// Determine the cache level.
    RFTYPE::UInt8 Level;
    /// How does the cache will by filled.
    CacheAssociativity::Type Associativity;
    /// Describe the purpose of how the cache is used.
    CacheUseCase::Type UsedAs;
    /// This field is currently used as padding to speed up processing.
    RFTYPE::UInt8 ReservedPadding;
};
static_assert(sizeof(CacheInfo) == 16, "RF relies on that CacheInfo is 16 bytes large.");

} } }

#endif // RF_SYSTEM_HARDWARE_CACHEINFO_HPP