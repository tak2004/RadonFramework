#ifndef RF_CORE_SIMD_SSE2_HPP
#define RF_CORE_SIMD_SSE2_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <xmmintrin.h>
#include <pmmintrin.h>

namespace RadonFramework { namespace Core { namespace SIMD {
            
// some helper macros
#define SSE2_SPECIAL_INIT16(TYPE,OPNAME) template<>\
    void Operations<TYPE,OperationSet::SSE2>::OPNAME(const TYPE::ValueType Value, TYPE& A)\
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

#define SSE2_SPECIAL_INIT8(TYPE,OPNAME) template<>\
    void Operations<TYPE,OperationSet::SSE2>::OPNAME(const TYPE::ValueType Value, TYPE& A)\
    {\
        A[0]=Value; A[1]=Value;\
        A[2]=Value; A[3]=Value;\
        A[4]=Value; A[5]=Value;\
        A[6]=Value; A[7]=Value;\
    } 

#define SSE2_SPECIAL_INIT4(TYPE,OPNAME) template<>\
    void Operations<TYPE,OperationSet::SSE2>::OPNAME(const TYPE::ValueType Value, TYPE& A)\
    {\
        A[0]=Value; A[1]=Value;\
        A[2]=Value; A[3]=Value;\
    } 

#define SSE2_SPECIAL_INIT2(TYPE,OPNAME) template<>\
    void Operations<TYPE,OperationSet::SSE2>::OPNAME(const TYPE::ValueType Value, TYPE& A)\
    { A[0]=Value; A[1]=Value; }

#define SSE2_SPECIAL_OPERATOR(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        __m128i a=_mm_load_si128((const __m128i*)A.m_Vector);\
        __m128i b=_mm_load_si128((const __m128i*)B.m_Vector);\
        _mm_store_si128((__m128i*)ret.m_Vector,OP);\
        return ret;\
    }

#define SSE2_SPECIAL_OPERATORF(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        __m128 a=_mm_load_ps(A.m_Vector);\
        __m128 b=_mm_load_ps(B.m_Vector);\
        _mm_store_ps(ret.m_Vector,OP);\
        return ret;\
    }

#define SSE2_SPECIAL_OPERATOR_EMPTY(TYPE,OPNAME) template<>\
    TYPE Operations<TYPE,OperationSet::SSE2>::OPNAME(const TYPE& A){return A;}

#define SSE2_SPECIAL_OPERATOR16(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::SSE2>::OPNAME(\
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

#define SSE2_SPECIAL_OPERATOR8(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0]; ret[1]=A[1] OP B[1];\
        ret[2]=A[2] OP B[2]; ret[3]=A[3] OP B[3];\
        ret[4]=A[4] OP B[4]; ret[5]=A[5] OP B[5];\
        ret[6]=A[6] OP B[6]; ret[7]=A[7] OP B[7];\
        return ret;\
    }

#define SSE2_SPECIAL_OPERATOR4(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0]; ret[1]=A[1] OP B[1];\
        ret[2]=A[2] OP B[2]; ret[3]=A[3] OP B[3];\
        return ret;\
    }

#define SSE2_SPECIAL_OPERATOR2(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0]; ret[1]=A[1] OP B[1];\
        return ret;\
    }

#define SSE2_SPECIAL_LOGICOPERATOR16(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::SSE2>::OPNAME(\
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

#define SSE2_SPECIAL_LOGICOPERATOR8(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0] ? 0xffff : 0x00; ret[1]=A[1] OP B[1] ? 0xffff : 0x00;\
        ret[2]=A[2] OP B[2] ? 0xffff : 0x00; ret[3]=A[3] OP B[3] ? 0xffff : 0x00;\
        ret[4]=A[4] OP B[4] ? 0xffff : 0x00; ret[5]=A[5] OP B[5] ? 0xffff : 0x00;\
        ret[6]=A[6] OP B[6] ? 0xffff : 0x00; ret[7]=A[7] OP B[7] ? 0xffff : 0x00;\
        return ret;\
    }

#define SSE2_SPECIAL_LOGICOPERATOR4(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0] ? 0xffffffff : 0x00; ret[1]=A[1] OP B[1] ? 0xffffffff : 0x00;\
        ret[2]=A[2] OP B[2] ? 0xffffffff : 0x00; ret[3]=A[3] OP B[3] ? 0xffffffff : 0x00;\
        return ret;\
    }

#define SSE2_SPECIAL_LOGICOPERATOR2(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        ret[0]=A[0] OP B[0] ? 0xffffffffffffffff : 0x00; ret[1]=A[1] OP B[1]? 0xffffffffffffffff : 0x00;\
        return ret;\
    }

#define SSE2_SPECIAL_OPERATOR_NOT(TYPE,OPNAME) template<>\
    TYPE Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        const TYPE& A)\
    {\
        TYPE ret;\
        __m128i one=_mm_set1_epi8(0xff);\
        __m128i a=_mm_load_si128((const __m128i*)A.m_Vector);\
        _mm_store_si128((__m128i*)ret.m_Vector,_mm_andnot_si128(a,one));\
        return ret;\
    }

#define SSE2_SPECIAL_NOTOPERATOR(TYPE,OPNAME,OP) template<>\
    TYPE Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        const TYPE& A, const TYPE& B)\
    {\
        TYPE ret;\
        __m128i one=_mm_set1_epi8(0xff);\
        __m128i a=_mm_load_si128((const __m128i*)A.m_Vector);\
        __m128i b=_mm_load_si128((const __m128i*)B.m_Vector);\
        _mm_store_si128((__m128i*)ret.m_Vector,_mm_andnot_si128(OP,one));\
        return ret;\
    }

#define SSE2_SPECIAL_ASSIGNOPERATOR(TYPE,OPNAME,OP) template<>\
    TYPE& Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        TYPE& A, const TYPE& B)\
    {\
        __m128i a=_mm_load_si128((const __m128i*)A.m_Vector);\
        __m128i b=_mm_load_si128((const __m128i*)B.m_Vector);\
        _mm_store_si128((__m128i*)A.m_Vector,OP);\
        return A;\
    }

#define SSE2_SPECIAL_ASSIGNOPERATORF(TYPE,OPNAME,OP) template<>\
    TYPE& Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        TYPE& A, const TYPE& B)\
    {\
        __m128 a=_mm_load_ps(A.m_Vector);\
        __m128 b=_mm_load_ps(B.m_Vector);\
        _mm_store_ps(A.m_Vector,OP);\
        return A;\
    }

#define SSE2_SPECIAL_ASSIGNOPERATOR16(TYPE,OPNAME,OP) template<>\
    TYPE& Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        TYPE& A, const TYPE& B)\
    {\
        A[0]=A[0] OP B[0]; A[1]=A[1] OP B[1];\
        A[2]=A[2] OP B[2]; A[3]=A[3] OP B[3];\
        A[4]=A[4] OP B[4]; A[5]=A[5] OP B[5];\
        A[6]=A[6] OP B[6]; A[7]=A[7] OP B[7];\
        A[8]=A[8] OP B[8]; A[9]=A[9] OP B[9];\
        A[10]=A[10] OP B[10]; A[11]=A[11] OP B[11];\
        A[12]=A[12] OP B[12]; A[13]=A[13] OP B[13];\
        A[14]=A[14] OP B[14]; A[15]=A[15] OP B[15];\
        return A;\
    }

#define SSE2_SPECIAL_ASSIGNOPERATOR8(TYPE,OPNAME,OP) template<>\
    TYPE& Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        TYPE& A, const TYPE& B)\
    {\
        A[0]=A[0] OP B[0]; A[1]=A[1] OP B[1];\
        A[2]=A[2] OP B[2]; A[3]=A[3] OP B[3];\
        A[4]=A[4] OP B[4]; A[5]=A[5] OP B[5];\
        A[6]=A[6] OP B[6]; A[7]=A[7] OP B[7];\
        return A;\
    }

#define SSE2_SPECIAL_ASSIGNOPERATOR4(TYPE,OPNAME,OP) template<>\
    TYPE& Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        TYPE& A, const TYPE& B)\
    {\
        A[0]=A[0] OP B[0]; A[1]=A[1] OP B[1];\
        A[2]=A[2] OP B[2]; A[3]=A[3] OP B[3];\
        return A;\
    }

#define SSE2_SPECIAL_ASSIGNOPERATOR2(TYPE,OPNAME,OP) template<>\
    TYPE& Operations<TYPE,OperationSet::SSE2>::OPNAME(\
        TYPE& A, const TYPE& B)\
    {\
        A[0]=A[0] OP B[0]; A[1]=A[1] OP B[1];\
        return A;\
    }

// Init one value to vector
// fallback to alu
SSE2_SPECIAL_INIT16(RF_Type::Vec128Int8,Init)
SSE2_SPECIAL_INIT16(RF_Type::Vec128UInt8,Init)
SSE2_SPECIAL_INIT8(RF_Type::Vec128Int16,Init)
SSE2_SPECIAL_INIT8(RF_Type::Vec128UInt16,Init)
SSE2_SPECIAL_INIT4(RF_Type::Vec128Int32,Init)
SSE2_SPECIAL_INIT4(RF_Type::Vec128UInt32,Init)
// optimized
template<>
void Operations<RF_Type::Vec128Float32,OperationSet::SSE2>::Init(
    const typename RF_Type::Vec128Float32::ValueType Value, RF_Type::Vec128Float32& A)
{ _mm_store_ps(A.m_Vector,_mm_load1_ps(&Value)); }

// fallback to alu
SSE2_SPECIAL_INIT8(RF_Type::Vec64Int8,Init)
SSE2_SPECIAL_INIT8(RF_Type::Vec64UInt8,Init)
SSE2_SPECIAL_INIT4(RF_Type::Vec64Int16,Init)
SSE2_SPECIAL_INIT4(RF_Type::Vec64UInt16,Init)
SSE2_SPECIAL_INIT2(RF_Type::Vec64Int32,Init)
SSE2_SPECIAL_INIT2(RF_Type::Vec64UInt32,Init)         

// Addition
// optimized
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int8,Add,_mm_add_epi8(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt8,Add,_mm_add_epi8(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int16,Add,_mm_add_epi16(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt16,Add,_mm_add_epi16(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int32,Add,_mm_add_epi32(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt32,Add,_mm_add_epi32(a,b))
SSE2_SPECIAL_OPERATORF(RF_Type::Vec128Float32,Add,_mm_add_ps(a,b))
// fallback to alu
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec64Int8,Add,+)
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec64UInt8,Add,+)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec64Int16,Add,+)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec64UInt16,Add,+)
SSE2_SPECIAL_OPERATOR2(RF_Type::Vec64Int32,Add,+)
SSE2_SPECIAL_OPERATOR2(RF_Type::Vec64UInt32,Add,+)

// Substraction
// optimized
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int8,Sub,_mm_sub_epi8(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt8,Sub,_mm_sub_epi8(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int16,Sub,_mm_sub_epi16(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt16,Sub,_mm_sub_epi16(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int32,Sub,_mm_sub_epi32(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt32,Sub,_mm_sub_epi32(a,b))
SSE2_SPECIAL_OPERATORF(RF_Type::Vec128Float32,Sub,_mm_sub_ps(a,b))
// fallback to alu
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec64Int8,Sub,-)
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec64UInt8,Sub,-)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec64Int16,Sub,-)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec64UInt16,Sub,-)
SSE2_SPECIAL_OPERATOR2(RF_Type::Vec64Int32,Sub,-)
SSE2_SPECIAL_OPERATOR2(RF_Type::Vec64UInt32,Sub,-)

// Multiplication
// fallback to alu
SSE2_SPECIAL_OPERATOR16(RF_Type::Vec128Int8,Mul,*)
SSE2_SPECIAL_OPERATOR16(RF_Type::Vec128UInt8,Mul,*)
// optimized
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int16,Mul,_mm_mulhi_epi16(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt16,Mul,_mm_mulhi_epu16(a,b))
// fallback to alu
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec128Int32,Mul,*)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec128UInt32,Mul,*)
// optimized
SSE2_SPECIAL_OPERATORF(RF_Type::Vec128Float32,Mul,_mm_mul_ps(a,b))
// fallback to alu
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec64Int8,Mul,*)
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec64UInt8,Mul,*)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec64Int16,Mul,*)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec64UInt16,Mul,*)
SSE2_SPECIAL_OPERATOR2(RF_Type::Vec64Int32,Mul,*)
SSE2_SPECIAL_OPERATOR2(RF_Type::Vec64UInt32,Mul,*)

// Division
// fallback to alu
SSE2_SPECIAL_OPERATOR16(RF_Type::Vec128Int8,Div,/)
SSE2_SPECIAL_OPERATOR16(RF_Type::Vec128UInt8,Div,/)
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec128Int16,Div,/)
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec128UInt16,Div,/)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec128Int32,Div,/)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec128UInt32,Div,/)
// optimized
SSE2_SPECIAL_OPERATORF(RF_Type::Vec128Float32,Div,_mm_div_ps(a,b))
// fallback to alu
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec64Int8,Div,/)
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec64UInt8,Div,/)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec64Int16,Div,/)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec64UInt16,Div,/)
SSE2_SPECIAL_OPERATOR2(RF_Type::Vec64Int32,Div,/)
SSE2_SPECIAL_OPERATOR2(RF_Type::Vec64UInt32,Div,/)

// Modulo
// fallback to alu
SSE2_SPECIAL_OPERATOR16(RF_Type::Vec128Int8,Mod,%)
SSE2_SPECIAL_OPERATOR16(RF_Type::Vec128UInt8,Mod,%)
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec128Int16,Mod,%)
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec128UInt16,Mod,%)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec128Int32,Mod,%)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec128UInt32,Mod,%)
// optimized
template<>
RF_Type::Vec128Float32 Operations<RF_Type::Vec128Float32,OperationSet::SSE2>::Mod(
    const RF_Type::Vec128Float32& A, const RF_Type::Vec128Float32& B)
{
    RF_Type::Vec128Float32 ret;
    // Sub(A,Mul(B,Floor(Div(A,B))));
    __m128 a=_mm_load_ps(A.m_Vector);
    __m128 b=_mm_load_ps(B.m_Vector);
    _mm_store_ps(ret.m_Vector,_mm_sub_ps(a,_mm_mul_ps(a,
        _mm_cvtepi32_ps(_mm_cvttps_epi32(_mm_div_ps(a,b))))));
    return ret;
}
// fallback to alu
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec64Int8,Mod,%)
SSE2_SPECIAL_OPERATOR8(RF_Type::Vec64UInt8,Mod,%)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec64Int16,Mod,%)
SSE2_SPECIAL_OPERATOR4(RF_Type::Vec64UInt16,Mod,%)
SSE2_SPECIAL_OPERATOR2(RF_Type::Vec64Int32,Mod,%)
SSE2_SPECIAL_OPERATOR2(RF_Type::Vec64UInt32,Mod,%)
            
// Floor
// fallback to alu
SSE2_SPECIAL_OPERATOR_EMPTY(RF_Type::Vec128Int8,Floor)
SSE2_SPECIAL_OPERATOR_EMPTY(RF_Type::Vec128UInt8,Floor)
SSE2_SPECIAL_OPERATOR_EMPTY(RF_Type::Vec128Int16,Floor)
SSE2_SPECIAL_OPERATOR_EMPTY(RF_Type::Vec128UInt16,Floor)
SSE2_SPECIAL_OPERATOR_EMPTY(RF_Type::Vec128Int32,Floor)
SSE2_SPECIAL_OPERATOR_EMPTY(RF_Type::Vec128UInt32,Floor)
// optimized
template<>
RF_Type::Vec128Float32 Operations<RF_Type::Vec128Float32,OperationSet::SSE2>::Floor(
    const RF_Type::Vec128Float32& A)
{
    RF_Type::Vec128Float32 ret;
    __m128 c=_mm_cvtepi32_ps(_mm_cvttps_epi32(_mm_load_ps(A.m_Vector)));
    _mm_store_ps(ret.m_Vector,c);
    return ret;
}
// fallback to alu
SSE2_SPECIAL_OPERATOR_EMPTY(RF_Type::Vec64Int8,Floor)
SSE2_SPECIAL_OPERATOR_EMPTY(RF_Type::Vec64UInt8,Floor)
SSE2_SPECIAL_OPERATOR_EMPTY(RF_Type::Vec64Int16,Floor)
SSE2_SPECIAL_OPERATOR_EMPTY(RF_Type::Vec64UInt16,Floor)
SSE2_SPECIAL_OPERATOR_EMPTY(RF_Type::Vec64Int32,Floor)
SSE2_SPECIAL_OPERATOR_EMPTY(RF_Type::Vec64UInt32,Floor)

// And
// optimized
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int8,And,_mm_and_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt8,And,_mm_and_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int16,And,_mm_and_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt16,And,_mm_and_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int32,And,_mm_and_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt32,And,_mm_and_si128(a,b))
template<>
RF_Type::Vec128Float32 Operations<RF_Type::Vec128Float32,OperationSet::SSE2>::And(
    const RF_Type::Vec128Float32& A, const RF_Type::Vec128Float32& B)
{
    RF_Type::Vec128Float32 ret;
    __m128 a=_mm_load_ps(A.m_Vector);
    __m128 b=_mm_load_ps(B.m_Vector);
    _mm_store_ps(ret.m_Vector,_mm_and_ps(a,b));
    return ret;
}  
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64Int8,And,_mm_and_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64UInt8,And,_mm_and_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64Int16,And,_mm_and_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64UInt16,And,_mm_and_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64Int32,And,_mm_and_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64UInt32,And,_mm_and_si128(a,b))

// Or
// optimized
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int8,Or,_mm_or_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt8,Or,_mm_or_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int16,Or,_mm_or_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt16,Or,_mm_or_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int32,Or,_mm_or_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt32,Or,_mm_or_si128(a,b))
template<>
RF_Type::Vec128Float32 Operations<RF_Type::Vec128Float32,OperationSet::SSE2>::Or(
    const RF_Type::Vec128Float32& A, const RF_Type::Vec128Float32& B)
{
    RF_Type::Vec128Float32 ret;
    __m128 a=_mm_load_ps(A.m_Vector);
    __m128 b=_mm_load_ps(B.m_Vector);
    _mm_store_ps(ret.m_Vector,_mm_or_ps(a,b));
    return ret;
} 
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64Int8,Or,_mm_or_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64UInt8,Or,_mm_or_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64Int16,Or,_mm_or_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64UInt16,Or,_mm_or_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64Int32,Or,_mm_or_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64UInt32,Or,_mm_or_si128(a,b))

// Xor
// optimized
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int8,Xor,_mm_xor_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt8,Xor,_mm_xor_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int16,Xor,_mm_xor_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt16,Xor,_mm_xor_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int32,Xor,_mm_xor_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt32,Xor,_mm_xor_si128(a,b))
template<>
RF_Type::Vec128Float32 Operations<RF_Type::Vec128Float32,OperationSet::SSE2>::Xor(
    const RF_Type::Vec128Float32& A, const RF_Type::Vec128Float32& B)
{
    RF_Type::Vec128Float32 ret;
    __m128 a=_mm_load_ps(A.m_Vector);
    __m128 b=_mm_load_ps(B.m_Vector);
    _mm_store_ps(ret.m_Vector,_mm_xor_ps(a,b));
    return ret;
} 
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64Int8,Xor,_mm_xor_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64UInt8,Xor,_mm_xor_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64Int16,Xor,_mm_xor_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64UInt16,Xor,_mm_xor_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64Int32,Xor,_mm_xor_si128(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec64UInt32,Xor,_mm_xor_si128(a,b))

// Not
// optimized
SSE2_SPECIAL_OPERATOR_NOT(RF_Type::Vec128Int8,Not)
SSE2_SPECIAL_OPERATOR_NOT(RF_Type::Vec128UInt8,Not)
SSE2_SPECIAL_OPERATOR_NOT(RF_Type::Vec128Int16,Not)
SSE2_SPECIAL_OPERATOR_NOT(RF_Type::Vec128UInt16,Not)
SSE2_SPECIAL_OPERATOR_NOT(RF_Type::Vec128Int32,Not)
SSE2_SPECIAL_OPERATOR_NOT(RF_Type::Vec128UInt32,Not)
// little hack, move to float version if load/store will be optimized
SSE2_SPECIAL_OPERATOR_NOT(RF_Type::Vec128Float32,Not)
SSE2_SPECIAL_OPERATOR_NOT(RF_Type::Vec64Int8,Not)
SSE2_SPECIAL_OPERATOR_NOT(RF_Type::Vec64UInt8,Not)
SSE2_SPECIAL_OPERATOR_NOT(RF_Type::Vec64Int16,Not)
SSE2_SPECIAL_OPERATOR_NOT(RF_Type::Vec64UInt16,Not)
SSE2_SPECIAL_OPERATOR_NOT(RF_Type::Vec64Int32,Not)
SSE2_SPECIAL_OPERATOR_NOT(RF_Type::Vec64UInt32,Not)

// Equal
// optimized
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int8,Equal,_mm_cmpeq_epi8(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt8,Equal,_mm_cmpeq_epi8(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int16,Equal,_mm_cmpeq_epi16(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt16,Equal,_mm_cmpeq_epi16(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int32,Equal,_mm_cmpeq_epi32(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt32,Equal,_mm_cmpeq_epi32(a,b))
SSE2_SPECIAL_OPERATORF(RF_Type::Vec128Float32,Equal,_mm_cmpeq_ps(a,b))
// fallback to alu
SSE2_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64Int8,Equal,==)
SSE2_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64UInt8,Equal,==)
SSE2_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64Int16,Equal,==)
SSE2_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64UInt16,Equal,==)
SSE2_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64Int32,Equal,==)
SSE2_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64UInt32,Equal,==)

// Less
// optimized
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int8,Less,_mm_cmplt_epi8(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt8,Less,_mm_cmplt_epi8(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int16,Less,_mm_cmplt_epi16(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt16,Less,_mm_cmplt_epi16(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int32,Less,_mm_cmplt_epi32(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt32,Less,_mm_cmplt_epi32(a,b))
SSE2_SPECIAL_OPERATORF(RF_Type::Vec128Float32,Less,_mm_cmplt_ps(a,b))
// fallback to alu
SSE2_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64Int8,Less,<)
SSE2_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64UInt8,Less,<)
SSE2_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64Int16,Less,<)
SSE2_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64UInt16,Less,<)
SSE2_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64Int32,Less,<)
SSE2_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64UInt32,Less,<)

// LessEqual
// optimized
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128Int8,LessEqual,_mm_cmpgt_epi8(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128UInt8,LessEqual,_mm_cmpgt_epi8(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128Int16,LessEqual,_mm_cmpgt_epi16(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128UInt16,LessEqual,_mm_cmpgt_epi16(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128Int32,LessEqual,_mm_cmpgt_epi32(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128UInt32,LessEqual,_mm_cmpgt_epi32(a,b))
SSE2_SPECIAL_OPERATORF(RF_Type::Vec128Float32,LessEqual,_mm_cmple_ps(a,b))
// fallback to alu
SSE2_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64Int8,LessEqual,<=)
SSE2_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64UInt8,LessEqual,<=)
SSE2_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64Int16,LessEqual,<=)
SSE2_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64UInt16,LessEqual,<=)
SSE2_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64Int32,LessEqual,<=)
SSE2_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64UInt32,LessEqual,<=)

// Greater
// optimized
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int8,Greater,_mm_cmpgt_epi8(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt8,Greater,_mm_cmpgt_epi8(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int16,Greater,_mm_cmpgt_epi16(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt16,Greater,_mm_cmpgt_epi16(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128Int32,Greater,_mm_cmpgt_epi32(a,b))
SSE2_SPECIAL_OPERATOR(RF_Type::Vec128UInt32,Greater,_mm_cmpgt_epi32(a,b))
SSE2_SPECIAL_OPERATORF(RF_Type::Vec128Float32,Greater,_mm_cmpgt_ps(a,b))
// fallback to alu
SSE2_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64Int8,Greater,>)
SSE2_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64UInt8,Greater,>)
SSE2_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64Int16,Greater,>)
SSE2_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64UInt16,Greater,>)
SSE2_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64Int32,Greater,>)
SSE2_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64UInt32,Greater,>)

// GreaterEqual
// optimized
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128Int8,GreaterEqual,_mm_cmplt_epi8(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128UInt8,GreaterEqual,_mm_cmplt_epi8(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128Int16,GreaterEqual,_mm_cmplt_epi16(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128UInt16,GreaterEqual,_mm_cmplt_epi16(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128Int32,GreaterEqual,_mm_cmplt_epi32(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128UInt32,GreaterEqual,_mm_cmplt_epi32(a,b))
SSE2_SPECIAL_OPERATORF(RF_Type::Vec128Float32,GreaterEqual,_mm_cmpge_ps(a,b))
// fallback to alu
SSE2_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64Int8,GreaterEqual,>=)
SSE2_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64UInt8,GreaterEqual,>=)
SSE2_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64Int16,GreaterEqual,>=)
SSE2_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64UInt16,GreaterEqual,>=)
SSE2_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64Int32,GreaterEqual,>=)
SSE2_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64UInt32,GreaterEqual,>=)

// NotEqual
// optimized
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128Int8,NotEqual,_mm_cmpeq_epi8(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128UInt8,NotEqual,_mm_cmpeq_epi8(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128Int16,NotEqual,_mm_cmpeq_epi16(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128UInt16,NotEqual,_mm_cmpeq_epi16(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128Int32,NotEqual,_mm_cmpeq_epi32(a,b))
SSE2_SPECIAL_NOTOPERATOR(RF_Type::Vec128UInt32,NotEqual,_mm_cmpeq_epi32(a,b))
SSE2_SPECIAL_OPERATORF(RF_Type::Vec128Float32,NotEqual,_mm_cmpneq_ps(a,b))
// fallback to alu
SSE2_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64Int8,NotEqual,!=)
SSE2_SPECIAL_LOGICOPERATOR8(RF_Type::Vec64UInt8,NotEqual,!=)
SSE2_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64Int16,NotEqual,!=)
SSE2_SPECIAL_LOGICOPERATOR4(RF_Type::Vec64UInt16,NotEqual,!=)
SSE2_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64Int32,NotEqual,!=)
SSE2_SPECIAL_LOGICOPERATOR2(RF_Type::Vec64UInt32,NotEqual,!=)

// Ordered
SSE2_SPECIAL_OPERATORF(RF_Type::Vec128Float32,Ordered,_mm_cmpord_ps(a,b))

// Unordered
SSE2_SPECIAL_OPERATORF(RF_Type::Vec128Float32,Unordered,_mm_cmpunord_ps(a,b))

// AdditionAssign
// optimized
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128Int8,AddAssign,_mm_add_epi8(a,b))
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128UInt8,AddAssign,_mm_add_epi8(a,b))
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128Int16,AddAssign,_mm_add_epi16(a,b))
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128UInt16,AddAssign,_mm_add_epi16(a,b))
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128Int32,AddAssign,_mm_add_epi32(a,b))
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128UInt32,AddAssign,_mm_add_epi32(a,b))
SSE2_SPECIAL_ASSIGNOPERATORF(RF_Type::Vec128Float32,AddAssign,_mm_add_ps(a,b))
// fallback to alu
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,AddAssign,+)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,AddAssign,+)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,AddAssign,+)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,AddAssign,+)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,AddAssign,+)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,AddAssign,+)

// SubstractionAssign
// optimized
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128Int8,SubAssign,_mm_sub_epi8(a,b))
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128UInt8,SubAssign,_mm_sub_epi8(a,b))
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128Int16,SubAssign,_mm_sub_epi16(a,b))
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128UInt16,SubAssign,_mm_sub_epi16(a,b))
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128Int32,SubAssign,_mm_sub_epi32(a,b))
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128UInt32,SubAssign,_mm_sub_epi32(a,b))
SSE2_SPECIAL_ASSIGNOPERATORF(RF_Type::Vec128Float32,SubAssign,_mm_sub_ps(a,b))
// fallback to alu
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,SubAssign,-)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,SubAssign,-)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,SubAssign,-)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,SubAssign,-)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,SubAssign,-)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,SubAssign,-)

// MultiplicationAssign
// fallback to alu
SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,MulAssign,*=)
SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,MulAssign,*=)
// optimized
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128Int16,MulAssign,_mm_mulhi_epi16(a,b))
SSE2_SPECIAL_ASSIGNOPERATOR(RF_Type::Vec128UInt16,MulAssign,_mm_mulhi_epu16(a,b))
// fallback to alu
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,MulAssign,*=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,MulAssign,*=)
// optimized
SSE2_SPECIAL_ASSIGNOPERATORF(RF_Type::Vec128Float32,MulAssign,_mm_mul_ps(a,b))
// fallback to alu
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,MulAssign,*=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,MulAssign,*=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,MulAssign,*=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,MulAssign,*=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,MulAssign,*=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,MulAssign,*=)

// Division
// fallback to alu
SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,DivAssign,/=)
SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,DivAssign,/=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,DivAssign,/=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,DivAssign,/=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,DivAssign,/=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,DivAssign,/=)
// optimized
SSE2_SPECIAL_ASSIGNOPERATORF(RF_Type::Vec128Float32,DivAssign,_mm_div_ps(a,b))
// fallback to alu
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,DivAssign,/=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,DivAssign,/=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,DivAssign,/=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,DivAssign,/=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,DivAssign,/=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,DivAssign,/=)

// Modulo
// fallback to alu
SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,ModAssign,%=)
SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,ModAssign,%=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,ModAssign,%=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,ModAssign,%=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,ModAssign,%=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,ModAssign,%=)
// optimized
template<>
RF_Type::Vec128Float32& Operations<RF_Type::Vec128Float32,OperationSet::SSE2>::ModAssign(
    RF_Type::Vec128Float32& A, const RF_Type::Vec128Float32& B)
{
    // Sub(A,Mul(B,Floor(Div(A,B))));
    __m128 a=_mm_load_ps(A.m_Vector);
    __m128 b=_mm_load_ps(B.m_Vector);
    _mm_store_ps(A.m_Vector,_mm_sub_ps(a,_mm_mul_ps(a,
        _mm_cvtepi32_ps(_mm_cvttps_epi32(_mm_div_ps(a,b))))));
    return A;
}
// fallback to alu
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,ModAssign,%=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,ModAssign,%=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,ModAssign,%=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,ModAssign,%=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,ModAssign,%=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,ModAssign,%=)

SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,ShiftLeftAssign,<<=)
SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,ShiftLeftAssign,<<=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,ShiftLeftAssign,<<=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,ShiftLeftAssign,<<=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,ShiftLeftAssign,<<=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,ShiftLeftAssign,<<=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,ShiftLeftAssign,<<=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,ShiftLeftAssign,<<=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,ShiftLeftAssign,<<=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,ShiftLeftAssign,<<=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,ShiftLeftAssign,<<=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,ShiftLeftAssign,<<=)

SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,ShiftRightAssign,>>=)
SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,ShiftRightAssign,>>=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,ShiftRightAssign,>>=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,ShiftRightAssign,>>=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,ShiftRightAssign,>>=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,ShiftRightAssign,>>=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,ShiftRightAssign,>>=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,ShiftRightAssign,>>=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,ShiftRightAssign,>>=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,ShiftRightAssign,>>=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,ShiftRightAssign,>>=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,ShiftRightAssign,>>=)

SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,AndAssign,&=)
SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,AndAssign,&=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,AndAssign,&=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,AndAssign,&=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,AndAssign,&=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,AndAssign,&=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,AndAssign,&=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,AndAssign,&=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,AndAssign,&=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,AndAssign,&=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,AndAssign,&=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,AndAssign,&=)

SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,OrAssign,|=)
SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,OrAssign,|=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,OrAssign,|=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,OrAssign,|=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,OrAssign,|=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,OrAssign,|=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,OrAssign,|=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,OrAssign,|=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,OrAssign,|=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,OrAssign,|=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,OrAssign,|=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,OrAssign,|=)

SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128Int8,XorAssign,^=)
SSE2_SPECIAL_ASSIGNOPERATOR16(RF_Type::Vec128UInt8,XorAssign,^=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128Int16,XorAssign,^=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec128UInt16,XorAssign,^=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128Int32,XorAssign,^=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec128UInt32,XorAssign,^=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64Int8,XorAssign,^=)
SSE2_SPECIAL_ASSIGNOPERATOR8(RF_Type::Vec64UInt8,XorAssign,^=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64Int16,XorAssign,^=)
SSE2_SPECIAL_ASSIGNOPERATOR4(RF_Type::Vec64UInt16,XorAssign,^=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64Int32,XorAssign,^=)
SSE2_SPECIAL_ASSIGNOPERATOR2(RF_Type::Vec64UInt32,XorAssign,^=)

} } }

#ifndef RF_SHORTHAND_NAMESPACE_SIMD
#define RF_SHORTHAND_NAMESPACE_SIMD
namespace RF_SIMD = RadonFramework::Core::SIMD;
#endif

#endif // RF_CORE_SIMD_SSE2_HPP