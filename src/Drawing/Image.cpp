#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Image.hpp"
#include "RadonFramework/System/Memory.hpp"

namespace RadonFramework::Drawing {

Image::Image()
:m_Layers(0)
,m_Proxy(nullptr)
,m_ProxyBytes(0)
{
    m_Dimension = RF_Geo::Size2Du(0,0);
}

RF_Type::Bool Image::Initialize(const RF_Type::UInt32 Width, 
    const RF_Type::UInt32 Height, const RF_Type::UInt32 Layers, 
    const RF_Draw::PixelFormat& Format, RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data)
{
    RF_Type::Bool result = false;
    if(Width > 0 && Height > 0 && Layers > 0 && Format.BitPerPixel > 0 &&
       Data.IsEmpty() == false)
    {
        m_Dimension.Width = Width;
        m_Dimension.Height = Height;
        m_Layers = Layers;
        m_PixelFormat = Format;
        m_Data = Data;
        m_Proxy = m_Data.Get();
        m_ProxyBytes = m_Data.Size();
        result = true;
    }
    return result;
}

RF_Type::Bool Image::Initialize(const RF_Type::UInt32 Width,
    const RF_Type::UInt32 Height, const RF_Type::UInt32 Layers,
    const RF_Draw::PixelFormat& Format, RF_Type::UInt8* Data, 
    const RF_Type::Size Bytes)
{
    RF_Type::Bool result = false;
    if(Width > 0 && Height > 0 && Layers > 0 && Format.BitPerPixel > 0 &&
       Data && Bytes > 0)
    {
        m_Dimension.Width = Width;
        m_Dimension.Height = Height;
        m_Layers = Layers;
        m_PixelFormat = Format;
        m_Proxy = Data;
        m_ProxyBytes = Bytes;
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
    return m_Dimension.Width;
}

const RF_Type::UInt32 Image::Height() const
{
    return m_Dimension.Height;
}

const RF_Type::UInt32 Image::Layers() const
{
    return m_Layers;
}

RF_Type::UInt8* Image::UnsafeAccess() const
{
    return m_Proxy;
}

RF_Mem::AutoPointerArray<RF_Type::UInt8> Image::GetCopyOfLayer(RF_Type::UInt32 Layer) const
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result;
    if(Layer < m_Layers)
    {
        result.New((m_Dimension.Width * m_Dimension.Height * m_PixelFormat.BitPerPixel) / 8);
        RF_SysMem::Copy(result.Get(), m_Proxy+(result.Size() * Layer), result.Size());
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

            valueIn = *reinterpret_cast<RF_Type::Float32*>(Source.UnsafeAccess() + 
                ((p * Source.PixelFormat().BitPerPixel + bitOffsetIn) / 8));
            tmp = valueIn * 255.0f;

            *(Target.UnsafeAccess() + ((p * Target.PixelFormat().BitPerPixel + bitOffsetOut) / 8)) = tmp;

            bitOffsetIn += Source.PixelFormat().Channels(i).Bits;
            bitOffsetOut += Target.PixelFormat().Channels(i).Bits;
        }
    }
    return true;
}

RF_Type::Bool Image::ConvertTo(Image& Target, const RF_Draw::PixelType NewChannelType,
    const RF_Type::Size ChannelBitSize)
{
    RF_Type::Bool result = false;
    if(PixelFormat().Type != NewChannelType)
    {
        RF_Draw::Image tmp;
        auto newFormat = PixelFormat();
        newFormat.Type = NewChannelType;
        newFormat.BitPerPixel = ChannelBitSize * PixelFormat().Channels.Count();
        for (auto i = 0; i < newFormat.Channels.Count(); ++i)
        {
            newFormat.Channels(i).Bits = ChannelBitSize;
        }
        RF_Mem::AutoPointerArray<RF_Type::UInt8> empty(
            (newFormat.BitPerPixel * Width() * Height() * Layers()) / 8);
        tmp.Initialize(Width(), Height(), Layers(), newFormat, empty);

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
        switch(newFormat.Type)
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

RF_Type::Bool Image::CopyRegionOfInterestFrom(const Image& Source, 
    RF_Type::Size X, RF_Type::Size Y, RF_Type::Size Width, RF_Type::Size Height)
{
    RF_Type::Bool result = false;
    if(Width + X <= Source.m_Dimension.Width && Height + Y <= Source.m_Dimension.Height)
    {
        result = true;
        auto edgeSize = (Source.PixelFormat().BitPerPixel * Width) / 8;
        auto sourceEdgeSize = (Source.PixelFormat().BitPerPixel * Source.Width()) / 8;
        RF_Mem::AutoPointerArray<RF_Type::UInt8> data(edgeSize * Height);        
        for (auto row = 0; row < Height; ++row)
        {
            RF_SysMem::Copy(data.Get() + (row * edgeSize), 
                Source.m_Data.Get() + (row * sourceEdgeSize) + 
                ((X * Source.PixelFormat().BitPerPixel) / 8) +
                (Y * sourceEdgeSize), edgeSize);
        }        
        Initialize(Width, Height, 1, Source.PixelFormat(), data);
    }
    return result;
}

RF_Type::Bool Image::operator==(const Image& Other) const
{
    RF_Type::Bool result = true;
    result &= m_Dimension == Other.m_Dimension;
    result &= m_Layers == Other.m_Layers;
    result &= m_PixelFormat == Other.m_PixelFormat;
    result &= m_Data == Other.m_Data;
    return result;
}

RadonFramework::Drawing::Image& Image::operator=(const Image& Copy)
{
    m_Dimension = Copy.m_Dimension;
    m_Layers = Copy.Layers();
    m_PixelFormat = Copy.PixelFormat();
    m_Data = Copy.m_Data.Clone();
    m_Proxy = m_Data.Get();
    m_ProxyBytes = m_Data.Size();
    return *this;
}

const RF_Geo::Size2Du& Image::Dimension() const
{
    return m_Dimension;
}

RF_Type::Bool Image::CopyAtPosition(const Image& Source, const RF_Type::Size X, const RF_Type::Size Y)
{
    RF_Type::Bool result = false;
    if((Source.Dimension() + RF_Geo::Size2Du(X, Y)).FitsInto(m_Dimension))
    {
        result = true;
        auto* lineData = Source.UnsafeAccess();
        auto sourceLineSize = (Source.PixelFormat().BitPerPixel * Source.Width()) / 8;
        auto targetLineSize = (PixelFormat().BitPerPixel * m_Dimension.Width) / 8;;
        for(auto line = 0; line < Source.Height(); ++line)
        {
            RF_SysMem::Copy(m_Proxy + ((Y + line)*targetLineSize) + X, lineData, sourceLineSize);
            lineData += sourceLineSize;
        }
    }
    return result;    
}

}