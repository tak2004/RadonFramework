#ifndef RF_MATH_RANDOM_HPP
#define RF_MATH_RANDOM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>

namespace RadonFramework
{
    namespace Math
    {
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
                Random(const RFTYPE::Int32 Seed=99999999);

                virtual RFTYPE::Int32 Next();
                virtual RFTYPE::Int32 Next(const RFTYPE::Int32 MaxValue);
                virtual RFTYPE::Int32 Next(const RFTYPE::Int32 MinValue,
                                                             const RFTYPE::Int32 MaxValue);
                virtual RFTYPE::Float32 NextFloat();
            protected:
                virtual RFTYPE::Float32 Sample();
                RFTYPE::Int32 m_Seed;
                RFTYPE::Int32 m_J;
                RFTYPE::Int32 m_K;
                RFTYPE::Int32 m_Buffer[55];
                RFTYPE::Int32 m_Index;
        };
    }
}

#endif // RF_MATH_RANDOM_HPP
