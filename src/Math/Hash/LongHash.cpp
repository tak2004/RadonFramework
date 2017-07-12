#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Hash/LongHash.hpp"
#include "RadonFramework/Math/Hash/HashfunctionServiceLocator.hpp"
#include "RadonFramework/Math/Hash/IHashfunction.hpp"

namespace RadonFramework::Math::Hash {

void LongHash::FromData(const RF_Type::UInt8 * Data, const RF_Type::Size Size)
{
    auto& service = HashfunctionServiceLocator::Default();
    auto hashfunction = service.Create();
    if (hashfunction)
    {
        hashfunction->Reset();
        hashfunction->Update(Data, Size);
        hashfunction->Final();
        m_Hash = RF_Mem::AutoPointerArray<RF_Type::UInt8>(hashfunction->GetDigestLength());
        RF_SysMem::Copy(m_Hash.Get(), hashfunction->Digest(), hashfunction->GetDigestLength());
        service.Free(hashfunction);
    }
}

void LongHash::FromString(const RF_Type::String& Text)
{
    FromData(Text.ByteData(), Text.Size());
}

void LongHash::FromMemory(const Memory::AutoPointerArray<RF_Type::UInt8>& Data)
{
    FromData(Data.Get(), Data.Size());
}

const RF_Mem::AutoPointerArray<RF_Type::UInt8>& LongHash::GetHash() const
{
    return m_Hash;
}

}