#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/NativeShape.hpp"
#include "RadonFramework/Drawing/OpenGLMachine.hpp"
#include "RadonFramework/IO/MemoryCollectionStream.hpp"

using namespace RadonFramework::Drawing;
using namespace RadonFramework::IO;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;

NativeShape::NativeShape()
{
}

NativeShape::NativeShape(const NativeShape& Copy)
{
}

NativeShape& NativeShape::operator=(const NativeShape& Other)
{
    return *this;
}

NativeShape::~NativeShape()
{
}

void NativeShape::AssignByteCode(AutoPointerArray<UInt8>& Data,
                                 const ID StartupID, const ID ShutdownID)
{
    m_Data=Data;
    m_EntryTableSize=reinterpret_cast<UInt16*>(m_Data.Get());
    m_EntryTable=reinterpret_cast<Entry*>(m_EntryTableSize+1);
    m_ByteCodeBlock=m_Data.Get()+2+((*m_EntryTableSize)*sizeof(Entry));
    m_HandleDataList.Resize(*m_EntryTableSize);
    UInt32 offset=0;
    for (UInt16 i=0;i<m_HandleDataList.Count();++i)
    {
        m_HandleDataList(i).First=m_EntryTable+i;
        m_HandleDataList(i).Second=offset;
        offset+=m_EntryTable[i].ByteCodeSize;
    }
}

NativeShape::Handle NativeShape::GetCodeHandle(const ID ByID)
{
    if (ByID!=INVALID_ID)
        for (UInt16 i=0;i<*m_EntryTableSize;++i)
            if (m_EntryTable[i].Identifier==ByID)
                return i;
    return INVALID_HANDLE;
}

void NativeShape::Execute(const NativeShape::Handle AHandle)
{
    Collections::Pair<Entry*,Core::Types::UInt32>& h=m_HandleDataList(AHandle);
    UInt8* p=m_ByteCodeBlock+h.Second;
    UInt8* end=p+h.First->ByteCodeSize;
    GLFunctions::Type id;
    GLOpCode::Type opCode;

    for(;p<end;)
    {
        id=*reinterpret_cast<GLFunctions::Type*>(p);
        opCode=*reinterpret_cast<GLOpCode::Type*>(p);
        p+=sizeof(GLFunctions::Type);
        if (id>=GLFunctions::MAX)
            OpenGLMachine::CallOpCode(opCode,p);
        else
            OpenGLMachine::CallFunction(id);
    }
}

void NativeShape::Optimize()
{
    StripeOutUnchangedRegisterMoves();
}

void NativeShape::StripeOutUnchangedRegisterMoves()
{
    MemoryCollectionStream pipe;
    pipe.AddLast(m_Data.Clone());
    pipe.Seek(*m_EntryTableSize*4+2,SeekOrigin::Begin);

    const UInt32 regTypes=(GLOpCode::MAX-GLFunctions::MAX)/OpenGLMachine::RegisterCount;
    GLOpCode::Type lastOpCall[OpenGLMachine::RegisterCount];
    UInt8* lastp;
    GLFunctions::Type id;
    GLOpCode::Type opCode;
    UInt8* end,*p;
    UInt64 byteSize=0;
    Int32 ind,offset;
    UInt8 lastRegisterValue[OpenGLMachine::RegisterSize*OpenGLMachine::RegisterCount];
    for (UInt32 i=0;i<m_HandleDataList.Count();++i)
    {   
        for (UInt32 j=0;j<OpenGLMachine::RegisterCount;++j)
            lastOpCall[j]=GLOpCode::MAX;
        Collections::Pair<Entry*,Core::Types::UInt32>& h=m_HandleDataList(i);
        p=m_ByteCodeBlock+h.Second;
        end=p+h.First->ByteCodeSize;

        for (;p<end;)
        {
            id=*reinterpret_cast<GLFunctions::Type*>(p);
            opCode=*reinterpret_cast<GLOpCode::Type*>(p);
            p+=sizeof(GLFunctions::Type);
            if (id>=GLFunctions::MAX)
            {
                ind=static_cast<Int32>(Math::Math<Float32>::Floor((opCode-GLOpCode::MoveFloat32Reg0)/static_cast<Float32>(regTypes)));
                offset=OpenGLMachine::RegisterSize*ind;
                lastp=p;
                RFMEM::Copy(lastRegisterValue+offset,OpenGLMachine::Registers+offset,8);
                OpenGLMachine::CallOpCode(opCode,p);
                if (opCode!=lastOpCall[ind] || (opCode==lastOpCall[ind] && RFMEM::Compare(lastRegisterValue+offset,OpenGLMachine::Registers+offset,ptrdiff_t(p-lastp))!=0))
                {
                    pipe.WriteType<GLOpCode::Type>(opCode);                    
                    pipe.Write(lastp,0,ptrdiff_t(p-lastp));
                    lastOpCall[ind]=opCode;
                }
            }
            else
                pipe.WriteType<GLFunctions::Type>(id);
        }
        byteSize=pipe.Position()-byteSize;
        pipe.Seek(i*4+2,SeekOrigin::Begin);
        pipe.WriteType<UInt16>(h.First->Identifier);
        pipe.WriteType<UInt16>(static_cast<UInt16>(byteSize-(2+m_HandleDataList.Count()*4)));
        pipe.Seek(byteSize,SeekOrigin::Begin);
    }
    UInt64 byteCodeSize=pipe.Position();

    AutoPointerArray<UInt8> data(new UInt8[byteCodeSize],static_cast<UInt32>(byteCodeSize));
    pipe.Seek(0,SeekOrigin::Begin);
    pipe.Read(data.Get(),0,byteCodeSize);
    AssignByteCode(data);
}
