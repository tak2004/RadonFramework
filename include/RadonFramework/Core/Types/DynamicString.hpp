#ifndef RF_CORE_TYPES_DYNAMICSTRING_HPP
#define RF_CORE_TYPES_DYNAMICSTRING_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Core::Types {

struct DynamicString
{
    UInt8& operator[](const MemoryRange Index);
    UInt8 operator[](const MemoryRange Index)const;
    const UInt8* Raw()const;
    Size GetSize()const;
    UInt8* Raw();
    void Free();

    UInt8* m_Buffer;
    Size m_Size;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_TYPE
#define RF_SHORTHAND_NAMESPACE_TYPE
namespace RF_Type = RadonFramework::Core::Types;
#endif

#endif