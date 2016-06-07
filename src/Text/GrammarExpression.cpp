#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/GrammarExpression.hpp"
#include "RadonFramework/Text/LogicElement.hpp"

namespace RadonFramework { namespace Text {

GrammarExpression& GrammarExpression::Is(RF_Type::UInt16 TokenId, 
    Quantifier Quantity /*= Quantifier::Once*/)
{
    decltype(Logic)::NodeType* node = nullptr;
    auto& root = Logic.GetRootElement();
    if(root.Childs() > 0)
    {
        root.AddChild({Logic::And});
    }

    switch(Quantity)
    {
    case Quantifier::Once:
        root.AddChild({Logic::Return})->AddChild({Logic::CallRule, TokenId});
        break;
    case Quantifier::ZeroOrMore:
        root.AddChild({Logic::Repeat})->AddChild({Logic::Condition})->AddChild({Logic::CallRule, TokenId});
        root.AddChild({Logic::Return})->AddChild({Logic::Value,1});
        break;
    case Quantifier::OneOrMore:
        root.AddChild({Logic::Assign,0})->AddChild({Logic::Value, 0});
        node = root.AddChild({Logic::Repeat})->AddChild({Logic::Condition});
        node->AddChild({Logic::CallRule, TokenId});
        node = node->Parent();
        node->AddChild({Logic::Assign,0})->AddChild({Logic::Value, 1});
        root.AddChild({Logic::Return})->AddChild({Logic::Variable, 0});
        break;
    case Quantifier::ZeroOrOnce:
        break;
    }
    return *this;
}

GrammarExpression& GrammarExpression::Is(const RF_Type::String& Text, 
    Quantifier Quantity /*= Quantifier::Once*/)
{
    decltype(Logic)::NodeType* node = nullptr;
    auto& root = Logic.GetRootElement();
    if(root.Childs() > 0)
    {
        root.AddChild({Logic::And});
    }

    switch(Quantity)
    {
    case Quantifier::Once:
        break;
    case Quantifier::ZeroOrMore:
        break;
    case Quantifier::OneOrMore:
        break;
    case Quantifier::ZeroOrOnce:// return !C && C;
        node = root.AddChild({Logic::Return});
        node = node->AddChild({Logic::And});
        node->AddChild({Logic::Unequal,0,Text, true});
        node->AddChild({Logic::Equal,0,Text, true});
        break;
    }
    return *this;
}

GrammarExpression& GrammarExpression::Not(RF_Type::UInt16 TokenId, 
    Quantifier Quantity /*= Quantifier::Once*/)
{
    decltype(Logic)::NodeType* node = nullptr;
    auto& root = Logic.GetRootElement();
    if(root.Childs() > 0)
    {
        root.AddChild({Logic::And});
    }

    switch(Quantity)
    {
    case Quantifier::Once:

        break;
    case Quantifier::ZeroOrMore:

        break;
    case Quantifier::OneOrMore:

        break;
    case Quantifier::ZeroOrOnce:// return !C && C
        node = root.AddChild({Logic::Return});
        node = node->AddChild({Logic::And});
        node->AddChild({Logic::Unequal,TokenId});
        node->AddChild({Logic::Equal,TokenId});
        break;
    }
    return *this;
}

GrammarExpression& GrammarExpression::Any(std::initializer_list<RF_Type::UInt16> list, 
    Quantifier Quantity /*= Quantifier::Once*/)
{
    decltype(Logic)::NodeType* node = nullptr;
    auto& root = Logic.GetRootElement();
    if(root.Childs() > 0)
    {
        root.AddChild({Logic::And});
    }

    if(list.size() > 0)
    {
        switch(Quantity)
        {
        case Quantifier::Once:// return (C[0]||...||C[n-1]);
            node = root.AddChild({Logic::Return});
            node = node->AddChild({Logic::Or});
            for(auto i : list)
            {
                node->AddChild({Logic::CallRule,i});
            }
            break;
        case Quantifier::OneOrMore:// 
            break;
        case Quantifier::ZeroOrMore:// for(;C[0]||...||C[n-1];){} return true;
            node = root.AddChild({Logic::Repeat})->AddChild({Logic::Condition});
            node = node->AddChild({Logic::Or});
            for(auto i : list)
            {
                node->AddChild({Logic::CallRule, i});
            }
            root.AddChild({Logic::Return})->AddChild({Logic::Value,1});
            break;
        case Quantifier::ZeroOrOnce:// return (C[0]||...||C[n-1]) && (C[0]||...||C[n-1]);
            node = root.AddChild({Logic::Return});
            node = node->AddChild({Logic::And});
            node = node->AddChild({Logic::Or});
            for(auto i : list)
            {
                node->AddChild({Logic::CallRule,i});
            }
            node = node->Parent();
            node = node->AddChild({Logic::Or});
            for(auto i : list)
            {
                node->AddChild({Logic::CallRule,i});
            }
            break;
        }
    }
    return *this;
}

GrammarExpression& GrammarExpression::Any(const RF_Type::String& Text, 
    Quantifier Quantity /*= Quantifier::Once*/)
{
    decltype(Logic)::NodeType* node = nullptr;
    auto& root = Logic.GetRootElement();
    if(root.Childs() > 0)
    {
        root.AddChild({Logic::And});
    }

    if(Text.Length() > 0)
    {
        switch(Quantity)
        {
        case Quantifier::Once:
            node = root.AddChild({Logic::Return});
            node = node->AddChild({Logic::Or});
            for(RF_Type::Size i = 0; i < Text.Length(); ++i)
            {
                node->AddChild({Logic::Equal, Text[i]});
            }
            break;
        case Quantifier::ZeroOrMore:
            break;
        case Quantifier::OneOrMore:// for (r=false; (C[0]||...||C[n-1]); r=true){}
            root.AddChild({Logic::Assign,0})->AddChild({Logic::Value, 0});
            node = root.AddChild({Logic::Repeat})->AddChild({Logic::Condition});
            node = node->AddChild({Logic::Or});
            for(RF_Type::Size i = 0; i < Text.Length(); ++i)
            {
                node->AddChild({Logic::Equal, Text[i]});
            }
            node = node->Parent()->Parent();
            node->AddChild({Logic::Assign,0})->AddChild({Logic::Value, 1});
            root.AddChild({Logic::Return})->AddChild({Logic::Variable, 0});
            break;
        case Quantifier::ZeroOrOnce:
            break;
        }
    }
    return *this;
}

} }