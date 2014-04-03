#ifndef RF_CORE_POLICIES_CPPALLOCATOR_HPP
#define RF_CORE_POLICIES_CPPALLOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <new>

namespace RadonFramework
{
    namespace Core
    {
        namespace Policies
        {
            struct CPPAllocator
            {
                template <typename T>
                static T* New()
                {
                    return new (std::nothrow) T;
                }

                template <typename T>
                static T* NewArray(RFTYPE::Size Length)
                {
                    if (Length==0)
                        return 0;
                    return new (std::nothrow) T[Length];
                }

                template <typename T>
                static void Free(T* p)
                {
                    if (p)
                        delete p;
                }

                template <typename T>
                static void FreeArray(T* p)
                {
                    if (p)
                        delete[] p;
                }
            };
        }
    }
}

#endif // RF_CORE_POLICIES_CPPALLOCATOR_HPP