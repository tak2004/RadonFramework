#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/CommandBuffer.hpp"

namespace RadonFramework { namespace Drawing {

RF_Type::Bool CommandBuffer::Finalize()
{
    RF_Type::Bool result = false;
    m_Final = RF_Mem::AutoPointerArray<RF_Type::UInt8>(new RF_Type::UInt8[m_ScratchPad.Position()], m_ScratchPad.Position());
    m_ScratchPad.Seek(0, RF_IO::SeekOrigin::Begin);
    m_ScratchPad.Read(m_Final.Get(), 0, m_Final.Size());
    return result;
}

const RF_Mem::AutoPointerArray<RF_Type::UInt8>& CommandBuffer::Data() const
{
    return m_Final;
}

RF_Mem::AutoPointerArray<RF_Type::UInt8> CommandBuffer::ReleaseData()
{
    RF_Mem::AutoPointerArray<RF_Type::UInt8> result(m_Final);
    return result;
}

CommandBuffer::HandleList& CommandBuffer::ReserveHandleList()
{
    
}

CommandBuffer::DataStream& CommandBuffer::ReserveDataStream()
{

}

}
}