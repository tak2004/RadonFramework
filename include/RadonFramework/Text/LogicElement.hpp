#ifndef RF_TEXT_LOGICELEMENT_HPP
#define RF_TEXT_LOGICELEMENT_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Text {

enum class Logic
{
    Invalid,
    Rule,
    CallRule,
    Or,
    And,
    Return,
    Repeat,
    Assign,
    Variable,
    Equal,
    Unequal,
    Value,
    Condition
};

class LogicElement
{
public:
    void Print(RF_Type::Size Depth);

    Logic What;
    RF_Type::UInt32 Number;
    RF_Type::String Text;
    RF_Type::Bool IsText;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_TEXT
#define RF_SHORTHAND_NAMESPACE_TEXT
namespace RF_Text = RadonFramework::Text;
#endif

#endif // RF_TEXT_LOGICELEMENT_HPP