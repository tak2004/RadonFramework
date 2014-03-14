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
                Random(const RadonFramework::Core::Types::Int32 Seed=99999999);

                virtual RadonFramework::Core::Types::Int32 Next();
                virtual RadonFramework::Core::Types::Int32 Next(const RadonFramework::Core::Types::Int32 MaxValue);
                virtual RadonFramework::Core::Types::Int32 Next(const RadonFramework::Core::Types::Int32 MinValue,
                                                             const RadonFramework::Core::Types::Int32 MaxValue);
                virtual RadonFramework::Core::Types::Float32 NextFloat();
            protected:
                virtual RadonFramework::Core::Types::Float32 Sample();
                RadonFramework::Core::Types::Int32 m_Seed;
                RadonFramework::Core::Types::Int32 m_J;
                RadonFramework::Core::Types::Int32 m_K;
                RadonFramework::Core::Types::Int32 m_Buffer[55];
                RadonFramework::Core::Types::Int32 m_Index;
        };
    }
}

#endif // RF_MATH_RANDOM_HPP
