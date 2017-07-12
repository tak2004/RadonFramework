#ifndef RF_SYSTEM_DYNAMICLIBRARY_HPP
#define RF_SYSTEM_DYNAMICLIBRARY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/IO/Uri.hpp>

namespace RadonFramework::System {

class DynamicLibrary
{
public:
    static RF_Mem::AutoPointer<DynamicLibrary> Load(const RF_IO::Uri& Name);
    static RF_Mem::AutoPointer<DynamicLibrary> LoadSystemLibrary(const RF_Type::String& Name);

    /** 
    * @brief Unload the specified dynamic library.
    */
    static RF_Type::Bool Unload(DynamicLibrary& LibHandle);

    static const RF_Type::String& LineEnding();

    DynamicLibrary();

    DynamicLibrary(DynamicLibrary&& Move);

    /**
    * @brief Cleanup internal data.
    *
    * If you want to unload a library then you have to explicit call
    * the static Unload method because the destructor only clean up
    * internal data but don't unload the library.
    */
    ~DynamicLibrary();
                
    void* GetFunctionAddress(const RF_Type::String &Name);

    /**
    * @brief Return true if the object represent no library.
    *
    * This function return true if the library was unloaded but
    * the object hold information about it.
    */
    RF_Type::Bool IsDefault();                

    const RF_Type::String& GetName()const;

    DynamicLibrary& operator=(DynamicLibrary& Move);
    DynamicLibrary& operator=(DynamicLibrary&& Move);
protected:
    void* m_ImplementationData;
    RF_Type::String m_Name;

    DynamicLibrary(const DynamicLibrary& NoCopy) = delete;
    DynamicLibrary& operator=(const DynamicLibrary& NoCopy) = delete;
};
    
}

#ifndef RF_SHORTHAND_NAMESPACE_SYS
#define RF_SHORTHAND_NAMESPACE_SYS
namespace RF_Sys = RadonFramework::System;
#endif

#endif // RF_SYSTEM_DYNAMICLIBRARY_HPP
