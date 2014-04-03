#ifndef RF_CORE_TYPES_TYPECODE_HPP
#define RF_CORE_TYPES_TYPECODE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Types {

namespace TypeCode
{
    enum Type{
        Empty,
        Object,
        Boolean,
        Int8,
        UInt8,
        Int16,
        UInt16,
        Int32,
        UInt32,
        Int64,
        UInt64,
        Size,
        Float32,
        Float64,
        String,//Ascii
        Char,//Ascii
        MemoryRange,
        AtomicInt,
        AtomicPointer,
        Vec64Int,
        Vec64UInt,
        Vec128Int,
        Vec128UInt,
        Vec128Float,
        MAX//for array mapping
    };
}

} } }

#endif // RF_CORE_TYPES_TYPECODE_HPP
