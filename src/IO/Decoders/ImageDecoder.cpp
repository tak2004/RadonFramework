#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/Decoders/ImageDecoder.hpp"

namespace RadonFramework { namespace IO { namespace Decoders {

ImageDecoder::ImageDecoder()
{

}

const RF_Draw::PixelFormat& ImageDecoder::PixelFormat() const
{
    return m_PixelFormat;
}

const RF_Type::UInt32 ImageDecoder::Width() const
{
    return m_Width;
}

const RF_Type::UInt32 ImageDecoder::Height() const
{
    return m_Height;
}

const RF_Type::UInt32 ImageDecoder::Layers() const
{
    return m_Layers;
}

} } }