#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/Grammar.hpp"

namespace RadonFramework { namespace Text {

class Interpreter
{
public:
    static RF_Type::Bool IsEqual(RF_Collect::ArrayNode<LogicElement>& Node)
    {
        RF_Type::Bool result = Node.Data().What == Logic::Equal;
        return result;
    }

    static RF_Type::Bool IsUnequal(RF_Collect::ArrayNode<LogicElement>& Node)
    {
        RF_Type::Bool result = Node.Data().What == Logic::Unequal;
        return result;
    }

    static RF_Type::Bool IsOr(RF_Collect::ArrayNode<LogicElement>& Node)
    {
        RF_Type::Bool result = false;
        if(Node.Data().What == Logic::Or)
        {
            RF_Collect::ArrayNode<LogicElement>* node = Node.FirstChild();
            while(node != nullptr)
            {
                result = IsEqual(*node) || IsUnequal(*node) || IsCallRule(*node);
                if(result)
                    node = node->Next();
                else
                    break;
            }

            if(node != nullptr)
            {// error

            }
        }
        return result;
    }

    static RF_Type::Bool IsAnd(RF_Collect::ArrayNode<LogicElement>& Node)
    {
        RF_Type::Bool result = false;
        if(Node.Data().What == Logic::And)
        {
            RF_Collect::ArrayNode<LogicElement>* node = Node.FirstChild();
            while(node != nullptr)
            {
                result = IsEqual(*node) || IsUnequal(*node) || IsCallRule(*node);
                if(result)
                    node = node->Next();
                else
                    break;
            }

            if(node != nullptr)
            {// error

            }
        }
        return result;
    }

    static RF_Type::Bool IsVariable(RF_Collect::ArrayNode<LogicElement>& Node)
    {
        RF_Type::Bool result = Node.Data().What == Logic::Variable;
        return result;
    }

    static RF_Type::Bool IsValue(RF_Collect::ArrayNode<LogicElement>& Node)
    {
        RF_Type::Bool result = Node.Data().What == Logic::Value;
        return result;
    }

    static RF_Type::Bool IsCallRule(RF_Collect::ArrayNode<LogicElement>& Node)
    {
        RF_Type::Bool result = Node.Data().What == Logic::CallRule;
        return result;
    }

    static RF_Type::Bool IsCondition(RF_Collect::ArrayNode<LogicElement>& Node)
    {
        RF_Type::Bool result = false;
        if(Node.Data().What == Logic::Condition)
        {
            RF_Collect::ArrayNode<LogicElement>* node = Node.FirstChild();
            while(node != nullptr)
            {
                result = IsOr(*node) || IsAnd(*node) || IsCallRule(*node) ||
                    IsUnequal(*node) || IsEqual(*node);
                if(result)
                    node = node->Next();
                else
                    break;
            }

            if(node != nullptr)
            {// error

            }
        }
        return result;
    }

    static RF_Type::Bool IsRepeat(RF_Collect::ArrayNode<LogicElement>& Node)
    {
        RF_Type::Bool result = false;
        RF_Type::Bool containsCondition = false;
        if(Node.Data().What == Logic::Repeat)
        {
            RF_Collect::ArrayNode<LogicElement>* node = Node.FirstChild();
            while(node != nullptr)
            {
                if(containsCondition == false)
                    containsCondition = IsCondition(*node);

                result = IsAssign(*node) || IsCondition(*node);
                if(result)
                    node = node->Next();
                else
                    break;
            }

            if(node != nullptr)
            {// error

            }
        }
        return result && containsCondition;
    }

    static RF_Type::Bool IsReturnIfZero(RF_Collect::ArrayNode<LogicElement>& Node)
    {
        RF_Type::Bool result = false;
        if(Node.Data().What == Logic::ReturnIfZero)
        {
            RF_Collect::ArrayNode<LogicElement>* node = Node.FirstChild();
            while(node != nullptr)
            {
                result = IsValue(*node) || IsCondition(*node) ||
                    IsCallRule(*node) || IsVariable(*node);
                if(result)
                    node = node->Next();
                else
                    break;
            }

            if(node != nullptr)
            {// error

            }
        }
        return result;
    }

    static RF_Type::Bool IsAssign(RF_Collect::ArrayNode<LogicElement>& Node)
    {
        RF_Type::Bool result = false;
        if(Node.Data().What == Logic::Assign && Node.Childs() == 1 &&
           Node.Child(0)->Data().What == Logic::Value)
        {            
            result = true;
        }
        return result;
    }

    static RF_Type::Bool IsRule(RF_Collect::ArrayNode<LogicElement>& Node)
    {
        RF_Type::Bool result = false;
        RF_Type::Bool containsReturn = false;
        if(Node.Data().What == Logic::Rule)
        {    
            RF_Collect::ArrayNode<LogicElement>* node = Node.FirstChild();            
            while(node != nullptr)
            {
                if (containsReturn == false)
                    containsReturn = IsReturnIfZero(*node);

                result = IsRepeat(*node) || IsReturnIfZero(*node) || IsAssign(*node);
                if (result)
                    node = node->Next();
                else
                    break;
            }

            if(node != nullptr)
            {// error

            }
        }
        return result && containsReturn;
    }

    static void GenerateRuleByteCode(RF_Collect::ArrayNode<LogicElement>& Node)
    {

    }
};

GrammarExpression& Grammar::Add(RF_Type::UInt16 Id)
{
    m_Expressions.Resize(m_Expressions.Count() + 1);
    m_Expressions(m_Expressions.Count() - 1).Id = Id;
    return m_Expressions(m_Expressions.Count() - 1);
}

RF_Mem::AutoPointerArray<RF_Type::UInt8> Grammar::GetByteCode()
{
    return m_ByteCode.Clone();
}

const RF_Mem::AutoPointerArray<RF_Type::UInt8>& Grammar::GetByteCode()const
{
    return m_ByteCode;
}

void Grammar::Compile()
{
    // finalize grammar tree
    auto& root = m_LogicTree.GetRootElement();
    RF_Collect::ArrayNode<LogicElement>* node = nullptr;
    for(RF_Type::Size i = 0; i < m_Expressions.Count(); ++i)
    {
        node = root.AddChild({Logic::Rule, m_Expressions(i).Id});
        node->MoveFrom(m_Expressions(i).Logic.GetRootElement(), 0, m_Expressions(i).Logic.GetRootElement().Childs() - 1);
    }

    // Syntax check
    node = m_LogicTree.GetRootElement().FirstChild();
    while(node)
    {
        if(Interpreter::IsRule(*node))
        {
            node = node->Next();
        }
        else
        {
            // raise syntax error

            break;
        }
    }

    if(node == nullptr)
    {
        GenerateByteCode();
    }
}

void Grammar::GenerateByteCode()
{
    m_ByteCode.Release();

    RF_Collect::ArrayNode<LogicElement>* node = nullptr;
    node = m_LogicTree.GetRootElement().FirstChild();
    while(node)
    {
        Interpreter::GenerateRuleByteCode(*node);
        node = node->Next();
    }
}

RF_Type::Size Grammar::GetFunctionSymbol(RF_Type::UInt32)
{
    return 0;
}

void Grammar::Print()
{
    RF_Type::Size depth = 0;
    decltype(m_LogicTree)::NodeType* current = 0;
    current = m_LogicTree.GetRootElement().FirstChild();
    while(current != 0)
    {
        current->Data().Print(depth);

        if(current->Childs() > 0)
        {// go down
            current = current->FirstChild();
            ++depth;
        }
        else
        {// go up
            while(current != 0 && current->Next() == 0)
            {
                current = current->Parent();
                --depth;
            }

            if(current != 0)
            {
                current = current->Next();
            }
        }
    }
    RF_Pattern::Singleton<RF_Thread::ThreadPool>::GetInstance().WaitTillDoneWithInactiveQueue();
}

RF_Type::String Grammar::ToString() const
{
    RF_Type::String result;
    RF_Type::Size depth = 0;
    const decltype(m_LogicTree)::NodeType* current = 0;
    current = m_LogicTree.GetRootElement().FirstChild();
    while(current != 0)
    {
        for (RF_Type::Size i = 0; i < depth; ++i)
        {
            result += " ";
        }
        result += current->Data().ToString() + "\n";

        if(current->Childs() > 0)
        {// go down
            current = current->FirstChild();
            ++depth;
        }
        else
        {// go up
            while(current != 0 && current->Next() == 0)
            {
                current = current->Parent();
                --depth;
            }

            if(current != 0)
            {
                current = current->Next();
            }
        }
    }
    return result;
}

} }