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

        const RF_Type::String TypeKindName[TypeKind::RF_MAX] = {
            RF_Type::String("unknown type", sizeof("unknown type")),
            RF_Type::String("Float32", sizeof("Float32")),
            RF_Type::String("Float64", sizeof("Float64")),
            RF_Type::String("Int32", sizeof("Int32")),
            RF_Type::String("UInt32", sizeof("UInt32")),
            RF_Type::String("Int64", sizeof("Int64")),
            RF_Type::String("UInt64", sizeof("UInt64")),
            RF_Type::String("Int16", sizeof("Int16")),
            RF_Type::String("UInt16", sizeof("UInt16")),
            RF_Type::String("Int8", sizeof("Int8")),
            RF_Type::String("UInt8", sizeof("UInt8")),
            RF_Type::String("String", sizeof("String")),
            RF_Type::String("Char", sizeof("Char")),
            RF_Type::String("Bool", sizeof("Bool"))};
        const RF_Type::UInt32 TypeSize[TypeKind::RF_MAX]={0,4,8,4,4,8,8,2,2,1,1,0,1,1};
    }
}

#endif
