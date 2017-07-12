#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/mDNS/MessageWriter.hpp"

namespace RadonFramework::Net::mDNS {

static const RF_Type::Size MAXMULTICASTDNSPACKETSIZE = 9000;

MessageWriter::MessageWriter()
	:m_Header({ 0 })
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

void MessageWriter::WriteQueryHeader(RF_Type::UInt16 TransactionId,
	RF_Type::UInt16 Flags /*= 0*/)
{
	m_Data.WriteType(TransactionId);
	m_Data.WriteType(Flags);
	m_Data.WriteType(m_Header.QuestionCount);
	m_Data.WriteType(m_Header.AnswerCount);
	m_Data.WriteType(m_Header.AuthorityCount);
	m_Data.WriteType(m_Header.AdditionalCount);
}

void MessageWriter::WriteQuestion(const RF_Type::String& Name, RecordType Type,
	RecordClass Class /*= RecordClass::Internet*/)
{
	auto names = Name.Split("."_rfs);
	for (RF_Type::Size i = 0; i < names.Count(); ++i)
	{
		m_Data.WriteType<RF_Type::UInt8>(names[i].Length());
		m_Data.Write(reinterpret_cast<const RF_Type::UInt8*>(names[i].c_str()), 0, names[i].Length());
	}
	m_Data.WriteType<RF_Type::UInt8>(0);
	m_Data.WriteType(static_cast<RF_Type::UInt16>(Type));
	m_Data.WriteType(static_cast<RF_Type::UInt16>(Class));
	++m_Header.QuestionCount;
}

void MessageWriter::WriteAnswerServerSelection(const RF_Type::String& Name,
	const RF_Type::String& Target, RF_Type::UInt16 Port,
	RecordClass Class /*= RecordClass::Internet*/, RF_Type::Bool Flush /*= false*/)
{
	auto targets = Target.Split("."_rfs);
	auto names = Name.Split("."_rfs);
	for (RF_Type::Size i = 0; i < names.Count(); ++i)
	{
		m_Data.WriteType<RF_Type::UInt8>(names[i].Length());
		m_Data.Write(reinterpret_cast<const RF_Type::UInt8*>(names[i].c_str()), 0, names[i].Length());
	}
	m_Data.WriteType<RF_Type::UInt8>(0);

	RecordType type = RecordType::SRV;
	m_Data.WriteType(type);
	RF_Type::UInt16 classAndFlag = static_cast<RF_Type::UInt16>(Class);
	if (Flush)
	{
		classAndFlag |= 1 << 15;
	}
	m_Data.WriteType(classAndFlag);

	RF_Type::UInt32 ttl = 0;
	m_Data.WriteType(ttl);

	RF_Type::UInt16 payload = sizeof(RF_Type::UInt16) * 3 + targets.Count() + 1;
	for (RF_Type::Size i = 0; i < targets.Count(); ++i)
	{
		payload += targets[i].Length();
	}
	m_Data.WriteType(payload);

	RF_Type::UInt16 priority = 0;
	m_Data.WriteType(priority);

	RF_Type::UInt16 weight = 0;
	m_Data.WriteType(weight);
	m_Data.WriteType(Port);

	for (RF_Type::Size i = 0; i < targets.Count(); ++i)
	{
		m_Data.WriteType<RF_Type::UInt8>(targets[i].Length());
		m_Data.Write(reinterpret_cast<const RF_Type::UInt8*>(targets[i].c_str()), 0, targets[i].Length());
	}
	m_Data.WriteType<RF_Type::UInt8>(0);
	++m_Header.AnswerCount;
}

RF_Type::Size MessageWriter::DataSize() const
{
	return m_Data.GetAbsolutePosition();
}

const RF_Type::UInt8* MessageWriter::Data() const
{
	return m_Data.GetRawBuffer();
}

void MessageWriter::WriteAdditionalAnswer(const RF_Type::String& Name,
	const RF_Net::IPAddress& IP, RecordClass Class /*= RecordClass::Internet*/,
	RF_Type::Bool Flush /*= false*/)
{
	RecordType type = RecordType::A;
	switch (IP.GetAddressFamily())
	{
	case AddressFamily::InterNetwork6: type = RecordType::A6; break;
	case AddressFamily::InterNetwork: type = RecordType::A; break;
	default:
		return;
	}

	auto names = Name.Split("."_rfs);
	for (RF_Type::Size i = 0; i < names.Count(); ++i)
	{
		m_Data.WriteType<RF_Type::UInt8>(names[i].Length());
		m_Data.Write(reinterpret_cast<const RF_Type::UInt8*>(names[i].c_str()), 0, names[i].Length());
	}
	m_Data.WriteType<RF_Type::UInt8>(0);

	m_Data.WriteType(static_cast<RF_Type::UInt16>(type));
	RF_Type::UInt16 classAndFlag = static_cast<RF_Type::UInt16>(Class);
	if (Flush)
	{
		classAndFlag |= 1 << 15;
	}
	m_Data.WriteType(classAndFlag);

	RF_Type::UInt32 ttl = 120;
	m_Data.WriteType(ttl);
	m_Data.WriteType(static_cast<RF_Type::UInt16>(IP.GetByteArraySize()));
	m_Data.Write(IP.AsByteArray(), 0, IP.GetByteArraySize());
	++m_Header.AdditionalCount;
}

}