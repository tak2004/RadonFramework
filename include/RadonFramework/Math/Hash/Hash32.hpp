#ifndef RF_MATH_HASH_HASH32_HPP
#define RF_MATH_HASH_HASH32_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Math { namespace Hash {
            
struct Hash32
{
public:
    void FromData(const RF_Type::UInt8 * Data, const RF_Type::Size Size);                    
    void FromString(const RF_Type::String& Text);
    void FromMemory(const Memory::AutoPointerArray<RF_Type::UInt8>& Data);
    RF_Type::UInt32 GetHash()const;
private:
    RF_Type::UInt32 m_Hash;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_HASH
#define RF_SHORTHAND_NAMESPACE_HASH
namespace RF_Hash = RadonFramework::Math::Hash;
#endif

#endif // RF_MATH_HASH_HASH32_HPP
