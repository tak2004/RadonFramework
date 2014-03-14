#ifndef RF_HASHLIBHASHFUNCTIONSERVICE_HPP
#define RF_HASHLIBHASHFUNCTIONSERVICE_HPP

#include <RadonFramework/Math/Hash/HashfunctionService.hpp>
#include <string>

namespace RadonFramework
{
    namespace Math
    {
        namespace Hash
        {
            class HashlibMD5HashfunctionService:public HashfunctionService
            {
                public:
                    HashlibMD5HashfunctionService(const Core::Types::String &Name);
                    IHashfunction* Create();
            };

            class HashlibSHA1HashfunctionService:public HashfunctionService
            {
                public:
                    HashlibSHA1HashfunctionService(const Core::Types::String &Name);
                    IHashfunction* Create();
            };

            class HashlibSHA256HashfunctionService:public HashfunctionService
            {
                public:
                    HashlibSHA256HashfunctionService(const Core::Types::String &Name);
                    IHashfunction* Create();
            };

            class HashlibSHA384HashfunctionService:public HashfunctionService
            {
                public:
                    HashlibSHA384HashfunctionService(const Core::Types::String &Name);
                    IHashfunction* Create();
            };

            class HashlibSHA512HashfunctionService:public HashfunctionService
            {
                public:
                    HashlibSHA512HashfunctionService(const Core::Types::String &Name);
                    IHashfunction* Create();
            };
        }
    }
}

#endif
