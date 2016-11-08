#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Image.hpp"

namespace RadonFramework { namespace Drawing {

Image::Image()
:m_Width(0)
,m_Height(0)
,m_Layers(0)
{
}

RF_Type::Bool Image::Initialize(const RF_Type::UInt32 Width, 
    const RF_Type::UInt32 Height, const RF_Type::UInt32 Layers, 
    const RF_Draw::PixelFormat& Format, RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data)
{
    RF_Type::Bool result = false;
    if(Width > 0 && Height > 0 && Layers > 0 && Format.BitPerPixel > 0 &&
        Data.IsEmpty() == false)
    {
        m_Width = Width;
        m_Height = Height;
        m_Layers = Layers;
        m_PixelFormat = Format;
        m_Data = Data;
        result = true;
    }
    return result;
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
    return m_Data.Get();
}

RF_Mem::AutoPointerArray<RF_Type::UInt8> Image::GetCopyOfLayer(RF_Type::UInt32 Layer) const
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result;
    if(Layer < m_Layers)
    {
        result.New(m_Width*m_Height*m_PixelFormat.BitPerPixel/8);
        RF_SysMem::Copy(result.Get(), m_Data.Get()+(result.Size() * Layer), result.Size());
    }
    return result;
}

RF_Type::Bool Image::operator==(const Image& Other) const
{
    RF_Type::Bool result = true;
    result &= m_Width == Other.m_Width;
    result &= m_Height == Other.m_Height;
    result &= m_Layers == Other.m_Layers;
    result &= m_PixelFormat == Other.m_PixelFormat;
    result &= m_Data == Other.m_Data;
    return result;
}

RadonFramework::Drawing::Image& Image::operator=(const Image& Copy)
{
    m_Width = Copy.Width();
    m_Height = Copy.Height();
    m_Layers = Copy.Layers();
    m_PixelFormat = Copy.PixelFormat();
    m_Data = Copy.m_Data.Clone();
    return *this;
}

} }