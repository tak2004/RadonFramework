#ifndef RF_SYSTEM_DRAWING_WINDOWSOPENGL_HPP
#define RF_SYSTEM_DRAWING_WINDOWSOPENGL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/System/Drawing/OpenGLTypes.hpp>
#include <RadonFramework/System/Drawing/WindowsOpenGLConstants.hpp>
#include <windows.h>

using wglCopyContextCallback = BOOL (*)(HGLRC hglrcSrc,HGLRC hglrcDst,UINT mask);
extern wglCopyContextCallback wglCopyContext;
using wglCreateContextCallback = HGLRC (*)(HDC hDc);
extern wglCreateContextCallback wglCreateContext;
using wglCreateLayerContextCallback = HGLRC (*)(HDC hDc,void* level);
extern wglCreateLayerContextCallback wglCreateLayerContext;
using wglDeleteContextCallback = BOOL (*)(HGLRC oldContext);
extern wglDeleteContextCallback wglDeleteContext;
using wglDescribeLayerPlaneCallback = BOOL (*)(HDC hDc,void* pixelFormat,void *layerPlane,UINT nBytes,const LAYERPLANEDESCRIPTOR * plpd);
extern wglDescribeLayerPlaneCallback wglDescribeLayerPlane;
using wglGetCurrentContextCallback = HGLRC (*)();
extern wglGetCurrentContextCallback wglGetCurrentContext;
using wglGetCurrentDCCallback = HDC (*)();
extern wglGetCurrentDCCallback wglGetCurrentDC;
using GetEnhMetaFilePixelFormatCallback = UINT (*)(HENHMETAFILE hemf,const PIXELFORMATDESCRIPTOR * ppfd);
extern GetEnhMetaFilePixelFormatCallback GetEnhMetaFilePixelFormat;
using wglGetLayerPaletteEntriesCallback = void (*)(HDC hdc,void *iLayerPlane,void* iStart,void *cEntries,const COLORREF * pcr);
extern wglGetLayerPaletteEntriesCallback wglGetLayerPaletteEntries;
using wglGetProcAddressCallback = PROC (*)(LPCSTR lpszProc);
extern wglGetProcAddressCallback wglGetProcAddress;
using wglMakeCurrentCallback = BOOL (*)(HDC hDc,HGLRC newContext);
extern wglMakeCurrentCallback wglMakeCurrent;
using wglRealizeLayerPaletteCallback = BOOL (*)(HDC hdc,void *iLayerPlane,BOOL bRealize);
extern wglRealizeLayerPaletteCallback wglRealizeLayerPalette;
using wglSetLayerPaletteEntriesCallback = void (*)(HDC hdc,void *iLayerPlane,void *iStart,void *cEntries,const COLORREF * pcr);
extern wglSetLayerPaletteEntriesCallback wglSetLayerPaletteEntries;
using wglShareListsCallback = BOOL (*)(HGLRC hrcSrvShare,HGLRC hrcSrvSource);
extern wglShareListsCallback wglShareLists;
using wglSwapLayerBuffersCallback = BOOL (*)(HDC hdc,UINT fuFlags);
extern wglSwapLayerBuffersCallback wglSwapLayerBuffers;
using wglUseFontBitmapsCallback = BOOL (*)(HDC hDC,DWORD first,DWORD count,DWORD listBase);
extern wglUseFontBitmapsCallback wglUseFontBitmaps;
using wglUseFontBitmapsACallback = BOOL (*)(HDC hDC,DWORD first,DWORD count,DWORD listBase);
extern wglUseFontBitmapsACallback wglUseFontBitmapsA;
using wglUseFontBitmapsWCallback = BOOL (*)(HDC hDC,DWORD first,DWORD count,DWORD listBase);
extern wglUseFontBitmapsWCallback wglUseFontBitmapsW;
using wglUseFontOutlinesCallback = BOOL (*)(HDC hDC,DWORD first,DWORD count,DWORD listBase,FLOAT deviation,FLOAT extrusion,void *format,LPGLYPHMETRICSFLOAT lpgmf);
extern wglUseFontOutlinesCallback wglUseFontOutlines;
using wglUseFontOutlinesACallback = BOOL (*)(HDC hDC,DWORD first,DWORD count,DWORD listBase,FLOAT deviation,FLOAT extrusion,void *format,LPGLYPHMETRICSFLOAT lpgmf);
extern wglUseFontOutlinesACallback wglUseFontOutlinesA;
using wglUseFontOutlinesWCallback = BOOL (*)(HDC hDC,DWORD first,DWORD count,DWORD listBase,FLOAT deviation,FLOAT extrusion,void* format,LPGLYPHMETRICSFLOAT lpgmf);
extern wglUseFontOutlinesWCallback wglUseFontOutlinesW;

#endif // RF_SYSTEM_DRAWING_WINDOWSOPENGL_HPP