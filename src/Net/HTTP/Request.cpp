#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/HTTP/Request.hpp"

namespace RadonFramework { namespace Net { namespace HTTP {

const RadonFramework::Net::HTTP::Method Request::GetMethod() const
{
    return m_Method;    
}

void Request::SetMethod(Method NewMethod)
{
    m_Method = NewMethod;
}

const RadonFramework::Net::HTTP::Request::FieldList& Request::GetFields() const
{
    return m_Fields;
}

void Request::AddField(const Field Which, const RF_Type::String& Value)
{
    auto lastSize = m_Fields.Count();
    m_Fields.Resize(lastSize + 1);
    m_Fields(lastSize).First = Which;
    m_Fields(lastSize).Second = Value;
}

const RF_Type::String& Request::GetLocation() const
{
    return m_Location;
}

void Request::SetLocation(const RF_Type::String& NewLocation)
{
    m_Location = NewLocation;
}

} } }