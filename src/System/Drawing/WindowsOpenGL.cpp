#include "RadonFramework/System/Drawing/WindowsOpenGL.hpp"
#include "RadonFramework/System/Drawing/OpenGLSystem.hpp"

BOOL wglCopyContextDispatcher(HGLRC hglrcSrc, HGLRC hglrcDst, UINT mask)
{
    wglCopyContext = reinterpret_cast<wglCopyContextCallback>(OpenGLGetProcAddress("wglCopyContext"));
    return 	wglCopyContext(hglrcSrc, hglrcDst, mask);
}
wglCopyContextCallback wglCopyContext = wglCopyContextDispatcher;

HGLRC wglCreateContextDispatcher(HDC hDc)
{
    wglCreateContext = reinterpret_cast<wglCreateContextCallback>(OpenGLGetProcAddress("wglCreateContext"));
    return 	wglCreateContext(hDc);
}
wglCreateContextCallback wglCreateContext = wglCreateContextDispatcher;

HGLRC wglCreateLayerContextDispatcher(HDC hDc, void* level)
{
    wglCreateLayerContext = reinterpret_cast<wglCreateLayerContextCallback>(OpenGLGetProcAddress("wglCreateLayerContext"));
    return 	wglCreateLayerContext(hDc, level);
}
wglCreateLayerContextCallback wglCreateLayerContext = wglCreateLayerContextDispatcher;

BOOL wglDeleteContextDispatcher(HGLRC oldContext)
{
    wglDeleteContext = reinterpret_cast<wglDeleteContextCallback>(OpenGLGetProcAddress("wglDeleteContext"));
    return 	wglDeleteContext(oldContext);
}
wglDeleteContextCallback wglDeleteContext = wglDeleteContextDispatcher;

BOOL wglDescribeLayerPlaneDispatcher(HDC hDc, void *pixelFormat, void *layerPlane, UINT nBytes, const LAYERPLANEDESCRIPTOR * plpd)
{
    wglDescribeLayerPlane = reinterpret_cast<wglDescribeLayerPlaneCallback>(OpenGLGetProcAddress("wglDescribeLayerPlane"));
    return 	wglDescribeLayerPlane(hDc, pixelFormat, layerPlane, nBytes, plpd);
}
wglDescribeLayerPlaneCallback wglDescribeLayerPlane = wglDescribeLayerPlaneDispatcher;

HGLRC wglGetCurrentContextDispatcher()
{
    wglGetCurrentContext = reinterpret_cast<wglGetCurrentContextCallback>(OpenGLGetProcAddress("wglGetCurrentContext"));
    return 	wglGetCurrentContext();
}
wglGetCurrentContextCallback wglGetCurrentContext = wglGetCurrentContextDispatcher;

HDC wglGetCurrentDCDispatcher()
{
    wglGetCurrentDC = reinterpret_cast<wglGetCurrentDCCallback>(OpenGLGetProcAddress("wglGetCurrentDC"));
    return 	wglGetCurrentDC();
}
wglGetCurrentDCCallback wglGetCurrentDC = wglGetCurrentDCDispatcher;

UINT GetEnhMetaFilePixelFormatDispatcher(HENHMETAFILE hemf, const PIXELFORMATDESCRIPTOR * ppfd)
{
    GetEnhMetaFilePixelFormat = reinterpret_cast<GetEnhMetaFilePixelFormatCallback>(OpenGLGetProcAddress("GetEnhMetaFilePixelFormat"));
    return 	GetEnhMetaFilePixelFormat(hemf, ppfd);
}
GetEnhMetaFilePixelFormatCallback GetEnhMetaFilePixelFormat = GetEnhMetaFilePixelFormatDispatcher;

void wglGetLayerPaletteEntriesDispatcher(HDC hdc, void *iLayerPlane, void* iStart, void* cEntries, const COLORREF * pcr)
{
    wglGetLayerPaletteEntries = reinterpret_cast<wglGetLayerPaletteEntriesCallback>(OpenGLGetProcAddress("wglGetLayerPaletteEntries"));
    wglGetLayerPaletteEntries(hdc, iLayerPlane, iStart, cEntries, pcr);
}
wglGetLayerPaletteEntriesCallback wglGetLayerPaletteEntries = wglGetLayerPaletteEntriesDispatcher;

PROC wglGetProcAddressDispatcher(LPCSTR lpszProc)
{
    wglGetProcAddress = reinterpret_cast<wglGetProcAddressCallback>(OpenGLGetProcAddress("wglGetProcAddress"));
    return 	wglGetProcAddress(lpszProc);
}
wglGetProcAddressCallback wglGetProcAddress = wglGetProcAddressDispatcher;

BOOL wglMakeCurrentDispatcher(HDC hDc, HGLRC newContext)
{
    wglMakeCurrent = reinterpret_cast<wglMakeCurrentCallback>(OpenGLGetProcAddress("wglMakeCurrent"));
    return 	wglMakeCurrent(hDc, newContext);
}
wglMakeCurrentCallback wglMakeCurrent = wglMakeCurrentDispatcher;

BOOL wglRealizeLayerPaletteDispatcher(HDC hdc, void *iLayerPlane, BOOL bRealize)
{
    wglRealizeLayerPalette = reinterpret_cast<wglRealizeLayerPaletteCallback>(OpenGLGetProcAddress("wglRealizeLayerPalette"));
    return 	wglRealizeLayerPalette(hdc, iLayerPlane, bRealize);
}
wglRealizeLayerPaletteCallback wglRealizeLayerPalette = wglRealizeLayerPaletteDispatcher;

void wglSetLayerPaletteEntriesDispatcher(HDC hdc, void *iLayerPlane, void *iStart, void *cEntries, const COLORREF * pcr)
{
    wglSetLayerPaletteEntries = reinterpret_cast<wglSetLayerPaletteEntriesCallback>(OpenGLGetProcAddress("wglSetLayerPaletteEntries"));
    wglSetLayerPaletteEntries(hdc, iLayerPlane, iStart, cEntries, pcr);
}
wglSetLayerPaletteEntriesCallback wglSetLayerPaletteEntries = wglSetLayerPaletteEntriesDispatcher;

BOOL wglShareListsDispatcher(HGLRC hrcSrvShare, HGLRC hrcSrvSource)
{
    wglShareLists = reinterpret_cast<wglShareListsCallback>(OpenGLGetProcAddress("wglShareLists"));
    return 	wglShareLists(hrcSrvShare, hrcSrvSource);
}
wglShareListsCallback wglShareLists = wglShareListsDispatcher;

BOOL wglSwapLayerBuffersDispatcher(HDC hdc, UINT fuFlags)
{
    wglSwapLayerBuffers = reinterpret_cast<wglSwapLayerBuffersCallback>(OpenGLGetProcAddress("wglSwapLayerBuffers"));
    return 	wglSwapLayerBuffers(hdc, fuFlags);
}
wglSwapLayerBuffersCallback wglSwapLayerBuffers = wglSwapLayerBuffersDispatcher;

BOOL wglUseFontBitmapsDispatcher(HDC hDC, DWORD first, DWORD count, DWORD listBase)
{
    wglUseFontBitmaps = reinterpret_cast<wglUseFontBitmapsCallback>(OpenGLGetProcAddress("wglUseFontBitmaps"));
    return 	wglUseFontBitmaps(hDC, first, count, listBase);
}
wglUseFontBitmapsCallback wglUseFontBitmaps = wglUseFontBitmapsDispatcher;

BOOL wglUseFontBitmapsADispatcher(HDC hDC, DWORD first, DWORD count, DWORD listBase)
{
    wglUseFontBitmapsA = reinterpret_cast<wglUseFontBitmapsACallback>(OpenGLGetProcAddress("wglUseFontBitmapsA"));
    return 	wglUseFontBitmapsA(hDC, first, count, listBase);
}
wglUseFontBitmapsACallback wglUseFontBitmapsA = wglUseFontBitmapsADispatcher;

BOOL wglUseFontBitmapsWDispatcher(HDC hDC, DWORD first, DWORD count, DWORD listBase)
{
    wglUseFontBitmapsW = reinterpret_cast<wglUseFontBitmapsWCallback>(OpenGLGetProcAddress("wglUseFontBitmapsW"));
    return 	wglUseFontBitmapsW(hDC, first, count, listBase);
}
wglUseFontBitmapsWCallback wglUseFontBitmapsW = wglUseFontBitmapsWDispatcher;

BOOL wglUseFontOutlinesDispatcher(HDC hDC, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, void *format, LPGLYPHMETRICSFLOAT lpgmf)
{
    wglUseFontOutlines = reinterpret_cast<wglUseFontOutlinesCallback>(OpenGLGetProcAddress("wglUseFontOutlines"));
    return 	wglUseFontOutlines(hDC, first, count, listBase, deviation, extrusion, format, lpgmf);
}
wglUseFontOutlinesCallback wglUseFontOutlines = wglUseFontOutlinesDispatcher;

BOOL wglUseFontOutlinesADispatcher(HDC hDC, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, void *format, LPGLYPHMETRICSFLOAT lpgmf)
{
    wglUseFontOutlinesA = reinterpret_cast<wglUseFontOutlinesACallback>(OpenGLGetProcAddress("wglUseFontOutlinesA"));
    return 	wglUseFontOutlinesA(hDC, first, count, listBase, deviation, extrusion, format, lpgmf);
}
wglUseFontOutlinesACallback wglUseFontOutlinesA = wglUseFontOutlinesADispatcher;

BOOL wglUseFontOutlinesWDispatcher(HDC hDC, DWORD first, DWORD count, DWORD listBase, FLOAT deviation, FLOAT extrusion, void* format, LPGLYPHMETRICSFLOAT lpgmf)
{
    wglUseFontOutlinesW = reinterpret_cast<wglUseFontOutlinesWCallback>(OpenGLGetProcAddress("wglUseFontOutlinesW"));
    return 	wglUseFontOutlinesW(hDC, first, count, listBase, deviation, extrusion, format, lpgmf);
}
wglUseFontOutlinesWCallback wglUseFontOutlinesW = wglUseFontOutlinesWDispatcher;

