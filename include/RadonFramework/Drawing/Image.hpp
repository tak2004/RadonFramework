#ifndef RF_DRAWING_IMAGE_HPP
#define RF_DRAWING_IMAGE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/PixelFormat.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework::Drawing
{
class Image
{
public:
  Image();
  RF_Type::Bool Initialize(const RF_Type::UInt32 Width,
                           const RF_Type::UInt32 Height,
                           const RF_Type::UInt32 Layers,
                           const RF_Draw::PixelFormat& Format,
                           RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data);
  RF_Type::Bool Initialize(const RF_Type::UInt32 Width,
                           const RF_Type::UInt32 Height,
                           const RF_Type::UInt32 Layers,
                           const RF_Draw::PixelFormat& Format,
                           RF_Type::UInt8* Data,
                           const RF_Type::Size Bytes);

  const RF_Draw::PixelFormat& PixelFormat() const;
  const RF_Type::UInt32 Width() const;
  const RF_Type::UInt32 Height() const;
  const RF_Type::UInt32 Layers() const;
  const RF_Geo::Size2Du& Dimension() const;

  RF_Type::UInt8* UnsafeAccess() const;
  RF_Mem::AutoPointerArray<RF_Type::UInt8>
  GetCopyOfLayer(RF_Type::UInt32 Layer) const;
  RF_Type::Bool ConvertTo(Image& Target,
                          const RF_Draw::PixelType NewChannelType,
                          const RF_Type::Size ChannelBitSize);
  RF_Type::Bool CopyRegionOfInterestFrom(const Image& Source,
                                         RF_Type::Size X,
                                         RF_Type::Size Y,
                                         RF_Type::Size Width,
                                         RF_Type::Size Height);
  RF_Type::Bool CopyAtPosition(const Image& Source,
                               const RF_Type::Size X,
                               const RF_Type::Size Y);

  Image& operator=(const Image& Copy);
  bool operator==(const Image& Other) const;

protected:
  RF_Mem::AutoPointerArray<RF_Type::UInt8> m_Data;
  RF_Draw::PixelFormat m_PixelFormat;
  RF_Type::UInt8* m_Proxy;
  RF_Type::Size m_ProxyBytes;
  RF_Geo::Size2Du m_Dimension;
  RF_Type::UInt32 m_Layers;
};

}  // namespace RadonFramework::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif  // RF_DRAWING_IMAGE_HPP
