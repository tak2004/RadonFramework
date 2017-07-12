#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Forms/Image.hpp"

namespace RadonFramework::Forms {

Image::Image(Control* Parent /*= nullptr*/)
:Control(Parent)
{
    SetSize({100,100});
}

void Image::SetImage(const RF_Draw::Image& NewImage)
{
    m_Image = NewImage;
    RebuildVisuals();
}

const RF_Draw::Image& Image::GetImage() const
{
    return m_Image;
}

void Image::RebuildVisuals()
{
    Control::RebuildVisuals();

    RF_Geo::Point2Df position(Left(), Top());
    RF_Geo::Size2Df dimension(m_Image.Width(), m_Image.Height());
    m_Path.Clear();
    m_Path.AddImage(position, dimension, m_Image);
    m_Path.Finalize();
}

}