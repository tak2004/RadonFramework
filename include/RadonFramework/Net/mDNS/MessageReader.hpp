#ifndef RF_NET_MDNS_MESSAGEREADER_HPP
#define RF_NET_MDNS_MESSAGEREADER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Net/mDNS/Message.hpp>
#include <RadonFramework/IO/MemoryStream.hpp>
#include <RadonFramework/Net/NetworkStream.hpp>
#include <RadonFramework/Collections/Array.hpp>

namespace RadonFramework { namespace Net { namespace mDNS {

class Answer
{
public:
    RF_Type::String Name;
    RecordType Type;
    RecordClass Class;
    RF_Type::UInt32 TTL;
    RF_Type::Size Index;
};

class Question
{
public:
    RF_Type::String Name;
    RecordType Type;
    RecordClass Class;
};

class ServiceInfo
{
public:
    RF_Type::String Target;
    RF_Type::UInt16 Port;
    RF_Type::UInt16 Weight;
    RF_Type::UInt16 Priority;
};

class MessageReader
{
public:
    MessageReader();
    void Reset(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data);

    RF_Type::Bool ReadHeader();
    RF_Type::Bool ReadQuestions();
    RF_Type::Bool ReadAnswers();
    RF_Type::Bool ReadAdditionals();

    const Header& GetHeader()const;
    const RF_Collect::Array<Answer>& Answers()const;
    const RF_Collect::Array<Answer>& Additionals()const;
    const RF_Collect::Array<Question>& Questions()const;
    const RF_Collect::Array<RF_Type::String>& Domainnames()const;
    const RF_Collect::Array<RF_Type::String>& TextEntries()const;
    const RF_Collect::Array<ServiceInfo>& ServiceInfos()const;
    const RF_Collect::Array<RF_Type::UInt32>& IP4()const;
    RF_Type::Bool IsResponse()const;
protected:
    RF_Net::NetworkStream<RF_IO::MemoryStream> m_Data;
    Header m_Header;
    RF_Collect::Array<Answer> m_Answers;
    RF_Collect::Array<Answer> m_Additionals;
    RF_Collect::Array<Question> m_Questions;
    RF_Collect::Array<RF_Type::String> m_Domainname;
    RF_Collect::Array<RF_Type::String> m_Text;
    RF_Collect::Array<ServiceInfo> m_ServiceInfo;
    RF_Collect::Array<RF_Type::UInt32> m_Address;

    RF_Type::String ReadName();
    RF_Type::String ReadText();
};

} } }

#ifndef RF_SHORTHAND_NAMESPACE_MDNS
#define RF_SHORTHAND_NAMESPACE_MDNS
namespace RF_mDNS = RadonFramework::Net::mDNS;
#endif

#endif // RF_NET_MDNS_MESSAGEREADER_HPP