#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Hash/Hash64.hpp"
#include "RadonFramework/Math/Hash/HashfunctionServiceLocator.hpp"
#include "RadonFramework/Math/Hash/IHashfunction.hpp"

namespace RadonFramework { namespace Math { namespace Hash {

void Hash64::FromData(const RF_Type::UInt8 * Data, const RF_Type::Size Size)
{
    auto& service = HashfunctionServiceLocator::Default64();
    auto hashfunction = service.Create();
    if(hashfunction)
    {
        hashfunction->Reset();
        hashfunction->Update(Data, Size);
        hashfunction->Final();
        m_Hash = *reinterpret_cast<RF_Type::UInt64*>(hashfunction->Digest());
        service.Free(hashfunction);
    }
}

void Hash64::FromString(const RF_Type::String& Text)
{
    FromData(Text.ByteData(), Text.Size());
}

void Hash64::FromMemory(const Memory::AutoPointerArray<RF_Type::UInt8>& Data)
{
    FromData(Data.Get(), Data.Size());
}

RF_Type::UInt64 Hash64::GetHash() const
{
    return m_Hash;
}

} } }