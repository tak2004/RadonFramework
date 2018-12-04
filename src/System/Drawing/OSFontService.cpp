#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Drawing/OSFontService.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/System/String.hpp"

#if defined(RF_WINDOWS)
#include <windows.h>

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

struct IdentifierData
{
    RF_Type::UInt32 Start;
    RF_Type::UInt32 End;
    RF_Text::UnicodeRangeIdentifier Identifier;
};

static const IdentifierData DATA[169] = {
    {0x20, 0x7F, RF_Text::UnicodeRangeIdentifier::BasicLatin},
    {0xA0, 0xFF, RF_Text::UnicodeRangeIdentifier::Latin1Supplement},
    {0x100, 0x17F, RF_Text::UnicodeRangeIdentifier::LatinExtended_A},
    {0x180, 0x24F, RF_Text::UnicodeRangeIdentifier::LatinExtended_B},
    {0x250, 0x2AF, RF_Text::UnicodeRangeIdentifier::IPAExtensions},
    {0x1D00, 0x1D7F, RF_Text::UnicodeRangeIdentifier::PhoneticExtensions},
    {0x1D80, 0x1DBF, RF_Text::UnicodeRangeIdentifier::PhoneticExtensionsSupplement},
    {0x2B0, 0x2FF, RF_Text::UnicodeRangeIdentifier::SpacingModifierLetters},
    {0xA700, 0xA71F, RF_Text::UnicodeRangeIdentifier::ModifierToneLetters},
    {0x300, 0x36F, RF_Text::UnicodeRangeIdentifier::CombiningDiacriticalMarks},
    {0x1DC0, 0x1DFF, RF_Text::UnicodeRangeIdentifier::CombiningDiacriticalMarksSupplement},
    {0x370, 0x3FF, RF_Text::UnicodeRangeIdentifier::GreekAndCoptic},
    {0x2C80, 0x2CFF, RF_Text::UnicodeRangeIdentifier::Coptic},
    {0x400, 0x4FF, RF_Text::UnicodeRangeIdentifier::Cyrillic},
    {0x500, 0x52F, RF_Text::UnicodeRangeIdentifier::CyrillicSupplement},
    {0x2DE0, 0x2DFF, RF_Text::UnicodeRangeIdentifier::CyrillicExtended_A},
    {0xA640, 0xA69F, RF_Text::UnicodeRangeIdentifier::CyrillicExtended_B},
    {0x530, 0x58F, RF_Text::UnicodeRangeIdentifier::Armenian},
    {0x590, 0x5FF, RF_Text::UnicodeRangeIdentifier::Hebrew},
    {0xA500, 0xA63F, RF_Text::UnicodeRangeIdentifier::Vai},
    {0x600, 0x6FF, RF_Text::UnicodeRangeIdentifier::Arabic},
    {0x750, 0x77F, RF_Text::UnicodeRangeIdentifier::ArabicSupplement},
    {0x7C0, 0x7FF, RF_Text::UnicodeRangeIdentifier::NKo},
    {0x900, 0x97F, RF_Text::UnicodeRangeIdentifier::Devanagari},
    {0x980, 0x9FF, RF_Text::UnicodeRangeIdentifier::Bengali},
    {0xA00, 0xA7F, RF_Text::UnicodeRangeIdentifier::Gurmukhi},
    {0xA80, 0xAFF, RF_Text::UnicodeRangeIdentifier::Gujarati},
    {0xB00, 0xB7F, RF_Text::UnicodeRangeIdentifier::Oriya},
    {0xB80, 0xBFF, RF_Text::UnicodeRangeIdentifier::Tamil},
    {0xC00, 0xC7F, RF_Text::UnicodeRangeIdentifier::Telugu},
    {0xC80, 0xCFF, RF_Text::UnicodeRangeIdentifier::Kannada},
    {0xD00, 0xD7F, RF_Text::UnicodeRangeIdentifier::Malayalam},
    {0xE00, 0xE7F, RF_Text::UnicodeRangeIdentifier::Thai},
    {0xE80, 0xEFF, RF_Text::UnicodeRangeIdentifier::Lao},
    {0x10A0, 0x10FF, RF_Text::UnicodeRangeIdentifier::Georgian},
    {0x2D00, 0x2D2F, RF_Text::UnicodeRangeIdentifier::GeorgianSupplement},
    {0x1B00, 0x1B7F, RF_Text::UnicodeRangeIdentifier::Balinese},
    {0x1100, 0x11FF, RF_Text::UnicodeRangeIdentifier::HangulJamo},
    {0x1E00, 0x1EFF, RF_Text::UnicodeRangeIdentifier::LatinExtendedAdditional},
    {0x2C60, 0x2C7F, RF_Text::UnicodeRangeIdentifier::LatinExtended_C},
    {0xA720, 0xA7FF, RF_Text::UnicodeRangeIdentifier::LatinExtended_D},
    {0x1F00, 0x1FFF, RF_Text::UnicodeRangeIdentifier::GreekExtended},
    {0x2000, 0x206F, RF_Text::UnicodeRangeIdentifier::GeneralPunctuation},
    {0x2E00, 0x2E7F, RF_Text::UnicodeRangeIdentifier::SupplementalPunctuation},
    {0x2070, 0x209F, RF_Text::UnicodeRangeIdentifier::SuperscriptsAndSubscripts},
    {0x20A0, 0x20CF, RF_Text::UnicodeRangeIdentifier::CurrencySymbols},
    {0x20D0, 0x20FF, RF_Text::UnicodeRangeIdentifier::CombiningDiacriticalMarksForSymbols},
    {0x2100, 0x214F, RF_Text::UnicodeRangeIdentifier::LetterlikeSymbols},
    {0x2150, 0x218F, RF_Text::UnicodeRangeIdentifier::NumberForms},
    {0x2190, 0x21FF, RF_Text::UnicodeRangeIdentifier::Arrows},
    {0x27F0, 0x27FF, RF_Text::UnicodeRangeIdentifier::SupplementalArrows_A},
    {0x2900, 0x297F, RF_Text::UnicodeRangeIdentifier::SupplementalArrows_B},
    {0x2B00, 0x2BFF, RF_Text::UnicodeRangeIdentifier::MiscellaneousSymbolsAndArrows},
    {0x2200, 0x22FF, RF_Text::UnicodeRangeIdentifier::MathematicalOperators},
    {0x27C0, 0x27EF, RF_Text::UnicodeRangeIdentifier::MiscellaneousMathematicalSymbols_A},
    {0x2980, 0x29FF, RF_Text::UnicodeRangeIdentifier::MiscellaneousMathematicalSymbols_B},
    {0x2A00, 0x2AFF, RF_Text::UnicodeRangeIdentifier::SupplementalMathematicalOperators},
    {0x2300, 0x23FF, RF_Text::UnicodeRangeIdentifier::MiscellaneousTechnical},
    {0x2400, 0x243F, RF_Text::UnicodeRangeIdentifier::ControlPictures},
    {0x2440, 0x245F, RF_Text::UnicodeRangeIdentifier::OpticalCharacterRecognition},
    {0x2460, 0x24FF, RF_Text::UnicodeRangeIdentifier::EnclosedAlphanumerics},
    {0x2500, 0x257F, RF_Text::UnicodeRangeIdentifier::BoxDrawing},
    {0x2580, 0x259F, RF_Text::UnicodeRangeIdentifier::BlockElements},
    {0x25A0, 0x25FF, RF_Text::UnicodeRangeIdentifier::GeometricShapes},
    {0x2600, 0x26FF, RF_Text::UnicodeRangeIdentifier::MiscellaneousSymbols},
    {0x2700, 0x27BF, RF_Text::UnicodeRangeIdentifier::Dingbats},
    {0x3000, 0x303F, RF_Text::UnicodeRangeIdentifier::CJKSymbolsAndPunctuation},
    {0x3040, 0x309F, RF_Text::UnicodeRangeIdentifier::Hiragana},
    {0x30A0, 0x30FF, RF_Text::UnicodeRangeIdentifier::Katakana},
    {0x31F0, 0x31FF, RF_Text::UnicodeRangeIdentifier::KatakanaPhoneticExtensions},
    {0x3100, 0x312F, RF_Text::UnicodeRangeIdentifier::Bopomofo},
    {0x31A0, 0x31BF, RF_Text::UnicodeRangeIdentifier::BopomofoExtended},
    {0x3130, 0x318F, RF_Text::UnicodeRangeIdentifier::HangulCompatibilityJamo},
    {0xA840, 0xA87F, RF_Text::UnicodeRangeIdentifier::Phags_pa},
    {0x3200, 0x32FF, RF_Text::UnicodeRangeIdentifier::EnclosedCJKLettersAndMonths},
    {0x3300, 0x33FF, RF_Text::UnicodeRangeIdentifier::CJKCompatibility},
    {0xAC00, 0xD7AF, RF_Text::UnicodeRangeIdentifier::HangulSyllables},
    {0xD800, 0xDFFF, RF_Text::UnicodeRangeIdentifier::NonPlane0},
    {0x10900, 0x1091F, RF_Text::UnicodeRangeIdentifier::Phoenician},
    {0x2E80, 0x2EFF, RF_Text::UnicodeRangeIdentifier::CJKRadicalsSupplement},
    {0x2F00, 0x2FDF, RF_Text::UnicodeRangeIdentifier::KangxiRadicals},
    {0x2FF0, 0x2FFF, RF_Text::UnicodeRangeIdentifier::IdeographicDescriptionCharacters},
    {0x3190, 0x319F, RF_Text::UnicodeRangeIdentifier::Kanbun},
    {0x3400, 0x4DBF, RF_Text::UnicodeRangeIdentifier::CJKUnifiedIdeographsExtension_A},
    {0x4E00, 0x9FFF, RF_Text::UnicodeRangeIdentifier::CJKUnifiedIdeographs},
    {0x20000, 0x2A6DF, RF_Text::UnicodeRangeIdentifier::CJKUnifiedIdeographsExtension_B},
    {0xE000, 0xF8FF, RF_Text::UnicodeRangeIdentifier::PrivateUseArea},
    {0x31C0, 0x31EF, RF_Text::UnicodeRangeIdentifier::CJKStrokes},
    {0xF900, 0xFAFF, RF_Text::UnicodeRangeIdentifier::CJKCompatibilityIdeographs},
    {0x2F800, 0x2FA1F, RF_Text::UnicodeRangeIdentifier::CJKCompatibilityIdeographsSupplement},
    {0xFB00, 0xFB4F, RF_Text::UnicodeRangeIdentifier::AlphabeticPresentationForms},
    {0xFB50, 0xFDFF, RF_Text::UnicodeRangeIdentifier::ArabicPresentationForms_A},
    {0xFE20, 0xFE2F, RF_Text::UnicodeRangeIdentifier::CombiningHalfMarks},
    {0xFE10, 0xFE1F, RF_Text::UnicodeRangeIdentifier::VerticalForms},
    {0xFE30, 0xFE4F, RF_Text::UnicodeRangeIdentifier::CJKCompatibilityForms},
    {0xFE50, 0xFE6F, RF_Text::UnicodeRangeIdentifier::SmallFormVariants},
    {0xFE70, 0xFEFF, RF_Text::UnicodeRangeIdentifier::ArabicPresentationForms_B},
    {0xFF00, 0xFFEF, RF_Text::UnicodeRangeIdentifier::HalfwidthAndFullwidthForms},
    {0xFFF0, 0xFFFF, RF_Text::UnicodeRangeIdentifier::Specials},
    {0x0F00, 0x0FFF, RF_Text::UnicodeRangeIdentifier::Tibetan},
    {0x0700, 0x074F, RF_Text::UnicodeRangeIdentifier::Syriac},
    {0x0780, 0x07BF, RF_Text::UnicodeRangeIdentifier::Thaana},
    {0x0D80, 0x0DFF, RF_Text::UnicodeRangeIdentifier::Sinhala},
    {0x1000, 0x109F, RF_Text::UnicodeRangeIdentifier::Myanmar},
    {0x1200, 0x137F, RF_Text::UnicodeRangeIdentifier::Ethiopic},
    {0x1380, 0x139F, RF_Text::UnicodeRangeIdentifier::EthiopicSupplement},
    {0x2D80, 0x2DDF, RF_Text::UnicodeRangeIdentifier::EthiopicExtended},
    {0x13A0, 0x13FF, RF_Text::UnicodeRangeIdentifier::Cherokee},
    {0x1400, 0x167F, RF_Text::UnicodeRangeIdentifier::UnifiedCanadianAboriginalSyllabics},
    {0x1680, 0x169F, RF_Text::UnicodeRangeIdentifier::Ogham},
    {0x16A0, 0x16FF, RF_Text::UnicodeRangeIdentifier::Runic},
    {0x1780, 0x17FF, RF_Text::UnicodeRangeIdentifier::Khmer},
    {0x19E0, 0x19FF, RF_Text::UnicodeRangeIdentifier::KhmerSymbols},
    {0x1800, 0x18AF, RF_Text::UnicodeRangeIdentifier::Mongolian},
    {0x2800, 0x28FF, RF_Text::UnicodeRangeIdentifier::BraillePatterns},
    {0xA000, 0xA48F, RF_Text::UnicodeRangeIdentifier::YiSyllables},
    {0xA490, 0xA4CF, RF_Text::UnicodeRangeIdentifier::YiRadicals},
    {0x1700, 0x171F, RF_Text::UnicodeRangeIdentifier::Tagalog},
    {0x1720, 0x173F, RF_Text::UnicodeRangeIdentifier::Hanunoo},
    {0x1740, 0x175F, RF_Text::UnicodeRangeIdentifier::Buhid},
    {0x1760, 0x177F, RF_Text::UnicodeRangeIdentifier::Tagbanwa},
    {0x10300, 0x1032F, RF_Text::UnicodeRangeIdentifier::OldItalic},
    {0x10330, 0x1034F, RF_Text::UnicodeRangeIdentifier::Gothic},
    {0x10400, 0x1044F, RF_Text::UnicodeRangeIdentifier::Deseret},
    {0x1D000, 0x1D0FF, RF_Text::UnicodeRangeIdentifier::ByzantineMusicalSymbols},
    {0x1D100, 0x1D1FF, RF_Text::UnicodeRangeIdentifier::MusicalSymbols},
    {0x1D200, 0x1D24F, RF_Text::UnicodeRangeIdentifier::AncientGreekMusicalNotation},
    {0x1D400, 0x1D7FF, RF_Text::UnicodeRangeIdentifier::MathematicalAlphanumericSymbols},
    {0xFF000, 0xFFFFD, RF_Text::UnicodeRangeIdentifier::PrivateUsePlane15},
    {0x100000, 0x10FFFD, RF_Text::UnicodeRangeIdentifier::PrivateUsePlane16},
    {0xFE00, 0xFE0F, RF_Text::UnicodeRangeIdentifier::VariationSelectors},
    {0xE0100, 0xE01EF, RF_Text::UnicodeRangeIdentifier::VariationSelectorsSupplement},
    {0xE0000, 0xE007F, RF_Text::UnicodeRangeIdentifier::Tags},
    {0x1900, 0x194F, RF_Text::UnicodeRangeIdentifier::Limbu},
    {0x1950, 0x197F, RF_Text::UnicodeRangeIdentifier::TaiLe},
    {0x1980, 0x19DF, RF_Text::UnicodeRangeIdentifier::NewTaiLue},
    {0x1A00, 0x1A1F, RF_Text::UnicodeRangeIdentifier::Buginese},
    {0x2C00, 0x2C5F, RF_Text::UnicodeRangeIdentifier::Glagolitic},
    {0x2D30, 0x2D7F, RF_Text::UnicodeRangeIdentifier::Tifinagh},
    {0x4DC0, 0x4DFF, RF_Text::UnicodeRangeIdentifier::YijingHexagramSymbols},
    {0xA800, 0xA82F, RF_Text::UnicodeRangeIdentifier::SylotiNagri},
    {0x10000, 0x1007F, RF_Text::UnicodeRangeIdentifier::LinearBSyllabary},
    {0x10080, 0x100FF, RF_Text::UnicodeRangeIdentifier::LinearBIdeograms},
    {0x10100, 0x1013F, RF_Text::UnicodeRangeIdentifier::AegeanNumbers},
    {0x10140, 0x1018F, RF_Text::UnicodeRangeIdentifier::AncientGreekNumbers},
    {0x10380, 0x1039F, RF_Text::UnicodeRangeIdentifier::Ugaritic},
    {0x103A0, 0x103DF, RF_Text::UnicodeRangeIdentifier::OldPersian},
    {0x10450, 0x1047F, RF_Text::UnicodeRangeIdentifier::Shavian},
    {0x10480, 0x104AF, RF_Text::UnicodeRangeIdentifier::Osmanya},
    {0x10800, 0x1083F, RF_Text::UnicodeRangeIdentifier::CypriotSyllabary},
    {0x10A00, 0x10A5F, RF_Text::UnicodeRangeIdentifier::Kharoshthi},
    {0x1D300, 0x1D35F, RF_Text::UnicodeRangeIdentifier::TaiXuanJingSymbols},
    {0x12000, 0x123FF, RF_Text::UnicodeRangeIdentifier::Cuneiform},
    {0x12400, 0x1247F, RF_Text::UnicodeRangeIdentifier::CuneiformNumbersAndPunctuation},
    {0x1D360, 0x1D37F, RF_Text::UnicodeRangeIdentifier::CountingRodNumerals},
    {0x1B80, 0x1BBF, RF_Text::UnicodeRangeIdentifier::Sundanese},
    {0x1C00, 0x1C4F, RF_Text::UnicodeRangeIdentifier::Lepcha},
    {0x1C50, 0x1C7F, RF_Text::UnicodeRangeIdentifier::OlChiki},
    {0xA880, 0xA8DF, RF_Text::UnicodeRangeIdentifier::Saurashtra},
    {0xA900, 0xA92F, RF_Text::UnicodeRangeIdentifier::KayahLi},
    {0xA930, 0xA95F, RF_Text::UnicodeRangeIdentifier::Rejang},
    {0xAA00, 0xAA5F, RF_Text::UnicodeRangeIdentifier::Cham},
    {0x10190, 0x101CF, RF_Text::UnicodeRangeIdentifier::AncientSymbols},
    {0x101D0, 0x101FF, RF_Text::UnicodeRangeIdentifier::PhaistosDisc},
    {0x10280, 0x1029F, RF_Text::UnicodeRangeIdentifier::Lycian},
    {0x102A0, 0x102DF, RF_Text::UnicodeRangeIdentifier::Carian},
    {0x10920, 0x1093F, RF_Text::UnicodeRangeIdentifier::Lydian},
    {0x1F000, 0x1F02F, RF_Text::UnicodeRangeIdentifier::MahjongTiles},
    {0x1F030, 0x1F09F, RF_Text::UnicodeRangeIdentifier::DominoTiles},
};

void ImplementationGetUnicodeCharRange(const RF_Text::UnicodeRangeIdentifier Identifier,
                                       RF_Text::UnicodeRangeInfo& Out)
{
    for (RF_Type::Size i= 0; i < 170; ++i)
    {
        if (DATA[i].Identifier == Identifier)
        {
            Out = RF_Text::UnicodeRangeInfo(DATA[i].Identifier, DATA[i].Start, DATA[i].End);
            break;
        }
    }
}

void ObtainUnicodeRangeIdentifierFromUsb(const DWORD USB[4],
    RF_Collect::Array<RF_Text::UnicodeRangeIdentifier>& Out)
{
    const RF_Type::Size BitsPerByte = 8;
    RF_Type::Size matches = 0, index = 0;
    for(RF_Type::Size i = 0; i < 4; ++i)
    {
        for(RF_Type::Size j = 0; j < sizeof(DWORD); ++j)
        {
            if(USB[i] & (1 << j))
            {
                index = (i * sizeof(DWORD)*BitsPerByte) + j;
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
                    index = (i * sizeof(DWORD)*BitsPerByte) + j;
                    for(RF_Type::Size k = 0; k < IDCOUNT[index]; ++k)
                    {
                        Out(Out.Count() - matches) = DATA[IDOFFSET[index] + k].Identifier;
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

void ObtainUnicodeRangeInfoFromUsb(const DWORD USB[4], 
    RF_Collect::Array<RF_Text::UnicodeRangeInfo>& Out)
{
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
                        Out(Out.Count() - matches) = RF_Text::UnicodeRangeInfo(
                            DATA[IDOFFSET[index] + k].Identifier,
                            DATA[IDOFFSET[index] + k].Start, 
                            DATA[IDOFFSET[index] + k].End);
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
        const RF_Type::String STRINGLOOKUPTABLE[TABLESIZE] = {"Bold"_rfs, 
            "BoldItalic"_rfs, "BoldOblique"_rfs, "Bold Italic"_rfs, 
            "Bold Oblique"_rfs, "Italic"_rfs, "Oblique"_rfs, "Regular"_rfs, 
            "Roman"_rfs, "Standard"_rfs, "ExtraLight"_rfs};
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
    RF_Collect::Array<RF_Text::UnicodeRangeInfo>& Out)
{
    LOCALESIGNATURE signature;
    WCHAR languageUtf16[LOCALE_NAME_MAX_LENGTH];
    mbstowcs(languageUtf16, Text.c_str(), LOCALE_NAME_MAX_LENGTH);
    int result = GetLocaleInfoEx(languageUtf16, LOCALE_FONTSIGNATURE,
        (LPWSTR)&signature, sizeof(signature) / sizeof(WCHAR));
    if(result > 0)
    {
        ObtainUnicodeRangeInfoFromUsb(signature.lsUsb, Out);
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
        if(!stringList.IsEmpty())
        {
            RF_Type::UInt8* cursor = stringList.Get();
            RF_Type::Size leftBytes = stringList.Size();
            RF_Type::String hiddenFont;
            while(*cursor != '\0')
            {
                RF_Type::Size bytes = RF_SysStr::CStringSizeOf(cursor, leftBytes);
              hiddenFont =
                  RF_Type::String(reinterpret_cast<const char*>(cursor), bytes,
                                  RF_Core::DataManagment::UnmanagedInstance);
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

void ImplementationLoadGlyphs(const RF_Draw::FontDescription& FromFont,
    const RF_Collect::Array<RF_Type::UInt32>& GlyphsUtf32,
    RF_Collect::Array<RF_Draw::Path2D>& Out)
{
    HDC hdc = GetDC(0);
    GLYPHMETRICS gm;
    UINT glyph='A';
    const MAT2 identity = {{0,1},{0,0},{0,0},{0,1}};
    DWORD needed;
    LOGFONTW lf;
    lf.lfOrientation = FromFont.Variations(0).HorizontalOrientation;
    lf.lfStrikeOut = 0;
    lf.lfUnderline = 0;
    lf.lfItalic = 0;
    lf.lfHeight = 0;
    lf.lfWidth = 0;
    lf.lfEscapement = 0;
    lf.lfOrientation = 0;
    lf.lfWeight = 0;
    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfQuality = DEFAULT_QUALITY;
    lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    mbstowcs(lf.lfFaceName, FromFont.Name.c_str(), LOCALE_NAME_MAX_LENGTH);
    HFONT old_font, unscaled_font;
    unscaled_font = CreateFontIndirectW(&lf);
    old_font = (HFONT)SelectObject(hdc, unscaled_font);

    needed = GetGlyphOutline(hdc, glyph, GGO_NATIVE, &gm, 0, nullptr, &identity);
    if(needed != GDI_ERROR)
    {
        RF_Mem::AutoPointerArray<RF_Type::UInt8> buffer(needed);
        if(GetGlyphOutline(hdc, glyph, GGO_NATIVE, &gm, needed, buffer.Get(), &identity) != GDI_ERROR)
        {
        }
    }

    unscaled_font = (HFONT)SelectObject(hdc, old_font);
    DeleteObject(unscaled_font);
}

void ImplementationLoadGlyphs(const RF_Draw::FontDescription& FromFont,
    const RF_Collect::Array<RF_Type::UInt32>& GlyphsUtf32,
    const RF_Type::UInt32 FontPixelSize,
    RF_Collect::Array<RF_Draw::Image>& RasterizedGlyphs, 
    RF_Collect::Array<RF_Draw::GlyphMetric>& Metrics)
{
    RasterizedGlyphs.Resize(GlyphsUtf32.Count());
    Metrics.Resize(GlyphsUtf32.Count());
    HDC hdc = GetDC(0);
    GLYPHMETRICS gm;
    UINT glyph = 'A';
    const MAT2 identity = {{0,1},{0,0},{0,0},{0,1}};
    DWORD needed;
    LOGFONTW lf;
    lf.lfOrientation = FromFont.Variations(0).HorizontalOrientation;
    lf.lfStrikeOut = 0;
    lf.lfUnderline = 0;
    lf.lfItalic = 0;
    lf.lfHeight = -MulDiv(FontPixelSize, GetDeviceCaps(hdc, LOGPIXELSY), 96);
    lf.lfWidth = 0;
    lf.lfEscapement = 0;
    lf.lfOrientation = 0;
    lf.lfWeight = 0;
    lf.lfCharSet = DEFAULT_CHARSET;
    lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
    lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
    lf.lfQuality = DEFAULT_QUALITY;
    lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    mbstowcs(lf.lfFaceName, FromFont.Name.c_str(), LOCALE_NAME_MAX_LENGTH);
    HFONT old_font, unscaled_font;
    unscaled_font = CreateFontIndirectW(&lf);
    old_font = (HFONT)SelectObject(hdc, unscaled_font);

    RF_Draw::PixelFormat gray;
    gray.BitPerPixel = 8;
    gray.Channels.Resize(1);
    gray.Channels(0).Bits = 8;
    gray.Channels(0).Type = RF_Draw::ChannelType::Luminocity;
    gray.Type = RF_Draw::PixelType::Unsigned;

    for (RF_Type::Size i = 0; i < GlyphsUtf32.Count(); ++i)
    {
        glyph = GlyphsUtf32(i);
        needed = GetGlyphOutline(hdc, glyph, GGO_GRAY8_BITMAP, &gm, 0, nullptr, &identity);
        if(needed != GDI_ERROR)
        {
            GetGlyphOutline(hdc, glyph, GGO_METRICS, &gm, 0, nullptr, &identity);
            RF_Type::Size rowSize = needed / gm.gmBlackBoxY;
            RF_Mem::AutoPointerArray<RF_Type::UInt8> buffer(needed);
            if(GetGlyphOutline(hdc, glyph, GGO_GRAY8_BITMAP, &gm, needed, buffer.Get(), &identity) != GDI_ERROR)
            {
                for(auto i = 0; i < buffer.Count(); ++i)
                {
                    buffer[i] = (buffer[i]/64.f)*255;
                }
                RasterizedGlyphs(i).Initialize(rowSize, gm.gmBlackBoxY, 1, gray, buffer);
                Metrics(i).Width = gm.gmBlackBoxX;
                Metrics(i).Height = gm.gmBlackBoxY;
                Metrics(i).OriginLeft = gm.gmptGlyphOrigin.x;
                Metrics(i).OriginTop = gm.gmptGlyphOrigin.y;
                Metrics(i).HorizontalAdvance = gm.gmCellIncX;
                Metrics(i).VerticalAdvance = gm.gmCellIncY;
            }
        }
    }

    unscaled_font = (HFONT)SelectObject(hdc, old_font);
    DeleteObject(unscaled_font);
}
#else
void ImplementationGetAvailableFonts(RF_Collect::List<RF_Draw::FontDescription>& fonts)
{
}

void ImplementationGetUnicodeCharRanges(const RF_Type::String& Text,
                                        RF_Collect::Array<RF_Text::UnicodeRangeInfo>& Out)
{
}

void ImplementationGetUnicodeCharRange(const RF_Text::UnicodeRangeIdentifier Identifier,
    RF_Text::UnicodeRangeInfo& Out)
{

}

void ImplementationLoadGlyphs(const RF_Draw::FontDescription& FromFont,
    const RF_Collect::Array<RF_Type::UInt32>& GlyphsUtf32,
    RF_Collect::Array<RF_Draw::Image>& Out)
{
}

void ImplementationLoadGlyphs(const RF_Draw::FontDescription& FromFont,
    const RF_Collect::Array<RF_Type::UInt32>& GlyphsUtf32,
    RF_Collect::Array<RF_Draw::Path2D>& Out)
{
}
#endif

namespace RadonFramework::System::Drawing {

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
    RF_Collect::Array<RF_Text::UnicodeRangeInfo>& Out)
{
    ImplementationGetUnicodeCharRanges(Text, Out);
}

void OSFontService::GetUnicodeCharRange(const RF_Text::UnicodeRangeIdentifier Identifier, 
    RF_Text::UnicodeRangeInfo& Out)
{
    ImplementationGetUnicodeCharRange(Identifier, Out);
}

void OSFontService::LoadGlyphs(const RF_Draw::FontDescription& FromFont,
    const RF_Collect::Array<RF_Type::UInt32>& GlyphsUtf32,
    RF_Collect::Array<RF_Draw::Path2D>& Out)
{
    ImplementationLoadGlyphs(FromFont, GlyphsUtf32, Out);
}

void OSFontService::LoadGlyphs(const RF_Draw::FontDescription& FromFont,
    const RF_Collect::Array<RF_Type::UInt32>& GlyphsUtf32,
    const RF_Type::UInt32 FontPixelSize,
    RF_Collect::Array<RF_Draw::Image>& RasterizedGlyphs,
    RF_Collect::Array<RF_Draw::GlyphMetric>& Metrics)
{
    ImplementationLoadGlyphs(FromFont, GlyphsUtf32, FontPixelSize, RasterizedGlyphs, Metrics);
}

}
