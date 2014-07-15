#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/IO/Log.hpp>
#include <RadonFramework/Reflection/ParameterStack.hpp>

using namespace RadonFramework::Reflection;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::IO;

ParameterStack::ParameterStack()
:m_Cursor(-1)
{
}

ParameterStack::~ParameterStack()
{
    for (UInt32 i=0;i<m_Parameters.size();++i)
    {   // check whether the datasize is bigger than 1 cause compiler optimization
        // would switch from new[] to new on array size 1 and then delete[]
        // wouldn't match and we get some memory leaks
        if ( 1 < m_Parameters[i].Datasize )
        {
            if (m_Parameters[i].Datatype!=TypeKind::RF_STRING)
                delete[] m_Parameters[i].Data;
            else
                delete[] reinterpret_cast<String*>(m_Parameters[i].Data);
        }
        else
        {
            if (m_Parameters[i].Datatype!=TypeKind::RF_STRING)
                delete m_Parameters[i].Data;
            else
                delete reinterpret_cast<String*>(m_Parameters[i].Data);
        }
    }
    m_Parameters.clear();
}

void ParameterStack::Push(const void* Data, const TypeKind::Type Datatype, const UInt32 Count)
{
    if (Datatype!=TypeKind::RF_UNKNOWN && Datatype!=TypeKind::RF_MAX)
    {
        Parameter par;
        par.Datatype=Datatype;
        par.Count=Count;
        if (Datatype==TypeKind::RF_STRING)
        {
            par.Datasize=sizeof(String);
            par.Data=reinterpret_cast<void*>(new String[par.Count]);
            for (UInt32 i=0;i<par.Count;++i)
            {
                String* temp = new String( const_cast<String*>(static_cast<const String*>(Data))[i] );
                reinterpret_cast<String*>(par.Data)[i] = *temp;
            }
        }
        else
        {
            par.Datasize=TypeSize[Datatype];
            par.Data=new char[par.Datasize*par.Count];
            RF_SysMem::Copy(par.Data,Data,par.Datasize*par.Count);
        }

        if ( (m_Cursor+1) < m_Parameters.size() )
        {   // check whether the datasize is bigger than 1 cause compiler optimization
            // would switch from new[] to new on array size 1 and then delete[]
            // wouldn't match and we get some memory leaks
            if ( 1 < m_Parameters[m_Cursor+1].Datasize )
            {
                if (m_Parameters[m_Cursor+1].Datatype!=TypeKind::RF_STRING)
                    delete[] m_Parameters[m_Cursor+1].Data;
                else
                    delete[] reinterpret_cast<String*>(m_Parameters[m_Cursor+1].Data);
            }
            else
            {
                if (m_Parameters[m_Cursor+1].Datatype!=TypeKind::RF_STRING)
                    delete m_Parameters[m_Cursor+1].Data;
                else
                    delete reinterpret_cast<String*>(m_Parameters[m_Cursor+1].Data);
            }
            m_Parameters[m_Cursor+1]=par;
        }
        else
            m_Parameters.push_back(par);
        ++m_Cursor;
    }
    else
        LogError("Invalid Datatype.");
}

void ParameterStack::Push(const void* Data, const UInt32 Datasize, const UInt32 Count)
{
    Parameter par;
    par.Datasize=Datasize;
    par.Count=Count;
    par.Data=new char[par.Datasize*par.Count];
    RF_SysMem::Copy(par.Data,Data,par.Datasize*par.Count);
    par.Datatype=TypeKind::RF_UNKNOWN;

    if (m_Cursor<m_Parameters.size())
    {
        delete[] m_Parameters[m_Cursor].Data;
        m_Parameters[m_Cursor]=par;
    }
    else
        m_Parameters.push_back(par);
    m_Cursor+=par.Count;
}

void ParameterStack::Pop()
{
    m_Cursor--;
}

void ParameterStack::ResetCursor()
{
    m_Cursor=static_cast<Int32>(m_Parameters.size())-1;
}

TypeKind::Type ParameterStack::TopType()
{
    if (m_Cursor > -1)
        return m_Parameters[m_Cursor].Datatype;
    return TypeKind::RF_UNKNOWN;
}

RadonFramework::Core::Types::Bool ParameterStack::IsEmpty()
{
    return m_Parameters.empty();
}

RadonFramework::Core::Types::Bool ParameterStack::IsSameType(const ParameterStack &Stack)
{
    if (m_Parameters[m_Cursor].Datatype==Stack.m_Parameters[Stack.m_Cursor].Datatype)
        return true;

    return false;
}

RadonFramework::Core::Types::UInt32 ParameterStack::Size() const
{
    return static_cast<UInt32>(m_Parameters.size());
}
