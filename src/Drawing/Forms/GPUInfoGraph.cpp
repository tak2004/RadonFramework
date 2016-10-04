#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/GPUInfoGraph.hpp"

namespace RadonFramework { namespace Forms {

GPUInfoGraph::GPUInfoGraph(Control* Parent /*= nullptr*/)
:Control(Parent)
,m_DataOffset(0)
{
    m_DataPoints.Resize(20);
    for (auto i = 0; i < m_DataPoints.Count(); ++i)
    {
        m_DataPoints(i) = 0;
    }
    m_ClientRectangle.Width(100);
    m_ClientRectangle.Height(100);

    m_Service = &RF_Prof::GPUServiceLocator::Default();
    m_Info = RF_Prof::GPUService::Activity;
}

void GPUInfoGraph::SetInfo(RF_Prof::GPUService::ValueSymbol Which)
{
    m_Info = Which;
}

RF_Prof::GPUService::ValueSymbol GPUInfoGraph::GetInfo() const
{
    return m_Info;
}

void GPUInfoGraph::Animate()
{
    Control::Animate();
    // gather data
    m_Service->Update(0);
    m_DataPoints(m_DataOffset) = m_Service->CurrentValues(0)(m_Info) / m_Service->MaxValues(0)(m_Info);
    ++m_DataOffset;
    if(m_DataOffset == m_DataPoints.Count())
    {
        m_DataOffset = 0;
    }
    // generate graph
    RF_Geo::Point2Df position(m_ClientRectangle.Left(), m_ClientRectangle.Top());
    m_Path.Clear();
    m_Path.MoveTo(position);
    position.X += m_ClientRectangle.Width();
    m_Path.LineTo(position);
    for (auto i = 0; i < m_DataPoints.Count(); ++i)
    {
        position.Y = m_DataPoints((m_DataOffset-i)%m_DataPoints.Count()) * m_ClientRectangle.Height();
        position.X -= m_ClientRectangle.Width()/m_DataPoints.Count();        
        m_Path.LineTo(position);
    }
    m_Path.Close();
    m_Path.Finalize();
}

} }