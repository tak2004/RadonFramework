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

namespace RadonFramework::Drawing {

Canvas3D::Canvas3D(RF_Form::Form& Window, RF_Form::Control* Parent)
:m_Renderer(0)
,Control(Parent != nullptr ? Parent : &Window)
{
    m_Backend = Canvas3DServiceLocator::Default().CreateCanvas3D();
    if (m_Backend != nullptr)
    {
        m_Backend->SetWindowInfos(*Window.Backend());
        m_Backend->Generate(GetSize());
        m_Renderer = m_Backend->GetRenderer();
    }
    Window.OnIdle += SignalReceiver::Connector<Canvas3D>(&Canvas3D::Draw);
}

void Canvas3D::ChangeContentRectangle(const RF_Geo::Rectanglef& NewContent,
                                      const RF_Geo::Rectanglef& OldContent)
{
    Control::ChangeContentRectangle(NewContent, OldContent);
    Math::Geometry::Rectangle<> rec;
    rec.Left(NewContent.Left());
    rec.Top(NewContent.Top());
    rec.Height(NewContent.Height());
    rec.Width(NewContent.Width());
    m_Backend->MakeCurrent();
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
void RecursiveVisit(RF_Form::Control& Ctrl, T Func)
{
    for(auto it = Ctrl.Begin(); it != Ctrl.End(); ++it)
    {
        Func(**it);
        RecursiveVisit(**it, Func);
    }
}

void Canvas3D::Draw()
{
    if(m_Renderer)
    {
        // Switch to the current context to support multiple windows.
        m_Backend->MakeCurrent();
        m_Renderer->StartFrame();
        // inform the renderer about the existing controls
        RecursiveVisit(*this, [=](RF_Form::Control& Ctrl) 
        {
            if(Ctrl.Visible() && Ctrl.GetPath().GetHash() != 0)
            {
                RF_Type::UInt32 entityId = Ctrl.GetVisualId();
                if(entityId != 0)
                {
                    m_Renderer->Process(entityId, Ctrl.GetPath());
                }
                else
                {
                    entityId = m_Renderer->Process(entityId, Ctrl.GetPath());
                    Ctrl.SetVisualId(entityId);
                }
            }
        });
        // request to draw the visible controls
        m_Renderer->Draw();
        m_Renderer->EndFrame();
    }
}

RadonFramework::Drawing::AbstractRenderer* Canvas3D::GetRenderer() const
{
    return m_Renderer;
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

}