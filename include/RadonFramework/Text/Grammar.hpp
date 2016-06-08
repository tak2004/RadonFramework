#ifndef RF_TEXT_GRAMMAR_HPP
#define RF_TEXT_GRAMMAR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Tree.hpp>
#include <RadonFramework/Text/GrammarExpression.hpp>
#include <RadonFramework/Text/LogicElement.hpp>

namespace RadonFramework { namespace Text {

class Grammar
{
public:
    using TokenizerFunction = RF_Type::Bool(*)(RF_Mem::AutoPointerArray<RF_Type::UInt8>&);

    GrammarExpression& Add(RF_Type::UInt16 Id);

    RF_Mem::AutoPointerArray<RF_Type::UInt8> GetByteCode();
    const RF_Mem::AutoPointerArray<RF_Type::UInt8>& GetByteCode()const;

    void Compile();

    RF_Type::Size GetFunctionSymbol(RF_Type::UInt32);

    void Print();
protected:
    RF_Collect::Array<GrammarExpression> m_Expressions;
    RF_Collect::Tree<LogicElement> m_LogicTree;
    RF_Mem::AutoPointerArray<RF_Type::UInt8> m_ByteCode;
private:
    void GenerateByteCode();
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_TEXT
#define RF_SHORTHAND_NAMESPACE_TEXT
namespace RF_Text = RadonFramework::Text;
#endif

#endif // RF_TEXT_GRAMMAR_HPP
