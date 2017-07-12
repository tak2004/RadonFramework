#ifndef RF_CORE_TYPES_ATOMICUINT32_HPP
#define RF_CORE_TYPES_ATOMICUINT32_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Core::Types {

struct AtomicUInt32
{
public:
    AtomicUInt32(UInt32 Value=0);
    AtomicUInt32(const AtomicUInt32& Other);

    UInt32 Increment();
    UInt32 Decrement();
    UInt32 FetchAndAdd(UInt32 Addend);
    UInt32 FetchAndExchange(UInt32 Value);
    UInt32 CompareAndExchange(UInt32 Compare, UInt32 Value);
    UInt32 Add(UInt32 Value);

    operator UInt32()const;
    bool operator !()const;
    bool operator !=(UInt32 Value)const;
    AtomicUInt32& operator =(UInt32 Value);
    AtomicUInt32& operator =(const AtomicUInt32& Other);
    bool operator ==(UInt32 Value)const;
    AtomicUInt32& operator++();
    AtomicUInt32 operator++(Int32);
    AtomicUInt32& operator--();
    AtomicUInt32 operator--(Int32);
protected:
    UInt32 m_Data;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif // RF_CORE_TYPES_ATOMICUINT32_HPP