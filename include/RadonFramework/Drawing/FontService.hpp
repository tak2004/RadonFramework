#ifndef RF_FONTSERVICE_HPP
#define RF_FONTSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Text/UnicodeRangeInfo.hpp>
#include <RadonFramework/Drawing/Path2D.hpp>
#include <RadonFramework/Drawing/Image.hpp>

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
    RF_Collect::Array<RF_Text::UnicodeRangeIdentifier> SupportedUnicodeSubranges;
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
    /// Return a list of UnicodeRangeInfo which is used by the specified language definition.
    virtual void GetUnicodeCharRanges(const RF_Type::String& Text,
            RF_Collect::Array<RF_Text::UnicodeRangeIdentifier>& Out)=0;
    void EnableStyleFilter(const FontStyle StyleFilter);
    void DisableStyleFilter();
    void EnableOrientationFilter(RF_Type::Bool Horizontal);
    void DisableOrientationFilter();
    void EnableCharRangeFilter(const RF_Collect::Array<RF_Text::UnicodeRangeIdentifier>& Filter);
    void DisableCharRangeFilter();
    virtual void LoadGlyphs(const FontDescription& FromFont, 
        const RF_Collect::Array<RF_Type::UInt32>& GlyphsUtf32,
        RF_Collect::Array<RF_Draw::Path2D>& Out) = 0;
    virtual void LoadGlyphs(const FontDescription& FromFont,
        const RF_Collect::Array<RF_Type::UInt32>& GlyphsUtf32,
        RF_Collect::Array<RF_Draw::Image>& Out) = 0;
protected:
    RF_Type::Bool MatchFilter(const FontVariation& Variation);

    RF_Collect::Array<FontDescription> m_Fonts;
    FontStyle m_StyleFilter;
    RF_Collect::Array<RF_Text::UnicodeRangeIdentifier> m_RangeFilter;
    RF_Type::Bool m_HorizontalOrientation;
    RF_Type::Bool m_EnableStyleFilter;
    RF_Type::Bool m_EnableOrientationFilter;
    RF_Type::Bool m_EnableCharRangeFilter;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_FONTSERVICE_HPP
