#ifndef RF_FONTSERVICE_HPP
#define RF_FONTSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework { namespace Drawing {

enum class FontStyle
{
    Unknown=0,
    Regular=1,
    Roman=2,
    Bold=4,
    Italic=8,
    Oblique=16,
    Standard=32,
    ExtraLight=64
};

inline FontStyle operator|(FontStyle a, FontStyle b)
{
    return static_cast<FontStyle>(static_cast<RF_Type::Size>(a) |
        static_cast<RF_Type::Size>(b));
}

class FontVariation
{
public:
    RF_Type::String Name;
    FontStyle Style;
    RF_Type::String Script;
    RF_Type::Bool HorizontalOrientation;
};

class FontDescription
{
public:
    RF_Type::String Name;
    RF_Collect::Array<FontVariation> Variations;
};

class Glyph
{
public:
    RF_Type::Float32 Width;
    RF_Type::Float32 Height;
    RF_Type::Float32 Baseline;
};

class FontService:public RF_Pattern::Service
{
public:
    FontService(const RF_Type::String &Name);
    ~FontService();
    virtual void Update() = 0;
    const RF_Collect::Array<FontDescription>& Fonts()const;
    void SetFilter(const FontStyle StyleFilter, const RF_Type::Bool OrientationFilter=true, 
        const RF_Type::Bool HorizontalOrientation=true);
//    void LoadGlyphs(const FontDescription& FromFont, );
protected:
    RF_Collect::Array<FontDescription> m_Fonts;
    FontStyle m_StyleFilter;
    RF_Type::Bool m_OrientationFilter;
    RF_Type::Bool m_HorizontalOrientation;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_FONTSERVICE_HPP
