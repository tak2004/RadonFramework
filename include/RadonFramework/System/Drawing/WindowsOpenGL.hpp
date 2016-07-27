#ifndef RF_SYSTEM_DRAWING_WINDOWSOPENGL_HPP
#define RF_SYSTEM_DRAWING_WINDOWSOPENGL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/System/Drawing/WindowsOpenGLTypes.hpp>
#include <RadonFramework/System/Drawing/WindowsOpenGLConstants.hpp>

using wglChoosePixelFormatARBCallback = BOOL (*)(HDC hdc, const int *piAttribIList,
    const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
extern wglChoosePixelFormatARBCallback wglChoosePixelFormatARB;
using wglCreateContextAttribsARBCallback = HGLRC(*)(HDC hDC, HGLRC hShareContext,
    const int *attribList);
extern wglCreateContextAttribsARBCallback wglCreateContextAttribsARB;
using wglSwapIntervalEXTCallback = BOOL(*)(int interval);
extern wglSwapIntervalEXTCallback wglSwapIntervalEXT;
using wglGetExtensionsStringARBCallback = const char*(*)(HDC hDC);
extern wglGetExtensionsStringARBCallback wglGetExtensionsStringARB;

#endif // RF_SYSTEM_DRAWING_WINDOWSOPENGL_HPP