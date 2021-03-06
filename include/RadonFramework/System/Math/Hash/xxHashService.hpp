#ifndef RF_SYSTEM_MATH_HASH_XXHASHSERVICE_HPP
#define RF_SYSTEM_MATH_HASH_XXHASHSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Math/Hash/HashfunctionService.hpp>

namespace RadonFramework::System::Math::Hash
{
class xxHash32HashfunctionService : public RF_Hash::HashfunctionService
{
public:
  xxHash32HashfunctionService(const RF_Type::String& Name);
  RF_Hash::IHashfunction* Create() override;
  void Free(RF_Hash::IHashfunction*& Instance) override;
  RF_Type::Size BitLength() const override;
};

class xxHash64HashfunctionService : public RF_Hash::HashfunctionService
{
public:
  xxHash64HashfunctionService(const RF_Type::String& Name);
  RF_Hash::IHashfunction* Create() override;
  void Free(RF_Hash::IHashfunction*& Instance) override;
  RF_Type::Size BitLength() const override;
};

}  // namespace RadonFramework::System::Math::Hash

#ifndef RF_SHORTHAND_NAMESPACE_SYSHASH
#define RF_SHORTHAND_NAMESPACE_SYSHASH
namespace RF_SysHash = RadonFramework::System::Math::Hash;
#endif  // RF_SHORTHAND_NAMESPACE_SYSHASH

#endif  //! RF_SYSTEM_MATH_HASH_XXHASHSERVICE_HPP