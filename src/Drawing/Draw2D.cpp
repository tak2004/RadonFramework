#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Draw2D.hpp"

namespace RadonFramework { namespace Drawing {

Draw2D::Draw2D()
:m_PathListUsed(0)
,m_TextListUsed(0)
{
    m_PathList.Resize(8);
    m_TextList.Resize(8);
}

Draw2D::~Draw2D()
{
    m_PathList.Resize(0);
    m_TextList.Resize(0);
}

void Draw2D::Clear()
{
    m_PathListUsed = 0;
    m_TextListUsed = 0;
}

Path2D& Draw2D::BeginPath()
{
    if(m_PathListUsed == m_PathList.Count())
    {
        m_PathList.Resize(m_PathListUsed*2);
    }
    return m_PathList(m_PathListUsed++);
}

void Draw2D::EndPath(const Path2D& Path)
{

}

Text2D& Draw2D::Text(const FontDescription& WhichFont, const RF_Type::String& Text)
{
    if(m_TextListUsed == m_TextList.Count())
    {
        m_TextList.Resize(m_TextListUsed * 2);
    }
    return m_TextList(m_TextListUsed++);
}

void Draw2D::DrawPath(const Path2D& Instance, const RF_Geo::Point2Df& Position, RF_Type::Float32 Angle/*=0.0f*/)
{

}

void Draw2D::DrawText(const Text2D& Instance, const RF_Geo::Point2Df& Position, RF_Type::Float32 Angle /*= 0.0f*/)
{

}

} }