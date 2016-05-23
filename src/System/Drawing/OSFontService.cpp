#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Drawing/OSFontService.hpp"
#include "RadonFramework/Collections/List.hpp"

#if defined(RF_WINDOWS)
#include <windows.h>

void ObtainUnicodeRangeIdentifierFromUsb(const DWORD USB[4], 
    RF_Collect::Array<RF_Text::UnicodeRangeIdentifier>& Out)
{
    static const RF_Type::UInt8 IDCOUNT[128] = {
        1,1,1,1,3,2,2,1,1,14,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,3,1,2,1,1,1,1,
        4,4,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,7,1,3,1,1,1,2,1,1,1,1,1,1,1,1,
        1,3,1,1,1,1,2,1,1,2,4,1,1,1,3,1,2,2,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,
        2,1,1,1,1,1,1,1,1,1,1,3,2};

    static const RF_Type::UInt8 IDOFFSET[128] = {
        0, 1, 2, 3, 4, 7, 9, 11, 12, 13, 18, 19, 20, 21, 23, 24, 25, 26, 27, 28, 
        29, 30, 31, 32, 33, 34, 35, 37, 38, 39, 42, 43, 45, 46, 47, 48, 49, 53,
        57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 70, 72, 73, 74, 75, 76, 
        77, 78, 79, 86, 87, 90, 91, 92, 93, 95, 96, 97, 98, 99, 100, 101, 102,
        103, 104, 107, 108, 109, 110, 111, 113, 114, 115, 117, 121, 122, 123, 124,
        127, 128, 130, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 144, 145,
        146, 147, 148, 149, 150, 151, 152, 154, 155, 156, 157, 158, 159, 160, 161, 
        162, 163, 164, 167, 169};

    static const RF_Text::UnicodeRangeIdentifier IDS[169] = {
        RF_Text::UnicodeRangeIdentifier::BasicLatin,
        RF_Text::UnicodeRangeIdentifier::Latin1Supplement,
        RF_Text::UnicodeRangeIdentifier::LatinExtended_A,
        RF_Text::UnicodeRangeIdentifier::LatinExtended_B,
        RF_Text::UnicodeRangeIdentifier::IPAExtensions,
        RF_Text::UnicodeRangeIdentifier::PhoneticExtensions,
        RF_Text::UnicodeRangeIdentifier::PhoneticExtensionsSupplement,
        RF_Text::UnicodeRangeIdentifier::SpacingModifierLetters,
        RF_Text::UnicodeRangeIdentifier::ModifierToneLetters,
        RF_Text::UnicodeRangeIdentifier::CombiningDiacriticalMarks,
        RF_Text::UnicodeRangeIdentifier::CombiningDiacriticalMarksSupplement,
        RF_Text::UnicodeRangeIdentifier::GreekAndCoptic,
        RF_Text::UnicodeRangeIdentifier::Coptic,
        RF_Text::UnicodeRangeIdentifier::Cyrillic,
        RF_Text::UnicodeRangeIdentifier::CyrillicSupplement,
        RF_Text::UnicodeRangeIdentifier::CyrillicExtended_A,
        RF_Text::UnicodeRangeIdentifier::CyrillicExtended_B,
        RF_Text::UnicodeRangeIdentifier::Armenian,
        RF_Text::UnicodeRangeIdentifier::Hebrew,
        RF_Text::UnicodeRangeIdentifier::Vai,
        RF_Text::UnicodeRangeIdentifier::Arabic,
        RF_Text::UnicodeRangeIdentifier::ArabicSupplement,
        RF_Text::UnicodeRangeIdentifier::NKo,
        RF_Text::UnicodeRangeIdentifier::Devanagari,
        RF_Text::UnicodeRangeIdentifier::Bengali,
        RF_Text::UnicodeRangeIdentifier::Gurmukhi,
        RF_Text::UnicodeRangeIdentifier::Gujarati,
        RF_Text::UnicodeRangeIdentifier::Oriya,
        RF_Text::UnicodeRangeIdentifier::Tamil,
        RF_Text::UnicodeRangeIdentifier::Telugu,
        RF_Text::UnicodeRangeIdentifier::Kannada,
        RF_Text::UnicodeRangeIdentifier::Malayalam,
        RF_Text::UnicodeRangeIdentifier::Thai,
        RF_Text::UnicodeRangeIdentifier::Lao,
        RF_Text::UnicodeRangeIdentifier::Georgian,
        RF_Text::UnicodeRangeIdentifier::GeorgianSupplement,
        RF_Text::UnicodeRangeIdentifier::Balinese,
        RF_Text::UnicodeRangeIdentifier::HangulJamo,
        RF_Text::UnicodeRangeIdentifier::LatinExtendedAdditional,
        RF_Text::UnicodeRangeIdentifier::LatinExtended_C,
        RF_Text::UnicodeRangeIdentifier::LatinExtended_D,
        RF_Text::UnicodeRangeIdentifier::GreekExtended,
        RF_Text::UnicodeRangeIdentifier::GeneralPunctuation,
        RF_Text::UnicodeRangeIdentifier::SupplementalPunctuation,
        RF_Text::UnicodeRangeIdentifier::SuperscriptsAndSubscripts,
        RF_Text::UnicodeRangeIdentifier::CurrencySymbols,
        RF_Text::UnicodeRangeIdentifier::CombiningDiacriticalMarksForSymbols,
        RF_Text::UnicodeRangeIdentifier::LetterlikeSymbols,
        RF_Text::UnicodeRangeIdentifier::NumberForms,
        RF_Text::UnicodeRangeIdentifier::Arrows,
        RF_Text::UnicodeRangeIdentifier::SupplementalArrows_A,
        RF_Text::UnicodeRangeIdentifier::SupplementalArrows_B,
        RF_Text::UnicodeRangeIdentifier::MiscellaneousSymbolsAndArrows,
        RF_Text::UnicodeRangeIdentifier::MathematicalOperators,
        RF_Text::UnicodeRangeIdentifier::MiscellaneousMathematicalSymbols_A,
        RF_Text::UnicodeRangeIdentifier::MiscellaneousMathematicalSymbols_B,
        RF_Text::UnicodeRangeIdentifier::SupplementalMathematicalOperators,
        RF_Text::UnicodeRangeIdentifier::MiscellaneousTechnical,
        RF_Text::UnicodeRangeIdentifier::ControlPictures,
        RF_Text::UnicodeRangeIdentifier::OpticalCharacterRecognition,
        RF_Text::UnicodeRangeIdentifier::EnclosedAlphanumerics,
        RF_Text::UnicodeRangeIdentifier::BoxDrawing,
        RF_Text::UnicodeRangeIdentifier::BlockElements,
        RF_Text::UnicodeRangeIdentifier::GeometricShapes,
        RF_Text::UnicodeRangeIdentifier::MiscellaneousSymbols,
        RF_Text::UnicodeRangeIdentifier::Dingbats,
        RF_Text::UnicodeRangeIdentifier::CJKSymbolsAndPunctuation,
        RF_Text::UnicodeRangeIdentifier::Hiragana,
        RF_Text::UnicodeRangeIdentifier::Katakana,
        RF_Text::UnicodeRangeIdentifier::KatakanaPhoneticExtensions,
        RF_Text::UnicodeRangeIdentifier::Bopomofo,
        RF_Text::UnicodeRangeIdentifier::BopomofoExtended,
        RF_Text::UnicodeRangeIdentifier::HangulCompatibilityJamo,
        RF_Text::UnicodeRangeIdentifier::Phags_pa,
        RF_Text::UnicodeRangeIdentifier::EnclosedCJKLettersAndMonths,
        RF_Text::UnicodeRangeIdentifier::CJKCompatibility,
        RF_Text::UnicodeRangeIdentifier::HangulSyllables,
        RF_Text::UnicodeRangeIdentifier::NonPlane0,
        RF_Text::UnicodeRangeIdentifier::Phoenician,
        RF_Text::UnicodeRangeIdentifier::CJKRadicalsSupplement,
        RF_Text::UnicodeRangeIdentifier::KangxiRadicals,
        RF_Text::UnicodeRangeIdentifier::IdeographicDescriptionCharacters,
        RF_Text::UnicodeRangeIdentifier::Kanbun,
        RF_Text::UnicodeRangeIdentifier::CJKUnifiedIdeographsExtension_A,
        RF_Text::UnicodeRangeIdentifier::CJKUnifiedIdeographs,
        RF_Text::UnicodeRangeIdentifier::CJKUnifiedIdeographsExtension_B,
        RF_Text::UnicodeRangeIdentifier::PrivateUseArea,
        RF_Text::UnicodeRangeIdentifier::CJKStrokes,
        RF_Text::UnicodeRangeIdentifier::CJKCompatibilityIdeographs,
        RF_Text::UnicodeRangeIdentifier::CJKCompatibilityIdeographsSupplement,
        RF_Text::UnicodeRangeIdentifier::AlphabeticPresentationForms,
        RF_Text::UnicodeRangeIdentifier::ArabicPresentationForms_A,
        RF_Text::UnicodeRangeIdentifier::CombiningHalfMarks,
        RF_Text::UnicodeRangeIdentifier::VerticalForms,
        RF_Text::UnicodeRangeIdentifier::CJKCompatibilityForms,
        RF_Text::UnicodeRangeIdentifier::SmallFormVariants,
        RF_Text::UnicodeRangeIdentifier::ArabicPresentationForms_B,
        RF_Text::UnicodeRangeIdentifier::HalfwidthAndFullwidthForms,
        RF_Text::UnicodeRangeIdentifier::Specials,
        RF_Text::UnicodeRangeIdentifier::Tibetan,
        RF_Text::UnicodeRangeIdentifier::Syriac,
        RF_Text::UnicodeRangeIdentifier::Thaana,
        RF_Text::UnicodeRangeIdentifier::Sinhala,
        RF_Text::UnicodeRangeIdentifier::Myanmar,
        RF_Text::UnicodeRangeIdentifier::Ethiopic,
        RF_Text::UnicodeRangeIdentifier::EthiopicSupplement,
        RF_Text::UnicodeRangeIdentifier::EthiopicExtended,
        RF_Text::UnicodeRangeIdentifier::Cherokee,
        RF_Text::UnicodeRangeIdentifier::UnifiedCanadianAboriginalSyllabics,
        RF_Text::UnicodeRangeIdentifier::Ogham,
        RF_Text::UnicodeRangeIdentifier::Runic,
        RF_Text::UnicodeRangeIdentifier::Khmer,
        RF_Text::UnicodeRangeIdentifier::KhmerSymbols,
        RF_Text::UnicodeRangeIdentifier::Mongolian,
        RF_Text::UnicodeRangeIdentifier::BraillePatterns,
        RF_Text::UnicodeRangeIdentifier::YiSyllables,
        RF_Text::UnicodeRangeIdentifier::YiRadicals,
        RF_Text::UnicodeRangeIdentifier::Tagalog,
        RF_Text::UnicodeRangeIdentifier::Hanunoo,
        RF_Text::UnicodeRangeIdentifier::Buhid,
        RF_Text::UnicodeRangeIdentifier::Tagbanwa,
        RF_Text::UnicodeRangeIdentifier::OldItalic,
        RF_Text::UnicodeRangeIdentifier::Gothic,
        RF_Text::UnicodeRangeIdentifier::Deseret,
        RF_Text::UnicodeRangeIdentifier::ByzantineMusicalSymbols,
        RF_Text::UnicodeRangeIdentifier::MusicalSymbols,
        RF_Text::UnicodeRangeIdentifier::AncientGreekMusicalNotation,
        RF_Text::UnicodeRangeIdentifier::MathematicalAlphanumericSymbols,
        RF_Text::UnicodeRangeIdentifier::PrivateUsePlane15,
        RF_Text::UnicodeRangeIdentifier::PrivateUsePlane16,
        RF_Text::UnicodeRangeIdentifier::VariationSelectors,
        RF_Text::UnicodeRangeIdentifier::VariationSelectorsSupplement,
        RF_Text::UnicodeRangeIdentifier::Tags,
        RF_Text::UnicodeRangeIdentifier::Limbu,
        RF_Text::UnicodeRangeIdentifier::TaiLe,
        RF_Text::UnicodeRangeIdentifier::NewTaiLue,
        RF_Text::UnicodeRangeIdentifier::Buginese,
        RF_Text::UnicodeRangeIdentifier::Glagolitic,
        RF_Text::UnicodeRangeIdentifier::Tifinagh,
        RF_Text::UnicodeRangeIdentifier::YijingHexagramSymbols,
        RF_Text::UnicodeRangeIdentifier::SylotiNagri,
        RF_Text::UnicodeRangeIdentifier::LinearBSyllabary,
        RF_Text::UnicodeRangeIdentifier::LinearBIdeograms,
        RF_Text::UnicodeRangeIdentifier::AegeanNumbers,
        RF_Text::UnicodeRangeIdentifier::AncientGreekNumbers,
        RF_Text::UnicodeRangeIdentifier::Ugaritic,
        RF_Text::UnicodeRangeIdentifier::OldPersian,
        RF_Text::UnicodeRangeIdentifier::Shavian,
        RF_Text::UnicodeRangeIdentifier::Osmanya,
        RF_Text::UnicodeRangeIdentifier::CypriotSyllabary,
        RF_Text::UnicodeRangeIdentifier::Kharoshthi,
        RF_Text::UnicodeRangeIdentifier::TaiXuanJingSymbols,
        RF_Text::UnicodeRangeIdentifier::Cuneiform,
        RF_Text::UnicodeRangeIdentifier::CuneiformNumbersAndPunctuation,
        RF_Text::UnicodeRangeIdentifier::CountingRodNumerals,
        RF_Text::UnicodeRangeIdentifier::Sundanese,
        RF_Text::UnicodeRangeIdentifier::Lepcha,
        RF_Text::UnicodeRangeIdentifier::OlChiki,
        RF_Text::UnicodeRangeIdentifier::Saurashtra,
        RF_Text::UnicodeRangeIdentifier::KayahLi,
        RF_Text::UnicodeRangeIdentifier::Rejang,
        RF_Text::UnicodeRangeIdentifier::Cham,
        RF_Text::UnicodeRangeIdentifier::AncientSymbols,
        RF_Text::UnicodeRangeIdentifier::PhaistosDisc,
        RF_Text::UnicodeRangeIdentifier::Lycian,
        RF_Text::UnicodeRangeIdentifier::Carian,
        RF_Text::UnicodeRangeIdentifier::Lydian,
        RF_Text::UnicodeRangeIdentifier::MahjongTiles,
        RF_Text::UnicodeRangeIdentifier::DominoTiles};

    const RF_Type::Size BitsPerByte = 8;
    RF_Type::Size matches = 0, index = 0;
    for (RF_Type::Size i = 0; i < 4; ++i)
    {
        for (RF_Type::Size j = 0; j < sizeof(DWORD); ++j)
        {
            if(USB[i] & (1 << j))
            {
                index = (i*sizeof(DWORD)*BitsPerByte) + j;
                matches += IDCOUNT[index];
            }
        }
    }

    Out.Resize(matches);

    if(matches > 0)
    {
        for(RF_Type::Size i = 0; i < 4; ++i)
        {
            for(RF_Type::Size j = 0; j < sizeof(DWORD)*BitsPerByte; ++j)
            {
                if(USB[i] & (1 << j))
                {
                    index = (i*sizeof(DWORD)*BitsPerByte) + j;
                    for(RF_Type::Size k = 0; k < IDCOUNT[index]; ++k)
                    {
                        Out(Out.Count() - matches) = IDS[IDOFFSET[index] + k];
                        --matches;

                        if(matches == 0)
                        {
                            return;
                        }
                    }
                }
            }
        }
    }
}

int CALLBACK EnumerateFontFamily(const ENUMLOGFONTEX *lpelfe, const NEWTEXTMETRICEX *lpntme,
    DWORD FontType, LPARAM lParam)
{
    if(FontType & TRUETYPE_FONTTYPE)
    {

        const RF_Type::Size TABLESIZE = 11;
        const RF_Type::String STRINGLOOKUPTABLE[TABLESIZE] = {RF_Type::String("Bold"), 
            RF_Type::String("BoldItalic"), RF_Type::String("BoldOblique"), 
            RF_Type::String("Bold Italic"), RF_Type::String("Bold Oblique"), 
            RF_Type::String("Italic"), RF_Type::String("Oblique"),
            RF_Type::String("Regular"), RF_Type::String("Roman"), 
            RF_Type::String("Standard"), RF_Type::String("ExtraLight")};
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
        variation->HorizontalOrientation = lpelfe->elfLogFont.lfOrientation == 0;
        ObtainUnicodeRangeIdentifierFromUsb(lpntme->ntmFontSig.fsUsb, variation->SupportedUnicodeSubranges);

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

void ImplementationGetUnicodeCharRanges(const RF_Type::String& Text,
    RF_Collect::Array<RF_Text::UnicodeRangeIdentifier>& Out)
{
    LOCALESIGNATURE signature;
    WCHAR languageUtf16[LOCALE_NAME_MAX_LENGTH];
    mbstowcs(languageUtf16, Text.c_str(), LOCALE_NAME_MAX_LENGTH);
    int result = GetLocaleInfoEx(languageUtf16, LOCALE_FONTSIGNATURE,
        (LPWSTR)&signature, sizeof(signature) / sizeof(WCHAR));
    if(result > 0)
    {
        ObtainUnicodeRangeIdentifierFromUsb(signature.lsUsb,Out);
    }
}

void ImplementationGetAvailableFonts(RF_Collect::List<RF_Draw::FontDescription>& fonts)
{
    // get all system fonts
    HDC dc = GetDC(0);
    LOGFONT logfont;
    logfont.lfCharSet = DEFAULT_CHARSET;
    logfont.lfFaceName[0] = '\0';
    logfont.lfPitchAndFamily = 0;
    EnumFontFamiliesEx(dc, &logfont, (FONTENUMPROC)EnumerateFontFamily, reinterpret_cast<LPARAM>(&fonts), 0);
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
#else
void ImplementationGetAvailableFonts(RF_Collect::List<RF_Draw::FontDescription>& fonts)
{
}

void ImplementationGetUnicodeCharRanges(const RF_Type::String& Text,
                                        RF_Collect::Array<RF_Text::UnicodeRangeIdentifier>& Out)
{
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
            if(MatchFilter(fonts[i].Variations(j)))
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
                    if(MatchFilter(fonts[i].Variations(j)))
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

void OSFontService::GetUnicodeCharRanges(const RF_Type::String& Text, 
    RF_Collect::Array<RF_Text::UnicodeRangeIdentifier>& Out)
{
    ImplementationGetUnicodeCharRanges(Text, Out);
}

} } }
