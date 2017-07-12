#ifndef RF_MATH_HASH_HASHFUNCTIONSERVICELOCATOR_HPP
#define RF_MATH_HASH_HASHFUNCTIONSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/Math/Hash/HashfunctionService.hpp>

namespace RadonFramework::Math::Hash {

class IHashfunction;

class NullHashfunctionService: public HashfunctionService
{
public:
    NullHashfunctionService(const RF_Type::String &Name);
    virtual IHashfunction* Create() override;
    virtual void Free(IHashfunction*& Instance) override;
    virtual RF_Type::Size BitLength()const override;
};

class HashfunctionServiceLocator: public RF_Pattern::Locator<HashfunctionService, NullHashfunctionService>
{
public:
    static HashfunctionService& Default64();
    static HashfunctionService& Default32();
    static void SetDefault64(const RF_Type::String& Name);
    static void SetDefault32(const RF_Type::String& Name);
    static void Remove(const RF_Type::String& Name);
private:
    static RF_Type::UInt32 m_Default64;
    static RF_Type::UInt32 m_Default32;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_HASH
#define RF_SHORTHAND_NAMESPACE_HASH
namespace RF_Hash = RadonFramework::Math::Hash;
#endif

#endif // RF_MATH_HASH_HASHFUNCTIONSERVICELOCATOR_HPP
