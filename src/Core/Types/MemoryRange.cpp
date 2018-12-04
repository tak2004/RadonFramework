#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Types/MemoryRange.hpp"
#include "RadonFramework/Defines.hpp"
#include "RadonFramework/Core/Types/UInt64.hpp"

const RadonFramework::Core::Types::MemoryRange RadonFramework::Core::Types::MemoryRangeMin=0;

#if defined(RF_64BIT)
    const RadonFramework::Core::Types::MemoryRange RadonFramework::Core::Types::MemoryRangeMax=RadonFramework::Core::Types::UInt64Max;
#else
    const RadonFramework::Core::Types::MemoryRange RadonFramework::Core::Types::MemoryRangeMax=RadonFramework::Core::Types::UInt32Max;
#endif
