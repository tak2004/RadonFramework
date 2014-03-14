#ifndef RF_CORE_SIMD_OPSET_HPP
#define RF_CORE_SIMD_OPSET_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework
{
    namespace Core
    {
        namespace SIMD
        {
            namespace OperationSet
            {
                enum Type
                {
                    Unset=-1,
                    FPU_ALU=0,
                    MMX=1,
                    SSE,
                    SSE2,
                    SSE3,
                    SSE4_1,
                    SSE4_2,
                    AVX
                };
            }

            // Simple FPU and ALU implementation.
            template <typename VecType,Types::Int32 OpSet=OperationSet::Unset>
            struct Operations
            {
                // Store
                static inline void Init(const typename VecType::ValueType Value, VecType& A);

                // Arithmetic operations
                static inline VecType Add(const VecType& A, const VecType& B);
                static inline VecType Sub(const VecType& A, const VecType& B);
                static inline VecType Mul(const VecType& A, const VecType& B);
                static inline VecType Div(const VecType& A, const VecType& B);
                static inline VecType Mod(const VecType& A, const VecType& B);
                static inline VecType Avg(const VecType& A, const VecType& B);
                static inline VecType Min(const VecType& A, const VecType& B);
                static inline VecType Max(const VecType& A, const VecType& B);
                static inline VecType Reciprocal(const VecType& A);
                static inline VecType ReciprocalOfSqrt(const VecType& A);
                static inline VecType Sum(const VecType& A);
                static inline VecType Floor(const VecType& A);

                // Logical operations
                static inline VecType And(const VecType& A, const VecType& B);
                static inline VecType Not(const VecType& A);
                static inline VecType Or(const VecType& A, const VecType& B);
                static inline VecType Xor(const VecType& A, const VecType& B);

                // Comparsion
                static inline VecType Equal(const VecType& A, const VecType& B);
                static inline VecType Less(const VecType& A, const VecType& B);
                static inline VecType LessEqual(const VecType& A, const VecType& B);
                static inline VecType Greater(const VecType& A, const VecType& B);
                static inline VecType GreaterEqual(const VecType& A, const VecType& B);
                static inline VecType NotEqual(const VecType& A, const VecType& B);
                static inline VecType Ordered(const VecType& A, const VecType& B);
                static inline VecType Unordered(const VecType& A, const VecType& B);

                // Compound assignment operations
                static inline VecType& AddAssign(VecType& A, const VecType& B);
                static inline VecType& SubAssign(VecType& A, const VecType& B);
                static inline VecType& MulAssign(VecType& A, const VecType& B);
                static inline VecType& DivAssign(VecType& A, const VecType& B);
                static inline VecType& ModAssign(VecType& A, const VecType& B);
                static inline VecType& ShiftRightAssign(VecType& A, const VecType& B);
                static inline VecType& ShiftLeftAssign(VecType& A, const VecType& B);
                static inline VecType& AndAssign(VecType& A, const VecType& B);
                static inline VecType& XorAssign(VecType& A, const VecType& B);
                static inline VecType& OrAssign(VecType& A, const VecType& B);
            };

            // Default all types throw a compiler error except the specialized.

            template <typename VecType,Types::Int32 OpSet>
            void Operations<VecType,OpSet>::Init(const typename VecType::ValueType Value, VecType& A)
            { static_assert(0,"Not allowed template parameter use SIMD types"); }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Add(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Sub(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Mul(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Div(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Mod(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Avg(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Min(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Max(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Reciprocal(const VecType& A)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::ReciprocalOfSqrt(const VecType& A)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Sum(const VecType& A)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::And(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Not(const VecType& A)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Or(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Xor(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Equal(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Less(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::LessEqual(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Greater(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::GreaterEqual(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::NotEqual(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Ordered(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Unordered(const VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType Operations<VecType,OpSet>::Floor(const VecType& A)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType& Operations<VecType,OpSet>::AddAssign(VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType& Operations<VecType,OpSet>::SubAssign(VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType& Operations<VecType,OpSet>::MulAssign(VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType& Operations<VecType,OpSet>::DivAssign(VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType& Operations<VecType,OpSet>::ModAssign(VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType& Operations<VecType,OpSet>::ShiftRightAssign(VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType& Operations<VecType,OpSet>::ShiftLeftAssign(VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType& Operations<VecType,OpSet>::AndAssign(VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType& Operations<VecType,OpSet>::XorAssign(VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }

            template <typename VecType,Types::Int32 OpSet>
            VecType& Operations<VecType,OpSet>::OrAssign(VecType& A, const VecType& B)
            { static_assert(0,"Not allowed template parameter use SIMD types"); return A; }
        }
    }
}

#endif // RF_CORE_SIMD_OPSET_HPP