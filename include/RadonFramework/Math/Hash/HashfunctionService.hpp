#ifndef RF_MATH_HASH_HASHFUNCTIONSERVICE_HPP
#define RF_MATH_HASH_HASHFUNCTIONSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>

namespace RadonFramework::Math::Hash
{
// forward declaration
class IHashfunction;

class HashfunctionService : public Core::Pattern::Service
{
public:
  HashfunctionService(const RF_Type::String& Name);
  ~HashfunctionService() override;
  virtual IHashfunction* Create() = 0;
  virtual void Free(IHashfunction*& Instance) = 0;
  virtual RF_Type::Size BitLength() const = 0;
};

}  // namespace RadonFramework::Math::Hash

#ifndef RF_SHORTHAND_NAMESPACE_HASH
#define RF_SHORTHAND_NAMESPACE_HASH
namespace RF_Hash = RadonFramework::Math::Hash;
#endif

#endif  // RF_MATH_HASH_HASHFUNCTIONSERVICE_HPP
