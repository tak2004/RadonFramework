#ifndef RF_MATH_HASH_HASHFUNCTION_HPP
#define RF_MATH_HASH_HASHFUNCTION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework
{
    namespace Math
    {
        namespace Hash
        {
	        class IHashfunction
	        {
	            public:
                    virtual void Reset()=0;
                    virtual void Update(Core::Types::UInt8 Input)=0;
                    virtual void Update(const Core::Types::UInt8 * Data, 
                                        Core::Types::UInt32 Size)=0;
                    virtual void Final()=0;
                    virtual Core::Types::String ToString()=0;
                    virtual Core::Types::UInt32 GetDigestLength()=0;
                    virtual Core::Types::UInt8* Digest()=0;
	        };
        }
    }
}

#endif // RF_MATH_HASH_HASHFUNCTION_HPP

