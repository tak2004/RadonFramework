#include "OpenGLSystem.hpp"
#include "RadonFramework/Defines.hpp"

#if defined(RF_WINDOWS)
#include <windows.h>
HMODULE MODULE=0;
#endif // defined(RF_WINDOWS)

void* OpenGLGetProcAddress(const char* Name)
{
#if defined(RF_WINDOWS)
    void *p = (void *)wglGetProcAddress(Name);
    if(p == 0 ||
        (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
        (p == (void*)-1))
    {
        
        p = (void *)GetProcAddress(MODULE, Name);
    }
#elif defined(RF_LINUX) || defined(RF_OSX)
    void* p = (void*)glXGetProcAddress​(Name);
#endif

    return p;
}

void OpenGLInit()
{
#if defined(RF_WINDOWS)
    MODULE = LoadLibraryA("opengl32.dll");
#endif
}

void OpenGLExit()
{
#if defined(RF_WINDOWS)
    FreeLibrary(MODULE);
    MODULE = 0;
#endif
}
