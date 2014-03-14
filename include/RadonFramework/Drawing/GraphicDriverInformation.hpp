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
            Core::Types::Bool DoubleBuffer;//a single boolean value indicating whether double buffering is supported
            Core::Types::Bool Stereo;//indicating whether stereo buffers(left and right) are supported
            Core::Types::Int32 MajorVersion;
            Core::Types::Int32 MinorVersion;
            Core::Types::String Renderer;
            Core::Types::Int32 ShaderModel;
            Core::Types::String Vendor;
            Core::Types::String Version;
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
