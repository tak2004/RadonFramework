#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Net/EndPoint.hpp>

using namespace RadonFramework::Net;
using namespace RadonFramework::Core::Types;

EndPoint::EndPoint(const IPAddress &Addr, RF_Type::UInt16 Port)
:m_IP(Addr)
,m_Port(Port)
{
}

RadonFramework::Net::EndPoint::EndPoint()
:m_IP(IPAddress::IPv4Any)
,m_Port(0)
{
}

void RadonFramework::Net::EndPoint::Address( const IPAddress &Value )
{
	m_IP=Value;
}

void RadonFramework::Net::EndPoint::Port(RF_Type::UInt16 Value )
{
	m_Port=Value;
}

bool RadonFramework::Net::EndPoint::operator==( const EndPoint &Other )
{
	return (m_Port==Other.m_Port) && (m_IP==Other.m_IP);
}

const String EndPoint::ToString()const
{
	return String::Format("%s:%uh", m_IP.ToString().c_str(), m_Port);
}

const IPAddress& EndPoint::Address()const
{
	return m_IP;
}

RF_Type::UInt16 EndPoint::Port()const
{
	return m_Port;
}
