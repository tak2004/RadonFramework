#ifndef RF_NET_MDNS_MESSAGE_HPP
#define RF_NET_MDNS_MESSAGE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::Net::mDNS {

enum class RecordType: RF_Type::UInt16
{
    A = 1,
    NS = 2,
    CNAME = 5,
    SOA = 6,
    WKS = 11,
    PTR = 12,
    MX = 15,
    TXT = 16,
    SRV = 33,
    A6 = 38,
    ANY = 255
};

enum class RecordClass: RF_Type::UInt16
{
    Internet = 1
};

struct Header
{
    RF_Type::UInt16 TransactionID;
    RF_Type::UInt16 Flags;
    RF_Type::UInt16 QuestionCount;
    RF_Type::UInt16 AnswerCount;
    RF_Type::UInt16 AuthorityCount;
    RF_Type::UInt16 AdditionalCount;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_MDNS
#define RF_SHORTHAND_NAMESPACE_MDNS
namespace RF_mDNS = RadonFramework::Net::mDNS;
#endif

#endif // RF_NET_MDNS_MESSAGE_HPP