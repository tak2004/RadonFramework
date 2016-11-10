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

RF_Type::Bool NotImplemented(RF_Draw::Image& Target, const RF_Draw::Image& Source)
{
    return false;
}

RF_Type::Bool Unsigned2Float(RF_Draw::Image& Target, const RF_Draw::Image& Source)
{
    RF_Type::Size bitOffsetIn, bitOffsetOut;
    for(RF_Type::Size p = 0; p < Source.Width()*Source.Height(); ++p)
    {
        bitOffsetIn = 0;
        bitOffsetOut = 0;
        for(RF_Type::Size i = 0; i < Source.PixelFormat().Channels.Count(); ++i)
        {
            RF_Type::Float32 tmp;
            RF_Type::UInt32 valueIn = 0;

            valueIn = *reinterpret_cast<RF_Type::UInt32*>(Source.UnsafeAccess() + ((p * Source.PixelFormat().BitPerPixel + bitOffsetIn) / 8));
            valueIn = valueIn >> (32 - Source.PixelFormat().Channels(i).Bits);
            tmp = valueIn;
            tmp /= 255.0f;

            *reinterpret_cast<RF_Type::Float32*>(Target.UnsafeAccess() + ((p * Target.PixelFormat().BitPerPixel + bitOffsetOut) / 8)) = tmp;

            bitOffsetIn += Source.PixelFormat().Channels(i).Bits;
            bitOffsetOut += Target.PixelFormat().Channels(i).Bits;
        }
    }
    return true;
}

RF_Type::Bool Float2Unsigned(RF_Draw::Image& Target, const RF_Draw::Image& Source)
{
    RF_Type::Size bitOffsetIn, bitOffsetOut;
    for(RF_Type::Size p = 0; p < Source.Width()*Source.Height(); ++p)
    {
        bitOffsetIn = 0;
        bitOffsetOut = 0;
        for(RF_Type::Size i = 0; i < Source.PixelFormat().Channels.Count(); ++i)
        {
            RF_Type::Float32 valueIn = 0;
            RF_Type::UInt8 tmp;

            valueIn = *reinterpret_cast<RF_Type::Float32*>(Source.UnsafeAccess() + ((p * Source.PixelFormat().BitPerPixel + bitOffsetIn) / 8));
            tmp = valueIn * 255.0f;

            *reinterpret_cast<RF_Type::UInt8*>(Target.UnsafeAccess() + ((p * Target.PixelFormat().BitPerPixel + bitOffsetOut) / 8)) = tmp;

            bitOffsetIn += Source.PixelFormat().Channels(i).Bits;
            bitOffsetOut += Target.PixelFormat().Channels(i).Bits;
        }
    }
    return true;
}

RF_Type::Bool Image::ConvertTo(Image& Target, const RF_Draw::PixelFormat& NewFormat)
{
    RF_Type::Bool result = false;
    if(PixelFormat() != NewFormat)
    {
        RF_Draw::Image tmp;
        RF_Mem::AutoPointerArray<RF_Type::UInt8> empty((NewFormat.BitPerPixel*Width()*Height()*Layers()) / 8);
        tmp.Initialize(Width(), Height(), Layers(), NewFormat, empty);

        RF_Type::Size offset = 0;
        switch(PixelFormat().Type)
        {
        case RF_Draw::PixelType::Float:
            break;
        case RF_Draw::PixelType::Unsigned:
            offset += 1;
            break;
        case RF_Draw::PixelType::Signed:
            offset += 2;
            break;
        }
        switch(NewFormat.Type)
        {
        case RF_Draw::PixelType::Float:
            break;
        case RF_Draw::PixelType::Unsigned:
            offset += 3;
            break;
        case RF_Draw::PixelType::Signed:
            offset += 6;
            break;
        }
        /* Float->Float, Unsigned->Float, Signed->Float,
           Float->Unsigned, Unsigned->Unsigned, Signed->Unsigned,
           Float->Signed, Unsigned->Signed, Signed,Signed
        */
        typedef RF_Type::Bool(*Conversion)(RF_Draw::Image&, const RF_Draw::Image&);
        Conversion conversionFunctions[9] = {NotImplemented, Unsigned2Float,
            NotImplemented, Float2Unsigned, NotImplemented, NotImplemented,
            NotImplemented, NotImplemented, NotImplemented};

        result = conversionFunctions[offset](tmp, *this);
        Target = tmp;
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