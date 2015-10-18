#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/DynamicLibrary.hpp"
#include "RadonFramework/IO/Uri.hpp"

using namespace RadonFramework;
using namespace RadonFramework::System;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::IO;

#if defined(RF_WINDOWS)
#include <Windows.h>

void* LoadLib(const RF_Type::String& Name)
{
    void* result=0;
    HMODULE dl=LoadLibrary(TEXT(Name.c_str()));
    if (dl)
    {
        result=new HMODULE;
        *static_cast<HMODULE*>(result)=dl;
    }
    return result;
}

Bool UnloadLib(void* Data)
{
    RF_Type::Bool result = FreeLibrary(*static_cast<HMODULE*>(Data)) != 0;
    delete static_cast<HMODULE*>(Data);
    return result;
}

void* GetFunctionLib(void* Data, const RF_Type::String& Name)
{
    return static_cast<void*>(GetProcAddress(*static_cast<HMODULE*>(Data),Name.c_str()));
}
#endif

#if defined(RF_UNIX)
#include <dlfcn.h>

void* LoadLib(const RF_Type::String& Name)
{
    void* result=0;
    void* dl=dlopen(Name.c_str(),RTLD_LAZY);
    if (dl)
    {
        result=new void*;
        *static_cast<void**>(result)=dl;
    }
    return result;
}

Bool UnloadLib(void* Data)
{
    RF_Type::Bool result = dlclose(*static_cast<void**>(Data))==0;
    delete static_cast<void**>(Data);
    return result;
}

void* GetFunctionLib(void* Data, const RF_Type::String& Name)
{
    return static_cast<void*>(dlsym(*static_cast<void**>(Data),Name.c_str()));
}
#endif

AutoPointer<DynamicLibrary> DynamicLibrary::Load(const Uri& Name)
{
    void* data;
    AutoPointer<DynamicLibrary> result;
    
    data = LoadLib(Name.GetComponents(UriComponents::Path));

    if (data)
    {
        result=AutoPointer<DynamicLibrary>(new DynamicLibrary());
        result->m_ImplementationData=data;
    }
    return result;
}

Bool DynamicLibrary::Unload(DynamicLibrary& LibHandle)
{
    if (LibHandle.m_ImplementationData)
        return UnloadLib(LibHandle.m_ImplementationData);
    return false;
}

const RF_Type::String& DynamicLibrary::LineEnding()
{    
#if defined(RF_WINDOWS)
static RF_Type::String LINEENDING("dll", sizeof("dll"));
return LINEENDING;
#else
    #if defined(RF_LINUX)
    static RF_Type::String LINEENDING("so");
    return LINEENDING;    
    #else
    RF_COMPILER_WARNING("Congratulation, you're the one who allowed to implement this case!");
    #endif
#endif
}

DynamicLibrary::DynamicLibrary()
:m_ImplementationData(0)
{

}

DynamicLibrary::DynamicLibrary(DynamicLibrary&& Move)
{
    *this=Move;
}

DynamicLibrary::~DynamicLibrary()
{
    if (m_ImplementationData)
        UnloadLib(m_ImplementationData);
}

DynamicLibrary& DynamicLibrary::operator=(DynamicLibrary& Move)
{
    if (m_ImplementationData)
        UnloadLib(m_ImplementationData);
    m_ImplementationData = Move.m_ImplementationData;
    Move.m_ImplementationData = 0;
    return *this;
}

DynamicLibrary& DynamicLibrary::operator=(DynamicLibrary&& Move)
{
    *this = Move;
    return *this;
}

void* DynamicLibrary::GetFunctionAddress(const RF_Type::String &Name)
{
    if (m_ImplementationData)
        return GetFunctionLib(m_ImplementationData,Name);
    return 0;
}

Bool DynamicLibrary::IsDefault()
{
    return m_ImplementationData==0;
}
