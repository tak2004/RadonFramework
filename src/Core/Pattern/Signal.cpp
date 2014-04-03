#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Core/Pattern/Signal.hpp>

using namespace RadonFramework;
using namespace RadonFramework::Threading;

Connection0::Connection0(Connection0::DefaultMethod Methode)
:m_Method(Methode)
{
}

Connection0::~Connection0()
{
    Scopelock lock(m_Mutex);
    for ( Collections::List<Signal*>::Iterator it=m_Signals.Begin();
            it!=m_Signals.End(); ++it)
        (*it)->ConnectionRemoved(this);
}

Connection0::DefaultMethod Connection0::Methode()
{
    return m_Method;
}

void Connection0::AddSignal(RadonFramework::Signal* Obj)
{
    Scopelock lock(m_Mutex);
    for ( Collections::List<Signal*>::Iterator it=m_Signals.Begin();
            it!=m_Signals.End(); ++it)
        if ((void*)*it==(void*)Obj)
            return;
    m_Signals.AddLast(Obj);
}

void Connection0::RemoveSignal(RadonFramework::Signal* Obj)
{
    Scopelock lock(m_Mutex);
    UnsafeRemoveSignal(Obj);
}

void Connection0::UnsafeRemoveSignal(Signal* Obj)
{    
    for ( Collections::List<Signal*>::Iterator it=m_Signals.Begin();
            it!=m_Signals.End();)
        if ((void*)*it==(void*)Obj)
        {
            m_Signals.Remove(it);
            return;
        }
}


SignalReceiver::~SignalReceiver()
{
    Scopelock lock(m_Mutex);
    for (Collections::List<Connection0*>::Iterator it=m_Connections.Begin();it!=m_Connections.End(); ++it)
        delete *it;
}