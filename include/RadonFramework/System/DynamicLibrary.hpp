#ifndef RF_SYSTEM_DYNAMICLIBRARY_HPP
#define RF_SYSTEM_DYNAMICLIBRARY_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/IO/Uri.hpp>

namespace RadonFramework
{
    namespace System
    {
        class DynamicLibrary
        {
            public:
                static RadonFramework::Memory::AutoPointer<DynamicLibrary> Load(
                    const RadonFramework::IO::Uri& Name);

                /** 
                 * @brief Unload the specified dynamic library.
                 */
                static RFTYPE::Bool Unload(DynamicLibrary& LibHandle);

                static const RFTYPE::String& LineEnding();

                DynamicLibrary();                
                
                DynamicLibrary(const DynamicLibrary& Copy);
                
                /**
                 * @brief Cleanup internal data.
                 *
                 * If you want to unload a library then you have to explicit call
                 * the static Unload method because the destructor only clean up
                 * internal data but don't unload the library.
                 */
                ~DynamicLibrary();
                
                void* GetFunctionAddress(const RFTYPE::String &Name);

                /**
                 * @brief Return true if the object represent no library.
                 *
                 * This function return true if the library was unloaded but
                 * the object hold information about it.
                 */
                RFTYPE::Bool IsDefault();                

                DynamicLibrary& operator=(const DynamicLibrary& Other);
            protected:                
                void* m_ImplementationData;
        };
    }    
}

#endif // RF_SYSTEM_DYNAMICLIBRARY_HPP
