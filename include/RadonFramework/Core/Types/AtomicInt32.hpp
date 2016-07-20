#ifndef RF_CORE_TYPES_ATOMICINT32_HPP
#define RF_CORE_TYPES_ATOMICINT32_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Types {

struct AtomicInt32
{
public:
    AtomicInt32(Int32 Value=0);
    AtomicInt32(const AtomicInt32& Other);

    Int32 Increment();
    Int32 Decrement();
    Int32 FetchAndAdd(Int32 Addend);
    Int32 FetchAndExchange(Int32 Value);
    Int32 CompareAndExchange(Int32 Compare, Int32 Value);
    Int32 Add(Int32 Value);

    operator Int32()const;
    bool operator !()const;
    bool operator !=(Int32 Value)const;
    AtomicInt32& operator =(Int32 Value);
    AtomicInt32& operator =(const AtomicInt32& Other);
    bool operator ==(Int32 Value)const;
    AtomicInt32& operator++();
    AtomicInt32 operator++(Int32);
    AtomicInt32& operator--();
    AtomicInt32 operator--(Int32);
protected:
    Int32 m_Data;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif // RF_CORE_TYPES_ATOMICINT_HPP