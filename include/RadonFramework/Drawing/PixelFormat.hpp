#ifndef RF_DRAWING_PIXELFORMAT_HPP
#define RF_DRAWING_PIXELFORMAT_HPP

#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework { namespace Drawing {

enum class ChannelType:RF_Type::UInt8
{
    Red,
    Green,
    Blue,
    Luminocity,
    Alpha,
    ChromaBlue,
    ChromaRed
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
    RF_Collect::Array<ChannelFormat> Channels;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_PIXELFORMAT_HPP