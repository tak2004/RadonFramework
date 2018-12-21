#ifndef RF_FONTSERVICELOCATOR_HPP
#define RF_FONTSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/Drawing/FontService.hpp>

namespace RadonFramework::Drawing
{
class NullFontService : public FontService
{
public:
  NullFontService(const RF_Type::String& Name) : FontService(Name) {}

  void Update() final {}

  void
  GetUnicodeCharRanges(const RF_Type::String& Text,
                       RF_Collect::Array<RF_Text::UnicodeRangeInfo>& Out) final
  {
  }

  void LoadGlyphs(const FontDescription& FromFont,
                  const RF_Collect::Array<RF_Type::UInt32>& GlyphsUtf32,
                  RF_Collect::Array<RF_Draw::Path2D>& Out) final
  {
  }

  void LoadGlyphs(const FontDescription& FromFont,
                  const RF_Collect::Array<RF_Type::UInt32>& GlyphsUtf32,
                  const RF_Type::UInt32 FontPixelSize,
                  RF_Collect::Array<RF_Draw::Image>& RasterizedGlyphs,
                  RF_Collect::Array<RF_Draw::GlyphMetric>& Metrics) final
  {
  }

  void GetUnicodeCharRange(const RF_Text::UnicodeRangeIdentifier Identifier,
                           RF_Text::UnicodeRangeInfo& Out) final
  {
  }
};

using FontServiceLocator = RF_Pattern::Locator<FontService, NullFontService>;

}  // namespace RadonFramework::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif  // RF_FONTSERVICELOCATOR_HPP
