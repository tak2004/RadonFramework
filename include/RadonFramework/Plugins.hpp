#ifndef RF_PLUGINS_HPP
#define RF_PLUGINS_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#if defined(RF_WINDOWS)
    #include <RadonFramework/backend/Windows/Forms/WindowsWindowService.hpp>
    #include <RadonFramework/backend/Windows/Drawing/GDIOpenGL1Canvas3DService.hpp>
    #include <RadonFramework/backend/Windows/Drawing/GDIOpenGL2Canvas3DService.hpp>
    #include <RadonFramework/backend/Windows/Drawing/GDIOpenGL3Canvas3DService.hpp>
    #include <RadonFramework/backend/Windows/WindowsSMBiosService.hpp>
    #include <RadonFramework/backend/Windows/WindowsProcessService.hpp>
#endif

#if defined(RF_LINUX)
    #include <RadonFramework/backend/Linux/LinuxProcessService.hpp>
    #include <RadonFramework/backend/Linux/LinuxSMBiosService.hpp>
    #include <RadonFramework/backend/X11/Drawing/X11OpenGL1Canvas3DService.hpp>
    #include <RadonFramework/backend/X11/Drawing/X11OpenGL2Canvas3DService.hpp>
    #include <RadonFramework/backend/X11/Drawing/X11OpenGL3Canvas3DService.hpp>
    #include <RadonFramework/backend/X11/Forms/X11WindowService.hpp>
#endif

#if defined(RF_MACOSX)

#endif

#include <RadonFramework/backend/hashlib++/HashlibHashfunctionService.hpp>
#include <RadonFramework/backend/MurmurHash/MurmurHashHashfunctionService.hpp>

#endif
