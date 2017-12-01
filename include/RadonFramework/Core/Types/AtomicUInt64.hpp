#ifndef RF_CORE_TYPES_ATOMICUINT64_HPP
#define RF_CORE_TYPES_ATOMICUINT64_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Core::Types {

struct AtomicUInt64
{
public:
    AtomicUInt64(UInt64 Value=0);
    AtomicUInt64(const AtomicUInt64& Other);

    UInt64 Increment();
    UInt64 Decrement();
    UInt64 FetchAndAdd(UInt64 Addend);
    UInt64 FetchAndExchange(UInt64 Value);
    /// Returns the initial value.
    UInt64 CompareAndExchange(UInt64 Compare, UInt64 Value);
    UInt64 Add(UInt64 Value);

    operator UInt64()const;
    bool operator !()const;
    bool operator !=(UInt64 Value)const;
    AtomicUInt64& operator =(UInt64 Value);
    AtomicUInt64& operator =(const AtomicUInt64& Other);
    bool operator ==(UInt64 Value)const;
    AtomicUInt64& operator++();
    AtomicUInt64 operator++(int);
    AtomicUInt64& operator--();
    AtomicUInt64 operator--(int);
protected:
    UInt64 m_Data;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif // RF_CORE_TYPES_ATOMICUINT64_HPP