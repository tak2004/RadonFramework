#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/Encoders/ImageEncoder.hpp"

namespace RadonFramework::IO::Encoders {

ImageEncoder::ImageEncoder()
:m_Width(0)
,m_Height(0)
,m_Layers(0)
{

}

const RF_Draw::PixelFormat& ImageEncoder::PixelFormat() const
{
    return m_PixelFormat;
}

const RF_Type::UInt32 ImageEncoder::Width() const
{
    return m_Width;
}

const RF_Type::UInt32 ImageEncoder::Height() const
{
    return m_Height;
}

const RF_Type::UInt32 ImageEncoder::Layers() const
{
    return m_Layers;
}

void ImageEncoder::SetPixelFormat(const RF_Draw::PixelFormat& NewPixelFormat)
{
    m_PixelFormat = NewPixelFormat;
}

void ImageEncoder::SetWidth(RF_Type::UInt32 NewWidth)
{
    m_Width = NewWidth;
}

void ImageEncoder::SetHeight(RF_Type::UInt32 NewHeight)
{
    m_Height = NewHeight;
}

void ImageEncoder::SetLayers(RF_Type::UInt32 NewLayerCount)
{
    m_Layers = NewLayerCount;
}

}