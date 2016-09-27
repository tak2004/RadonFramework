#ifndef RF_HASHLIBHASHFUNCTIONSERVICE_HPP
#define RF_HASHLIBHASHFUNCTIONSERVICE_HPP

#include <RadonFramework/Math/Hash/HashfunctionService.hpp>

namespace RadonFramework { namespace Math { namespace Hash {

class HashlibMD5HashfunctionService:public HashfunctionService
{
public:
    HashlibMD5HashfunctionService(const Core::Types::String &Name);
    virtual IHashfunction* Create() override;
    virtual void Free(IHashfunction*& Instance) override;
    virtual RF_Type::Size BitLength() const override;
};

class HashlibSHA1HashfunctionService:public HashfunctionService
{
public:
    HashlibSHA1HashfunctionService(const Core::Types::String &Name);
    virtual IHashfunction* Create()override;
    virtual void Free(IHashfunction*& Instance) override;
    virtual RF_Type::Size BitLength() const override;
};

class HashlibSHA256HashfunctionService:public HashfunctionService
{
public:
    HashlibSHA256HashfunctionService(const Core::Types::String &Name);
    virtual IHashfunction* Create()override;
    virtual void Free(IHashfunction*& Instance) override;
    virtual RF_Type::Size BitLength() const override;
};

class HashlibSHA384HashfunctionService:public HashfunctionService
{
public:
    HashlibSHA384HashfunctionService(const Core::Types::String &Name);
    virtual IHashfunction* Create()override;
    virtual void Free(IHashfunction*& Instance) override;
    virtual RF_Type::Size BitLength() const override;
};

class HashlibSHA512HashfunctionService:public HashfunctionService
{
public:
    HashlibSHA512HashfunctionService(const Core::Types::String &Name);
    virtual IHashfunction* Create()override;
    virtual void Free(IHashfunction*& Instance) override;
    virtual RF_Type::Size BitLength() const override;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_HASH
#define RF_SHORTHAND_NAMESPACE_HASH
namespace RF_Hash = RadonFramework::Math::Hash;
#endif

#endif
