#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Core/Pattern/Event.hpp"

using namespace RadonFramework;

IObserver::~IObserver(){
  for (Collections::List<Connection<>*>::Iterator it=m_Connections.Begin();
    it!=m_Connections.End(); ++it)
    delete *it;
}
