#include "RadonFramework/System/Drawing/WindowsOpenGL.hpp"
#include "RadonFramework/System/Drawing/OpenGLSystem.hpp"

BOOL wglChoosePixelFormatARBDispatcher(HDC hdc,
    const int *piAttribIList,
    const FLOAT *pfAttribFList,
    UINT nMaxFormats,
    int *piFormats,
    UINT *nNumFormats)
{
    wglChoosePixelFormatARB = reinterpret_cast<wglChoosePixelFormatARBCallback>(OpenGLGetProcAddress("wglChoosePixelFormatARB"));
    return wglChoosePixelFormatARB(hdc, piAttribIList, pfAttribFList, nMaxFormats, piFormats, nNumFormats);
}
wglChoosePixelFormatARBCallback wglChoosePixelFormatARB = wglChoosePixelFormatARBDispatcher;

HGLRC wglCreateContextAttribsARBDispatcher(HDC hDC, HGLRC hShareContext,
    const int *attribList)
{
    wglCreateContextAttribsARB = reinterpret_cast<wglCreateContextAttribsARBCallback>(OpenGLGetProcAddress("wglCreateContextAttribsARB"));
    return wglCreateContextAttribsARB(hDC, hShareContext, attribList);
}
wglCreateContextAttribsARBCallback wglCreateContextAttribsARB = wglCreateContextAttribsARBDispatcher;