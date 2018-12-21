#include "RadonFramework/precompiled.hpp"
#include <GraphicDriverInformationOpenGL.hpp>
#include <RadonFramework/Diagnostics/Debugging/Assert.hpp>

using namespace RadonFramework::Drawing;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;


UInt32 OpenGLCapabilitySize[OpenGLCapabilitiesType::MAX]={
    0,
    sizeof(Float32),
    sizeof(Float64),
    sizeof(Int32),
    sizeof(Int64),
    sizeof(Bool),
    sizeof(String)
};

OpenGLCapability::OpenGLCapability()
:m_Data(0)
,m_Type(OpenGLCapabilitiesType::NOTSET)
,m_ElementCount(0)
{
}

OpenGLCapability::OpenGLCapability(const OpenGLCapability& Copy)
{
    *this=Copy;
}

OpenGLCapability::OpenGLCapability(OpenGLCapabilitiesType::Type Type,
                                   const String& Name,
                                   UInt32 ElementCount)
:m_Data(0)
,m_Type(Type)
,m_ElementCount(ElementCount)
,m_Name(Name)
{
    UInt32 size=OpenGLCapabilitySize[m_Type]*m_ElementCount;
    m_Data=new UInt8[size];
    RF_SysMem::Set(m_Data,0,size);
}

OpenGLCapability::~OpenGLCapability()
{
    if (m_Data)
        delete[] m_Data;
}

OpenGLCapability& OpenGLCapability::operator =(const OpenGLCapability& Other)
{
    if (m_Data)
        delete[] m_Data;
    m_Data=0;
    m_Type=Other.m_Type;
    m_ElementCount=Other.m_ElementCount;
    m_Name=Other.m_Name;
    if (m_ElementCount>0)
    {
        UInt32 size=OpenGLCapabilitySize[m_Type]*m_ElementCount;
        m_Data=new UInt8[size];
        RF_SysMem::Copy(m_Data,Other.m_Data,size);
    }
    return *this;
}

const Int32 OpenGLCapability::GLInt(const UInt32 Index)const
{
    RF_ASSERT(m_Type==OpenGLCapabilitiesType::GLINT,"Illegal usage.");
    return *(reinterpret_cast<Int32*>(m_Data)+Index);
}

const Bool OpenGLCapability::GLBoolean(const UInt32 Index)const
{
    RF_ASSERT(m_Type==OpenGLCapabilitiesType::GLBOOLEAN,"Illegal usage.");
    return *(reinterpret_cast<Bool*>(m_Data)+Index);
}

const Float32 OpenGLCapability::GLFloat(const UInt32 Index)const
{
    RF_ASSERT(m_Type==OpenGLCapabilitiesType::GLFLOAT,"Illegal usage.");
    return *(reinterpret_cast<Float32*>(m_Data)+Index);
}

const String& OpenGLCapability::GLString(const UInt32 Index)const
{
    RF_ASSERT(m_Type==OpenGLCapabilitiesType::GLSTRING,"Illegal usage.");
    return *(reinterpret_cast<String*>(m_Data)+Index);
}

const Float64 OpenGLCapability::GLDouble(const UInt32 Index)const
{
    RF_ASSERT(m_Type==OpenGLCapabilitiesType::GLDOUBLE,"Illegal usage.");
    return *(reinterpret_cast<Float64*>(m_Data)+Index);
}

const Int64 OpenGLCapability::GLInt64(const UInt32 Index)const
{
    RF_ASSERT(m_Type==OpenGLCapabilitiesType::GLINT64,"Illegal usage.");
    return *(reinterpret_cast<Int64*>(m_Data)+Index);
}

String OpenGLCapability::ToString()const
{
    String str;
    for (UInt32 i=0;i<m_ElementCount;++i)
    {
        switch(m_Type)
        {
            case OpenGLCapabilitiesType::GLBOOLEAN:
                str+=GLBoolean(i); break;
            case OpenGLCapabilitiesType::GLDOUBLE:
                str+=Convert::ToString(GLDouble(i)); break;
            case OpenGLCapabilitiesType::GLFLOAT:
                str+=Convert::ToString(GLFloat(i)); break;
            case OpenGLCapabilitiesType::GLINT:
                str+=Convert::ToString(GLInt(i)); break;
            case OpenGLCapabilitiesType::GLINT64:
                str+=Convert::ToString(GLInt64(i)); break;
            case OpenGLCapabilitiesType::GLSTRING:
                str+=GLString(i); break;
            default:
                str+="unknown data type";
        }
        if (i<m_ElementCount-1)
            str+=",";
    }
    if (0==m_ElementCount)
        str="no values";
    return str;
}

void* OpenGLCapability::Ptr()
{
    return m_Data;
}

const String& OpenGLCapability::Name()const
{
    return m_Name;
}

GraphicDriverInformationOpenGL::GraphicDriverInformationOpenGL(
    Array<String>& Extensions, GraphicDriverCapabilitiesOpenGL& Capabilities)
:m_Capabilities(Capabilities)
,m_Extensions(Extensions)
{

}

GraphicDriverCapabilitiesOpenGL::GraphicDriverCapabilitiesOpenGL()
{
    RF_SysMem::Set(this,0,sizeof(GraphicDriverCapabilitiesOpenGL));
}

GraphicDriverCapabilitiesOpenGL::GraphicDriverCapabilitiesOpenGL(const GraphicDriverCapabilitiesOpenGL& Copy)
{
    RF_SysMem::Copy(IsAvaiable,Copy.IsAvaiable,sizeof(Bool)*OpenGLCapabilities::MAX);
    for (UInt32 i=0;i<OpenGLCapabilities::MAX;++i)
        Value[i]=Copy.Value[i];
}


const Array<String>& GraphicDriverInformationOpenGL::Extensions()const
{
    return m_Extensions;
}

const GraphicDriverCapabilitiesOpenGL& GraphicDriverInformationOpenGL::Capabilities()const
{
    return m_Capabilities;
}