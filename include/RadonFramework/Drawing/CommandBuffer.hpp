#ifndef RF_DRAWING_COMMANDBUFFER_HPP
#define RF_DRAWING_COMMANDBUFFER_HPP

#include <RadonFramework/Drawing/OpenGLMachine.hpp>
#include <RadonFramework/IO/MemoryCollectionStream.hpp>
#include <RadonFramework/Collections/HashMap.hpp>
#include <RadonFramework/Math/Hash/Hash.hpp>

namespace RadonFramework { namespace Drawing {

class CommandBuffer
{
public:
    enum { CHUNKSIZE = 4096 };

    template<typename T>
    struct Variable
    {
        Variable() {}

        RF_Type::Size Count;
        RF_Type::Size Offset;
        RF_Type::Size Bytes;
        RF_Type::UInt64 Hash;
        RF_Type::Int32 Index;
        RF_Type::Bool Extern;

        Variable operator [](RF_Type::Size Index)
        {
            Assert(Index > Count, "Index out of bound!");
            Variable result = *this;
            result.Index = Index;
            return result;
        }

        Variable Ptr()
        {
            Variable result = *this;
            result.Index = -1;
            return result;
        }
    private:
        Variable(const T&) {}
    };

    template<GLFunctions::Type FUNC, typename... ARGS>
    void Call(ARGS... Parameters)
    {
        static const RF_Type::UInt64 PARAMETERS = sizeof...(ARGS);
        Assert(OpenGLMachine::FunctionParameterCount[FUNC] == PARAMETERS, "");

        if(m_ScratchPad.Length() - m_ScratchPad.Position() < (sizeof(RF_Type::UInt64) + sizeof(RF_Type::UInt16)) * (PARAMETERS + 1))
        {
            RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(new RF_Type::UInt8[CHUNKSIZE], CHUNKSIZE);
            m_ScratchPad.AddLast(newMemoryBlock);
        }

        Resolve<PARAMETERS>(Parameters...);
        m_ScratchPad.WriteType<RF_Type::UInt16>(FUNC);
    }

    template<GLFunctions::Type FUNC>
    void Call()
    {
        Assert(OpenGLMachine::FunctionParameterCount[FUNC] == 0, "");

        if(m_ScratchPad.Length() - m_ScratchPad.Position() < sizeof(RF_Type::UInt16))
        {
            RF_Mem::AutoPointerArray<RF_Type::UInt8> newMemoryBlock(new RF_Type::UInt8[CHUNKSIZE], CHUNKSIZE);
            m_ScratchPad.AddLast(newMemoryBlock);
        }

        m_ScratchPad.WriteType<RF_Type::UInt16>(FUNC);
    }

    RF_Type::Bool Finalize();

    const RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data()const;

    RF_Mem::AutoPointerArray<RF_Type::UInt8> ReleaseData();

    void State(const RF_Type::String& Name);

    template<typename T>
    void CopyResult(Variable<T>& To)
    {
        static_assert(GetReadOpCodeTrait<sizeof(T)>::SUPPORTED, "There is no Read command for this type!");
        static const GLOpCode::Type opCode = GetReadOpCode<sizeof(T)>::COMMAND;
        m_ScratchPad.WriteType<RF_Type::UInt16>(opCode);
    }

    template<typename T>
    Variable<T> AddVariable(RF_Type::Size HowMany)
    {
        return AddVariable<T>(HowMany,false,RF_Type::String());
    }

    template<typename T>
    Variable<T> AddVariable(RF_Type::Size HowMany, RF_Type::Bool Extern,
                            const RF_Type::String& Name)
    {
        static_assert(GetCopyOpCodeTrait<T>::SUPPORTED, "There is no Move command for this type!");
        Variable<T> result;
        result.Offset = m_ScratchPad.Position();
        for(RF_Type::Size i = 0; i < HowMany; ++i)
        {
            m_ScratchPad.WriteType<T>(0);
        }
        result.Bytes = m_ScratchPad.Position() - result.Offset;
        result.Count = HowMany;
        result.Index = 0;
        auto keyHashArray = RF_Math::Hash::Hash::Generate(Name.c_str(), "MurmurHash");
        RF_SysMem::Copy(&result.Hash, keyHashArray.Get(), sizeof(RF_Type::UInt64));
        m_DebugNames[result.Hash] = Name;
        result.Extern = Extern;
        return result;
    }
private:
    RF_IO::MemoryCollectionStream m_ScratchPad;
    RF_Mem::AutoPointerArray<RF_Type::UInt8> m_Final;
    RF_Collect::SparseHashMap<RF_Type::UInt64, RF_Type::String> m_DebugNames;


    template<RF_Type::Size TOTALPARAM, typename T>
    void Resolve(T Value)
    {
        static_assert(OpenGLMachine::RegisterCount >= 1, "There is no Move command for this amount of parameter!");
        WriteData<TOTALPARAM - 1>(Value);
    }

    template<RF_Type::Size TOTALPARAM, typename T, typename... ARGS>
    void Resolve(T First, ARGS... Rest)
    {
        static const RF_Type::UInt64 PARAMETERS = sizeof...(ARGS);
        static_assert(OpenGLMachine::RegisterCount > PARAMETERS, "There is no Move command for this amount of parameter!");
        WriteData<TOTALPARAM - PARAMETERS - 1>(First);
        Resolve<TOTALPARAM>(Rest...);
    }

    template<RF_Type::Size PARAMETER, typename T>
    void WriteData(T Value)
    {
        static_assert(GetMoveOpCodeTrait<T>::SUPPORTED, "There is no Move command for this type!");
        static const GLOpCode::Type opCode = GetMoveOpCode<T>::COMMAND[PARAMETER];
        m_ScratchPad.WriteType<RF_Type::UInt16>(opCode);
        m_ScratchPad.WriteType(Value);
    }

    template<RF_Type::Size PARAMETER,template<typename> class Variable, typename T>
    void WriteData(Variable<T> Value)
    {
        static_assert(GetCopyOpCodeTrait<T>::SUPPORTED, "There is no Copy command for this type!");
        static_assert(GetAddrOpCodeTrait<void*>::SUPPORTED, "There is no Addr command for this type!");
        static const GLOpCode::Type copyOperation = GetCopyOpCode<T>::COMMAND[PARAMETER];
        static const GLOpCode::Type addressOperation = GetAddrOpCode<void*>::COMMAND[PARAMETER];

        RF_Type::Size offset = m_ScratchPad.Position();

        if(Value.Extern)
        {
            if(Value.Index > -1)
            { // extern variable[N]
                m_ScratchPad.WriteType<RF_Type::UInt16>(copyOperation);
                m_ScratchPad.WriteType<RF_Type::Int32>((offset - Value.Offset) +
                                                       (sizeof(T) * Value.Index));
            }
            else
            { // extern variable.Ptr()
                m_ScratchPad.WriteType<RF_Type::UInt16>(copyOperation);
                m_ScratchPad.WriteType<RF_Type::Int32>(offset - Value.Offset);
            }
        }
        else
        {
            if(Value.Index > -1)
            { // variable[N]
                m_ScratchPad.WriteType<RF_Type::UInt16>(copyOperation);
                m_ScratchPad.WriteType<RF_Type::Int32>(offset -
                    (Value.Offset + (sizeof(T) * Value.Index)));
            }
            else
            { // variable.Ptr()
                m_ScratchPad.WriteType<RF_Type::UInt16>(addressOperation);
                m_ScratchPad.WriteType<RF_Type::Int32>(offset - Value.Offset);
            }
        }
    }
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_COMMANDBUFFER_HPP
