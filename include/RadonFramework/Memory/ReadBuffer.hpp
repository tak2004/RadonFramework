#ifndef RF_READBUFFER_HPP
#define RF_READBUFFER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/Int64.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/Int16.hpp>
#include <RadonFramework/Core/Types/Int8.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>
#include <RadonFramework/Core/Types/Float64.hpp>
#include <RadonFramework/Core/Types/Char.hpp>

namespace RadonFramework { namespace Memory {

class ReadBuffer
{
public:
	ReadBuffer();
	ReadBuffer(ReadBuffer& Other);
	ReadBuffer(AutoPointerArray<RF_Type::UInt8> Data,
				const RF_Type::UInt32 MemorySize,
				const RF_Type::Bool SourceEndianIsLittle=true);

	/** @brief This method read 1 Byte from the Buffer.
		* This will be performed by a common register copy.
		*/
	RF_Type::Bool ReadBool();
	/** @brief This method read 1 Byte from the Buffer.
		* This will be performed by a common register copy.
		*/
	RF_Type::UInt8 ReadUInt8();
	/** @brief This method read 1 Byte from the Buffer.
		* This will be performed by a 8Bit register copy.
		*/
	RF_Type::Int8 ReadInt8();
	/** @brief This method read 1 Byte from the Buffer.
		* This will be performed by a 8Bit register copy.
		*/
	RF_Type::Char ReadChar();
	/** @brief This method read 2 Bytes from the Buffer.
		* This will be performed by a 16Bit register copy.
		*/
	RF_Type::UInt16 ReadUInt16();
	/** @brief This method read 2 Bytes from the Buffer.
		* This will be performed by a 16Bit register copy.
		*/
	RF_Type::Int16 ReadInt16();
	/** @brief This method read 4 Bytes from the Buffer.
		* This will be performed by a 32bit register copy.
		*/
	RF_Type::UInt32 ReadUInt32();
	/** @brief This method read 4 Bytes from the Buffer.
		* This will be performed by a 32bit register copy.
		*/
	RF_Type::Int32 ReadInt32();
	/** @brief This method read 4 Bytes from the Buffer.
		* This will be performed by a 32bit register copy.
		*/
	RF_Type::Float32 ReadFloat32();
	/** @brief This method read 8 Bytes from the Buffer.
		* This will be performed by two 32Bit register copies on
		* a 32Bit CPU or one 64Bit register copy on a 64Bit CPU.
		*/
	RF_Type::UInt64 ReadUInt64();
	/** @brief This method read 8 Bytes from the Buffer.
		* This will be performed by two 32Bit register copies on
		* a 32Bit CPU or one 64Bit register copy on a 64Bit CPU.
		*/
	RF_Type::Int64 ReadInt64();
	/** @brief This method read 8 Bytes from the Buffer.
		* This will be performed by two 32Bit register copies on
		* a 32Bit CPU or one 64Bit register copy on a 64Bit CPU.
		*/
	RF_Type::Float64 ReadFloat64();

	RF_Type::UInt8 AsUInt8()const;
/*
	RF_Type::UInt8* Read4Byte(const RF_Type::UInt32 Quantity);
	RF_Type::UInt8* Read8Byte(const RF_Type::UInt32 Quantity);
	RF_Type::UInt8* Read16Byte(const RF_Type::UInt32 Quantity);
	*/
	AutoPointerArray<RF_Type::UInt8> ReadBytes(const RF_Type::UInt32 Bytes);

	RF_Type::UInt32 Seek(const RF_Type::UInt32 Bytes);
	RF_Type::Bool IsEnd()const;
	RF_Type::UInt32 GetSize()const;
	RF_Type::UInt8 const* GetData()const;
	RF_Type::UInt8 const* GetCursorData()const;
	void ResetCursor();

	ReadBuffer& operator=(ReadBuffer& OldOwner);
	ReadBuffer Clone()const;
	ReadBuffer& AssignTo(ReadBuffer& Destination)const;
protected:
	AutoPointerArray<RF_Type::UInt8> m_Data;
	RF_Type::UInt32 m_Size;
	RF_Type::UInt32 m_CursorPosition;
	RF_Type::Bool m_IsLittleEndian;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_MEM
#define RF_SHORTHAND_NAMESPACE_MEM
namespace RF_Mem = RadonFramework::Memory;
#endif

#endif
