#include <RadonFramework/precompiled.hpp>
#include "RadonFramework\Drawing\PixelFormat.hpp"

namespace RadonFramework::Drawing {

PixelFormat PixelFormat::Gray8 = [](){
    PixelFormat result;
    result.BitPerPixel = 8;
    result.Channels.Resize(1);
    result.Channels(0).Bits = 8;
    result.Channels(0).Type = RF_Draw::ChannelType::Alpha;
    result.Type = RF_Draw::PixelType::Unsigned;
    return result;
}();

}