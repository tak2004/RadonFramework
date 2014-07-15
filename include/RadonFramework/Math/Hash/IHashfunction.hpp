#ifndef RF_MATH_HASH_HASHFUNCTION_HPP
#define RF_MATH_HASH_HASHFUNCTION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework { namespace Math { namespace Hash {

class IHashfunction
{
public:
    virtual void Reset()=0;
    virtual void Update(RF_Type::UInt8 Input)=0;
    virtual void Update(const RF_Type::UInt8 * Data, RF_Type::UInt32 Size)=0;
    virtual void Final()=0;
    virtual RF_Type::String ToString()=0;
    virtual RF_Type::UInt32 GetDigestLength()=0;
    virtual RF_Type::UInt8* Digest()=0;
};
    
} } }

#ifndef RF_SHORTHAND_NAMESPACE_HASH
#define RF_SHORTHAND_NAMESPACE_HASH
namespace RF_Hash = RadonFramework::Math::Hash;
#endif

#endif // RF_MATH_HASH_HASHFUNCTION_HPP

