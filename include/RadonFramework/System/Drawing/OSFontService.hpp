#ifndef RF_SYSTEM_DRAWING_OSFONTSERVICE_HPP
#define RF_SYSTEM_DRAWING_OSFONTSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Drawing/FontService.hpp>

namespace RadonFramework::System::Drawing {

class OSFontService:public RF_Draw::FontService
{
public:
    OSFontService(const RF_Type::String &Name);
    virtual ~OSFontService() override;
    virtual void Update() override;
    virtual void GetUnicodeCharRanges(const RF_Type::String& Text, 
        RF_Collect::Array<RF_Text::UnicodeRangeInfo>& Out) override;
    virtual void GetUnicodeCharRange(const RF_Text::UnicodeRangeIdentifier Identifier, 
        RF_Text::UnicodeRangeInfo& Out) override;
    virtual void LoadGlyphs(const RF_Draw::FontDescription& FromFont,
        const RF_Collect::Array<RF_Type::UInt32>& GlyphsUtf32,
        RF_Collect::Array<RF_Draw::Path2D>& Out) override;
    virtual void LoadGlyphs(const RF_Draw::FontDescription& FromFont,
        const RF_Collect::Array<RF_Type::UInt32>& GlyphsUtf32,
        const RF_Type::UInt32 FontPixelSize,
        RF_Collect::Array<RF_Draw::Image>& RasterizedGlyphs,
        RF_Collect::Array<RF_Draw::GlyphMetric>& Metrics) override;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_SYSDRAW
#define RF_SHORTHAND_NAMESPACE_SYSDRAW
namespace RF_SysDraw = RadonFramework::System::Drawing;
#endif

#endif // RF_SYSTEM_DRAWING_OSFONTSERVICE_HPP