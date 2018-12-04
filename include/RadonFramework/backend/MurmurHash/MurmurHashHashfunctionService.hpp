#ifndef RF_MURMURHASHHASHFUNCTIONSERVICE_HPP
#define RF_MURMURHASHHASHFUNCTIONSERVICE_HPP

#include <RadonFramework/Math/Hash/HashfunctionService.hpp>

namespace RadonFramework::Math::Hash
{
class MurmurHashHashfunctionService : public HashfunctionService
{
public:
  MurmurHashHashfunctionService(const Core::Types::String& Name);
  IHashfunction* Create() final;
  void Free(IHashfunction*& Instance) final;
  RF_Type::Size BitLength() const final;
};

}  // namespace RadonFramework::Math::Hash

#endif
