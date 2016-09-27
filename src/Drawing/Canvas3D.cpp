#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Canvas3D.hpp"
#include "RadonFramework/Drawing/Canvas3DServiceLocator.hpp"
#include "RadonFramework/Drawing/Forms/AbstractWindow.hpp"
#include "RadonFramework/Drawing/Forms/Form.hpp"
#include "RadonFramework/Math/Geometry/Point2D.hpp"
#include "RadonFramework/Math/Geometry/Size2D.hpp"
#include "RadonFramework/Math/Geometry/Rectangle.hpp"
#include "RadonFramework/Drawing/AbstractCanvas.hpp"
#include "RadonFramework/System/Threading/Mutex.hpp"
#include "RadonFramework/Drawing/Forms/Form.hpp"
#include "RadonFramework/Drawing/AbstractRenderer.hpp"

namespace RadonFramework { namespace Drawing {

Canvas3D::Canvas3D(RF_Form::Form& Window, RF_Form::Control* Parent)
:m_Renderer(0)
{
    if(Parent)
    {
        Control(Parent);
    }
    else
    {
        Control(Window);
    }
    m_Backend = Canvas3DServiceLocator::Default().CreateCanvas3D();
    m_Backend->SetWindowInfos(*Window.Backend());
    m_Backend->Generate();
    Window.OnIdle += SignalReceiver::Connector<Canvas3D>(&Canvas3D::Draw);
}

void Canvas3D::Resize(const RF_Geo::Size2D<>& Value)
{
    Math::Geometry::Rectangle<> rec(RF_Geo::Point2D<>(0, 0), 
        RF_Geo::Point2D<>(Value.Width, Value.Height));
    m_Backend->UpdateRectangle(rec);
}

void Canvas3D::Clear()
{
    m_Backend->Clear();
}

void Canvas3D::SwapBuffer()
{
    m_Backend->SwapBuffer();
}

const GraphicDriverInformation& Canvas3D::GetGraphicDriverInformation()
{
    return m_Backend->GetGraphicDriverInformation();
}

AbstractCanvas const* Canvas3D::Backend()const
{
    return m_Backend;
}

template<typename T>
void RecursiveVisit(const RF_Form::Control& Ctrl, T Func)
{
    for(auto it = Ctrl.ConstBegin(); it != Ctrl.ConstEnd(); ++it)
    {
        Func(**it);
        RecursiveVisit(**it, Func);
    }
}

void Canvas3D::Draw()
{
    if(m_Renderer)
    {
        m_Renderer->StartFrame();
        // inform the renderer about the existing controls
        RecursiveVisit(*this, [=](const RF_Form::Control& Ctrl) 
        {
            m_Renderer->Process(Ctrl.GetPath()); 
        });
        // request to draw the visible controls
        RecursiveVisit(*this, [=](const RF_Form::Control& Ctrl) 
        {
            m_Renderer->Draw(Ctrl.GetPath()); 
        });
        m_Renderer->EndFrame();
    }
}

void Canvas3D::SetRenderer(AbstractRenderer& NewRenderer)
{
    m_Renderer = &NewRenderer;
}

void Canvas3D::MakeCurrent()
{
    m_Backend->MakeCurrent();
}

void Canvas3D::SetVSync(const RF_Type::Bool Synchronize /*= true*/,
    const RF_Type::Bool ShouldContinue /*= true*/)
{
    m_Backend->SetVSync(Synchronize, ShouldContinue);
}

} }