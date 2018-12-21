#ifndef RF_IO_DECODERS_IMAGEDECODER_HPP
#define RF_IO_DECODERS_IMAGEDECODER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/PixelFormat.hpp>
#include <RadonFramework/IO/Decoder.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework::Drawing
{
class Image;
}

namespace RadonFramework::IO::Decoders
{
class ImageDecoder : public Decoder
{
public:
  ImageDecoder();
  const RF_Draw::PixelFormat& PixelFormat() const;
  const RF_Type::UInt32 Width() const;
  const RF_Type::UInt32 Height() const;
  const RF_Type::UInt32 Layers() const;

  virtual RF_Mem::AutoPointerArray<RF_Type::UInt8>
  LoadLayer(RF_Type::UInt32 Layer) = 0;
  const RF_Type::Bool ConvertToImage(RF_Draw::Image& Destination);

protected:
  RF_Draw::PixelFormat m_PixelFormat;
  RF_Type::UInt32 m_Width;
  RF_Type::UInt32 m_Height;
  RF_Type::UInt32 m_Layers;
};

}  // namespace RadonFramework::IO::Decoders

#ifndef RF_SHORTHAND_NAMESPACE_DECODERS
#define RF_SHORTHAND_NAMESPACE_DECODERS
namespace RF_Decoders = RadonFramework::IO::Decoders;
#endif

#endif  // RF_IO_DECODERS_IMAGEDECODER_HPP
