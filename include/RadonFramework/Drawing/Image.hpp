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
    const RF_Draw::PixelFormat& PixelFormat()const;
    const RF_Type::UInt32 Width()const;
    const RF_Type::UInt32 Height()const;
    const RF_Type::UInt32 Layers()const;

    RF_Type::UInt8* UnsafeAccess()const;
    RF_Mem::AutoPointerArray<RF_Type::UInt8> GetCopyOfLayer(RF_Type::UInt32 Layer)const;
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
