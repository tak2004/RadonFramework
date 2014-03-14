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

        const RadonFramework::Core::Types::String TypeKindName[TypeKind::RF_MAX]={"unknown type","Float32","Float64","Int32","UInt32","Int64","UInt64","Int16","UInt16","Int8","UInt8","String","Char","Bool"};
        const RadonFramework::Core::Types::UInt32 TypeSize[TypeKind::RF_MAX]={0,4,8,4,4,8,8,2,2,1,1,0,1,1};
    }
}

#endif
