#ifndef RF_MATH_HASH_HASHFUNCTIONSERVICE_HPP
#define RF_MATH_HASH_HASHFUNCTIONSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>

namespace RadonFramework { namespace Math { namespace Hash {
// forward declaration
class IHashfunction;

class HashfunctionService:public Core::Pattern::Service
{
    public:
        HashfunctionService(const RF_Type::String &Name);
        ~HashfunctionService();
        virtual IHashfunction* Create()=0;
        virtual void Free(IHashfunction*& Instance) = 0;
        virtual RF_Type::Size BitLength()const = 0;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_HASH
#define RF_SHORTHAND_NAMESPACE_HASH
namespace RF_Hash = RadonFramework::Math::Hash;
#endif

#endif // RF_MATH_HASH_HASHFUNCTIONSERVICE_HPP
