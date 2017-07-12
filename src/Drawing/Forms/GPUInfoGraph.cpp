#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/GPUInfoGraph.hpp"

namespace RadonFramework::Forms {

GPUInfoGraph::GPUInfoGraph(Control* Parent /*= nullptr*/)
	:Control(Parent)
	, m_DataOffset(0)
	, m_NextUpdate(0)
{
	m_TextFill.Color = RF_Draw::Color4f::Black();
	m_GraphFill.Color = RF_Draw::Color4f::Gray();
	m_GraphBackgroundFill.Color = RF_Draw::Color4f::White();
	m_GraphBackgroundStroke.Color = RF_Draw::Color4f::Black();
	m_DataPoints.Resize(100);
	for (auto i = 0; i < m_DataPoints.Count(); ++i)
	{
		m_DataPoints(i) = 0;
	}
	SetSize({ 100,100 });

	m_Service = &RF_Prof::GPUServiceLocator::Default();
	m_Info = RF_Prof::GPUService::GPUActivity;
}

void GPUInfoGraph::SetInfo(RF_Prof::GPUService::ValueSymbol Which)
{
	m_Info = Which;
}

RF_Prof::GPUService::ValueSymbol GPUInfoGraph::GetInfo() const
{
	return m_Info;
}

void GPUInfoGraph::Animate(const RF_Type::UInt64 Now)
{
	Control::Animate(Now);

	if (Now > m_NextUpdate)
	{
		if (Now - m_NextUpdate > RF_Time::TimeSpan::TicksPerSecond)
		{
			m_NextUpdate = Now;
		}
		else
		{
			m_NextUpdate += RF_Time::TimeSpan::TicksPerSecond;
		}
		// gather data
		m_Service->Update(0);
		m_DataPoints(m_DataOffset) = m_Service->CurrentValues(0)(m_Info) / m_Service->MaxValues(0)(m_Info);
		++m_DataOffset;
		if (m_DataOffset == m_DataPoints.Count())
		{
			m_DataOffset = 0;
		}
	}
}

void GPUInfoGraph::RebuildVisuals()
{
	Control::RebuildVisuals();

	// generate graph
	RF_Geo::Point2Df position(Left(), Top() + Height());
	m_Path.Clear();
	m_Path.SetFill(m_GraphBackgroundFill);
	m_Path.SetStroke(m_GraphBackgroundStroke);
	m_Path.AddRectangle(GetPosition(), GetSize());
	m_Path.SetFill(m_GraphFill);
	m_Path.MoveTo(position);
	position.X += Width();
	m_Path.LineTo(position);
	for (auto i = 0; i < m_DataPoints.Count(); ++i)
	{
		position.Y = Top() + Height() - m_DataPoints((i + m_DataOffset) % m_DataPoints.Count()) * Height();
		m_Path.LineTo(position);
		position.X -= Width() / (m_DataPoints.Count() - 1);
	}
	m_Path.Close();
	m_Path.SetFill(m_TextFill);
	position.Y = Top() + Height();
	position.X = Left();
	//m_Path.AddText("Fan"_rfs, position);
	m_Path.Finalize();
}

}