#ifndef RF_TEXT_TOKENIZER_HPP
#define RF_TEXT_TOKENIZER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/Stack.hpp>
#include <RadonFramework/Collections/Tree.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/IO/Log.hpp>

namespace RadonFramework { namespace Text {

class Token
{
public:
    Token();
    virtual ~Token();
    RF_Type::UInt16 Type;
    virtual void Print()
    {
        RF_IO::LogInfo("Token");
    }
};

class CodePart: public Token
{
public:
    CodePart();
    CodePart(RF_Type::Size CodeStart, RF_Type::Size Bytes);

    RF_Type::Size Start;
    RF_Type::Size Count;

    virtual void Print()
    {
        RF_IO::LogInfo("CodePart: %llu %llu", Start, Count);
    }

    static RF_Type::UInt16 ID;
};

class Delimiter: public Token
{
public:
    Delimiter();
    Delimiter(RF_Type::UInt8 DelimiterValue);
        
    virtual void Print()
    {
        RF_IO::LogInfo("Delimiter: %s", Value.c_str());
    }

    RF_Type::String Value;
    static RF_Type::UInt16 ID;
};

class ASTCommand
{
public:
    virtual void Execute(RF_Collect::Tree<RF_Mem::AutoPointer<Token>>::NodeType& Parent,
        RF_Type::Int32& Offset);
    RF_Type::Size IndexOfToken;
};

class Visitor
{
public:
    typedef RF_Collect::Tree<RF_Mem::AutoPointer<Token>>::NodeType TokenNode;
    typedef RF_Collect::Stack<TokenNode*> TokenStack;

    virtual ~Visitor();
    virtual RF_Type::Bool Visit(const TokenNode& AToken)=0;

    void ReplaceToken(const TokenNode& AToken,
        RF_Mem::AutoPointer<Token> NewToken);
    void MoveTokens(const TokenNode& Destination,
        const TokenNode& First, const TokenNode& Last);
    void DeleteToken(const TokenNode& AToken);

    RF_Collect::List<RF_Mem::AutoPointer<ASTCommand>> Todo;
};

class Tokenizer
{
public:
    void Delimiter(const RF_Type::String& Delimiter);
    void Process(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Code);
    void AddRule(RF_Mem::AutoPointer<Visitor> Rule);
    void Print();
private:
    RF_Collect::Tree<RF_Mem::AutoPointer<Token>> m_AST;
    RF_Type::String m_Delimiter;
    RF_Collect::AutoVector<Visitor> m_Rules;

    void ParseCode(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Code);
    void RecursiveVisit();
    void ApplyChanges(RF_Collect::Tree<RF_Mem::AutoPointer<Token>>::NodeType*& Node, 
        RF_Collect::List<RF_Mem::AutoPointer<ASTCommand>>& Todo);
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_TEXT
#define RF_SHORTHAND_NAMESPACE_TEXT
namespace RF_Text = RadonFramework::Text;
#endif

#endif // RF_TEXT_REGEX_HPP
