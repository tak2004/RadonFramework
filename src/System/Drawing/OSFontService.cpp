#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Drawing/OSFontService.hpp"

#if defined(RF_WINDOWS)
#include "RadonFramework/Collections/List.hpp"
#include <windows.h>

int CALLBACK EnumerateFontFamily(const LOGFONT *lpelfe, const TEXTMETRIC *lpntme,
    DWORD FontType, LPARAM lParam)
{
    auto* fontList = reinterpret_cast<RF_Collect::List<RF_Draw::FontDescription>*>(lParam);
    auto& fontDescription = fontList->CreateElementAtEnd();
    fontDescription.Name = RF_Type::String(lpelfe->lfFaceName, 32);
    return 1;
}

void ImplementationUpdate(RF_Collect::Array<RF_Draw::FontDescription>& KnownFonts)
{
    RF_Collect::List<RF_Draw::FontDescription> fonts;
    HDC dc = GetDC(0);
    LOGFONT logfont;
    logfont.lfCharSet = DEFAULT_CHARSET;
    logfont.lfFaceName[0] = '\0';
    logfont.lfPitchAndFamily = 0;
    EnumFontFamiliesEx(dc, &logfont, EnumerateFontFamily, reinterpret_cast<DWORD>(&fonts), 0);
    ReleaseDC(0,dc);
    KnownFonts.Resize(fonts.Count());
    for(RF_Type::Size i = 0; i < fonts.Count(); ++i)
    {
        KnownFonts(i) = fonts[i];
    }
}
#endif

namespace RadonFramework { namespace System { namespace Drawing {

OSFontService::OSFontService(const RF_Type::String &Name)
:FontService(Name)
{
}

OSFontService::~OSFontService()
{
}

void OSFontService::Update()
{
    ImplementationUpdate(m_Fonts);
}

} } }