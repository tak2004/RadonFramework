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
            RF_Type::UInt32 Datasize;
            RF_Type::UInt32 Count;
        };

        class ParameterStack
        {
            public:
                ParameterStack();
                ~ParameterStack();
                void Push(const void* Data, const TypeKind::Type Datatype, const RF_Type::UInt32 Count=1);
                void Push(const void* Data, const RF_Type::UInt32 Datasize, const RF_Type::UInt32 Count=1);

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
                RF_Type::Bool IsEmpty();
                RF_Type::Bool IsSameType(const ParameterStack &Stack);
                RF_Type::UInt32 Size() const;
            protected:
                std::vector<Parameter> m_Parameters;
                RF_Type::Int32 m_Cursor;
        };
    }
}

#endif
