#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/Decoders/ImageDecoder.hpp"
#include "RadonFramework/Drawing/Image.hpp"

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

const RF_Type::Bool ImageDecoder::ConvertToImage(RF_Draw::Image& Destination)
{
    RF_Type::Size bytes = (m_Layers * m_Height * m_Width * m_PixelFormat.BitPerPixel) / 8;
    RF_Mem::AutoPointerArray<RF_Type::UInt8> data(bytes);
    for (auto i = 0; i < m_Layers; ++i)
    {
        auto layerData = LoadLayer(i);
        RF_SysMem::Copy(data.Get() + (i*layerData.Size()), layerData.Get(), layerData.Size());
    }
    return Destination.Initialize(m_Width, m_Height, m_Layers, m_PixelFormat, data);
}

} } }