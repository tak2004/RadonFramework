#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/IPHostEntry.hpp"

using namespace RadonFramework::Net;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;

IPHostEntry::IPHostEntry(const String &Hostname, const List<String> &Aliases,const List<IPAddress> &AddressList)
:m_Hostname(Hostname),
 m_Aliases(Aliases),
 m_AddressList(AddressList)
{
}

const String& IPHostEntry::Hostname()
{
    return m_Hostname;
}

const List<String>& IPHostEntry::Aliases()
{
    return m_Aliases;
}

const List<IPAddress>& IPHostEntry::AddressList()
{
    return m_AddressList;
}
