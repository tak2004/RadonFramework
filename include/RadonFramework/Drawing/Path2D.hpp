#ifndef RF_DRAWING_PATH2D_HPP
#define RF_DRAWING_PATH2D_HPP

#include <RadonFramework/Drawing/Color.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/Collections/List.hpp>

namespace RadonFramework { namespace Drawing {

class Stroke
{
public:
    Stroke();
    Color4f Color;
    RF_Type::Float32 Width;
};

class Fill
{
public:
    Fill();
    Color4f Color;
};

/// Represent a state machine to construct 2d vector shapes.
class Path2D
{
public:
    Path2D();
    ~Path2D();

    void Clear();

    void MoveTo(const RF_Geo::Point2Df& Position);
    void LineTo(const RF_Geo::Point2Df& Position);
    void BezierTo(const RF_Geo::Point2Df& ControlPoint1, 
                  const RF_Geo::Point2Df& ControlPoint2,
                  const RF_Geo::Point2Df& Position);
    void QuadraticBezierTo(const RF_Geo::Point2Df& ControlPoint, 
                           const RF_Geo::Point2Df& Position);
    void ArcTo(const RF_Geo::Point2Df& Position1, const RF_Geo::Point2Df& Position2,
               RF_Type::Float32 Radius);
    void Close();

    void AddArc(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius,
                RF_Type::Float32 AngleStart, RF_Type::Float32 AngleStop);
    void AddRectangle(const RF_Geo::Point2Df& Position, const RF_Geo::Size2Df& Dimension);
    void AddRoundRectangle(const RF_Geo::Point2Df& Position, 
                           const RF_Geo::Size2Df& Dimension, 
                           RF_Type::Float32 Radius);
    void AddEllipse(const RF_Geo::Point2Df& Position, const RF_Geo::Size2Df& Dimension,
                    RF_Type::Float32 Angle);
    void AddCircle(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius);
    Stroke& StrokeProperties();
    Fill& FillProperties();
protected:
    enum class Command:RF_Type::UInt8;

    RF_Geo::Point2Df m_CurrentPosition;
    Stroke m_StrokeProperties;
    Fill m_FillProperties;
    RF_Collect::List<Command> m_CommandBuffer;
    RF_Collect::List<RF_Type::Float32> m_ValueBuffer;
};

} }



#endif // RF_DRAWING_PATH2D_HPP