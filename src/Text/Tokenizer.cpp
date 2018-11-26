#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/Tokenizer.hpp"
#include "RadonFramework/Collections/Algorithm/FindAll.hpp"
#include "RadonFramework/Collections/Algorithm/QuickSort.hpp"

namespace RadonFramework::Text {

class DeleteTokenCommand: public ASTCommand
{
public:
    virtual void Execute(RF_Collect::Tree<RF_Mem::AutoPointer<Token>>::NodeType& Parent,
        RF_Type::Int32& Offset) override
    {
        auto* node = Parent.Child(IndexOfToken + Offset);
        Parent.RemoveChild(node);
        --Offset;
    }
};

class ReplaceTokenCommand: public ASTCommand
{
public:
    ReplaceTokenCommand(RF_Mem::AutoPointer<Token>& AToken)
    :NewToken(AToken)
    {

    }

    virtual void Execute(RF_Collect::Tree<RF_Mem::AutoPointer<Token>>::NodeType& Parent,
        RF_Type::Int32& Offset) override
    {
        auto* node = Parent.Child(IndexOfToken + Offset);
        node->Data() = NewToken;
    }
    RF_Mem::AutoPointer<Token> NewToken;
};

class MoveIntoCommand: public ASTCommand
{
public:
    MoveIntoCommand(RF_Type::Size Start, RF_Type::Size End)
    :StartToken(Start)
    ,EndToken(End)
    { }

    virtual void Execute(RF_Collect::Tree<RF_Mem::AutoPointer<Token>>::NodeType& Parent,
        RF_Type::Int32& Offset) override
    {
        auto* node = Parent.Child(IndexOfToken + Offset);
        node->MoveFrom(Parent, StartToken+Offset, EndToken + Offset);
        Offset -= EndToken - StartToken + 1;
    }

    RF_Type::Size StartToken;
    RF_Type::Size EndToken;
};

void Tokenizer::Delimiter(const RF_Type::String& Delimiter)
{
    m_Delimiter = Delimiter;
}

void Tokenizer::Process(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Code)
{
  ParseCode(Code);
  
  for(RF_Type::Size i = 0; i < m_Rules.Count(); ++i)
  {
    m_Rules[i]->Code = &Code;
  }
  
  RecursiveVisit();

  for(RF_Type::Size i = 0; i < m_Rules.Count(); ++i)
  {
    m_Rules[i]->Code = nullptr;
  }
}

void Tokenizer::AddRule(RF_Mem::AutoPointer<Visitor> Rule)
{
    m_Rules.PushBack(Rule);
}

void Tokenizer::Print()
{
    decltype(m_AST)::NodeType* current = 0;
    current = m_AST.GetRootElement().FirstChild();
    while(current != 0)
    {
        if (current->Data())
            current->Data()->Print();

        if(current->Childs() > 0)
        {// go down
            current = current->FirstChild();
        }
        else
        {// go up
             while(current != 0 && current->Next() == 0)
             {
                 current = current->Parent();
             }

            if(current != 0)
            {
                current = current->Next();
            }
        }
    }
}

void Tokenizer::ParseCode(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Code)
{
    auto hits = RF_Algo::FindAll(Code, [=](RF_Mem::AutoPointerArray<RF_Type::UInt8>::ConstEnumeratorType& Element) {
        RF_Type::Bool result = false;
        for(RF_Type::Size i = 0; i < m_Delimiter.Length(); ++i)
        {
            if(*Element == m_Delimiter[i])
            {
                result = true;
                break;
            }
        }
        return result;
    });

    auto& node = m_AST.GetRootElement();
    RF_Mem::AutoPointer<Token> token;
    if(hits.Count() > 0)
    {
        RF_Type::Size childs = 0;
        if(hits[0] > 0)
        {
            ++childs;
        }
        ++childs;
        for(RF_Type::Size i = 1; i < hits.Count(); ++i)
        {
            if(hits[i] - hits[i - 1] > 1)
            {
                ++childs;
            }
            ++childs;
        }
        if(hits[hits.Count() - 1] < Code.Count())
        {
            ++childs;
        }
        node.AddChilds(childs);

        auto* currentNode = node.FirstChild();
        if(hits[0] > 0)
        {
            token.Reset(new CodePart(0, hits[0]));
            currentNode->Data() = token;
            currentNode = currentNode->Next();
        }

        token.Reset(new RF_Text::Delimiter(Code[hits[0]]));
        currentNode->Data() = token;
        currentNode = currentNode->Next();

        for(RF_Type::Size i = 1; i < hits.Count(); ++i)
        {
            if(hits[i] - hits[i - 1] > 1)
            {
                token.Reset(new CodePart(hits[i - 1] + 1, hits[i] - hits[i - 1] - 1));
                currentNode->Data() = token;
                currentNode = currentNode->Next();
            }

            token.Reset(new RF_Text::Delimiter(Code[hits[i]]));
            currentNode->Data() = token;
            currentNode = currentNode->Next();
        }

        if(hits[hits.Count() - 1] < Code.Count())
        {
            token.Reset(new CodePart(hits[hits.Count() - 1], Code.Count() - hits[hits.Count() - 1]));
            currentNode->Data() = token;
            currentNode = currentNode->Next();
        }
    }
}

void Tokenizer::ApplyChanges(RF_Collect::Tree<RF_Mem::AutoPointer<Token>>::NodeType*& Node, 
    RF_Collect::List<RF_Mem::AutoPointer<ASTCommand>>& Todo)
{
    RF_Type::Int32 offset = 0;
    RF_Collect::Tree<RF_Mem::AutoPointer<Token>>::NodeType* parent = Node->Parent();
    for(RF_Type::Size i = 0; i < Todo.Count(); ++i)
    {
        Todo[i]->Execute(*parent, offset);
    }
}

void Tokenizer::RecursiveVisit()
{
    RF_Collect::Stack<RF_Collect::Tree<RF_Mem::AutoPointer<Token>>::NodeType*> stack;
    for(RF_Type::Size i = 0; i < m_Rules.Count(); ++i)
    {
        decltype(m_AST)::NodeType* current = 0;
        RF_Type::Size stackItem = 0;
        stack.Push(&m_AST.GetRootElement());
        current = stack.Peek();
        while(stack.Size() > 0)
        {
            if(m_Rules[i]->Visit(*current) == false)
            {
                return;
            }

            // apply changes and go downwards need special treatment
            if(current->Childs() > 0 && stack.Size() > 1 && m_Rules[i]->Todo.Count() > 0)
            {
                ApplyChanges(current, m_Rules[i]->Todo);
                m_Rules[i]->Todo.Clear();
                stack.Pop();
                current = stack.Peek();
            }

            if(current->Childs() > 0)
            {// go down
                stack.Push(current->FirstChild());
                current = stack.Peek();
            }
            else
            {// go up
                while(stack.Size() > 0 && stack.Peek()->Next() == 0)
                {
                    ApplyChanges(current, m_Rules[i]->Todo);
                    m_Rules[i]->Todo.Clear();
                    stack.Pop();
                }

                if(stack.Size() > 0)
                {
                    current = stack.Peek()->Next();
                    stack.Pop();
                    stack.Push(current);
                }
            }            
        }

    }
}

Visitor::Visitor() 
:Code(nullptr)
{
}

Visitor::~Visitor() {

}

void Visitor::ReplaceToken(const TokenNode& AToken, 
    RF_Mem::AutoPointer<Token> NewToken)
{
    RF_Mem::AutoPointer<ASTCommand> cmd(new ReplaceTokenCommand(NewToken));
    if(AToken.Parent()->IndexOf(AToken, cmd->IndexOfToken))
    {
        Todo.AddLast(cmd);
    }
}

void Visitor::MoveTokens(const TokenNode& Destination,
    const TokenNode& First, const TokenNode& Last)
{
    RF_Type::Size ChildStart;
    RF_Type::Size ChildEnd;
    if(First.Parent()->IndexOf(First, ChildStart) &&
        Last.Parent()->IndexOf(Last, ChildEnd) &&
        First.Parent() == Last.Parent())
    {
        RF_Mem::AutoPointer<ASTCommand> cmd(new MoveIntoCommand(ChildStart, ChildEnd));
        if(Destination.Parent()->IndexOf(Destination, cmd->IndexOfToken))
        {
            Todo.AddLast(cmd);
        }
    }
}

void Visitor::DeleteToken(const TokenNode& AToken)
{
    RF_Mem::AutoPointer<ASTCommand> cmd(new DeleteTokenCommand);
    if(AToken.Parent()->IndexOf(AToken, cmd->IndexOfToken))
    {
        Todo.AddLast(cmd);
    }
}

Delimiter::Delimiter()
{
    Type = ID;
}

Delimiter::Delimiter(RF_Type::UInt8 DelimiterValue)
{
    Type = ID;
    Value = RF_Type::String(2);
    Value[0] = DelimiterValue;
}

RF_Type::UInt16 Delimiter::ID = 1;

Token::Token()
:Type(0)
{

}

Token::~Token()
{
}

CodePart::CodePart()
:Start(0)
,Count(0)
{
    Type = ID;
}

CodePart::CodePart(RF_Type::Size CodeStart, RF_Type::Size Bytes)
{
    Type = ID;
    Start = CodeStart;
    Count = Bytes;
}

RF_Type::UInt16 CodePart::ID = 2;

void ASTCommand::Execute(RF_Collect::Tree<RF_Mem::AutoPointer<Token>>::NodeType& Parent,
    RF_Type::Int32& Offset)
{

}

}