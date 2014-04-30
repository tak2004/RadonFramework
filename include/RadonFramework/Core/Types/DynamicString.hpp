#ifndef RF_CORE_TYPES_DYNAMICSTRING_HPP
#define RF_CORE_TYPES_DYNAMICSTRING_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Types {

class DynamicString
{
public:
    Char operator[](const MemoryRange Index);
    Char operator[](const MemoryRange Index)const;
protected:
    RadonFramework::Memory::AutoPointerArray<Char> m_Buffer;
};

} } }

#endif