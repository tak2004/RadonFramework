#ifndef RF_MATH_HASH_HASHFUNCTIONSERVICELOCATOR_HPP
#define RF_MATH_HASH_HASHFUNCTIONSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/Math/Hash/HashfunctionService.hpp>
#include <RadonFramework/Math/Hash/IHashfunction.hpp>

namespace RadonFramework
{
    namespace Math
    {
        namespace Hash
        {
            class NullHashfunctionService:public HashfunctionService
            {
                public:
                    NullHashfunctionService(const RFTYPE::String &Name)
                    :HashfunctionService(Name)
                    {
                    }

                    IHashfunction* Create()
                    {
                        return 0;
                    }
            };

            typedef Core::Pattern::Locator<HashfunctionService,NullHashfunctionService> HashfunctionServiceLocator;
        }
    }
}

#endif // RF_MATH_HASH_HASHFUNCTIONSERVICELOCATOR_HPP
