#ifndef RF_CORE_SIMD_HPP
#define RF_CORE_SIMD_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/SIMD/FPU_ALU.hpp>

namespace RadonFramework { namespace Core {

// primitive cpu-dispatcher for methods or class operator without parameter
#define SIMD_CPU_DISPATCHER_1(OPERATION) SIMDVec a;\
    executeoperation:\
    switch (m_OperationSet)\
    {\
        case SIMD::OperationSet::FPU_ALU:\
            a.m_Value=RadonFramework::Core::SIMD::Operations<VecType,SIMD::OperationSet::FPU_ALU>::OPERATION(m_Value);\
            break;\
        case SIMD::OperationSet::SSE2:\
            a.m_Value=RadonFramework::Core::SIMD::Operations<VecType,SIMD::OperationSet::SSE2>::OPERATION(m_Value);\
            break;\
        case SIMD::OperationSet::Unset:\
            CheckAndSetOperationSet();\
            goto executeoperation;\
            break;\
    }\
    return a;\
}

// primitive cpu-dispatcher for methods or class operator with one parameter
#define SIMD_CPU_DISPATCHER_2(OPERATION) SIMDVec a;\
    executeoperation:\
    switch (m_OperationSet)\
    {\
        case SIMD::OperationSet::FPU_ALU:\
            a.m_Value=RadonFramework::Core::SIMD::Operations<VecType,SIMD::OperationSet::FPU_ALU>::OPERATION(m_Value,Other);\
            break;\
        case SIMD::OperationSet::SSE2:\
            a.m_Value=RadonFramework::Core::SIMD::Operations<VecType,SIMD::OperationSet::SSE2>::OPERATION(m_Value,Other);\
            break;\
        case SIMD::OperationSet::Unset:\
            CheckAndSetOperationSet();\
            goto executeoperation;\
            break;\
    }\
    return a;\
}

// Define a operator with no parameter.
#define SIMD_OPERATION_0(OPERATOR,OPERATION) SIMDVec operator OPERATOR()const{\
    SIMD_CPU_DISPATCHER_1(OPERATION)

// Define a method with no parameter.
#define SIMD_FUNCTION_0(OPERATOR,OPERATION) SIMDVec OPERATOR()const{\
    SIMD_CPU_DISPATCHER_1(OPERATION)

// Define a operator with one parameter.
#define SIMD_OPERATION_1(OPERATOR,OPERATION) SIMDVec operator OPERATOR(const VecType& Other)const{\
    SIMD_CPU_DISPATCHER_2(OPERATION)

// Define a method with one parameter.
#define SIMD_FUNCTION_1(OPERATOR,OPERATION) SIMDVec OPERATOR(const VecType& Other)const{\
    SIMD_CPU_DISPATCHER_2(OPERATION)

// Define a assignment operator.
#define SIMD_ASSIGNMENTOPERATION(OPERATOR,OPERATION) SIMDVec& operator OPERATOR(const VecType& Other){\
    executeoperation:\
    switch (m_OperationSet)\
    {\
        case SIMD::OperationSet::FPU_ALU:\
            RadonFramework::Core::SIMD::Operations<VecType,SIMD::OperationSet::FPU_ALU>::OPERATION(m_Value,Other);\
            break;\
        case SIMD::OperationSet::SSE2:\
            RadonFramework::Core::SIMD::Operations<VecType,SIMD::OperationSet::SSE2>::OPERATION(m_Value,Other);\
            break;\
        case SIMD::OperationSet::Unset:\
            CheckAndSetOperationSet();\
            goto executeoperation;\
            break;\
    }\
    return *this;\
}

// This facade look for the best cpu extension and call it.
template <typename VecType>
struct SIMDVec
{
    SIMDVec& Init(const typename VecType::ValueType Value)
    {
        executeoperation:
        switch (m_OperationSet)
        {
            case SIMD::OperationSet::FPU_ALU:
                RadonFramework::Core::SIMD::Operations<VecType,SIMD::OperationSet::FPU_ALU>::Init(Value,m_Value);
                break;
            case SIMD::OperationSet::SSE2:
                RadonFramework::Core::SIMD::Operations<VecType,SIMD::OperationSet::SSE2>::Init(Value,m_Value);
                break;
            case SIMD::OperationSet::Unset:
                CheckAndSetOperationSet();
                goto executeoperation;
                break;
        }
        return *this;
    }

    // Arithmetic operations
    SIMD_OPERATION_1(+,Add)
    SIMD_OPERATION_1(-,Sub)
    SIMD_OPERATION_1(*,Mul)
    SIMD_OPERATION_1(/,Div)
    SIMD_OPERATION_1(%,Mod)
    SIMD_FUNCTION_0(Floor,Floor)

    // Binary operations
    SIMD_OPERATION_1(&,And)
    SIMD_OPERATION_1(|,Or)
    SIMD_OPERATION_1(^,Xor)
    SIMD_OPERATION_0(~,Not)
            
    operator VecType(){
        return m_Value;
    }

    static void CheckAndSetOperationSet()
    {
        m_OperationSet=SIMD::OperationSet::SSE2;
    }

    // Comparsion
    SIMD_OPERATION_1(==,Equal)
    SIMD_OPERATION_1(<,Less)
    SIMD_OPERATION_1(<=,LessEqual)
    SIMD_OPERATION_1(>,Greater)
    SIMD_OPERATION_1(>=,GreaterEqual)
    SIMD_OPERATION_1(!=,NotEqual)
    /** 
    * Return a vector which set true(all bits 1) or false(0x0) for each element.
    * An element is set to true if the same element of each vector isn't NaN.
    * If one or both elements are NaN then the element will be set to false. 
    **/
    SIMD_FUNCTION_1(Ordered,Ordered);
            
    /** 
    * Return a vector which set true(all bits 1) or false(0x0) for each element.
    * An element is set to true if the same element of one or both vector is NaN.
    * If both elements aren't NaN then the element will be set to false. 
    **/
    SIMD_FUNCTION_1(Unordered,Unordered);

    // Compound assignment operations
    SIMD_ASSIGNMENTOPERATION(+=,AddAssign)
    SIMD_ASSIGNMENTOPERATION(-=,SubAssign)
    SIMD_ASSIGNMENTOPERATION(*=,MulAssign)
    SIMD_ASSIGNMENTOPERATION(/=,DivAssign)
    SIMD_ASSIGNMENTOPERATION(%=,ModAssign)
    SIMD_ASSIGNMENTOPERATION(>>=,ShiftRightAssign)
    SIMD_ASSIGNMENTOPERATION(<<=,ShiftLeftAssign)
    SIMD_ASSIGNMENTOPERATION(&=,AndAssign)
    SIMD_ASSIGNMENTOPERATION(^=,XorAssign)
    SIMD_ASSIGNMENTOPERATION(|=,OrAssign)

    // Additional operations
    SIMD_FUNCTION_1(Avg,Avg);            
    SIMD_FUNCTION_1(Min,Min);
    SIMD_FUNCTION_1(Max,Max);
    SIMD_FUNCTION_0(Reciprocal,Reciprocal);
    SIMD_FUNCTION_0(ReciprocalOfSqrt,ReciprocalOfSqrt);
    SIMD_FUNCTION_0(Sum,Sum);

    VecType m_Value;
    static RF_Type::Int32 m_OperationSet;
};
template <typename T> RF_Type::Int32 SIMDVec<T>::m_OperationSet=-1;

} }

#endif // RF_SYSTEM_SIMD_HPP