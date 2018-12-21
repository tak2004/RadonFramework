#ifndef RF_DRAWING_BASICRENDERFUNCTION_HPP
#define RF_DRAWING_BASICRENDERFUNCTION_HPP
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER > 1000

#include <RadonFramework/Drawing/AbstractRenderer.hpp>

namespace RadonFramework::Drawing
{
using GraphicHandle = RF_Type::UInt32;

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

struct AssignBufferToObject
{
  static AbstractRenderer::Dispatcher DispatchFunction;
  GraphicHandle* Buffer;
  GraphicHandle* Object;
  RF_Type::UInt8 Stride;
};

struct GenerateObject
{
  static AbstractRenderer::Dispatcher DispatchFunction;
  GraphicHandle* Object;
  GraphicHandle* Material;
};

struct DestroyObject
{
  static AbstractRenderer::Dispatcher DispatchFunction;
  GraphicHandle* Object;
};

struct RenderObject
{
  enum ElementType : RF_Type::UInt8
  {
    Triangles = 0,
    PointSprites = 1
  };
  static AbstractRenderer::Dispatcher DispatchFunction;
  RF_Type::Size Elements;
  RF_Type::UInt32 ElementType;
  GraphicHandle* Object;
};

struct GenerateProgram
{
  static AbstractRenderer::Dispatcher DispatchFunction;
  GraphicHandle* Program;
  const char* VertexData;
  const char* FragmentData;
  const char* GeometryData;
  RF_Type::UInt32 VertexByteSize;
  RF_Type::UInt32 FragmentByteSize;
  RF_Type::UInt32 GeometryByteSize;
};

struct DestroyProgram
{
  static AbstractRenderer::Dispatcher DispatchFunction;
  GraphicHandle* Program;
};

struct GenerateMaterial
{
  static AbstractRenderer::Dispatcher DispatchFunction;
  GraphicHandle* Material;
  GraphicHandle* Program;
  RF_Type::Bool Blending;
};

struct GenerateTexture
{
  static AbstractRenderer::Dispatcher DispatchFunction;
  GraphicHandle* Texture;
  RF_Type::UInt8* Data;
  RF_Type::Size ByteSize;
  RF_Type::UInt16 Width;
  RF_Type::UInt16 Height;
  RF_Type::UInt8 Channels;
  RF_Type::Bool Transparent;
};

struct UpdateTexture
{
  static AbstractRenderer::Dispatcher DispatchFunction;
  RF_Type::UInt8* Data;
  RF_Type::Size ByteSize;
  GraphicHandle* Texture;
  RF_Type::UInt16 Width;
  RF_Type::UInt16 Height;
};

struct DestroyTexture
{
  static AbstractRenderer::Dispatcher DispatchFunction;
  GraphicHandle* Texture;
};

struct AssignTextureToMaterial
{
  static AbstractRenderer::Dispatcher DispatchFunction;
  GraphicHandle* Material;
  GraphicHandle* Texture;
};

}  // namespace RadonFramework::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif  // !RF_DRAWING_BASICRENDERFUNCTION_HPP