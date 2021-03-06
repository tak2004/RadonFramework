#ifndef RF_MATH_GEOMETRY_PACKRECTANGLE_HPP
#define RF_MATH_GEOMETRY_PACKRECTANGLE_HPP

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Collections/Pair.hpp>
#include <RadonFramework/Math/Geometry/Rectangle.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>

namespace RadonFramework::Math::Geometry
{
class PackRectangle
{
public:
  struct RectangleInfo
  {
    RF_Geo::Rectangle<> Rectangle;
    void* UserData;
    RF_Type::Bool Flipped;
  };
  using Bin = RF_Collect::Array<RectangleInfo>;

  PackRectangle(const RF_Type::Size EdgeSize);
  PackRectangle(const RF_Type::Size MaxWidth, const RF_Type::Size MaxHeight);
  PackRectangle(const RF_Geo::Size2D<>& MaxSize);
  ~PackRectangle();

  /// Remove all unprocessed and processed rectangles.
  void Clear();
  /// Enqueue the specified rectangle and user data to the processing queue.
  void AddRectangle(const RF_Geo::Size2D<>& Size, void* UserData);

  RF_Type::Bool Pack();

  void SetDimension(const RF_Type::Size EdgeSize);
  void
  SetDimension(const RF_Type::Size MaxWidth, const RF_Type::Size MaxHeight);
  void SetDimension(const RF_Geo::Size2D<>& MaxSize);
  const RF_Geo::Size2D<>& GetDimension() const;

  const RF_Collect::Array<Bin>& GetBins() const;
  RF_Type::Bool NeedProcessing() const;

private:
  RF_Collect::List<RF_Collect::Pair<RF_Geo::Size2D<>, void*>>
      m_NotProcessedRectangles;
  RF_Collect::Array<Bin> m_Bins;
  RF_Geo::Size2D<> m_Dimension;

  void SortLargestToSmallest();
  RF_Type::Bool IsDimensionRequirementFullfilled() const;
};

}  // namespace RadonFramework::Math::Geometry

#endif  //! RF_MATH_GEOMETRY_PACKRECTANGLE_HPP