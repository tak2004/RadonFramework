#ifndef RF_GRAPHICDRIVERINFORMATIONOPENGL_HPP
#define RF_GRAPHICDRIVERINFORMATIONOPENGL_HPP

#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>
#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Drawing/OpenGLCapabilities.hpp>
#include <RadonFramework/Drawing/OpenGLCapabilitiesType.hpp>

namespace RadonFramework
{
    namespace Drawing
    {
        class OpenGLCapability
        {
            public:
                OpenGLCapability();
                OpenGLCapability(const OpenGLCapability& Copy);
                OpenGLCapability(OpenGLCapabilitiesType::Type Type,
                                 Core::Types::String Name,
                                 Core::Types::UInt32 ElementCount=1);
                ~OpenGLCapability();
                OpenGLCapability& operator =(const OpenGLCapability& Other);
                const Core::Types::Int32 GLInt(const Core::Types::UInt32 Index=0)const;
                const Core::Types::Bool GLBoolean(const Core::Types::UInt32 Index=0)const;
                const Core::Types::Float32 GLFloat(const Core::Types::UInt32 Index=0)const;
                const Core::Types::String& GLString(const Core::Types::UInt32 Index=0)const;
                const Core::Types::Float64 GLDouble(const Core::Types::UInt32 Index=0)const;
                const Core::Types::Int64 GLInt64(const Core::Types::UInt32 Index=0)const;
                Core::Types::String ToString()const;
                const Core::Types::String& Name()const;
                void* Ptr();
            protected:
                void* m_Data;
                OpenGLCapabilitiesType::Type m_Type;
                Core::Types::UInt32 m_ElementCount;
                Core::Types::String m_Name;
        };

        struct GraphicDriverCapabilitiesOpenGL
        {
            Core::Types::Bool IsAvaiable[OpenGLCapabilities::MAX];
            OpenGLCapability Value[OpenGLCapabilities::MAX];
            GraphicDriverCapabilitiesOpenGL();
            GraphicDriverCapabilitiesOpenGL(const GraphicDriverCapabilitiesOpenGL& Copy);
        };

        class GraphicDriverInformationOpenGL
        {
            public:
                GraphicDriverInformationOpenGL(Collections::AutoVector<Core::Types::String>& Extensions,
                                               GraphicDriverCapabilitiesOpenGL& Capabilities);
                const GraphicDriverCapabilitiesOpenGL& Capabilities()const;
                const Collections::AutoVector<Core::Types::String>& Extensions()const;
            protected:
                GraphicDriverCapabilitiesOpenGL m_Capabilities;
                Collections::AutoVector<Core::Types::String> m_Extensions;
        };
    }
}

#endif // RF_GRAPHICDRIVERINFORMATIONOPENGL_HPP
