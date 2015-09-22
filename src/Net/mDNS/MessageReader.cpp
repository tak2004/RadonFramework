#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/mDNS/MessageReader.hpp"

namespace RadonFramework { namespace Net { namespace mDNS {

static const RF_Type::Size MAXMULTICASTDNSPACKETSIZE = 9000;

MessageReader::MessageReader()
:m_Header({0})
{

}

void MessageReader::Reset(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data)
{
    m_Data.Replace(Data);
    RF_SysMem::Set(&m_Header, 0, sizeof(m_Header));
}

void MessageReader::ReadHeader()
{
    m_Data.ReadType(m_Header.TransactionID);
    m_Data.ReadType(m_Header.Flags);
    m_Data.ReadType(m_Header.QuestionCount);
    m_Data.ReadType(m_Header.AnswerCount);
    m_Data.ReadType(m_Header.AuthorityCount);
    m_Data.ReadType(m_Header.AdditionalCount);
}

void MessageReader::ReadAnswers()
{
    m_Answers.Resize(m_Header.AnswerCount);
    for(RF_Type::UInt16 i = 0; i < m_Header.AnswerCount; ++i)
    {
        m_Answers(i).Name = ReadName();
        m_Data.ReadType(m_Answers(i).Type);
        m_Data.ReadType(m_Answers(i).Class);
        m_Data.ReadType(m_Answers(i).TTL);
        RF_Type::UInt16 dataLength;
        m_Data.ReadType(dataLength);

        switch(m_Answers(i).Type)
        {
        case RecordType::A:
            m_Address.Resize(m_Address.Count() + 1);
            m_Data.ReadType(m_Address(m_Address.Count() - 1));
            m_Answers(i).Index = m_Address.Count() - 1;
            break;
        case RecordType::SRV:
        {
            m_ServiceInfo.Resize(m_ServiceInfo.Count() + 1);
            auto& svc = m_ServiceInfo(m_ServiceInfo.Count() - 1);
            m_Data.ReadType(svc.Priority);
            m_Data.ReadType(svc.Weight);
            m_Data.ReadType(svc.Port);
            svc.Target = ReadName();
            m_Answers(i).Index = m_ServiceInfo.Count() - 1;
            break;
        }
        case RecordType::PTR:
            m_Domainname.Resize(m_Domainname.Count() + 1);
            m_Domainname(m_Domainname.Count() - 1) = ReadName();
            m_Answers(i).Index = m_Domainname.Count() - 1;
            break;
        case RecordType::TXT:
            m_Text.Resize(m_Text.Count() + 1);
            m_Text(m_Text.Count() - 1) = ReadText();
            m_Answers(i).Index = m_Text.Count() - 1;
            break;
        default:
            m_Data.Seek(dataLength, RF_IO::SeekOrigin::Current);
            m_Answers(i).Index = ~0;
            break;
        }        
    }
}

const Header& MessageReader::GetHeader() const
{
    return m_Header;
}

const RF_Collect::Array<Answer>& MessageReader::Answers() const
{
    return m_Answers;
}

const RF_Collect::Array<RF_Type::String>& MessageReader::Domainnames() const
{
    return m_Domainname;
}

const RF_Collect::Array<RF_Type::String>& MessageReader::TextEntries() const
{
    return m_Text;
}

const RF_Collect::Array<ServiceInfo>& MessageReader::ServiceInfos() const
{
    return m_ServiceInfo;
}

const RF_Collect::Array<RF_Type::UInt32>& MessageReader::IP4() const
{
    return m_Address;
}

RF_Type::String MessageReader::ReadName()
{
    RF_Type::String result;
    RF_Type::UInt8 byte;
    m_Data.PeekType(byte);
    if(byte >= 192)
    {// is pointer
        RF_Type::UInt16 ptr;
        m_Data.ReadType(ptr);
        ptr -= 49152;
        RF_Type::UInt64 currentPosition = m_Data.Position();
        m_Data.Seek(ptr, RF_IO::SeekOrigin::Begin);
        result = ReadName();
        m_Data.Seek(currentPosition, RF_IO::SeekOrigin::Begin);
    }
    else
    {// compressed name
        RF_Type::UInt8 buffer[256];
        RF_Type::UInt64 offset = 0;
        m_Data.ReadType(byte);
        while(byte > 0 && byte < 192)
        {
            m_Data.Read(buffer, offset, byte);
            offset += byte;
            m_Data.ReadType(byte);
            buffer[offset] = '.';
            ++offset;
        }

        buffer[offset - 1] = 0;
        result = RF_Type::String(reinterpret_cast<char*>(buffer), offset + 1);

        if(byte >= 192)
        {            
            m_Data.Seek(-1, RF_IO::SeekOrigin::Current);
            result = result + "." + ReadName();
        }
    }
    return result;
}

RF_Type::String MessageReader::ReadText()
{
    RF_Type::UInt8 buffer[256];
    RF_Type::UInt8 byte;
    m_Data.ReadType(byte);
    m_Data.Read(buffer, 0, byte);
    buffer[byte] = 0;
    RF_Type::String result(reinterpret_cast<char*>(buffer), byte+1);
    return result;
}

} } }