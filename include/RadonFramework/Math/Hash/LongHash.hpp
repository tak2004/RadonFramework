#ifndef RF_MATH_HASH_LONGHASH_HPP
#define RF_MATH_HASH_LONGHASH_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Size.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework::Core::Types
{
class String;
}

namespace RadonFramework::Math::Hash
{
struct LongHash
{
public:
  void FromData(const RF_Type::UInt8* Data, const RF_Type::Size Size);
  void FromString(const RF_Type::String& Text);
  void FromMemory(const Memory::AutoPointerArray<RF_Type::UInt8>& Data);
  const RF_Mem::AutoPointerArray<RF_Type::UInt8>& GetHash() const;

private:
  Memory::AutoPointerArray<RF_Type::UInt8> m_Hash;
};

}  // namespace RadonFramework::Math::Hash

#ifndef RF_SHORTHAND_NAMESPACE_HASH
#define RF_SHORTHAND_NAMESPACE_HASH
namespace RF_Hash = RadonFramework::Math::Hash;
#endif

#endif  // RF_MATH_HASH_LONGHASH_HPP
