#ifndef RF_MURMURHASHHASHFUNCTIONSERVICE_HPP
#define RF_MURMURHASHHASHFUNCTIONSERVICE_HPP

#include <RadonFramework/Math/Hash/HashfunctionService.hpp>
#include <string>

namespace RadonFramework
{
    namespace Math
    {
        namespace Hash
        {
            class MurmurHashHashfunctionService:public HashfunctionService
            {
                public:
                    MurmurHashHashfunctionService(const Core::Types::String &Name);
                    IHashfunction* Create();
            };
        }
    }
}

#endif
