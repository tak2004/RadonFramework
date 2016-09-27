#ifndef RF_MURMURHASHHASHFUNCTIONSERVICE_HPP
#define RF_MURMURHASHHASHFUNCTIONSERVICE_HPP

#include <RadonFramework/Math/Hash/HashfunctionService.hpp>

namespace RadonFramework { namespace Math { namespace Hash {

class MurmurHashHashfunctionService:public HashfunctionService
{
public:
    MurmurHashHashfunctionService(const Core::Types::String &Name);
    virtual IHashfunction* Create() override;
    virtual void Free(IHashfunction*& Instance) override;
    virtual RF_Type::Size BitLength() const override;

};

} } }

#endif
