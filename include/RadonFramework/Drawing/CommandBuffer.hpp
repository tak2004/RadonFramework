#ifndef RF_DRAWING_COMMANDBUFFER_HPP
#define RF_DRAWING_COMMANDBUFFER_HPP

#include <RadonFramework/Drawing/OpenGLMachine.hpp>
#include <RadonFramework/IO/MemoryCollectionStream.hpp>

namespace RadonFramework { namespace Drawing {

class CommandBuffer
{
public:
    enum { CHUNKSIZE = 4096 };

    template<GLFunctions::Type FUNC, typename... ARGS>
    void Call(ARGS... Parameters)
    {
        static const RF_Type::UInt64 PARAMETERS = sizeof...(ARGS);
        Assert(OpenGLMachine::FunctionParameterCount[FUNC] == PARAMETERS, "");

        if(m_ScratchPad.Length() - m_ScratchPad.Position() < (sizeof(RF_Type::UInt64) + sizeof(RF_Type::UInt16)) * (PARAMETERS + 1))
        {
            RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
            m_ScratchPad.AddLast(newMemoryBlock);
        }

        Resolve<PARAMETERS>(Parameters...);
        m_ScratchPad.Write<RF_Type::UInt16>(FUNC);
    }

    template<GLFunctions::Type FUNC>
    void Call()
    {
        Assert(OpenGLMachine::FunctionParameterCount[FUNC] == 0, "");

        if(m_ScratchPad.Length() - m_ScratchPad.Position() < sizeof(RF_Type::UInt16))
        {
            RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(CHUNKSIZE);
            m_ScratchPad.AddLast(newMemoryBlock);
        }

        m_ScratchPad.Write<RF_Type::UInt16>(FUNC);
    }

    RF_Type::Bool Finalize()
    {
        RF_Type::Bool result = false;
        m_Final = RF_Mem::AutoPointerArray<RF_Type::UInt8>(m_ScratchPad.Position());
        m_ScratchPad.Seek(0, RF_IO::SeekOrigin::Begin);
        m_ScratchPad.Read(m_Final.Get(), 0, m_Final.Size());
        return result;
    }

    const RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data()const
    {
        return m_Final;
    }
private:
    RF_IO::MemoryCollectionStream m_ScratchPad;
    RF_Mem::AutoPointerArray<RF_Type::UInt8> m_Final;

    template<RF_Type::Size TOTALPARAM, typename T>
    void Resolve(T Value)
    {
        static_assert(GetOpCodeTrait<T>::SUPPORTED, "There is no Move command for this type!");
        static_assert(OpenGLMachine::RegisterCount >= 1, "There is no Move command for this amount of parameter!");
        static const GLOpCode::Type opCode = GetOpCode<T>::COMMAND[TOTALPARAM-1];

        m_ScratchPad.Write<RF_Type::UInt16>(opCode);
        m_ScratchPad.Write(Value);
    }

    template<RF_Type::Size TOTALPARAM, typename T, typename... ARGS>
    void Resolve(T First, ARGS... Rest)
    {
        static_assert(GetOpCodeTrait<T>::SUPPORTED, "There is no Move command for this type!");
        static const RF_Type::UInt64 PARAMETERS = sizeof...(ARGS);
        static_assert(OpenGLMachine::RegisterCount > PARAMETERS, "There is no Move command for this amount of parameter!");
        static const GLOpCode::Type opCode = GetOpCode<T>::COMMAND[TOTALPARAM-PARAMETERS-1];

        m_ScratchPad.Write<RF_Type::UInt16>(opCode);
        m_ScratchPad.Write(First);
        Resolve<TOTALPARAM>(Rest...);
    }
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_COMMANDBUFFER_HPP
