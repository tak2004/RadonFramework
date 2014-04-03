#ifndef RF_MATH_HASH_HASH_HPP
#define RF_MATH_HASH_HASH_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>

namespace RadonFramework
{
    namespace Math
    {
        namespace Hash
        {
            class IHashfunction;

            struct Hash
            {
                static Memory::AutoPointerArray<RFTYPE::UInt8> Generate(
                    const RFTYPE::UInt8 * Data, 
                    RFTYPE::UInt32 Size,
                    IHashfunction& Hashfunction);

                static Memory::AutoPointerArray<RFTYPE::UInt8> Generate(
                    const RFTYPE::UInt8 * Data, 
                    RFTYPE::UInt32 Size,
                    const RFTYPE::String& HashfunctionName);
                    
                static Memory::AutoPointerArray<RFTYPE::UInt8> Generate(
                    const char* Text,
                    const RFTYPE::String& HashfunctionName);

                template <typename T>
                static T Generate(const RFTYPE::UInt8 * Data, 
                                  RFTYPE::UInt32 Size,
                                  const RFTYPE::String& HashfunctionName);

                template <typename T>
                static T Generate(const char* Text,
                                  const RFTYPE::String& HashfunctionName);
            };

            template <typename T>
            T Hash::Generate(const RFTYPE::UInt8 * Data, 
                                RFTYPE::UInt32 Size,
                                const RFTYPE::String& HashfunctionName)
            {
                Memory::AutoPointerArray<RFTYPE::UInt8> data=Generate(Data,Size,HashfunctionName);
                if (data)
                    if (data.Size()>=sizeof(T))
                        return *reinterpret_cast<T*>(data.Get());
                return T(0);
            }

            template <typename T>
            T Hash::Generate(const char* Text,
                                const RFTYPE::String& HashfunctionName)
            {
                Memory::AutoPointerArray<RFTYPE::UInt8> data=Generate(Text,HashfunctionName);
                if (data)
                    if (data.Size()>=sizeof(T))
                        return *reinterpret_cast<T*>(data.Get());
                return T(0);
            }
        }
    }
}

#endif // RF_MATH_HASH_HASH_HPP
