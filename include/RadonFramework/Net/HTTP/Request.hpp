#ifndef RF_NET_HTTP_REQUEST_HPP
#define RF_NET_HTTP_REQUEST_HPP

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/Pair.hpp>
#include <RadonFramework/Net/HTTP/Field.hpp>
#include <RadonFramework/Net/HTTP/Method.hpp>

namespace RadonFramework { namespace Net { namespace HTTP {

class Request
{
public:    
    typedef RF_Collect::Array<RF_Collect::Pair<Field, RF_Type::String>> FieldList;

    const Method GetMethod()const;
    void SetMethod(Method NewMethod);
    const FieldList& GetFields()const;
    void AddField(const Field Which, const RF_Type::String& Value);
    const RF_Type::String& GetLocation()const;
    void SetLocation(const RF_Type::String& NewLocation);
private:
    Method m_Method;
    FieldList m_Fields;
    RF_Type::String m_Location;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_HTTP
#define RF_SHORTHAND_NAMESPACE_HTTP
namespace RF_HTTP = RadonFramework::Net::HTTP;
#endif

#endif // RF_NET_HTTP_REQUEST_HPP