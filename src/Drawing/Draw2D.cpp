#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/Draw2D.hpp"
#include "RadonFramework/Math/Geometry/Point2D.hpp"
#include "RadonFramework/Drawing/Path2D.hpp"
#include "RadonFramework/Drawing/Text2D.hpp"
#include "RadonFramework/Drawing/MeshGenerator2D.hpp"

namespace RadonFramework { namespace Drawing {

Draw2D::Draw2D()
{

}

Draw2D::~Draw2D()
{

}

RF_Mem::AutoPointer<Path2D> Draw2D::BeginPath()const
{
    RF_Mem::AutoPointer<Path2D> result(new Path2D);
    return result;
}

RF_Mem::AutoPointer<NativeShape> Draw2D::EndPath(Path2D& Path)const
{
    RF_Mem::AutoPointer<NativeShape> result;
    Path.Finalize();
    result = m_MeshGenerator->Generate(Path);
    result->MapVariable("shader", m_UIShader);
    return result;
}

RF_Mem::AutoPointer<Text2D> Draw2D::BeginText(const FontDescription& WhichFont, 
    const RF_Type::String& Text)const
{
    RF_Mem::AutoPointer<Path2D> result(new Path2D);
    return result;
}

RF_Mem::AutoPointer<NativeShape> Draw2D::EndText(Text2D& Text)const
{
    RF_Mem::AutoPointer<NativeShape> result;// = m_MeshGenerator->Generate(Path);
    return result;
}

void Draw2D::DrawPath(const NativeShape& Instance, const RF_Geo::Point2Df& Position,
    RF_Type::Float32 Angle/*=0.0f*/)
{

}

void Draw2D::DrawText(const NativeShape& Instance, const RF_Geo::Point2Df& Position,
    RF_Type::Float32 Angle /*= 0.0f*/)
{

}

void Draw2D::SetMeshGenerator(const MeshGenerator2D& Instance)
{
    m_MeshGenerator = &Instance;
}

const MeshGenerator2D* Draw2D::GetMeshGenerator() const
{
    return m_MeshGenerator;
}

} }