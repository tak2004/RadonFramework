#ifndef RF_CORE_POLICIES_CMEMORYOPERATION_HPP
#define RF_CORE_POLICIES_CMEMORYOPERATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <type_traits>
#include <RadonFramework/System/Memory.hpp>

namespace RadonFramework { namespace Core { namespace Policies {

struct CMemoryOperation
{
    template <typename T>
    static Types::Int32 Compare(const T* P1, const T* P2,
        Types::Size ElementCount)
    {
        return RF_SysMem::Compare(reinterpret_cast<const void*>(P1), reinterpret_cast<const void*>(P2), ElementCount*sizeof(T));
    }

    template <typename T>
    static T* Copy(T* Destination, const T* Source,
        Types::Size ElementCount)
    {
        // Visual Studio suppor the necessary C++11 trait since 2012.
        #if defined(RF_HAVE_IS_TRIVIALLY_COPYABLE)
        if(std::is_trivially_copyable<T>::value == false)
        #endif
        {
            for(Types::Size i = 0; i < ElementCount; ++i)
                Destination[i] = Source[i];
            return Destination;
        }
        #if defined(RF_HAVE_IS_TRIVIALLY_COPYABLE)
        else        
        {
            RF_SysMem::Copy(Destination, Source, ElementCount*sizeof(T));
            return Destination;
        }
        #endif
    }

    template <typename T>
    static T* Move(T* Destination, const T* Source,
        Types::Size ElementCount)
    {
        #if defined(RF_HAVE_IS_TRIVIALLY_COPYABLE)
        if(std::is_trivially_copyable<T>::value == false)
        {
        #endif
            for(Types::Size i = 0; i < ElementCount; ++i)
                Destination[i] = Source[i];
            return Destination;
        #if defined(RF_HAVE_IS_TRIVIALLY_COPYABLE)
        }
        else
        {
            RF_SysMem::Move(Destination, Source, ElementCount*sizeof(T));
            return Destination;
        }
        #endif
    }

    template <typename T>
    static T* Set(T* Pointer, Types::UInt32 Value,
        Types::Size ElementCount)
    {
        RF_SysMem::Set(Pointer, Value, ElementCount*sizeof(T));
        return Pointer;
    }
};
        
} } }

#ifndef RF_SHORTHAND_NAMESPACE_POLICY
#define RF_SHORTHAND_NAMESPACE_POLICY
namespace RF_Policy = RadonFramework::Core::Policies;
#endif

#endif // RF_CORE_POLICIES_CMEMORYOPERATION_HPP