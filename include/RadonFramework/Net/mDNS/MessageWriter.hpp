#ifndef RF_NET_MDNS_MESSAGEWRITER_HPP
#define RF_NET_MDNS_MESSAGEWRITER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/IO/MemoryStream.hpp>
#include <RadonFramework/Net/NetworkStream.hpp>
#include <RadonFramework/Net/mDNS/Message.hpp>

namespace RadonFramework { namespace Net { namespace mDNS {

class MessageWriter
{
public:
    MessageWriter();
    void Reset();

    void Finalize();

    void WriteQueryHeader(RF_Type::UInt16 TransactionId);

    void WriteQuestion(const RF_Type::String& Name, RecordType Type,
        RecordClass Class = RecordClass::Internet);

    RF_Type::Size DataSize()const;

    const RF_Type::UInt8* Data()const;
protected:
    RF_Net::NetworkStream<RF_IO::MemoryStream> m_Data;
    Header m_Header;
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_MDNS
#define RF_SHORTHAND_NAMESPACE_MDNS
namespace RF_mDNS = RadonFramework::Net::mDNS;
#endif

#endif // RF_NET_MDNS_MESSAGEWRITER_HPP