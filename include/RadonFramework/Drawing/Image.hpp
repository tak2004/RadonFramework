#ifndef RF_DRAWING_IMAGE_HPP
#define RF_DRAWING_IMAGE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Drawing/PixelFormat.hpp>

namespace RadonFramework { namespace Drawing {

class Image
{
public:
    Image();
    RF_Type::Bool Initialize(const RF_Type::UInt32 Width, const RF_Type::UInt32 Height,
        const RF_Type::UInt32 Layers, const RF_Draw::PixelFormat& Format,
        RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data);

    const RF_Draw::PixelFormat& PixelFormat()const;
    const RF_Type::UInt32 Width()const;
    const RF_Type::UInt32 Height()const;
    const RF_Type::UInt32 Layers()const;

    RF_Type::UInt8* UnsafeAccess()const;
    RF_Mem::AutoPointerArray<RF_Type::UInt8> GetCopyOfLayer(RF_Type::UInt32 Layer)const;
    RF_Type::Bool ConvertTo(Image& Target, const RF_Draw::PixelFormat& NewFormat);

    Image& operator = (const Image& Copy);
    RF_Type::Bool operator ==(const Image& Other)const;
protected:
    RF_Mem::AutoPointerArray<RF_Type::UInt8> m_Data;
    RF_Draw::PixelFormat m_PixelFormat;
    RF_Type::UInt32 m_Width;
    RF_Type::UInt32 m_Height;
    RF_Type::UInt32 m_Layers;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_IMAGE_HPP