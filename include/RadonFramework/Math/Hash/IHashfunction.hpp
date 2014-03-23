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
    virtual void Update(RFTYPE::UInt8 Input)=0;
    virtual void Update(const RFTYPE::UInt8 * Data, RFTYPE::UInt32 Size)=0;
    virtual void Final()=0;
    virtual RFTYPE::String ToString()=0;
    virtual RFTYPE::UInt32 GetDigestLength()=0;
    virtual RFTYPE::UInt8* Digest()=0;
};
    
} } }

#endif // RF_MATH_HASH_HASHFUNCTION_HPP

