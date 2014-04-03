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

namespace RadonFramework
{
	namespace Memory
	{
		class ReadBuffer
		{
			public:
				ReadBuffer();
				ReadBuffer(ReadBuffer& Other);
				ReadBuffer(AutoPointerArray<RFTYPE::UInt8> Data,
					       const RFTYPE::UInt32 MemorySize,
						   const RFTYPE::Bool SourceEndianIsLittle=true);

				/** @brief This method read 1 Byte from the Buffer.
				  * This will be performed by a common register copy.
				  */
				RFTYPE::Bool ReadBool();
				/** @brief This method read 1 Byte from the Buffer.
				  * This will be performed by a common register copy.
				  */
				RFTYPE::UInt8 ReadUInt8();
				/** @brief This method read 1 Byte from the Buffer.
				  * This will be performed by a 8Bit register copy.
				  */
				RFTYPE::Int8 ReadInt8();
				/** @brief This method read 1 Byte from the Buffer.
				  * This will be performed by a 8Bit register copy.
				  */
				RFTYPE::Char ReadChar();
				/** @brief This method read 2 Bytes from the Buffer.
				  * This will be performed by a 16Bit register copy.
				  */
				RFTYPE::UInt16 ReadUInt16();
				/** @brief This method read 2 Bytes from the Buffer.
				  * This will be performed by a 16Bit register copy.
				  */
				RFTYPE::Int16 ReadInt16();
				/** @brief This method read 4 Bytes from the Buffer.
				  * This will be performed by a 32bit register copy.
				  */
				RFTYPE::UInt32 ReadUInt32();
				/** @brief This method read 4 Bytes from the Buffer.
				  * This will be performed by a 32bit register copy.
				  */
				RFTYPE::Int32 ReadInt32();
				/** @brief This method read 4 Bytes from the Buffer.
				  * This will be performed by a 32bit register copy.
				  */
				RFTYPE::Float32 ReadFloat32();
				/** @brief This method read 8 Bytes from the Buffer.
				  * This will be performed by two 32Bit register copies on
				  * a 32Bit CPU or one 64Bit register copy on a 64Bit CPU.
				  */
				RFTYPE::UInt64 ReadUInt64();
				/** @brief This method read 8 Bytes from the Buffer.
				  * This will be performed by two 32Bit register copies on
				  * a 32Bit CPU or one 64Bit register copy on a 64Bit CPU.
				  */
				RFTYPE::Int64 ReadInt64();
				/** @brief This method read 8 Bytes from the Buffer.
				  * This will be performed by two 32Bit register copies on
				  * a 32Bit CPU or one 64Bit register copy on a 64Bit CPU.
				  */
				RFTYPE::Float64 ReadFloat64();

				RFTYPE::UInt8 AsUInt8()const;
/*
				RFTYPE::UInt8* Read4Byte(const RFTYPE::UInt32 Quantity);
				RFTYPE::UInt8* Read8Byte(const RFTYPE::UInt32 Quantity);
				RFTYPE::UInt8* Read16Byte(const RFTYPE::UInt32 Quantity);
				*/
				AutoPointerArray<RFTYPE::UInt8> ReadBytes(const RFTYPE::UInt32 Bytes);

				RFTYPE::UInt32 Seek(const RFTYPE::UInt32 Bytes);
				RFTYPE::Bool IsEnd()const;
				RFTYPE::UInt32 GetSize()const;
				RFTYPE::UInt8 const* GetData()const;
				RFTYPE::UInt8 const* GetCursorData()const;
				void ResetCursor();

				ReadBuffer& operator=(ReadBuffer& OldOwner);
				ReadBuffer Clone()const;
				ReadBuffer& AssignTo(ReadBuffer& Destination)const;
			protected:
				AutoPointerArray<RFTYPE::UInt8> m_Data;
				RFTYPE::UInt32 m_Size;
				RFTYPE::UInt32 m_CursorPosition;
				RFTYPE::Bool m_IsLittleEndian;
		};
	}
}

#endif
