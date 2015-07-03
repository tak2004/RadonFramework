#ifndef RF_FONTSERVICE_HPP
#define RF_FONTSERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Service.hpp>
#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework { namespace Drawing {

class FontDescription
{
public:
    RF_Type::String Name;
};

class FontService:public RF_Pattern::Service
{
public:
    FontService(const RF_Type::String &Name);
    ~FontService();
    virtual void Update() = 0;
    const RF_Collect::Array<FontDescription>& Fonts()const;
protected:
    RF_Collect::Array<FontDescription> m_Fonts;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_FONTSERVICE_HPP
