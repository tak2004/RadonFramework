#ifndef RF_IO_ENCODERS_IMAGEENCODER_HPP
#define RF_IO_ENCODERS_IMAGEENCODER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/PixelFormat.hpp>
#include <RadonFramework/IO/Encoder.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework::IO::Encoders
{
class ImageEncoder : public Encoder
{
public:
  ImageEncoder();
  const RF_Draw::PixelFormat& PixelFormat() const;
  const RF_Type::UInt32 Width() const;
  const RF_Type::UInt32 Height() const;
  const RF_Type::UInt32 Layers() const;

  virtual void SetPixelFormat(const RF_Draw::PixelFormat& NewPixelFormat);
  virtual void SetWidth(RF_Type::UInt32 NewWidth);
  virtual void SetHeight(RF_Type::UInt32 NewHeight);
  virtual void SetLayers(RF_Type::UInt32 NewLayerCount);

  virtual RF_Type::Bool
  StoreLayerData(RF_Type::UInt32 Layer,
                 const RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data) = 0;

protected:
  RF_Draw::PixelFormat m_PixelFormat;
  RF_Type::UInt32 m_Width;
  RF_Type::UInt32 m_Height;
  RF_Type::UInt32 m_Layers;
};

}  // namespace RadonFramework::IO::Encoders

#ifndef RF_SHORTHAND_NAMESPACE_ENCODERS
#define RF_SHORTHAND_NAMESPACE_ENCODERS
namespace RF_Encoders = RadonFramework::IO::Encoders;
#endif

#endif  // RF_IO_ENCODERS_IMAGEENCODER_HPP
