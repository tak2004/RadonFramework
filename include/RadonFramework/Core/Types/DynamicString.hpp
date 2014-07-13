#ifndef RF_CORE_TYPES_DYNAMICSTRING_HPP
#define RF_CORE_TYPES_DYNAMICSTRING_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Types {

struct DynamicString
{
    Char& operator[](const MemoryRange Index);
    Char operator[](const MemoryRange Index)const;
    const Char* Raw()const;
    Size GetSize()const;
    Char* Raw();
    void Free();

    Char* m_Buffer;
    Size m_Size;
};

} } }

#endif