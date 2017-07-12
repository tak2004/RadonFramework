#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Drawing/FontService.hpp>
#include <RadonFramework/Drawing/FontServiceLocator.hpp>

namespace RadonFramework::Drawing {

FontService::FontService(const RadonFramework::Core::Types::String &Name)
:Service(Name)
,m_HorizontalOrientation(true)
,m_EnableStyleFilter(false)
,m_EnableOrientationFilter(true)
,m_EnableCharRangeFilter(false)
{
}

FontService::~FontService()
{
}

const RF_Collect::Array<FontDescription>& FontService::Fonts() const
{
    return m_Fonts;
}

void FontService::Update()
{

}

void FontService::EnableStyleFilter(const FontStyle StyleFilter)
{
    m_EnableStyleFilter = true;
    m_StyleFilter = StyleFilter;
}

void FontService::DisableStyleFilter()
{
    m_EnableStyleFilter = false;
}

void FontService::EnableOrientationFilter(RF_Type::Bool Horizontal)
{
    m_EnableOrientationFilter = true;
    m_HorizontalOrientation = Horizontal;
}

void FontService::DisableOrientationFilter()
{
    m_EnableOrientationFilter = false;
}

void FontService::EnableCharRangeFilter(const RF_Collect::Array<RF_Text::UnicodeRangeInfo>& Filter)
{
    m_EnableCharRangeFilter = true;
    m_RangeFilter = Filter;
}

void FontService::DisableCharRangeFilter()
{
    m_EnableCharRangeFilter = false;
}

RF_Type::Bool FontService::MatchFilter(const FontVariation& Variation)
{
    RF_Type::Bool result = true;
    if(m_EnableStyleFilter &&
       (static_cast<RF_Type::Size>(Variation.Style) &
       static_cast<RF_Type::Size>(m_StyleFilter) == 0))
    {
        result = false;
    }

    if(m_EnableOrientationFilter &&
       (m_HorizontalOrientation != Variation.HorizontalOrientation))
    {
        result = false;
    }

    if(m_EnableCharRangeFilter)
    {
        RF_Type::Size k, l;
        for(k = 0; k < m_RangeFilter.Count(); ++k)
        {
            for(l = 0; l < Variation.SupportedUnicodeSubranges.Count(); ++l)
            {
                if(m_RangeFilter(k).Identifier() == Variation.SupportedUnicodeSubranges(l))
                {
                    break;
                }
            }

            if(l == Variation.SupportedUnicodeSubranges.Count())
            {
                break;
            }
        }

        if(k < m_RangeFilter.Count())
        {
            result = false;
        }
    }
    return result;
}

}