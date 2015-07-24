#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Drawing/OSFontService.hpp"

#if defined(RF_WINDOWS)
#include "RadonFramework/Collections/List.hpp"
#include <windows.h>

int CALLBACK EnumerateFontFamily(const ENUMLOGFONTEX *lpelfe, const NEWTEXTMETRICEX *lpntme,
    DWORD FontType, LPARAM lParam)
{
    if(FontType & TRUETYPE_FONTTYPE)
    {
        const DWORD* u32_Flags128 = lpntme->ntmFontSig.fsUsb;

        const RF_Type::Size TABLESIZE = 11;
        const RF_Type::String STRINGLOOKUPTABLE[TABLESIZE] = {"Bold", "BoldItalic",
            "BoldOblique", "Bold Italic", "Bold Oblique", "Italic", "Oblique",
            "Regular", "Roman", "Standard", "ExtraLight"};
        const RF_Draw::FontStyle TYPELOOKUPTABLE[TABLESIZE] = {RF_Draw::FontStyle::Bold,
            RF_Draw::FontStyle::Bold | RF_Draw::FontStyle::Italic,
            RF_Draw::FontStyle::Bold | RF_Draw::FontStyle::Oblique,
            RF_Draw::FontStyle::Bold | RF_Draw::FontStyle::Italic,
            RF_Draw::FontStyle::Bold | RF_Draw::FontStyle::Oblique,
            RF_Draw::FontStyle::Italic, RF_Draw::FontStyle::Oblique,
            RF_Draw::FontStyle::Regular, RF_Draw::FontStyle::Roman,
            RF_Draw::FontStyle::Standard, RF_Draw::FontStyle::ExtraLight};

        auto* fontList = reinterpret_cast<RF_Collect::List<RF_Draw::FontDescription>*>(lParam);
        RF_Type::String fontname = RF_Type::String(reinterpret_cast<const char*>(lpelfe->elfLogFont.lfFaceName), 32);
        // look for the variation set
        RF_Type::Size i;
        RF_Draw::FontDescription* fontDescription = 0;
        for(i = 0; i < fontList->Count(); ++i)
        {
            if((*fontList)[i].Name == fontname)
            {
                fontDescription = &(*fontList)[i];
                break;
            }
        }

        if(fontDescription == 0)
        {
            fontDescription = &fontList->CreateElementAtEnd();
            fontDescription->Name = fontname;
        }
        fontDescription->Variations.Resize(fontDescription->Variations.Count() + 1);
        RF_Draw::FontVariation* variation = &fontDescription->Variations(fontDescription->Variations.Count() - 1);

        variation->Name = RF_Type::String(reinterpret_cast<const char*>(lpelfe->elfFullName), 64);
        variation->Script = RF_Type::String(reinterpret_cast<const char*>(lpelfe->elfScript), 32);
        variation->HorizontalOrientation = lpelfe->elfLogFont.lfOrientation;
        RF_Type::String style = RF_Type::String(reinterpret_cast<const char*>(lpelfe->elfStyle), 32);

        for(i = 0; i < TABLESIZE; ++i)
        {
            if(style == STRINGLOOKUPTABLE[i])
            {
                variation->Style = TYPELOOKUPTABLE[i];
                break;
            }
        }

        if(i == TABLESIZE)
        {
            variation->Style = RF_Draw::FontStyle::Unknown;
        }
    }
    return 1;
}

void ImplementationGetAvailableFonts(RF_Collect::List<RF_Draw::FontDescription>& fonts)
{
    // get all system fonts
    HDC dc = GetDC(0);
    LOGFONT logfont;
    logfont.lfCharSet = DEFAULT_CHARSET;
    logfont.lfFaceName[0] = '\0';
    logfont.lfPitchAndFamily = 0;
    EnumFontFamiliesEx(dc, &logfont, (FONTENUMPROC)EnumerateFontFamily, reinterpret_cast<DWORD>(&fonts), 0);
    ReleaseDC(0, dc);

    // get list of all fonts which are hidden by user or system
    RF_Mem::AutoPointerArray<RF_Type::UInt8> stringList;
    HKEY hkey;
    if(RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows NT\\CurrentVersion\\Font Management",
        0, KEY_QUERY_VALUE, &hkey) == ERROR_SUCCESS)
    {
        DWORD bufferSize = 4096;
        stringList = RF_Mem::AutoPointerArray<RF_Type::UInt8>(new RF_Type::UInt8[bufferSize], bufferSize);
        DWORD errorCode = RegQueryValueEx(hkey, "Inactive Fonts", NULL, NULL, (PBYTE)stringList.Get(), &bufferSize);
        while(errorCode == ERROR_MORE_DATA)
        {
            bufferSize = bufferSize << 1;
            stringList = RF_Mem::AutoPointerArray<RF_Type::UInt8>(new RF_Type::UInt8[bufferSize], bufferSize);
            errorCode = RegQueryValueEx(hkey, "Inactive Fonts", NULL, NULL, (PBYTE)stringList.Get(), &bufferSize);
        }

        if(errorCode != ERROR_SUCCESS)
        {
            stringList.Release();
        }
        RegCloseKey(hkey);
    }

    for(RF_Type::Int64 i = fonts.Count() - 1; i >= 0; --i)
    {
        if(stringList)
        {
            RF_Type::UInt8* cursor = stringList.Get();
            RF_Type::Size leftBytes = stringList.Size();
            RF_Type::String hiddenFont;
            while(*cursor != '\0')
            {
                RF_Type::Size bytes = RF_SysStr::CStringSizeOf(cursor, leftBytes);
                hiddenFont = RF_Type::String(reinterpret_cast<const char*>(cursor), bytes, RF_Common::DataManagment::UnmanagedInstance);
                cursor += bytes;
                leftBytes -= bytes;
                if(hiddenFont == fonts[i].Name)
                {
                    fonts.RemoveAt(i);
                    break;
                }
            }
        }
    }
}
#endif

namespace RadonFramework {
namespace System {
namespace Drawing {

OSFontService::OSFontService(const RF_Type::String &Name)
    :FontService(Name)
{
}

OSFontService::~OSFontService()
{
}

void OSFontService::Update()
{
    RF_Collect::List<RF_Draw::FontDescription> fonts;

    ImplementationGetAvailableFonts(fonts);

    // apply specified filters
    for(RF_Type::Int64 i = fonts.Count() - 1; i >= 0; --i)
    {
        RF_Type::Size matches = 0;
        for(RF_Type::Int64 j = fonts[i].Variations.Count() - 1; j >= 0; --j)
        {
            if((static_cast<RF_Type::Size>(fonts[i].Variations(j).Style) & 
               static_cast<RF_Type::Size>(m_StyleFilter) > 0) ||
               (m_OrientationFilter && m_HorizontalOrientation == fonts[i].Variations(j).HorizontalOrientation))
            {
                ++matches;
            }
        }

        if(matches == 0)
        {
            fonts.RemoveAt(i);
        }
        else
        {
            if(matches < fonts[i].Variations.Count())
            {
                RF_Collect::Array<RF_Draw::FontVariation> newArray(matches);
                for(RF_Type::Size j = 0, cursor = 0; j < fonts[i].Variations.Count(); ++j)
                {
                    if(static_cast<RF_Type::Size>(fonts[i].Variations(j).Style) &
                       static_cast<RF_Type::Size>(m_StyleFilter) > 0)
                    {
                        newArray(cursor) = fonts[i].Variations(j);
                        ++cursor;
                    }
                }
                fonts[i].Variations = newArray;
            }
        }
    }

    // finalize public list of fonts
    m_Fonts.Resize(fonts.Count());
    for(RF_Type::Size i = 0; i < fonts.Count(); ++i)
    {
        m_Fonts(i) = fonts[i];
    }
}

}
}
}