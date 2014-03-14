#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Memory/PointerID.hpp>
#include <RadonFramework/Defines.hpp>

using namespace RadonFramework::Memory;

PointerID PointerID::GenerateFromPointer(void* Ptr)
{
    PointerID result;
    result.m_PtrID.ID=0;
    #if defined(RF_32BIT)
        result.m_PtrID.Ptr32=Ptr;
    #elif defined(RF_64BIT)
        result.m_PtrID.Ptr=Ptr;
    #else
        #error Unknown Bit-Arch
    #endif
    return result;
}

PointerID PointerID::GenerateFromID(PtrID ID)
{
    PointerID result;
    result.m_PtrID.ID=ID;
    return result;
}

PtrID PointerID::GetID()const
{
    return m_PtrID.ID;
}

void* PointerID::GetPointer()const
{
    #if defined(RF_32BIT)
        return m_PtrID.Ptr32;
    #elif defined(RF_64BIT)
        return m_PtrID.Ptr;
    #else
        #error Unknown Bit-Arch
    #endif
}

const PointerID& PointerID::Zero()
{
    static PointerID result;
    return result;
}

bool PointerID::operator ==(const PointerID& other)const
{
    return other.m_PtrID.ID==this->m_PtrID.ID;
}

bool PointerID::operator !=(const PointerID& other)const
{
    return other.m_PtrID.ID!=this->m_PtrID.ID;
}