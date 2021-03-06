#ifndef RF_SYSTEM_HARDWARE_CACHEINFO_HPP
#define RF_SYSTEM_HARDWARE_CACHEINFO_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/System/CompilerConfig.hpp>

namespace RadonFramework::System::Hardware
{
enum class CacheAssociativity : RF_Type::UInt8
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

enum class CacheUseCase : RF_Type::UInt8
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

struct RF_ALIGN(16) CacheInfo
{
  /// Cache size.
  RF_Type::UInt32 Size;
  /// Cache line count.
  RF_Type::UInt32 LineCount;
  /// Cache line size in bytes.
  RF_Type::UInt32 LineSize;
  /// Determine the cache level.
  RF_Type::UInt8 Level;
  /// How does the cache will by filled.
  CacheAssociativity Associativity;
  /// Describe the purpose of how the cache is used.
  CacheUseCase UsedAs;
  /// This field is currently used as padding to speed up processing.
  RF_Type::UInt8 ReservedPadding;
};
static_assert(sizeof(CacheInfo) == 16,
              "RF relies on that CacheInfo is 16 bytes large.");

}  // namespace RadonFramework::System::Hardware

#endif  // RF_SYSTEM_HARDWARE_CACHEINFO_HPP