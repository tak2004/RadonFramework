#ifndef RF_UTIL_UUID_HPP
#define RF_UTIL_UUID_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Util {

/// UUID Version 5
struct RF_ALIGN(16) UUID
{
    static UUID FastRandomUUID();
    static UUID SecureRandomUUID();
    static UUID UUIDFromString(const RF_Type::String& Text);

    static UUID NIL;
    static UUID DNS;
    static UUID URL;
    static UUID OID;
    static UUID X500;

    RF_Type::Bool IsNil()const;
    void Swap(UUID& Other);
    RF_Type::String ToString()const;
    RF_Type::Int32 CompareTo(const UUID& Other)const;

    union {
        RF_Type::Vec128UInt8 Bytes;
        #pragma pack(push,1)
        struct
        {
            RF_Type::UInt32 TimeLow;
            RF_Type::UInt16 TimeMid;
            RF_Type::UInt16 TimeHiAndVersion;
            RF_Type::UInt8  ClockSeqHiAndReserved;
            RF_Type::UInt8  ClockSeqLow;
            RF_Type::UInt8  Node[6];
        } Structure;
        #pragma pack(pop)
    };
};

bool operator==(UUID const& lhs, UUID const& rhs);
bool operator!=(UUID const& lhs, UUID const& rhs);
bool operator<(UUID const& lhs, UUID const& rhs);
bool operator>(UUID const& lhs, UUID const& rhs);
bool operator<=(UUID const& lhs, UUID const& rhs);
bool operator>=(UUID const& lhs, UUID const& rhs);

}

#ifndef RF_SHORTHAND_NAMESPACE_UTIL
#define RF_SHORTHAND_NAMESPACE_UTIL
namespace RF_Util = RadonFramework::Util;
#endif

#endif // RF_UTIL_UUID_HPP