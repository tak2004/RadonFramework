#ifndef RF_REFLECTIONTYPES_HPP
#define RF_REFLECTIONTYPES_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
namespace RadonFramework
{
    namespace Reflection
    {
        namespace TypeKind
        {
            enum Type{
                RF_UNKNOWN,
                RF_FLOAT32,
                RF_FLOAT64,
                RF_INT32,
                RF_UINT32,
                RF_INT64,
                RF_UINT64,
                RF_INT16,
                RF_UINT16,
                RF_INT8,
                RF_UINT8,
                RF_STRING,
                RF_CHAR,
                RF_BOOL,
                RF_MAX};
        }

        const RFTYPE::String TypeKindName[TypeKind::RF_MAX] = {
            RFTYPE::String("unknown type", sizeof("unknown type")),
            RFTYPE::String("Float32", sizeof("Float32")),
            RFTYPE::String("Float64", sizeof("Float64")),
            RFTYPE::String("Int32", sizeof("Int32")),
            RFTYPE::String("UInt32", sizeof("UInt32")),
            RFTYPE::String("Int64", sizeof("Int64")),
            RFTYPE::String("UInt64", sizeof("UInt64")),
            RFTYPE::String("Int16", sizeof("Int16")),
            RFTYPE::String("UInt16", sizeof("UInt16")),
            RFTYPE::String("Int8", sizeof("Int8")),
            RFTYPE::String("UInt8", sizeof("UInt8")),
            RFTYPE::String("String", sizeof("String")),
            RFTYPE::String("Char", sizeof("Char")),
            RFTYPE::String("Bool", sizeof("Bool"))};
        const RFTYPE::UInt32 TypeSize[TypeKind::RF_MAX]={0,4,8,4,4,8,8,2,2,1,1,0,1,1};
    }
}

#endif
