#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/LogicElement.hpp"
#include "RadonFramework/IO/Log.hpp"

namespace RadonFramework { namespace Text {


void LogicElement::Print(RF_Type::Size Depth)
{
    static const char* Lookup[] = {"Invalid", "Rule","CallRule", "Or", "And",
        "Return","Repeat", "Assign", "Variable", "Equal", "Unequal", "Value",
        "Condition"};

    switch(What)
    {
    case RadonFramework::Text::Logic::Assign:
    case RadonFramework::Text::Logic::Rule:
    case RadonFramework::Text::Logic::CallRule:
    case RadonFramework::Text::Logic::Variable:
    case RadonFramework::Text::Logic::Equal:
    case RadonFramework::Text::Logic::Unequal:
    case RadonFramework::Text::Logic::Value:
        if(!IsText)
            RF_IO::LogInfo("%*c%s = %u", Depth + 1, '-', Lookup[static_cast<RF_Type::Size>(What)], Number);
        else
            RF_IO::LogInfo("%*c%s = '%s'", Depth + 1, '-', Lookup[static_cast<RF_Type::Size>(What)], Text.c_str());
        break;
    case RadonFramework::Text::Logic::Invalid:
    case RadonFramework::Text::Logic::Or:
    case RadonFramework::Text::Logic::And:
    case RadonFramework::Text::Logic::Return:
    case RadonFramework::Text::Logic::Repeat:
    case RadonFramework::Text::Logic::Condition:
        RF_IO::LogInfo("%*c%s", Depth + 1, '-', Lookup[static_cast<RF_Type::Size>(What)]);
        break;
    default:
        RF_IO::LogError("%*cUnkown(%d)", Depth + 1, '-', static_cast<RF_Type::UInt32>(What));
        break;
    }
}

} }