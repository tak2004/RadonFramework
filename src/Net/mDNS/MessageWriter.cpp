#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/mDNS/MessageWriter.hpp"

namespace RadonFramework { namespace Net { namespace mDNS {

static const RF_Type::Size MAXMULTICASTDNSPACKETSIZE = 9000;

MessageWriter::MessageWriter()
:m_Data(MAXMULTICASTDNSPACKETSIZE)
,m_AdditionalCount(0)
,m_AnswerCount(0)
,m_AuthorityCount(0)
,m_QuestionCount(0)
{
}

void MessageWriter::Reset()
{
    m_AdditionalCount = 0;
    m_AnswerCount = 0;
    m_AuthorityCount = 0;
    m_QuestionCount = 0;
    m_Data.Seek(0, RF_IO::SeekOrigin::Begin);
}

void MessageWriter::Finalize()
{
    RF_Type::Size currentPosition = m_Data.Position();
    m_Data.Seek(4, RF_IO::SeekOrigin::Begin);
    m_Data.WriteType(m_QuestionCount);
    m_Data.WriteType(m_AnswerCount);
    m_Data.WriteType(m_AuthorityCount);
    m_Data.WriteType(m_AdditionalCount);
    m_Data.Seek(currentPosition, RF_IO::SeekOrigin::Begin);
}

void MessageWriter::WriteQueryHeader(RF_Type::UInt16 TransactionId)
{
    m_Data.WriteType(TransactionId);
    m_Data.WriteType<RF_Type::UInt16>(0);
    m_Data.WriteType(m_QuestionCount);
    m_Data.WriteType(m_AnswerCount);
    m_Data.WriteType(m_AuthorityCount);
    m_Data.WriteType(m_AdditionalCount);
}

void MessageWriter::WriteQuestion(const RF_Type::String& Name, RecordType Type, 
    RecordClass Class /*= RecordClass::Internet*/)
{
    m_Data.WriteType<RF_Type::UInt8>(Name.Size());
    m_Data.Write(reinterpret_cast<const RF_Type::UInt8*>(Name.c_str()), 0, Name.Size());
    m_Data.WriteType<RF_Type::UInt8>(0);
    m_Data.WriteType(static_cast<RF_Type::UInt16>(Type));
    m_Data.WriteType(static_cast<RF_Type::UInt16>(Class));
    ++m_QuestionCount;
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