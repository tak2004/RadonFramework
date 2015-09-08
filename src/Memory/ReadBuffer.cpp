#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Memory/ReadBuffer.hpp>
#include <string.h>

using namespace RadonFramework::Memory;
using namespace RadonFramework;

RF_Mem::ReadBuffer::ReadBuffer()
: m_Size(0),
 m_CursorPosition(0),
 m_IsLittleEndian(true)
{
}

RF_Mem::ReadBuffer::ReadBuffer(RF_Mem::ReadBuffer& Other)
{
    m_Data=Other.m_Data;
	m_Size=Other.m_Size;
	m_CursorPosition=Other.m_CursorPosition;
	m_IsLittleEndian=Other.m_IsLittleEndian;
	Other.m_Size=0;
	Other.m_CursorPosition=0;
	Other.m_IsLittleEndian=true;
}

RF_Mem::ReadBuffer::ReadBuffer( AutoPointerArray<Core::Types::UInt8> Data,
	const Core::Types::UInt32 MemorySize,
	const Core::Types::Bool SourceEndianIsLittle)
	:m_Data(Data),
	m_Size(MemorySize),
	m_CursorPosition(0),
	m_IsLittleEndian(SourceEndianIsLittle)
{
}

ReadBuffer& RF_Mem::ReadBuffer::operator=( ReadBuffer& OldOwner )
{
	m_Data=OldOwner.m_Data;
	m_Size=OldOwner.m_Size;
	m_CursorPosition=OldOwner.m_CursorPosition;
	m_IsLittleEndian=OldOwner.m_IsLittleEndian;
	OldOwner.m_Size=0;
	OldOwner.m_CursorPosition=0;
	OldOwner.m_IsLittleEndian=true;
	return *this;
}

RF_Mem::ReadBuffer RF_Mem::ReadBuffer::Clone() const
{
	AutoPointerArray<Core::Types::UInt8> data(m_Size);
	RF_SysMem::Copy(data.Get(),m_Data.Get(),m_Size);
	ReadBuffer buf(data,m_Size,m_IsLittleEndian);
	buf.m_CursorPosition=m_CursorPosition;
	return buf;
}

RF_Mem::ReadBuffer& RF_Mem::ReadBuffer::AssignTo(RF_Mem::ReadBuffer& Destination)const
{
	Destination=(RF_Mem::ReadBuffer&)*this;
	return (RF_Mem::ReadBuffer&)*this;
}

Core::Types::UInt32 RF_Mem::ReadBuffer::GetSize() const
{
	return m_Size;
}

Core::Types::UInt8 const* RF_Mem::ReadBuffer::GetData() const
{
	return m_Data.Get();
}

Core::Types::Bool RF_Mem::ReadBuffer::ReadBool()
{
	Core::Types::Bool ret=*(Core::Types::Bool*)(m_Data.Get()+m_CursorPosition);
	++m_CursorPosition;
	return ret;
}

Core::Types::UInt8 RF_Mem::ReadBuffer::ReadUInt8()
{
	Core::Types::UInt8 ret=*(Core::Types::UInt8*)(m_Data.Get()+m_CursorPosition);
	++m_CursorPosition;
	return ret;
}

Core::Types::Int8 RF_Mem::ReadBuffer::ReadInt8()
{
	Core::Types::Int8 ret=*(Core::Types::Int8*)(m_Data.Get()+m_CursorPosition);
	++m_CursorPosition;
	return ret;
}

Core::Types::Char RF_Mem::ReadBuffer::ReadChar()
{
	Core::Types::Char ret=*(Core::Types::Char*)(m_Data.Get()+m_CursorPosition);
	++m_CursorPosition;
	return ret;
}

Core::Types::UInt16 RF_Mem::ReadBuffer::ReadUInt16()
{
	Core::Types::UInt16 ret=*(Core::Types::UInt16*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=2;
	return ret;
}

Core::Types::Int16 RF_Mem::ReadBuffer::ReadInt16()
{
	Core::Types::Int16 ret=*(Core::Types::Int16*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=2;
	return ret;
}

Core::Types::UInt32 RF_Mem::ReadBuffer::ReadUInt32()
{
	Core::Types::UInt32 ret=*(Core::Types::UInt32*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=4;
	return ret;
}

Core::Types::Int32 RF_Mem::ReadBuffer::ReadInt32()
{
	Core::Types::Int32 ret=*(Core::Types::Int32*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=4;
	return ret;
}

Core::Types::Float32 RF_Mem::ReadBuffer::ReadFloat32()
{
	Core::Types::Float32 ret=*(Core::Types::Float32*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=4;
	return ret;
}

Core::Types::UInt64 RF_Mem::ReadBuffer::ReadUInt64()
{
	Core::Types::UInt64 ret=*(Core::Types::UInt64*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=8;
	return ret;
}

Core::Types::Int64 RF_Mem::ReadBuffer::ReadInt64()
{
	Core::Types::Int64 ret=*(Core::Types::Int64*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=8;
	return ret;
}

Core::Types::Float64 RF_Mem::ReadBuffer::ReadFloat64()
{
	Core::Types::Float64 ret=*(Core::Types::Float64*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=8;
	return ret;
}

Core::Types::UInt8 RF_Mem::ReadBuffer::AsUInt8() const
{
	return *(Core::Types::UInt8*)(m_Data.Get()+m_CursorPosition);
}

Core::Types::Bool RF_Mem::ReadBuffer::IsEnd() const
{
	return m_CursorPosition==m_Size;
}

Core::Types::UInt32 RF_Mem::ReadBuffer::Seek( const Core::Types::UInt32 Bytes )
{
	Core::Types::UInt32 diff=(m_Size-m_CursorPosition)>Bytes?Bytes:m_Size-m_CursorPosition;
	m_CursorPosition+=diff;
	return diff;
}

Core::Types::UInt8 const* RF_Mem::ReadBuffer::GetCursorData() const
{
	return (Core::Types::UInt8*)(m_Data.Get()+m_CursorPosition);
}

AutoPointerArray<Core::Types::UInt8> RF_Mem::ReadBuffer::ReadBytes( const Core::Types::UInt32 Bytes )
{
	Core::Types::UInt32 diff=(m_Size-m_CursorPosition)>Bytes?Bytes:m_Size-m_CursorPosition;
	AutoPointerArray<Core::Types::UInt8> data(diff);
	RF_SysMem::Copy(data.Get(),GetCursorData(),diff);
	m_CursorPosition+=diff;
	return data;
}

void RF_Mem::ReadBuffer::ResetCursor()
{
	m_CursorPosition=0;
}
