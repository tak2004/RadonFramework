#ifndef RF_MATH_HASH_HASHFUNCTION_HPP
#define RF_MATH_HASH_HASHFUNCTION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Math::Hash
{
class IHashfunction
{
public:
  virtual ~IHashfunction() = default;
  virtual void Reset() = 0;
  virtual void Update(RF_Type::UInt8 Input) = 0;
  virtual void Update(const RF_Type::UInt8* Data, RF_Type::UInt32 Size) = 0;
  virtual void Final() = 0;
  virtual RF_Type::String ToString() = 0;
  virtual RF_Type::UInt32 GetDigestLength() = 0;
  virtual RF_Type::UInt8* Digest() = 0;
};

}  // namespace RadonFramework::Math::Hash

#ifndef RF_SHORTHAND_NAMESPACE_HASH
#define RF_SHORTHAND_NAMESPACE_HASH
namespace RF_Hash = RadonFramework::Math::Hash;
#endif

#endif  // RF_MATH_HASH_HASHFUNCTION_HPP
