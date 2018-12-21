#ifndef RF_DRAWING_PATH2D_HPP
#define RF_DRAWING_PATH2D_HPP

#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Drawing/Color.hpp>
#include <RadonFramework/Drawing/Image.hpp>
#include <RadonFramework/IO/MemoryCollectionStream.hpp>
#include <RadonFramework/Math/Geometry/Point2D.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>

namespace RadonFramework::Drawing
{
class Image;

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
  Path2D(const Path2D& CopyFrom);
  ~Path2D();

  void Clear();

  Path2D& MoveTo(const RF_Geo::Point2Df& Position);
  Path2D& LineTo(const RF_Geo::Point2Df& Position);
  Path2D& BezierTo(const RF_Geo::Point2Df& ControlPoint1,
                   const RF_Geo::Point2Df& ControlPoint2,
                   const RF_Geo::Point2Df& Position);
  Path2D& QuadraticBezierTo(const RF_Geo::Point2Df& ControlPoint,
                            const RF_Geo::Point2Df& Position);
  Path2D& ArcTo(const RF_Geo::Point2Df& Position1,
                const RF_Geo::Point2Df& Position2,
                RF_Type::Float32 Radius);
  Path2D& Close();

  Path2D& AddArc(const RF_Geo::Point2Df& Position,
                 RF_Type::Float32 Radius,
                 RF_Type::Float32 AngleStart,
                 RF_Type::Float32 AngleStop);
  Path2D& AddRectangle(const RF_Geo::Point2Df& Position,
                       const RF_Geo::Size2Df& Dimension);
  Path2D& AddRoundRectangle(const RF_Geo::Point2Df& Position,
                            const RF_Geo::Size2Df& Dimension,
                            RF_Type::Float32 Radius);
  Path2D& AddEllipse(const RF_Geo::Point2Df& Position,
                     const RF_Geo::Size2Df& Dimension,
                     RF_Type::Float32 Angle);
  Path2D& AddCircle(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius);
  Path2D&
  AddText(const RF_Type::String& Text, const RF_Geo::Point2Df& Position);
  Path2D& AddImage(const RF_Geo::Point2Df& Position,
                   const RF_Geo::Size2Df& Dimension,
                   const RF_Draw::Image& Source);

  Path2D& Finalize();

  Path2D& SetFill(const Fill& NewFill);
  Path2D& SetStroke(const Stroke& NewStroke);

  class Visitor
  {
  public:
    virtual void Initialize() = 0;
    virtual void Finalize() = 0;
    virtual void MoveTo(const RF_Geo::Point2Df& Position) = 0;
    virtual void LineTo(const RF_Geo::Point2Df& Position) = 0;
    virtual void Close() = 0;
    virtual void BezierTo(const RF_Geo::Point2Df& ControlPoint1,
                          const RF_Geo::Point2Df& ControlPoint2,
                          const RF_Geo::Point2Df& Position) = 0;
    virtual void QuadraticBezierTo(const RF_Geo::Point2Df& ControlPoint,
                                   const RF_Geo::Point2Df& Position) = 0;
    virtual void AddArc(const RF_Geo::Point2Df& Position,
                        RF_Type::Float32 Radius,
                        RF_Type::Float32 AngleStart,
                        RF_Type::Float32 AngleStop) = 0;
    virtual void AddRectangle(const RF_Geo::Point2Df& Position,
                              const RF_Geo::Size2Df& Dimension) = 0;
    virtual void AddRoundRectangle(const RF_Geo::Point2Df& Position,
                                   const RF_Geo::Size2Df& Dimension,
                                   RF_Type::Float32 Radius) = 0;
    virtual void AddEllipse(const RF_Geo::Point2Df& Position,
                            const RF_Geo::Size2Df& Dimension,
                            RF_Type::Float32 Angle) = 0;
    virtual void
    AddCircle(const RF_Geo::Point2Df& Position, RF_Type::Float32 Radius) = 0;
    virtual void
    AddText(const RF_Geo::Point2Df& Position, const RF_Type::String& Text) = 0;
    virtual void AddImage(const RF_Geo::Point2Df& Position,
                          const RF_Geo::Size2Df& Dimension,
                          const RF_Draw::Image& Source) = 0;
    virtual void SetFill(const Fill& NewFill) = 0;
    virtual void SetStroke(const Stroke& NewStroke) = 0;
    virtual void Error() = 0;
  };

  void Visit(Visitor& PathVisitor) const;
  RF_Type::UInt32 GetHash() const;

protected:
  RF_Geo::Point2Df m_CurrentPosition;

  RF_IO::MemoryCollectionStream m_ScratchPad;
  RF_Mem::AutoPointerArray<RF_Type::UInt8> m_Final;
  RF_Type::UInt32 m_Hash;
};

}  // namespace RadonFramework::Drawing

#endif  // RF_DRAWING_PATH2D_HPP