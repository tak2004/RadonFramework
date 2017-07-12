#ifndef RF_COLLECTIONS_LINKEDENUMERATOR_HPP
#define RF_COLLECTIONS_LINKEDENUMERATOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <RadonFramework/Collections/IEnumerator.hpp>

namespace RadonFramework::Collections {

template <typename T, typename N>
class LinkedEnumerator:public IEnumerator<T>
{
public:
    LinkedEnumerator(N* Start, N* End)
    :m_Current(0)
    ,m_Start(Start)
    ,m_End(End)
    ,m_Previous(0)
    {                    
    }

    T* Current()const
    {
        return &m_Current->m_Value;
    }

    RF_Type::Bool MoveNext()
    {
        if (m_Current==0 && m_Previous==0)
        {
            m_Current=m_Start;
            return true;
        }
        if (m_Current!=m_End)
        {
            m_Previous=m_Current;
            m_Current=m_Current->m_Next;
            return true;
        }
        else
        {
            m_Current=0;
            return false;
        }
        return false;
    }

    void Reset()
    {
        m_Current=0;
        m_Previous=0;
    }
protected:
    N* m_Start;
    N* m_End;
    N* m_Previous;
    N* m_Current;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_COLLECT
#define RF_SHORTHAND_NAMESPACE_COLLECT
namespace RF_Collect = RadonFramework::Collections;
#endif

#endif // RF_COLLECTIONS_LINKEDENUMERATOR_HPP