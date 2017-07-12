#ifndef RF_REFLECTIONTYPES_HPP
#define RF_REFLECTIONTYPES_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
namespace RadonFramework::Reflection::TypeKind {

enum Type {
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
	RF_MAX
};

}

namespace RadonFramework::Reflection {

const RF_Type::String TypeKindName[TypeKind::RF_MAX] = {
    "unknown type"_rfs, "Float32"_rfs, "Float64"_rfs,
    "Int32"_rfs, "UInt32"_rfs, "Int64"_rfs, "UInt64"_rfs,
    "Int16"_rfs, "UInt16"_rfs, "Int8"_rfs, "UInt8"_rfs,
    "String"_rfs, "Char"_rfs, "Bool"_rfs};
const RF_Type::UInt32 TypeSize[TypeKind::RF_MAX]={0,4,8,4,4,8,8,2,2,1,1,0,1,1};

}

#endif
