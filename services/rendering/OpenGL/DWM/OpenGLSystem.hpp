#ifndef RF_SYSTEM_DRAWING_OPENGLSYSTEM_HPP
#define RF_SYSTEM_DRAWING_OPENGLSYSTEM_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#if defined(RF_WINDOWS)
#include <WindowsOpenGL.hpp>
#elif defined(RF_LINUX) || defined(RF_OSX)
#include <RadonFramework/OpenGLX.hpp>
#endif

void* OpenGLGetProcAddress(const char* Name);
void OpenGLInit();
void OpenGLExit();

#endif // !RF_SYSTEM_DRAWING_OPENGLSYSTEM_HPP