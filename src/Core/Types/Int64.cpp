#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Types/Int64.hpp"

#ifdef RF_HAVE_LONG_LONG
    const RadonFramework::Core::Types::Int64 RadonFramework::Core::Types::Int64Max = 9223372036854775807ll;
    const RadonFramework::Core::Types::Int64 RadonFramework::Core::Types::Int64Min = -9223372036854775808ll;
#else
    #ifdef RF_IS_LITTLE_ENDIAN
        const RadonFramework::Core::Types::Int64 RadonFramework::Core::Types::Int64Max = {2147483647,2147483646};
        const RadonFramework::Core::Types::Int64 RadonFramework::Core::Types::Int64Min = {0,2147483648};
    #else
        const RadonFramework::Core::Types::Int64 RadonFramework::Core::Types::Int64Max = {2147483646,2147483647};
        const RadonFramework::Core::Types::Int64 RadonFramework::Core::Types::Int64Min = {2147483648,0};
    #endif
#endif
