#ifndef RF_FONTSERVICELOCATOR_HPP
#define RF_FONTSERVICELOCATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/ServiceLocator.hpp>
#include <RadonFramework/Drawing/FontService.hpp>

namespace RadonFramework { namespace Drawing {

class NullFontService:public FontService
{
public:
    NullFontService(const RF_Type::String &Name)
    :FontService(Name)
    {
    }
    virtual void Update() override
    {
    }
    virtual void GetUnicodeCharRanges(const RF_Type::String& Text, 
        RF_Collect::Array<RF_Text::UnicodeRangeIdentifier>& Out) override
    {

    }
};

typedef Core::Pattern::Locator<FontService, NullFontService> FontServiceLocator;

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_FONTSERVICELOCATOR_HPP