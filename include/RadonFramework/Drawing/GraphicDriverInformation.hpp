#ifndef RF_GRAPHICDRIVERINFORMATION_HPP
#define RF_GRAPHICDRIVERINFORMATION_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/Float32.hpp>

namespace RadonFramework
{
    namespace Drawing
    {
        struct GraphicDriverCapabilities
        {
            RF_Type::Bool DoubleBuffer;//a single boolean value indicating whether double buffering is supported
            RF_Type::Bool Stereo;//indicating whether stereo buffers(left and right) are supported
            RF_Type::Int32 MajorVersion;
            RF_Type::Int32 MinorVersion;
            RF_Type::String Renderer;
            RF_Type::Int32 ShaderModel;
            RF_Type::String Vendor;
            RF_Type::String Version;
        };

        class GraphicDriverInformation
        {
            public:
                GraphicDriverInformation(GraphicDriverCapabilities& Capabilities);
                const GraphicDriverCapabilities& Capabilities()const;
            protected:
                GraphicDriverCapabilities m_Capabilities;
        };

        inline const GraphicDriverCapabilities& GraphicDriverInformation::Capabilities()const
        {
            return m_Capabilities;
        }
    }
}

#endif // RF_GRAPHICDRIVERINFORMATION_HPP
