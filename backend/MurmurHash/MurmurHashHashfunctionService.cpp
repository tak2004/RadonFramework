#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/backend/MurmurHash/MurmurHashHashfunctionService.hpp"
#include "RadonFramework/Math/Hash/IHashfunction.hpp"
#include "RadonFramework/Collections/Array.hpp"

using namespace RadonFramework::Math::Hash;
using namespace RadonFramework::Core::Types;

extern unsigned long long int MurmurHash64(const void * key, int len, unsigned int seed);

class MurmurHashHashfunction:public IHashfunction
{
protected:
    UInt8 m_buf[8];
    RF_Collect::Array<UInt8> m_Data;
public:
    void Reset()
    {
        RF_SysMem::Set(m_buf, 0, 8);
        m_Data.Resize(0);
    }

    void Update(UInt8 Input)
    {
        m_Data.Resize(m_Data.Count() + 1);
        m_Data(m_Data.Count() - 2) = Input;
    }

    void Update(const UInt8 * Data, UInt32 Size)
    {
        RF_Type::Size size = m_Data.Count();
        m_Data.Resize(m_Data.Count() + Size);
        RF_SysMem::Copy(&m_Data(size), Data, Size);
    }

    void Final()
    {
        *reinterpret_cast<unsigned long long*>(m_buf) = MurmurHash64(&m_Data(0), m_Data.Count(), 0);
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
