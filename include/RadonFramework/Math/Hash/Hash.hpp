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
                static Memory::AutoPointerArray<Core::Types::UInt8> Generate(
                    const Core::Types::UInt8 * Data, 
                    Core::Types::UInt32 Size,
                    IHashfunction& Hashfunction);

                static Memory::AutoPointerArray<Core::Types::UInt8> Generate(
                    const Core::Types::UInt8 * Data, 
                    Core::Types::UInt32 Size,
                    const Core::Types::String& HashfunctionName);
                    
                static Memory::AutoPointerArray<Core::Types::UInt8> Generate(
                    const char* Text,
                    const Core::Types::String& HashfunctionName);

                template <typename T>
                static T Generate(const Core::Types::UInt8 * Data, 
                                  Core::Types::UInt32 Size,
                                  const Core::Types::String& HashfunctionName);

                template <typename T>
                static T Generate(const char* Text,
                                  const Core::Types::String& HashfunctionName);
            };

            template <typename T>
            T Hash::Generate(const Core::Types::UInt8 * Data, 
                                Core::Types::UInt32 Size,
                                const Core::Types::String& HashfunctionName)
            {
                Memory::AutoPointerArray<Core::Types::UInt8> data=Generate(Data,Size,HashfunctionName);
                if (data)
                    if (data.Size()>=sizeof(T))
                        return *reinterpret_cast<T*>(data.Get());
                return T(0);
            }

            template <typename T>
            T Hash::Generate(const char* Text,
                                const Core::Types::String& HashfunctionName)
            {
                Memory::AutoPointerArray<Core::Types::UInt8> data=Generate(Text,HashfunctionName);
                if (data)
                    if (data.Size()>=sizeof(T))
                        return *reinterpret_cast<T*>(data.Get());
                return T(0);
            }
        }
    }
}

#endif // RF_MATH_HASH_HASH_HPP
