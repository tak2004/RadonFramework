#ifndef RF_CORE_PATTERN_SERVICE_HPP
#define RF_CORE_PATTERN_SERVICE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework { namespace Core { namespace Pattern {

class Service
{
public:
    Service(const RF_Type::String& Name);
    virtual ~Service();
    virtual const RF_Type::String& Name();
protected:
    RF_Type::String m_Name;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_PATTERN
#define RF_SHORTHAND_NAMESPACE_PATTERN
namespace RF_Pattern = RadonFramework::Core::Pattern;
#endif

#endif // RF_CORE_PATTERN_SERVICE_HPP
