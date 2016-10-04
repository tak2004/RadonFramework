#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Math/Hash/xxHashService.hpp"
#include "RadonFramework/Math/Hash/IHashfunction.hpp"
#include "RadonFramework/Math/Hash/HashfunctionServiceLocator.hpp"
#include <xxhash.h>

namespace RadonFramework { namespace System { namespace Math { namespace Hash { 

class xxHash32Hashfunction: public RF_Hash::IHashfunction
{
public:
    xxHash32Hashfunction()
    :m_Context(nullptr)
    {}

    virtual ~xxHash32Hashfunction()
    {
        XXH32_freeState(m_Context);
        m_Context = nullptr;
    }

    virtual void Reset() override
    {
        if (m_Context == nullptr)
        {
            m_Context = XXH32_createState();
        }

        XXH32_reset(m_Context, 0);
        RF_SysMem::Set(m_Buffer, 0, 4);
    }

    virtual void Update(RF_Type::UInt8 Input) override
    {
        XXH32_update(m_Context, &Input, 1);
    }

    virtual void Update(const RF_Type::UInt8 * Data, RF_Type::UInt32 Size) override
    {
        XXH32_update(m_Context, Data, Size);
    }

    virtual void Final() override
    {
        XXH32_hash_t result = XXH32_digest(m_Context);
        RF_SysMem::Copy(m_Buffer, &result, 4);
    }

    virtual RF_Type::String ToString() override
    {
        RF_Type::String result;
        for(auto i = 0; i < 4; ++i)
            result += RF_Type::String::Format("%02X"_rfs, m_Buffer[i]);
        return result;
    }

    virtual RF_Type::UInt32 GetDigestLength() override
    {
        return 4;
    }

    virtual RF_Type::UInt8* Digest() override
    {
        return m_Buffer;
    }
private:
    XXH32_state_t* m_Context;
    RF_Type::UInt8 m_Buffer[4];
};

xxHash32HashfunctionService::xxHash32HashfunctionService(const RF_Type::String &Name)
:HashfunctionService(Name)
{
}

RF_Hash::IHashfunction* xxHash32HashfunctionService::Create()
{
    return new xxHash32Hashfunction;
}

void xxHash32HashfunctionService::Free(RF_Hash::IHashfunction*& Instance)
{
    if(Instance)
    {
        delete Instance;
        Instance = nullptr;
    }
}

RF_Type::Size xxHash32HashfunctionService::BitLength() const
{
    return 32;
}

class xxHash64Hashfunction: public RF_Hash::IHashfunction
{
public:
    xxHash64Hashfunction()
    :m_Context(nullptr)
    {}

    virtual ~xxHash64Hashfunction()
    {
        XXH64_freeState(m_Context);
        m_Context = nullptr;
    }

    virtual void Reset() override
    {
        if(m_Context == nullptr)
        {
            m_Context = XXH64_createState();
        }

        XXH64_reset(m_Context, 0);
        RF_SysMem::Set(m_Buffer, 0, 8);
    }

    virtual void Update(RF_Type::UInt8 Input) override
    {
        XXH64_update(m_Context, &Input, 1);
    }

    virtual void Update(const RF_Type::UInt8 * Data, RF_Type::UInt32 Size) override
    {
        XXH64_update(m_Context, Data, Size);
    }

    virtual void Final() override
    {
        XXH64_hash_t result = XXH64_digest(m_Context);
        RF_SysMem::Copy(m_Buffer, &result, 8);
    }

    virtual RF_Type::String ToString() override
    {
        RF_Type::String result;
        for(auto i = 0; i < 8; ++i)
            result += RF_Type::String::Format("%02X"_rfs, m_Buffer[i]);
        return result;
    }

    virtual RF_Type::UInt32 GetDigestLength() override
    {
        return 8;
    }

    virtual RF_Type::UInt8* Digest() override
    {
        return m_Buffer;
    }
private:
    XXH64_state_t* m_Context;
    RF_Type::UInt8 m_Buffer[8];
};

xxHash64HashfunctionService::xxHash64HashfunctionService(const RF_Type::String &Name)
:HashfunctionService(Name)
{
}

RF_Hash::IHashfunction* xxHash64HashfunctionService::Create()
{
    return new xxHash64Hashfunction;
}

void xxHash64HashfunctionService::Free(RF_Hash::IHashfunction*& Instance)
{
    if(Instance)
    {
        delete Instance;
        Instance = nullptr;
    }
}

RF_Type::Size xxHash64HashfunctionService::BitLength() const
{
    return 64;
}

} } } }