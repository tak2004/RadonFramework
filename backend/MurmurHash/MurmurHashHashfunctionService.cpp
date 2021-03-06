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
    void Reset()final
    {
        RF_SysMem::Set(m_buf, 0, 8);
        m_Data.Resize(0);
    }

    void Update(UInt8 Input) final
    {
        m_Data.Resize(m_Data.Count() + 1);
        m_Data(m_Data.Count() - 2) = Input;
    }

    void Update(const UInt8* Data, UInt32 Size) final
    {
        RF_Type::Size bufferSize = m_Data.Count();
        m_Data.Resize(bufferSize + Size);
        RF_SysMem::Copy(&m_Data(bufferSize), Data, Size);
    }

    void Final() final
    {
        *reinterpret_cast<unsigned long long*>(m_buf) = MurmurHash64(&m_Data(0), m_Data.Count(), 0);
    }

    String ToString() final
    {
        String result;
        for(int i:m_buf)
          {
            result+=String::Format(String("%02X", sizeof("%02X")), m_buf[i]);
            }
        return result;
    }

    UInt32 GetDigestLength() final
    {
        return 8;
    }

    UInt8* Digest() final
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

void MurmurHashHashfunctionService::Free(IHashfunction*& Instance)
{
    if(Instance != nullptr)
    {
        delete Instance;
        Instance = nullptr;
    }
}

RF_Type::Size MurmurHashHashfunctionService::BitLength() const
{
    return 64;
}
