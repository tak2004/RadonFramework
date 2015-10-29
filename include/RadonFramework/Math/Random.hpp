#ifndef RF_MATH_RANDOM_HPP
#define RF_MATH_RANDOM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>

namespace RadonFramework { namespace Math {

/** @brief This class represent a number generator, which produce a sequence of random numbers.
*
* This class is a Fibonacci generator base on a subtractive generator.
* A Fibonacci generator use the floating point range from 0.0 till 1.0.
* It use a sequence of 55 numbers, which will be filled by the Sample method.
* You can derive a new generator from this class and overload the Sample method to change the
* random distribution or principle of the generator.
*/
class Random
{
public:
    Random(const RF_Type::Int32 Seed=99999999);

    virtual RF_Type::Int32 Next();
    virtual RF_Type::Int32 Next(const RF_Type::Int32 MaxValue);
    virtual RF_Type::Int32 Next(const RF_Type::Int32 MinValue,
                                const RF_Type::Int32 MaxValue);
    virtual RF_Type::Float32 NextFloat();
protected:
    static const RF_Type::Int32 BUFFER_ELEMENT_COUNT = 55;
    RF_Type::Float32 Sample();

    RF_Type::Int32 m_Seed;
    RF_Type::Int32 m_J;
    RF_Type::Int32 m_K;
    RF_Type::Int32 m_Buffer[BUFFER_ELEMENT_COUNT];
    RF_Type::Int32 m_Index;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_MATH
#define RF_SHORTHAND_NAMESPACE_MATH
namespace RF_Math = RadonFramework::Math;
#endif

#endif // RF_MATH_RANDOM_HPP
