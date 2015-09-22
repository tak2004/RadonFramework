#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/mDNS/MessageWriter.hpp"

namespace RadonFramework { namespace Net { namespace mDNS {

static const RF_Type::Size MAXMULTICASTDNSPACKETSIZE = 9000;

MessageWriter::MessageWriter()
:m_Header({0})
{
    m_Data.Reserve(MAXMULTICASTDNSPACKETSIZE);
}

void MessageWriter::Reset()
{
    RF_SysMem::Set(&m_Header, 0, sizeof(m_Header));
    m_Data.Seek(0, RF_IO::SeekOrigin::Begin);
}

void MessageWriter::Finalize()
{
    RF_Type::Size currentPosition = m_Data.Position();
    m_Data.Seek(4, RF_IO::SeekOrigin::Begin);
    m_Data.WriteType(m_Header.QuestionCount);
    m_Data.WriteType(m_Header.AnswerCount);
    m_Data.WriteType(m_Header.AuthorityCount);
    m_Data.WriteType(m_Header.AdditionalCount);
    m_Data.Seek(currentPosition, RF_IO::SeekOrigin::Begin);
}

void MessageWriter::WriteQueryHeader(RF_Type::UInt16 TransactionId)
{
    m_Data.WriteType(TransactionId);
    m_Data.WriteType<RF_Type::UInt16>(0);
    m_Data.WriteType(m_Header.QuestionCount);
    m_Data.WriteType(m_Header.AnswerCount);
    m_Data.WriteType(m_Header.AuthorityCount);
    m_Data.WriteType(m_Header.AdditionalCount);
}

void MessageWriter::WriteQuestion(const RF_Type::String& Name, RecordType Type, 
    RecordClass Class /*= RecordClass::Internet*/)
{
    auto names = Name.Split(".");
    for(RF_Type::Size i = 0; i < names.Count(); ++i)
    {
        m_Data.WriteType<RF_Type::UInt8>(names[i].Length());
        m_Data.Write(reinterpret_cast<const RF_Type::UInt8*>(names[i].c_str()), 0, names[i].Length());
    }
    m_Data.WriteType<RF_Type::UInt8>(0);
    m_Data.WriteType(static_cast<RF_Type::UInt16>(Type));
    m_Data.WriteType(static_cast<RF_Type::UInt16>(Class));
    ++m_Header.QuestionCount;
}

RF_Type::Size MessageWriter::DataSize() const
{
    return m_Data.GetAbsolutePosition();
}

const RF_Type::UInt8* MessageWriter::Data() const
{
    return m_Data.GetRawBuffer();
}

} } }