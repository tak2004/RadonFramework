#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Math/Hash/Hash32.hpp"
#include "RadonFramework/Math/Hash/HashfunctionServiceLocator.hpp"
#include "RadonFramework/Math/Hash/IHashfunction.hpp"

namespace RadonFramework::Math::Hash {

void Hash32::FromData(const RF_Type::UInt8 * Data, const RF_Type::Size Size)
{
    auto& service = HashfunctionServiceLocator::Default32();
    auto hashfunction = service.Create();
    if(hashfunction)
    {
        hashfunction->Reset();
        hashfunction->Update(Data, Size);
        hashfunction->Final();
        m_Hash = *reinterpret_cast<RF_Type::UInt32*>(hashfunction->Digest());
        service.Free(hashfunction);
    }
}

void Hash32::FromString(const RF_Type::String& Text)
{
    FromData(Text.ByteData(), Text.Size());
}

void Hash32::FromMemory(const Memory::AutoPointerArray<RF_Type::UInt8>& Data)
{
    FromData(Data.Get(), Data.Size());
}

RF_Type::UInt32 Hash32::GetHash() const
{
    return m_Hash;
}

}