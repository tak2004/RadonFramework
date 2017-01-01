#ifndef RF_DRAWING_BASICRENDERFUNCTION_HPP
#define RF_DRAWING_BASICRENDERFUNCTION_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Drawing/AbstractRenderer.hpp>

namespace RadonFramework { namespace Drawing {

typedef RF_Type::UInt32 GraphicHandle;

struct UpdateBuffer
{
    static AbstractRenderer::Dispatcher DispatchFunction;
    RF_Type::UInt8* Data;
    RF_Type::Size ByteSize;
    GraphicHandle* Buffer;
};

struct GenerateBuffer
{
    static AbstractRenderer::Dispatcher DispatchFunction;
    GraphicHandle* Buffer;
    RF_Type::UInt8* Data;
    RF_Type::Size ByteSize;
};

struct DestroyBuffer
{
    static AbstractRenderer::Dispatcher DispatchFunction;
    GraphicHandle* Buffer;
};

struct RenderObject
{
    enum ElementType:RF_Type::UInt8
    {
        Triangles = 0,
        PointSprites = 1
    };
    static AbstractRenderer::Dispatcher DispatchFunction;
    RF_Type::Size Elements;
    RF_Type::UInt32 ElementType;
    GraphicHandle* Buffer;
};

struct GenerateMaterial
{
    static AbstractRenderer::Dispatcher DispatchFunction;
    GraphicHandle* Material;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // !RF_DRAWING_BASICRENDERFUNCTION_HPP