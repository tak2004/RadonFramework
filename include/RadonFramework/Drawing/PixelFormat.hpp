#ifndef RF_DRAWING_PIXELFORMAT_HPP
#define RF_DRAWING_PIXELFORMAT_HPP

#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework::Drawing
{
enum class ChannelType : RF_Type::UInt8
{
  Red,
  Green,
  Blue,
  Luminocity,
  Alpha,
  ChromaBlue,
  ChromaRed
};

enum class PixelType : RF_Type::UInt8
{
  Unsigned,
  Signed,
  Float
};

struct ChannelFormat
{
  ChannelType Type;
  RF_Type::UInt8 Bits;
};

class PixelFormat
{
public:
  RF_Type::UInt32 BitPerPixel;
  PixelType Type;
  RF_Collect::Array<ChannelFormat> Channels;
  PixelFormat& operator=(const PixelFormat& CopyFrom) = default;
  RF_Type::Bool operator==(const PixelFormat& Other) const;
  RF_Type::Bool operator!=(const PixelFormat& Other) const;

  static PixelFormat Gray8;
};

inline RF_Type::Bool PixelFormat::operator==(const PixelFormat& Other) const
{
  RF_Type::Bool result = true;
  result &= Type == Other.Type;
  result &= BitPerPixel == Other.BitPerPixel;
  result &= Channels.Count() == Other.Channels.Count();
  if(result)
  {
    for(auto i = 0; i < Channels.Count(); ++i)
    {
      result &= Channels(i).Type == Other.Channels(i).Type;
      result &= Channels(i).Bits == Other.Channels(i).Bits;
    }
  }
  return result;
}

inline RF_Type::Bool PixelFormat::operator!=(const PixelFormat& Other) const
{
  return !(*this == Other);
}

}  // namespace RadonFramework::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif  // RF_DRAWING_PIXELFORMAT_HPP