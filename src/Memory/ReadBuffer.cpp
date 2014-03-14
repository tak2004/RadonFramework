#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Memory/ReadBuffer.hpp>
#include <string.h>

using namespace RadonFramework::Memory;
using namespace RadonFramework;

RadonFramework::Memory::ReadBuffer::ReadBuffer()
: m_Size(0),
 m_CursorPosition(0),
 m_IsLittleEndian(true)
{
}

RadonFramework::Memory::ReadBuffer::ReadBuffer(RadonFramework::Memory::ReadBuffer& Other)
{
    m_Data=Other.m_Data;
	m_Size=Other.m_Size;
	m_CursorPosition=Other.m_CursorPosition;
	m_IsLittleEndian=Other.m_IsLittleEndian;
	Other.m_Size=0;
	Other.m_CursorPosition=0;
	Other.m_IsLittleEndian=true;
}

RadonFramework::Memory::ReadBuffer::ReadBuffer( AutoPointerArray<Core::Types::UInt8> Data,
	const Core::Types::UInt32 MemorySize,
	const Core::Types::Bool SourceEndianIsLittle)
	:m_Data(Data),
	m_Size(MemorySize),
	m_CursorPosition(0),
	m_IsLittleEndian(SourceEndianIsLittle)
{
}

ReadBuffer& RadonFramework::Memory::ReadBuffer::operator=( ReadBuffer& OldOwner )
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

RadonFramework::Memory::ReadBuffer RadonFramework::Memory::ReadBuffer::Clone() const
{
	AutoPointerArray<Core::Types::UInt8> data(new Core::Types::UInt8[m_Size],m_Size);
	RFMEM::Copy(data.Get(),m_Data.Get(),m_Size);
	ReadBuffer buf(data,m_Size,m_IsLittleEndian);
	buf.m_CursorPosition=m_CursorPosition;
	return buf;
}

RadonFramework::Memory::ReadBuffer& RadonFramework::Memory::ReadBuffer::AssignTo(RadonFramework::Memory::ReadBuffer& Destination)const
{
	Destination=(RadonFramework::Memory::ReadBuffer&)*this;
	return (RadonFramework::Memory::ReadBuffer&)*this;
}

Core::Types::UInt32 RadonFramework::Memory::ReadBuffer::GetSize() const
{
	return m_Size;
}

Core::Types::UInt8 const* RadonFramework::Memory::ReadBuffer::GetData() const
{
	return m_Data.Get();
}

Core::Types::Bool RadonFramework::Memory::ReadBuffer::ReadBool()
{
	Core::Types::Bool ret=*(Core::Types::Bool*)(m_Data.Get()+m_CursorPosition);
	++m_CursorPosition;
	return ret;
}

Core::Types::UInt8 RadonFramework::Memory::ReadBuffer::ReadUInt8()
{
	Core::Types::UInt8 ret=*(Core::Types::UInt8*)(m_Data.Get()+m_CursorPosition);
	++m_CursorPosition;
	return ret;
}

Core::Types::Int8 RadonFramework::Memory::ReadBuffer::ReadInt8()
{
	Core::Types::Int8 ret=*(Core::Types::Int8*)(m_Data.Get()+m_CursorPosition);
	++m_CursorPosition;
	return ret;
}

Core::Types::Char RadonFramework::Memory::ReadBuffer::ReadChar()
{
	Core::Types::Char ret=*(Core::Types::Char*)(m_Data.Get()+m_CursorPosition);
	++m_CursorPosition;
	return ret;
}

Core::Types::UInt16 RadonFramework::Memory::ReadBuffer::ReadUInt16()
{
	Core::Types::UInt16 ret=*(Core::Types::UInt16*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=2;
	return ret;
}

Core::Types::Int16 RadonFramework::Memory::ReadBuffer::ReadInt16()
{
	Core::Types::Int16 ret=*(Core::Types::Int16*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=2;
	return ret;
}

Core::Types::UInt32 RadonFramework::Memory::ReadBuffer::ReadUInt32()
{
	Core::Types::UInt32 ret=*(Core::Types::UInt32*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=4;
	return ret;
}

Core::Types::Int32 RadonFramework::Memory::ReadBuffer::ReadInt32()
{
	Core::Types::Int32 ret=*(Core::Types::Int32*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=4;
	return ret;
}

Core::Types::Float32 RadonFramework::Memory::ReadBuffer::ReadFloat32()
{
	Core::Types::Float32 ret=*(Core::Types::Float32*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=4;
	return ret;
}

Core::Types::UInt64 RadonFramework::Memory::ReadBuffer::ReadUInt64()
{
	Core::Types::UInt64 ret=*(Core::Types::UInt64*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=8;
	return ret;
}

Core::Types::Int64 RadonFramework::Memory::ReadBuffer::ReadInt64()
{
	Core::Types::Int64 ret=*(Core::Types::Int64*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=8;
	return ret;
}

Core::Types::Float64 RadonFramework::Memory::ReadBuffer::ReadFloat64()
{
	Core::Types::Float64 ret=*(Core::Types::Float64*)(m_Data.Get()+m_CursorPosition);
	m_CursorPosition+=8;
	return ret;
}

Core::Types::UInt8 RadonFramework::Memory::ReadBuffer::AsUInt8() const
{
	return *(Core::Types::UInt8*)(m_Data.Get()+m_CursorPosition);
}

Core::Types::Bool RadonFramework::Memory::ReadBuffer::IsEnd() const
{
	return m_CursorPosition==m_Size;
}

Core::Types::UInt32 RadonFramework::Memory::ReadBuffer::Seek( const Core::Types::UInt32 Bytes )
{
	Core::Types::UInt32 diff=(m_Size-m_CursorPosition)>Bytes?Bytes:m_Size-m_CursorPosition;
	m_CursorPosition+=diff;
	return diff;
}

Core::Types::UInt8 const* RadonFramework::Memory::ReadBuffer::GetCursorData() const
{
	return (Core::Types::UInt8*)(m_Data.Get()+m_CursorPosition);
}

AutoPointerArray<Core::Types::UInt8> RadonFramework::Memory::ReadBuffer::ReadBytes( const Core::Types::UInt32 Bytes )
{
	Core::Types::UInt32 diff=(m_Size-m_CursorPosition)>Bytes?Bytes:m_Size-m_CursorPosition;
	AutoPointerArray<Core::Types::UInt8> data(new Core::Types::UInt8[diff],diff);
	RFMEM::Copy(data.Get(),GetCursorData(),diff);
	m_CursorPosition+=diff;
	return data;
}

void RadonFramework::Memory::ReadBuffer::ResetCursor()
{
	m_CursorPosition=0;
}
