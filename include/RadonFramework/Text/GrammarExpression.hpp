#ifndef RF_TEXT_GRAMMAREXPRESSION_HPP
#define RF_TEXT_GRAMMAREXPRESSION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Tree.hpp>
#include <RadonFramework/Text/LogicElement.hpp>
#include <initializer_list>

namespace RadonFramework { namespace Text {

enum class Quantifier
{
    Once,
    ZeroOrMore,// 0-n
    OneOrMore,// 1-n
    ZeroOrOnce// 0 or 1
};

class GrammarExpression
{
public:
    /// \TokenId
    GrammarExpression& Is(RF_Type::UInt16 TokenId, Quantifier Quantity = Quantifier::Once);

    GrammarExpression& Is(const RF_Type::String& Text, Quantifier Quantity = Quantifier::Once);

    /// [^TokenId]
    GrammarExpression& Not(RF_Type::UInt16 TokenId, Quantifier Quantity = Quantifier::Once);

    /// [list]
    GrammarExpression& Any(std::initializer_list<RF_Type::UInt16> list, Quantifier Quantity = Quantifier::Once);

    /// [list]
    GrammarExpression& Any(const RF_Type::String& Text, Quantifier Quantity = Quantifier::Once);

    RF_Type::UInt16 Id;
    RF_Collect::Tree<LogicElement> Logic;
};


} }

#ifndef RF_SHORTHAND_NAMESPACE_TEXT
#define RF_SHORTHAND_NAMESPACE_TEXT
namespace RF_Text = RadonFramework::Text;
#endif

#endif // RF_TEXT_GRAMMAREXPRESSION_HPP
