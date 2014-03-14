#ifndef RF_PARAMETERSTACK_HPP
#define RF_PARAMETERSTACK_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Reflection/ReflectionTypes.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <vector>

namespace RadonFramework
{
    namespace Reflection
    {
        struct Parameter
        {
            void* Data;
            TypeKind::Type Datatype;
            Core::Types::UInt32 Datasize;
            Core::Types::UInt32 Count;
        };

        class ParameterStack
        {
            public:
                ParameterStack();
                ~ParameterStack();
                void Push(const void* Data, const TypeKind::Type Datatype, const Core::Types::UInt32 Count=1);
                void Push(const void* Data, const Core::Types::UInt32 Datasize, const Core::Types::UInt32 Count=1);

                void Pop();
                void ResetCursor();

                template<typename T>T* TopValue()
                {
                    if (m_Parameters.size()>0)
                    {
                        return (T*)(m_Parameters[m_Cursor].Data);
                    }
                    return 0;
                }
                TypeKind::Type TopType();
                RadonFramework::Core::Types::Bool IsEmpty();
                RadonFramework::Core::Types::Bool IsSameType(const ParameterStack &Stack);
                RadonFramework::Core::Types::UInt32 Size() const;
            protected:
                std::vector<Parameter> m_Parameters;
                Core::Types::Int32 m_Cursor;
        };
    }
}

#endif
