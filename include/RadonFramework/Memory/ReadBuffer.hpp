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
				ReadBuffer(AutoPointerArray<Core::Types::UInt8> Data,
					       const Core::Types::UInt32 MemorySize,
						   const Core::Types::Bool SourceEndianIsLittle=true);

				/** @brief This method read 1 Byte from the Buffer.
				  * This will be performed by a common register copy.
				  */
				Core::Types::Bool ReadBool();
				/** @brief This method read 1 Byte from the Buffer.
				  * This will be performed by a common register copy.
				  */
				Core::Types::UInt8 ReadUInt8();
				/** @brief This method read 1 Byte from the Buffer.
				  * This will be performed by a 8Bit register copy.
				  */
				Core::Types::Int8 ReadInt8();
				/** @brief This method read 1 Byte from the Buffer.
				  * This will be performed by a 8Bit register copy.
				  */
				Core::Types::Char ReadChar();
				/** @brief This method read 2 Bytes from the Buffer.
				  * This will be performed by a 16Bit register copy.
				  */
				Core::Types::UInt16 ReadUInt16();
				/** @brief This method read 2 Bytes from the Buffer.
				  * This will be performed by a 16Bit register copy.
				  */
				Core::Types::Int16 ReadInt16();
				/** @brief This method read 4 Bytes from the Buffer.
				  * This will be performed by a 32bit register copy.
				  */
				Core::Types::UInt32 ReadUInt32();
				/** @brief This method read 4 Bytes from the Buffer.
				  * This will be performed by a 32bit register copy.
				  */
				Core::Types::Int32 ReadInt32();
				/** @brief This method read 4 Bytes from the Buffer.
				  * This will be performed by a 32bit register copy.
				  */
				Core::Types::Float32 ReadFloat32();
				/** @brief This method read 8 Bytes from the Buffer.
				  * This will be performed by two 32Bit register copies on
				  * a 32Bit CPU or one 64Bit register copy on a 64Bit CPU.
				  */
				Core::Types::UInt64 ReadUInt64();
				/** @brief This method read 8 Bytes from the Buffer.
				  * This will be performed by two 32Bit register copies on
				  * a 32Bit CPU or one 64Bit register copy on a 64Bit CPU.
				  */
				Core::Types::Int64 ReadInt64();
				/** @brief This method read 8 Bytes from the Buffer.
				  * This will be performed by two 32Bit register copies on
				  * a 32Bit CPU or one 64Bit register copy on a 64Bit CPU.
				  */
				Core::Types::Float64 ReadFloat64();

				Core::Types::UInt8 AsUInt8()const;
/*
				Core::Types::UInt8* Read4Byte(const Core::Types::UInt32 Quantity);
				Core::Types::UInt8* Read8Byte(const Core::Types::UInt32 Quantity);
				Core::Types::UInt8* Read16Byte(const Core::Types::UInt32 Quantity);
				*/
				AutoPointerArray<Core::Types::UInt8> ReadBytes(const Core::Types::UInt32 Bytes);

				Core::Types::UInt32 Seek(const Core::Types::UInt32 Bytes);
				Core::Types::Bool IsEnd()const;
				Core::Types::UInt32 GetSize()const;
				Core::Types::UInt8 const* GetData()const;
				Core::Types::UInt8 const* GetCursorData()const;
				void ResetCursor();

				ReadBuffer& operator=(ReadBuffer& OldOwner);
				ReadBuffer Clone()const;
				ReadBuffer& AssignTo(ReadBuffer& Destination)const;
			protected:
				AutoPointerArray<Core::Types::UInt8> m_Data;
				Core::Types::UInt32 m_Size;
				Core::Types::UInt32 m_CursorPosition;
				Core::Types::Bool m_IsLittleEndian;
		};
	}
}

#endif
