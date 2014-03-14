#ifndef RF_CORE_TYPES_ATOMICINT32_HPP
#define RF_CORE_TYPES_ATOMICINT32_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Core
    {
        namespace Types
        {
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

                    operator Int32()const;
                    bool operator !()const;
                    bool operator !=(int Value)const;
                    AtomicInt32& operator =(int Value);
                    AtomicInt32& operator =(const AtomicInt32& Other);
                    bool operator ==(int Value)const;
                protected:
                    Int32 m_Data;
            };
        }
    }
}

#endif // RF_CORE_TYPES_ATOMICINT_HPP