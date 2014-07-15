#ifndef RF_CORE_SIMD_FPU_ALU_HPP
#define RF_CORE_SIMD_FPU_ALU_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Vec128Int.hpp>
#include <RadonFramework/Core/Types/Vec128UInt.hpp>
#include <RadonFramework/Core/Types/Vec128Float.hpp>
#include <RadonFramework/Core/Types/Vec64Int.hpp>
#include <RadonFramework/Core/Types/Vec64UInt.hpp>
#include <RadonFramework/Core/SIMD/OpSet.hpp>
#include <math.h>

namespace RadonFramework { namespace Core { namespace SIMD {
// helper macros to make the file more readable
#define FPU_ALU_SPECIAL_OPERATOR16(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0]; ret[1]=A[1] OP B[1];\
        ret[2]=A[2] OP B[2]; ret[3]=A[3] OP B[3];\
        ret[4]=A[4] OP B[4]; ret[5]=A[5] OP B[5];\
        ret[6]=A[6] OP B[6]; ret[7]=A[7] OP B[7];\
        ret[8]=A[8] OP B[8]; ret[9]=A[9] OP B[9];\
        ret[10]=A[10] OP B[10]; ret[11]=A[11] OP B[11];\
        ret[12]=A[12] OP B[12]; ret[13]=A[13] OP B[13];\
        ret[14]=A[14] OP B[14]; ret[15]=A[15] OP B[15];\
        return ret;\
    }                

#define FPU_ALU_SPECIAL_OPERATOR8(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0]; ret[1]=A[1] OP B[1];\
        ret[2]=A[2] OP B[2]; ret[3]=A[3] OP B[3];\
        ret[4]=A[4] OP B[4]; ret[5]=A[5] OP B[5];\
        ret[6]=A[6] OP B[6]; ret[7]=A[7] OP B[7];\
        return ret;\
    }

#define FPU_ALU_SPECIAL_OPERATOR4(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0]; ret[1]=A[1] OP B[1];\
        ret[2]=A[2] OP B[2]; ret[3]=A[3] OP B[3];\
        return ret;\
    }

#define FPU_ALU_SPECIAL_OPERATOR2(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0]; ret[1]=A[1] OP B[1];\
        return ret;\
    }

#define FPU_ALU_SPECIAL_LOGICOPERATOR16(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0] ? 0xff : 0x00; ret[1]=A[1] OP B[1] ? 0xff : 0x00;\
        ret[2]=A[2] OP B[2] ? 0xff : 0x00; ret[3]=A[3] OP B[3] ? 0xff : 0x00;\
        ret[4]=A[4] OP B[4] ? 0xff : 0x00; ret[5]=A[5] OP B[5] ? 0xff : 0x00;\
        ret[6]=A[6] OP B[6] ? 0xff : 0x00; ret[7]=A[7] OP B[7] ? 0xff : 0x00;\
        ret[8]=A[8] OP B[8] ? 0xff : 0x00; ret[9]=A[9] OP B[9] ? 0xff : 0x00;\
        ret[10]=A[10] OP B[10] ? 0xff : 0x00; ret[11]=A[11] OP B[11] ? 0xff : 0x00;\
        ret[12]=A[12] OP B[12] ? 0xff : 0x00; ret[13]=A[13] OP B[13] ? 0xff : 0x00;\
        ret[14]=A[14] OP B[14] ? 0xff : 0x00; ret[15]=A[15] OP B[15] ? 0xff : 0x00;\
        return ret;\
    }    

#define FPU_ALU_SPECIAL_LOGICOPERATOR8(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0] ? 0xffff : 0x00; ret[1]=A[1] OP B[1] ? 0xffff : 0x00;\
        ret[2]=A[2] OP B[2] ? 0xffff : 0x00; ret[3]=A[3] OP B[3] ? 0xffff : 0x00;\
        ret[4]=A[4] OP B[4] ? 0xffff : 0x00; ret[5]=A[5] OP B[5] ? 0xffff : 0x00;\
        ret[6]=A[6] OP B[6] ? 0xffff : 0x00; ret[7]=A[7] OP B[7] ? 0xffff : 0x00;\
        return ret;\
    }

#define FPU_ALU_SPECIAL_LOGICOPERATOR4(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0] ? 0xffffffff : 0x00; ret[1]=A[1] OP B[1] ? 0xffffffff : 0x00;\
        ret[2]=A[2] OP B[2] ? 0xffffffff : 0x00; ret[3]=A[3] OP B[3] ? 0xffffffff : 0x00;\
        return ret;\
    }

#define FPU_ALU_SPECIAL_LOGICOPERATOR2(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0] ? 0xffffffffffffffff : 0x00; ret[1]=A[1] OP B[1]? 0xffffffffffffffff : 0x00;\
        return ret;\
    }

#define FPU_ALU_SPECIAL_INIT16(TYPE,OPNAME) template<>\
    void Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(const TYPE::ValueType Value, TYPE& A)\
    {\
        A[0]=Value; A[1]=Value;\
        A[2]=Value; A[3]=Value;\
        A[4]=Value; A[5]=Value;\
        A[6]=Value; A[7]=Value;\
        A[8]=Value; A[9]=Value;\
        A[10]=Value; A[11]=Value;\
        A[12]=Value; A[13]=Value;\
        A[14]=Value; A[15]=Value;\
    }                

#define FPU_ALU_SPECIAL_INIT8(TYPE,OPNAME) template<>\
    void Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(const TYPE::ValueType Value, TYPE& A)\
    {\
        A[0]=Value; A[1]=Value;\
        A[2]=Value; A[3]=Value;\
        A[4]=Value; A[5]=Value;\
        A[6]=Value; A[7]=Value;\
    } 

#define FPU_ALU_SPECIAL_INIT4(TYPE,OPNAME) template<>\
    void Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(const TYPE::ValueType Value, TYPE& A)\
    {\
        A[0]=Value; A[1]=Value;\
        A[2]=Value; A[3]=Value;\
    } 

#define FPU_ALU_SPECIAL_INIT2(TYPE,OPNAME) template<>\
    void Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(const TYPE::ValueType Value, TYPE& A)\
    { A[0]=Value; A[1]=Value; }

#define FPU_ALU_SPECIAL_OPERATOR16_SINGLE(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(const TYPE& A)\
    {\
        TYPE ret;\
        ret[0]=OP(A[0]); ret[1]=OP(A[1]);\
        ret[2]=OP(A[2]); ret[3]=OP(A[3]);\
        ret[4]=OP(A[4]); ret[5]=OP(A[5]);\
        ret[6]=OP(A[6]); ret[7]=OP(A[7]);\
        ret[8]=OP(A[8]); ret[9]=OP(A[9]);\
        ret[10]=OP(A[10]); ret[11]=OP(A[11]);\
        ret[12]=OP(A[12]); ret[13]=OP(A[13]);\
        ret[14]=OP(A[14]); ret[15]=OP(A[15]);\
        return ret;\
    }                

#define FPU_ALU_SPECIAL_OPERATOR8_SINGLE(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(const TYPE& A)\
    {\
        TYPE ret;\
        ret[0]=OP(A[0]); ret[1]=OP(A[1]);\
        ret[2]=OP(A[2]); ret[3]=OP(A[3]);\
        ret[4]=OP(A[4]); ret[5]=OP(A[5]);\
        ret[6]=OP(A[6]); ret[7]=OP(A[7]);\
        return ret;\
    }

#define FPU_ALU_SPECIAL_OPERATOR4_SINGLE(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(const TYPE& A)\
    {\
        TYPE ret;\
        ret[0]=OP(A[0]); ret[1]=OP(A[1]);\
        ret[2]=OP(A[2]); ret[3]=OP(A[3]);\
        return ret;\
    }

#define FPU_ALU_SPECIAL_OPERATOR2_SINGLE(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(const TYPE& A)\
    {\
        TYPE ret;\
        ret[0]=OP(A[0]); ret[1]=OP(A[1]);\
        return ret;\
    }

#define FPU_ALU_SPECIAL_ASSIGNOPERATOR16(TYPE,OPNAME,OP) template<>\
    TYPE& Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(TYPE& A,const TYPE& B)\
    {\
        A[0]OP(B[0]); A[1]OP(B[1]);\
        A[2]OP(B[2]); A[3]OP(B[3]);\
        A[4]OP(B[4]); A[5]OP(B[5]);\
        A[6]OP(B[6]); A[7]OP(B[7]);\
        A[8]OP(B[8]); A[9]OP(B[9]);\
        A[10]OP(B[10]); A[11]OP(B[11]);\
        A[12]OP(B[12]); A[13]OP(B[13]);\
        A[14]OP(B[14]); A[15]OP(B[15]);\
        return A;\
    }   

#define FPU_ALU_SPECIAL_ASSIGNOPERATOR8(TYPE,OPNAME,OP) template<>\
    TYPE& Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(TYPE& A,const TYPE& B)\
    {\
        A[0]OP(B[0]); A[1]OP(B[1]);\
        A[2]OP(B[2]); A[3]OP(B[3]);\
        A[4]OP(B[4]); A[5]OP(B[5]);\
        A[6]OP(B[6]); A[7]OP(B[7]);\
        return A;\
    }  

#define FPU_ALU_SPECIAL_ASSIGNOPERATOR4(TYPE,OPNAME,OP) template<>\
    TYPE& Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(TYPE& A,const TYPE& B)\
    {\
        A[0]OP(B[0]); A[1]OP(B[1]);\
        A[2]OP(B[2]); A[3]OP(B[3]);\
        return A;\
    }  

#define FPU_ALU_SPECIAL_ASSIGNOPERATOR2(TYPE,OPNAME,OP) template<>\
    TYPE& Operations<TYPE,OperationSet::FPU_ALU>::OPNAME(TYPE& A,const TYPE& B)\
    {\
        A[0]OP(B[0]); A[1]OP(B[1]);\
        return A;\
    }  

FPU_ALU_SPECIAL_INIT16(RF_Type::Vec128Int8,Init)
FPU_ALU_SPECIAL_INIT16(RF_Type::Vec128UInt8,Init)
FPU_ALU_SPECIAL_INIT8(RF_Type::Vec128Int16,Init)
FPU_ALU_SPECIAL_INIT8(RF_Type::Vec128UInt16,Init)
FPU_ALU_SPECIAL_INIT4(RF_Type::Vec128Int32,Init)
FPU_ALU_SPECIAL_INIT4(RF_Type::Vec128UInt32,Init)
FPU_ALU_SPECIAL_INIT4(RF_Type::Vec128Float32,Init)
FPU_ALU_SPECIAL_INIT8(RF_Type::Vec64Int8,Init)
FPU_ALU_SPECIAL_INIT8(RF_Type::Vec64UInt8,Init)
FPU_ALU_SPECIAL_INIT4(RF_Type::Vec64Int16,Init)
FPU_ALU_SPECIAL_INIT4(RF_Type::Vec64UInt16,Init)
FPU_ALU_SPECIAL_INIT2(RF_Type::Vec64Int32,Init)
FPU_ALU_SPECIAL_INIT2(RF_Type::Vec64UInt32,Init)            

FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128Int8,Add,+)
FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128UInt8,Add,+)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128Int16,Add,+)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128UInt16,Add,+)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128Int32,Add,+)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128UInt32,Add,+)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128Float32,Add,+)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64Int8,Add,+)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64UInt8,Add,+)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64Int16,Add,+)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64UInt16,Add,+)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64Int32,Add,+)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64UInt32,Add,+)

FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128Int8,Sub,-)
FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128UInt8,Sub,-)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128Int16,Sub,-)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128UInt16,Sub,-)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128Int32,Sub,-)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128UInt32,Sub,-)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128Float32,Sub,-)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64Int8,Sub,-)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64UInt8,Sub,-)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64Int16,Sub,-)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64UInt16,Sub,-)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64Int32,Sub,-)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64UInt32,Sub,-)

FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128Int8,Mul,*)
FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128UInt8,Mul,*)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128Int16,Mul,*)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128UInt16,Mul,*)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128Int32,Mul,*)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128UInt32,Mul,*)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128Float32,Mul,*)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64Int8,Mul,*)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64UInt8,Mul,*)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64Int16,Mul,*)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64UInt16,Mul,*)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64Int32,Mul,*)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64UInt32,Mul,*)

FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128Int8,Div,/)
FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128UInt8,Div,/)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128Int16,Div,/)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128UInt16,Div,/)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128Int32,Div,/)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128UInt32,Div,/)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128Float32,Div,/)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64Int8,Div,/)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64UInt8,Div,/)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64Int16,Div,/)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64UInt16,Div,/)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64Int32,Div,/)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64UInt32,Div,/)

FPU_ALU_SPECIAL_OPERATOR16_SINGLE(RF_Type::Vec128Int8,Floor,)
FPU_ALU_SPECIAL_OPERATOR16_SINGLE(RF_Type::Vec128UInt8,Floor,)
FPU_ALU_SPECIAL_OPERATOR8_SINGLE(RF_Type::Vec128Int16,Floor,)
FPU_ALU_SPECIAL_OPERATOR8_SINGLE(RF_Type::Vec128UInt16,Floor,)
FPU_ALU_SPECIAL_OPERATOR4_SINGLE(RF_Type::Vec128Int32,Floor,)
FPU_ALU_SPECIAL_OPERATOR4_SINGLE(RF_Type::Vec128UInt32,Floor,)
FPU_ALU_SPECIAL_OPERATOR4_SINGLE(RF_Type::Vec128Float32,Floor,floor)
FPU_ALU_SPECIAL_OPERATOR8_SINGLE(RF_Type::Vec64Int8,Floor,)
FPU_ALU_SPECIAL_OPERATOR8_SINGLE(RF_Type::Vec64UInt8,Floor,)
FPU_ALU_SPECIAL_OPERATOR4_SINGLE(RF_Type::Vec64Int16,Floor,)
FPU_ALU_SPECIAL_OPERATOR4_SINGLE(RF_Type::Vec64UInt16,Floor,)
FPU_ALU_SPECIAL_OPERATOR2_SINGLE(RF_Type::Vec64Int32,Floor,)
FPU_ALU_SPECIAL_OPERATOR2_SINGLE(RF_Type::Vec64UInt32,Floor,)

FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128Int8,Mod,%)
FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128UInt8,Mod,%)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128Int16,Mod,%)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128UInt16,Mod,%)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128Int32,Mod,%)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128UInt32,Mod,%)
template<>
RF_Type::Vec128Float32 Operations<RF_Type::Vec128Float32,OperationSet::FPU_ALU>::Mod(
    const RF_Type::Vec128Float32& A, const RF_Type::Vec128Float32& B)
{
    RF_Type::Vec128Float32 ret;
    ret=Sub(A,Mul(B,Floor(Div(A,B))));
    return ret;
}         

FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64Int8,Mod,%)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64UInt8,Mod,%)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64Int16,Mod,%)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64UInt16,Mod,%)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64Int32,Mod,%)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64UInt32,Mod,%)

FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128Int8,And,&)
FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128UInt8,And,&)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128Int16,And,&)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128UInt16,And,&)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128Int32,And,&)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128UInt32,And,&)
template<>
RF_Type::Vec128Float32 Operations<RF_Type::Vec128Float32,OperationSet::FPU_ALU>::And(
    const RF_Type::Vec128Float32& A, const RF_Type::Vec128Float32& B)
{
    RF_Type::Vec128Float32 ret;
    ret[0]=((RF_Type::Int32)A[0])&((RF_Type::Int32)B[0]); ret[1]=((RF_Type::Int32)A[1])&((RF_Type::Int32)B[1]);
    ret[2]=((RF_Type::Int32)A[2])&((RF_Type::Int32)B[2]); ret[3]=((RF_Type::Int32)A[3])&((RF_Type::Int32)B[3]);
    return ret;
}  
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64Int8,And,&)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64UInt8,And,&)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64Int16,And,&)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64UInt16,And,&)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64Int32,And,&)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64UInt32,And,&)

FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128Int8,Or,|)
FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128UInt8,Or,|)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128Int16,Or,|)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128UInt16,Or,|)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128Int32,Or,|)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128UInt32,Or,|)
template<>
RF_Type::Vec128Float32 Operations<RF_Type::Vec128Float32,OperationSet::FPU_ALU>::Or(
    const RF_Type::Vec128Float32& A, const RF_Type::Vec128Float32& B)
{
    RF_Type::Vec128Float32 ret;
    ret[0]=((RF_Type::Int32)A[0])|((RF_Type::Int32)B[0]); ret[1]=((RF_Type::Int32)A[1])|((RF_Type::Int32)B[1]);
    ret[2]=((RF_Type::Int32)A[2])|((RF_Type::Int32)B[2]); ret[3]=((RF_Type::Int32)A[3])|((RF_Type::Int32)B[3]);
    return ret;
} 
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64Int8,Or,|)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64UInt8,Or,|)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64Int16,Or,|)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64UInt16,Or,|)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64Int32,Or,|)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64UInt32,Or,|)

FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128Int8,Xor,^)
FPU_ALU_SPECIAL_OPERATOR16(RF_Type::Vec128UInt8,Xor,^)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128Int16,Xor,^)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec128UInt16,Xor,^)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128Int32,Xor,^)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec128UInt32,Xor,^)
template<>
RF_Type::Vec128Float32 Operations<RF_Type::Vec128Float32,OperationSet::FPU_ALU>::Xor(
    const RF_Type::Vec128Float32& A, const RF_Type::Vec128Float32& B)
{
    RF_Type::Vec128Float32 ret;
    ret[0]=((RF_Type::Int32)A[0])^((RF_Type::Int32)B[0]); ret[1]=((RF_Type::Int32)A[1])^((RF_Type::Int32)B[1]);
    ret[2]=((RF_Type::Int32)A[2])^((RF_Type::Int32)B[2]); ret[3]=((RF_Type::Int32)A[3])^((RF_Type::Int32)B[3]);
    return ret;
} 
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64Int8,Xor,^)
FPU_ALU_SPECIAL_OPERATOR8(RF_Type::Vec64UInt8,Xor,^)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64Int16,Xor,^)
FPU_ALU_SPECIAL_OPERATOR4(RF_Type::Vec64UInt16,Xor,^)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64Int32,Xor,^)
FPU_ALU_SPECIAL_OPERATOR2(RF_Type::Vec64UInt32,Xor,^)

FPU_ALU_SPECIAL_OPERATOR16_SINGLE(RF_Type::Vec128Int8,Not,~)
FPU_ALU_SPECIAL_OPERATOR16_SINGLE(RF_Type::Vec128UInt8,Not,~)
FPU_ALU_SPECIAL_OPERATOR8_SINGLE(RF_Type::Vec128Int16,Not,~)
FPU_ALU_SPECIAL_OPERATOR8_SINGLE(RF_Type::Vec128UInt16,Not,~)
FPU_ALU_SPECIAL_OPERATOR4_SINGLE(RF_Type::Vec128Int32,Not,~)
FPU_ALU_SPECIAL_OPERATOR4_SINGLE(RF_Type::Vec128UInt32,Not,~)
template<>
RF_Type::Vec128Float32 Operations<RF_Type::Vec128Float32,OperationSet::FPU_ALU>::Not(
    const RF_Type::Vec128Float32& A)
{
    RF_Type::Vec128Float32 ret;
    ret[0]=~((RF_Type::Int32)A[0]); ret[1]=~((RF_Type::Int32)A[1]);
    ret[2]=~((RF_Type::Int32)A[2]); ret[3]=~((RF_Type::Int32)A[3]);
    return ret;
} 
FPU_ALU_SPECIAL_OPERATOR8_SINGLE(RF_Type::Vec64Int8,Not,~)
FPU_ALU_SPECIAL_OPERATOR8_SINGLE(RF_Type::Vec64UInt8,Not,~)
FPU_ALU_SPECIAL_OPERATOR4_SINGLE(RF_Type::Vec64Int16,Not,~)
FPU_ALU_SPECIAL_OPERATOR4_SINGLE(RF_Type::Vec64UInt16,Not,~)
FPU_ALU_SPECIAL_OPERATOR2_SINGLE(RF_Type::Vec64Int32,Not,~)
FPU_ALU_SPECIAL_OPERATOR2_SINGLE(RF_Type::Vec64UInt32,Not,~)

FPU_ALU_SPECIAL_LOGICOPERATOR16(RF_Type::Vec128Int8,Equal,==)
FPU_ALU_SPECIAL_LOGICOPERATOR16(RF_Type::Vec128UInt8,Equal,==)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec128Int16,Equal,==)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec128UInt16,Equal,==)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128Int32,Equal,==)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128UInt32,Equal,==)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128Float32,Equal,==)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64Int8,Equal,==)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64UInt8,Equal,==)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64Int16,Equal,==)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64UInt16,Equal,==)
FPU_ALU_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64Int32,Equal,==)
FPU_ALU_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64UInt32,Equal,==)

FPU_ALU_SPECIAL_LOGICOPERATOR16(RF_Type::Vec128Int8,Less,<)
FPU_ALU_SPECIAL_LOGICOPERATOR16(RF_Type::Vec128UInt8,Less,<)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec128Int16,Less,<)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec128UInt16,Less,<)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128Int32,Less,<)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128UInt32,Less,<)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128Float32,Less,<)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64Int8,Less,<)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64UInt8,Less,<)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64Int16,Less,<)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64UInt16,Less,<)
FPU_ALU_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64Int32,Less,<)
FPU_ALU_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64UInt32,Less,<)

FPU_ALU_SPECIAL_LOGICOPERATOR16(RF_Type::Vec128Int8,LessEqual,<=)
FPU_ALU_SPECIAL_LOGICOPERATOR16(RF_Type::Vec128UInt8,LessEqual,<=)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec128Int16,LessEqual,<=)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec128UInt16,LessEqual,<=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128Int32,LessEqual,<=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128UInt32,LessEqual,<=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128Float32,LessEqual,<=)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64Int8,LessEqual,<=)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64UInt8,LessEqual,<=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64Int16,LessEqual,<=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64UInt16,LessEqual,<=)
FPU_ALU_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64Int32,LessEqual,<=)
FPU_ALU_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64UInt32,LessEqual,<=)

FPU_ALU_SPECIAL_LOGICOPERATOR16(RF_Type::Vec128Int8,Greater,>)
FPU_ALU_SPECIAL_LOGICOPERATOR16(RF_Type::Vec128UInt8,Greater,>)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec128Int16,Greater,>)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec128UInt16,Greater,>)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128Int32,Greater,>)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128UInt32,Greater,>)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128Float32,Greater,>)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64Int8,Greater,>)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64UInt8,Greater,>)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64Int16,Greater,>)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64UInt16,Greater,>)
FPU_ALU_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64Int32,Greater,>)
FPU_ALU_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64UInt32,Greater,>)

FPU_ALU_SPECIAL_LOGICOPERATOR16(RF_Type::Vec128Int8,GreaterEqual,>=)
FPU_ALU_SPECIAL_LOGICOPERATOR16(RF_Type::Vec128UInt8,GreaterEqual,>=)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec128Int16,GreaterEqual,>=)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec128UInt16,GreaterEqual,>=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128Int32,GreaterEqual,>=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128UInt32,GreaterEqual,>=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128Float32,GreaterEqual,>=)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64Int8,GreaterEqual,>=)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64UInt8,GreaterEqual,>=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64Int16,GreaterEqual,>=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64UInt16,GreaterEqual,>=)
FPU_ALU_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64Int32,GreaterEqual,>=)
FPU_ALU_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64UInt32,GreaterEqual,>=)

FPU_ALU_SPECIAL_LOGICOPERATOR16(RF_Type::Vec128Int8,NotEqual,!=)
FPU_ALU_SPECIAL_LOGICOPERATOR16(RF_Type::Vec128UInt8,NotEqual,!=)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec128Int16,NotEqual,!=)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec128UInt16,NotEqual,!=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128Int32,NotEqual,!=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128UInt32,NotEqual,!=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec128Float32,NotEqual,!=)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64Int8,NotEqual,!=)
FPU_ALU_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64UInt8,NotEqual,!=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64Int16,NotEqual,!=)
FPU_ALU_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64UInt16,NotEqual,!=)
FPU_ALU_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64Int32,NotEqual,!=)
FPU_ALU_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64UInt32,NotEqual,!=)

template<>
RF_Type::Vec128Float32 Operations<RF_Type::Vec128Float32,OperationSet::FPU_ALU>::Ordered(
    const RF_Type::Vec128Float32& A, const RF_Type::Vec128Float32& B)
{
    RF_Type::Vec128Float32 ret;
    ret[0]=((RF_Type::Int32)A[0]==Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN) || 
        ((RF_Type::Int32)B[0]==Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN); 
    ret[1]=((RF_Type::Int32)A[1]==Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN) || 
        ((RF_Type::Int32)B[1]==Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN); 
    ret[2]=((RF_Type::Int32)A[2]==Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN) || 
        ((RF_Type::Int32)B[2]==Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN); 
    ret[3]=((RF_Type::Int32)A[3]==Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN) || 
        ((RF_Type::Int32)B[3]==Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN); 
    return ret;
} 

template<>
RF_Type::Vec128Float32 Operations<RF_Type::Vec128Float32,OperationSet::FPU_ALU>::Unordered(
    const RF_Type::Vec128Float32& A, const RF_Type::Vec128Float32& B)
{
    RF_Type::Vec128Float32 ret;
    ret[0]=((RF_Type::Int32)A[0]!=Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN) &&
        ((RF_Type::Int32)B[0]!=Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN); 
    ret[1]=((RF_Type::Int32)A[1]!=Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN) && 
        ((RF_Type::Int32)B[1]!=Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN); 
    ret[2]=((RF_Type::Int32)A[2]!=Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN) && 
        ((RF_Type::Int32)B[2]!=Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN); 
    ret[3]=((RF_Type::Int32)A[3]!=Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN) && 
        ((RF_Type::Int32)B[3]!=Math::Math<RF_Type::Vec128Float32::ValueType>::QUITE_NAN); 
    return ret;
} 

FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,AddAssign,+=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,AddAssign,+=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,AddAssign,+=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,AddAssign,+=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,AddAssign,+=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,AddAssign,+=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Float32,AddAssign,+=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,AddAssign,+=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,AddAssign,+=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,AddAssign,+=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,AddAssign,+=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,AddAssign,+=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,AddAssign,+=)

FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,SubAssign,-=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,SubAssign,-=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,SubAssign,-=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,SubAssign,-=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,SubAssign,-=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,SubAssign,-=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Float32,SubAssign,-=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,SubAssign,-=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,SubAssign,-=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,SubAssign,-=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,SubAssign,-=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,SubAssign,-=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,SubAssign,-=)

FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,MulAssign,*=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,MulAssign,*=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,MulAssign,*=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,MulAssign,*=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,MulAssign,*=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,MulAssign,*=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Float32,MulAssign,*=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,MulAssign,*=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,MulAssign,*=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,MulAssign,*=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,MulAssign,*=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,MulAssign,*=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,MulAssign,*=)

FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,DivAssign,/=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,DivAssign,/=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,DivAssign,/=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,DivAssign,/=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,DivAssign,/=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,DivAssign,/=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Float32,DivAssign,/=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,DivAssign,/=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,DivAssign,/=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,DivAssign,/=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,DivAssign,/=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,DivAssign,/=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,DivAssign,/=)

FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,ModAssign,%=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,ModAssign,%=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,ModAssign,%=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,ModAssign,%=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,ModAssign,%=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,ModAssign,%=)
template<>
RF_Type::Vec128Float32& Operations<RF_Type::Vec128Float32,OperationSet::FPU_ALU>::ModAssign(
    RF_Type::Vec128Float32& A, const RF_Type::Vec128Float32& B)
{
    A=Sub(A,Mul(B,Floor(Div(A,B))));
    return A;
}  
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,ModAssign,%=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,ModAssign,%=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,ModAssign,%=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,ModAssign,%=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,ModAssign,%=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,ModAssign,%=)

FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,ShiftRightAssign,>>=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,ShiftRightAssign,>>=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,ShiftRightAssign,>>=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,ShiftRightAssign,>>=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,ShiftRightAssign,>>=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,ShiftRightAssign,>>=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,ShiftRightAssign,>>=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,ShiftRightAssign,>>=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,ShiftRightAssign,>>=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,ShiftRightAssign,>>=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,ShiftRightAssign,>>=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,ShiftRightAssign,>>=)

FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,ShiftLeftAssign,<<=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,ShiftLeftAssign,<<=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,ShiftLeftAssign,<<=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,ShiftLeftAssign,<<=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,ShiftLeftAssign,<<=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,ShiftLeftAssign,<<=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,ShiftLeftAssign,<<=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,ShiftLeftAssign,<<=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,ShiftLeftAssign,<<=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,ShiftLeftAssign,<<=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,ShiftLeftAssign,<<=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,ShiftLeftAssign,<<=)

FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,AndAssign,&=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,AndAssign,&=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,AndAssign,&=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,AndAssign,&=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,AndAssign,&=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,AndAssign,&=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,AndAssign,&=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,AndAssign,&=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,AndAssign,&=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,AndAssign,&=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,AndAssign,&=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,AndAssign,&=)

FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,XorAssign,^=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,XorAssign,^=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,XorAssign,^=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,XorAssign,^=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,XorAssign,^=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,XorAssign,^=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,XorAssign,^=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,XorAssign,^=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,XorAssign,^=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,XorAssign,^=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,XorAssign,^=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,XorAssign,^=)

FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,OrAssign,|=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,OrAssign,|=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,OrAssign,|=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,OrAssign,|=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,OrAssign,|=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,OrAssign,|=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,OrAssign,|=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,OrAssign,|=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,OrAssign,|=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,OrAssign,|=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,OrAssign,|=)
FPU_ALU_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,OrAssign,|=)
        
} } }

#ifndef RF_SHORTHAND_NAMESPACE_SIMD
#define RF_SHORTHAND_NAMESPACE_SIMD
namespace RF_SIMD = RadonFramework::Core::SIMD;
#endif

#endif // RF_CORE_SIMD_FPU_ALU_HPP