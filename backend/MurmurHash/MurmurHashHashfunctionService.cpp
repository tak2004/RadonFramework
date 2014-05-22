#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/backend/MurmurHash/MurmurHashHashfunctionService.hpp"
#include "RadonFramework/Math/Hash/IHashfunction.hpp"

using namespace RadonFramework::Math::Hash;
using namespace RadonFramework::Core::Types;

class MurmurHashHashfunction:public IHashfunction
{
    protected:
        UInt8 m_buf[8];
    public:
        void Reset()
        {
        }

        void Update(UInt8 Input)
        {
        }

        void Update(const UInt8 * Data, UInt32 Size)
        {
        }

        void Final()
        {
        }

        String ToString()
        {
            String result;
            for(int i=0; i<8; ++i)
                result+=String::Format(String("%02X", sizeof("%02X")), m_buf[i]);
            return result;
        }

        UInt32 GetDigestLength()
        {
            return 8;
        }

        UInt8* Digest()
        {
            return m_buf;
        }
};

MurmurHashHashfunctionService::MurmurHashHashfunctionService(const String &Name)
:HashfunctionService(Name)
{
}

IHashfunction* MurmurHashHashfunctionService::Create()
{
  return static_cast<IHashfunction*>(new MurmurHashHashfunction);
}
