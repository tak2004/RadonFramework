#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/IPHostEntry.hpp"

using namespace RadonFramework::Net;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;

IPHostEntry::IPHostEntry(const String &Hostname, const List<String> &Aliases,
    const List<IPAddress> &AddressList)
:m_Hostname(Hostname)
,m_Aliases(Aliases)
,m_AddressList(AddressList)
{
}

IPHostEntry::IPHostEntry(const RF_Type::String &Hostname)
:m_Hostname(Hostname)
{

}

const String& IPHostEntry::Hostname()const
{
    return m_Hostname;
}

const List<String>& IPHostEntry::Aliases()const
{
    return m_Aliases;
}

const List<IPAddress>& IPHostEntry::AddressList()const
{
    return m_AddressList;
}

void IPHostEntry::AddAddress(const IPAddress& Address)
{
    m_AddressList.AddLast(Address);
}
