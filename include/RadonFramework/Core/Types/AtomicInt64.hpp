#ifndef RF_CORE_TYPES_ATOMICINT64_HPP
#define RF_CORE_TYPES_ATOMICINT64_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Types {

struct AtomicInt64
{
public:
    AtomicInt64(Int64 Value=0);
    AtomicInt64(const AtomicInt64& Other);

    Int64 Increment();
    Int64 Decrement();
    Int64 FetchAndAdd(Int64 Addend);
    Int64 FetchAndExchange(Int64 Value);
    Int64 CompareAndExchange(Int64 Compare, Int64 Value);
    Int64 Add(Int64 Value);

    operator Int64()const;
    bool operator !()const;
    bool operator !=(Int64 Value)const;
    AtomicInt64& operator =(Int64 Value);
    AtomicInt64& operator =(const AtomicInt64& Other);
    bool operator ==(Int64 Value)const;
    AtomicInt64& operator++();
    AtomicInt64 operator++(Int64);
    AtomicInt64& operator--();
    AtomicInt64 operator--(Int64);
protected:
    Int64 m_Data;
};

} } }

#endif // RF_CORE_TYPES_ATOMICINT64_HPP