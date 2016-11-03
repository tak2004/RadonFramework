#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Image.hpp"

namespace RadonFramework { namespace Drawing {

Image::Image()
:m_Width(0)
,m_Height(0)
,m_Layers(0)
{
}

const RF_Draw::PixelFormat& Image::PixelFormat() const
{
    return m_PixelFormat;
}

const RF_Type::UInt32 Image::Width() const
{
    return m_Width;
}

const RF_Type::UInt32 Image::Height() const
{
    return m_Height;
}

const RF_Type::UInt32 Image::Layers() const
{
    return m_Layers;
}

RF_Type::UInt8* Image::UnsafeAccess() const
{
    return nullptr;
}

RF_Mem::AutoPointerArray<RF_Type::UInt8> Image::GetCopyOfLayer(RF_Type::UInt32 Layer) const
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result;
    return result;
}

} }