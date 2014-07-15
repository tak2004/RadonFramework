#ifndef RF_CORE_PATTERN_SIGNAL_HPP
#define RF_CORE_PATTERN_SIGNAL_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/System/Threading/Mutex.hpp>
#include <RadonFramework/Threading/Scopelock.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework { namespace Core { namespace Pattern {

class SignalReciever;
class Signal;

class Connection0
{
typedef Delegate<> DefaultMethod;
protected:
    DefaultMethod m_Method;
    Collections::List<Signal*> m_Signals;
    System::Threading::Mutex m_Mutex;
public:
    Connection0(DefaultMethod Methode);
    ~Connection0();

    DefaultMethod Methode();
    void operator()()const
    {
        m_Method();
    }            
    void AddSignal(Signal* Obj);
    void RemoveSignal(Signal* Obj);
    void UnsafeRemoveSignal(Signal* Obj);            
};

class SignalReceiver
{
protected:
    Collections::List<Connection0*> m_Connections;
    System::Threading::Mutex m_Mutex;
public:
    template<class T>
    Connection0* Connector(void(T::*Method)())
    {
        Threading::Scopelock lock(m_Mutex);
        Delegate<> delegate(dynamic_cast<T*>(this),Method);
        Connection0* con=new Connection0(delegate);
        m_Connections.AddLast((Connection0*)con);
        return con;
    }
    virtual ~SignalReceiver();
};

class Signal
{
protected:
    Collections::List<Connection0*> m_EventHandler;
    System::Threading::Mutex m_Mutex;
public:
    ~Signal()
    {
        for (Collections::List<Connection0*>::Iterator it=m_EventHandler.Begin();
                it!=m_EventHandler.End();)
        {
            (*it)->UnsafeRemoveSignal(this);
            m_EventHandler.Remove(it);
        }
    }

    void Attach(Connection0* ConnectionHandler)
    {
        Threading::Scopelock lock(m_Mutex);
        m_EventHandler.AddLast(ConnectionHandler);
        ConnectionHandler->AddSignal(this);
    }

    void Detach(Connection0* ConnectionHandler)
    {
        Threading::Scopelock lock(m_Mutex);
        for (Collections::List<Connection0*>::Iterator it=m_EventHandler.Begin();
                it!=m_EventHandler.End();)
            if ((void*)*it==(void*)ConnectionHandler)
            {
                ConnectionHandler->RemoveSignal(this);
                m_EventHandler.Remove(it);
                return;
            }
    }

    void ConnectionRemoved(Connection0* ConnectionHandler)
    {
        Threading::Scopelock lock(m_Mutex);
        for (Collections::List<Connection0*>::Iterator it=m_EventHandler.Begin();
                it!=m_EventHandler.End();)
            if ((void*)*it==(void*)ConnectionHandler)
            {
                m_EventHandler.Remove(it);
                return;
            }
    }

    void Notify()
    {
        Threading::Scopelock lock(m_Mutex);
        for (Collections::List<Connection0*>::Iterator it=m_EventHandler.Begin();
                it!=m_EventHandler.End(); ++it)
            (*(*it))();
    }

    inline void operator()()
    {
        Notify();
    }

    inline Signal& operator+=(Connection0 *Con)
    {
        Attach(Con);
        return *this;
    }

    inline Signal& operator-=(Connection0 *Con)
    {
        Detach(Con);
        return *this;
    }
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_PATTERN
#define RF_SHORTHAND_NAMESPACE_PATTERN
namespace RF_Pattern = RadonFramework::Core::Pattern;
#endif

#endif
