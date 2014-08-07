#ifndef RF_DRAWING_COMMANDBUFFER_HPP
#define RF_DRAWING_COMMANDBUFFER_HPP

#include <RadonFramework/Drawing/OpenGLMachine.hpp>

namespace RadonFramework { namespace Drawing {

class CommandBuffer
{
public:
    template<typename T>
    class OpCode
    {
    public:
        OpCode(GLOpCode::Type Which, const T& Value);
    private:
        OpCode()delete;
    protected:
        GLOpCode::Type Which;
        T Value;
    };

    CommandBuffer& operator << (GLFunctions::Type Function);

    template<typename T>
    CommandBuffer& operator << (OpCode<T>& OpCodeObject);
};

template<typename T>
CommandBuffer& CommandBuffer::operator<<(OpCode<T>& OpCodeObject)
{
    return this
}

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_COMMANDBUFFER_HPP
