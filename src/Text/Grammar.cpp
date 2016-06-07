#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Text/Grammar.hpp"

namespace RadonFramework { namespace Text {

GrammarExpression& Grammar::Add(RF_Type::UInt16 Id)
{
    m_Expressions.Resize(m_Expressions.Count() + 1);
    m_Expressions(m_Expressions.Count() - 1).Id = Id;
    return m_Expressions(m_Expressions.Count() - 1);
}

RF_Mem::AutoPointerArray<RF_Type::UInt8> Grammar::ByteCode()
{
    return RF_Mem::AutoPointerArray<RF_Type::UInt8>();
}

void Grammar::Compile()
{
    auto& root = m_LogicTree.GetRootElement();
    RF_Collect::ArrayNode<LogicElement>* node = nullptr;
    for(RF_Type::Size i = 0; i < m_Expressions.Count(); ++i)
    {
        node = root.AddChild({Logic::Rule, m_Expressions(i).Id});
        node->MoveFrom(m_Expressions(i).Logic.GetRootElement(), 0, m_Expressions(i).Logic.GetRootElement().Childs() - 1);
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

} }