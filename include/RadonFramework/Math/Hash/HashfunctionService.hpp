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
        HashfunctionService(const Core::Types::String &Name);
        ~HashfunctionService();
        virtual IHashfunction* Create()=0;
};

} } }
#endif // RF_MATH_HASH_HASHFUNCTIONSERVICE_HPP
