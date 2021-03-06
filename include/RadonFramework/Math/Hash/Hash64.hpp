#ifndef RF_MATH_HASH_HASH64_HPP
#define RF_MATH_HASH_HASH64_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Size.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>

namespace RadonFramework::Core::Types
{
class String;
}  // namespace RadonFramework::Core::Types
namespace RadonFramework::Memory
{
template <class T>
class AutoPointerArray;
}

namespace RadonFramework::Math::Hash
{
struct Hash64
{
public:
  void FromData(const RF_Type::UInt8* Data, const RF_Type::Size Size);
  void FromString(const RF_Type::String& Text);
  void FromMemory(const Memory::AutoPointerArray<RF_Type::UInt8>& Data);
  RF_Type::UInt64 GetHash() const;

private:
  RF_Type::UInt64 m_Hash;
};

}  // namespace RadonFramework::Math::Hash

#ifndef RF_SHORTHAND_NAMESPACE_HASH
#define RF_SHORTHAND_NAMESPACE_HASH
namespace RF_Hash = RadonFramework::Math::Hash;
#endif

#endif  // RF_MATH_HASH_HASH64_HPP
