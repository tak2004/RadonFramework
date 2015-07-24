#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Drawing/FontService.hpp>
#include <RadonFramework/Drawing/FontServiceLocator.hpp>

namespace RadonFramework { namespace Drawing {

FontService::FontService(const RadonFramework::Core::Types::String &Name)
:Service(Name)
{
}

FontService::~FontService()
{
}

const RF_Collect::Array<FontDescription>& FontService::Fonts() const
{
    return m_Fonts;
}

void FontService::SetFilter(const FontStyle StyleFilter, const RF_Type::Bool OrientationFilter, 
    const RF_Type::Bool HorizontalOrientation)
{
    m_StyleFilter = StyleFilter;
    m_OrientationFilter = OrientationFilter;
    m_HorizontalOrientation = HorizontalOrientation;
}

} }