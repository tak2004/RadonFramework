#ifndef RF_CORE_TYPES_UUID_HPP
#define RF_CORE_TYPES_UUID_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/Vec128UInt.hpp>

namespace RadonFramework::Core::Types
{
/// UUID Version 5
struct alignas(16) UUID
{
  static UUID FastRandomUUID();
  static UUID SecureRandomUUID();
  static UUID UUIDFromString(const String& Text);

  static UUID NIL;
  static UUID DNS;
  static UUID URL;
  static UUID OID;
  static UUID X500;

  Bool IsNil() const;
  void Swap(UUID& Other);
  String ToString() const;
  Int32 CompareTo(const UUID& Other) const;

  union {
    Vec128UInt8 Bytes;
    struct
    {
      UInt32 TimeLow;
      UInt16 TimeMid;
      UInt16 TimeHiAndVersion;
      UInt8 ClockSeqHiAndReserved;
      UInt8 ClockSeqLow;
      UInt8 Node[6];
    } Structure;
  };
};

bool operator==(UUID const& lhs, UUID const& rhs);
bool operator!=(UUID const& lhs, UUID const& rhs);
bool operator<(UUID const& lhs, UUID const& rhs);
bool operator>(UUID const& lhs, UUID const& rhs);
bool operator<=(UUID const& lhs, UUID const& rhs);
bool operator>=(UUID const& lhs, UUID const& rhs);

}  // namespace RadonFramework::Core::Types

#ifndef RF_SHORTHAND_NAMESPACE_TYPES
#define RF_SHORTHAND_NAMESPACE_TYPES
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif  // RF_CORE_TYPES_UUID_HPP