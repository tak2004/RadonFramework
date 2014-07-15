#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Net/PacketStream.hpp"
#include "RadonFramework/IO/MemoryCollectionStream.hpp"
#include "RadonFramework/Threading/ThreadPool.hpp"
#include "RadonFramework/IO/Log.hpp"

using namespace RadonFramework::Net;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::IO;
using namespace RadonFramework::Threading;

class PIMPL
{
    public:
        MemoryCollectionStream MemoryStream;
        UInt32 MaxDataSize;
        PacketStream::SplitFunctionType SplitPacketFunction;
        PacketStream::DispatcherFunctionType PacketDispatcherFunction;
};

void ProcessStreamTask(void* Data)
{
    PIMPL* data=reinterpret_cast<PIMPL*>(Data);
    if (!data->SplitPacketFunction.empty())
        if (data->SplitPacketFunction(data->MemoryStream))
        {
            UInt32 bytes=static_cast<UInt32>(data->MemoryStream.Position())-1;
            data->MemoryStream.Seek(0,SeekOrigin::Begin);
            AutoPointerArray<UInt8> buf(new UInt8[bytes],bytes);
            data->MemoryStream.Read(buf.Get(),0,bytes);
            if (!data->PacketDispatcherFunction(buf))
                LogError("Dispatch packet failed");
        }
}

PacketStream::PacketStream()
{
    m_Data=AutoPointer<PIMPL>(new PIMPL);
    m_Data->MaxDataSize=104857600;// 100MB
}

void PacketStream::Enqueue(AutoPointerArray<UInt8>& packet)
{
    m_Data->MemoryStream.AddLast(packet);
    while (m_Data->MemoryStream.Length()>m_Data->MaxDataSize)
        m_Data->MemoryStream.RemoveFirst();
    RF_Pattern::Singleton<ThreadPool>::GetInstance().QueueUserWorkItem(ProcessStreamTask,m_Data.Get(),TaskStrategy::Concurrent,false);
}

void PacketStream::SetPacketSplitFunction(SplitFunctionType SplitFunction)
{
    m_Data->SplitPacketFunction=SplitFunction;
}

void PacketStream::SetPacketDispatcherFunction(DispatcherFunctionType DispatcherFunction)
{
    m_Data->PacketDispatcherFunction=DispatcherFunction;
}

void PacketStream::MaxDataSize(const UInt32 NewSize)
{
    m_Data->MaxDataSize=NewSize;
}

UInt32 PacketStream::MaxDataSize()const
{
    return m_Data->MaxDataSize;
}