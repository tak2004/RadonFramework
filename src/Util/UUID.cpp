#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Util/UUID.hpp"
#include "RadonFramework/System/Environment.hpp"

namespace RadonFramework { namespace Util {

UUID UUID::NIL = {0};
UUID UUID::DNS = {0x6ba7b810, 0x9dad11d1, 0x80b400c0, 0x4fd430c8};
UUID UUID::URL = {0x6ba7b811, 0x9dad11d1, 0x80b400c0, 0x4fd430c8};
UUID UUID::OID = {0x6ba7b812, 0x9dad11d1, 0x80b400c0, 0x4fd430c8};
UUID UUID::X500 = {0x6ba7b814, 0x9dad11d1, 0x80b400c0, 0x4fd430c8};

UUID UUID::FastRandomUUID()
{
    static_assert(std::is_pod<UUID>::value == true, "UUID have to be a POD structure!");
    static_assert(std::alignment_of<UUID>::value == 16, "UUID have to be 16byte aligned!");
    static_assert(sizeof(UUID) == 16, "UUID have to be 16 byte large!");

    UUID result=NIL;
    RFENV::FastRandomUUID(result);
    return result;
}


UUID UUID::SecureRandomUUID()
{
    UUID result = NIL;
    RFENV::SecureRandomUUID(result);
    return result;
}

UUID UUID::UUIDFromString(const RF_Type::String& Text)
{
    UUID result = NIL;
    RFENV::UUIDFromString(Text, result);
    return result;
}

RF_Type::Bool UUID::IsNil()const
{
    return RF_SysMem::Compare(Bytes.m_Vector, NIL.Bytes.m_Vector, 16) == 0;
}

void UUID::Swap(UUID& Other)
{
    RF_SysMem::Swap(Bytes.m_Vector, Other.Bytes.m_Vector, 16);
}

RF_Type::String UUID::ToString()const
{
    RF_Type::String result;
    result = RF_Type::String::Format("%8.8x-%4.4x-%4.4x-%2.2x%2.2x-%2.2x%2.2x%2.2x%2.2x%2.2x%2.2x",
        Structure.TimeLow, Structure.TimeMid, Structure.TimeHiAndVersion, 
        Structure.ClockSeqHiAndReserved, Structure.ClockSeqLow, 
        Structure.Node[0], Structure.Node[1], Structure.Node[2], 
        Structure.Node[3], Structure.Node[4], Structure.Node[5]);
    return result;
}

inline RF_Type::Int32 UUID::CompareTo(const UUID& Other) const
{
    return RF_SysMem::Compare(Bytes.m_Vector, Other.Bytes.m_Vector, 16);
}

bool operator==(UUID const& lhs, UUID const& rhs) RF_NOEXCEPT
{
    return lhs.CompareTo(rhs) == 0;
}

bool operator!=(UUID const& lhs, UUID const& rhs) RF_NOEXCEPT
{
    return lhs.CompareTo(rhs) != 0;
}

bool operator<(UUID const& lhs, UUID const& rhs) RF_NOEXCEPT
{
    return lhs.CompareTo(rhs) < 0;
}

bool operator>(UUID const& lhs, UUID const& rhs) RF_NOEXCEPT
{
    return lhs.CompareTo(rhs) > 0;
}

bool operator<=(UUID const& lhs, UUID const& rhs) RF_NOEXCEPT
{
    return lhs.CompareTo(rhs) <= 0;
}

bool operator>=(UUID const& lhs, UUID const& rhs) RF_NOEXCEPT
{
    return lhs.CompareTo(rhs) >= 0;
}

} }