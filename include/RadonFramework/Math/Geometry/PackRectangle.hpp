#ifndef RF_MATH_GEOMETRY_PACKRECTANGLE_HPP
#define RF_MATH_GEOMETRY_PACKRECTANGLE_HPP

#include <RadonFramework/Collections/Pair.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/List.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>
#include <RadonFramework/Math/Geometry/Rectangle.hpp>

namespace RadonFramework { namespace Math { namespace Geometry {

class PackRectangle
{
public:
    struct RectangleInfo
    {
        RF_Geo::Rectangle<> Rectangle;
        void* UserData;
        RF_Type::Bool Fliped;
    };
    PackRectangle(const RF_Type::Size EdgeSize);
    PackRectangle(const RF_Type::Size MaxWidth, const RF_Type::Size MaxHeight);
    PackRectangle(const RF_Geo::Size2D<>& MaxSize);
    ~PackRectangle();

    /// Remove all unprocessed and processed rectangles.
    void Clear();
    /// Enqueue the specified rectangle and user data to the processing queue.
    void AddRectangle(const RF_Geo::Size2D<>& Size, void* UserData);

    RF_Type::Bool Pack();
    RF_Type::Bool Rebuild();
    void SetDimension(const RF_Type::Size EdgeSize);
    void SetDimension(const RF_Type::Size MaxWidth, const RF_Type::Size MaxHeight);
    void SetDimension(const RF_Geo::Size2D<>& MaxSize);
    const RF_Geo::Size2D<>& GetDimension()const;

    const RF_Collect::Array<RF_Collect::Array<RectangleInfo>>& GetBins()const;
    RF_Type::Bool NeedProcessing()const;
private:
    RF_Collect::List<RF_Collect::Pair<RF_Geo::Size2D<>, void*> > m_NotProcessedRectangles;
    RF_Collect::Array<RF_Collect::Array<RectangleInfo>> m_Bins;
    RF_Geo::Size2D<> m_Dimension;
};

} } }

#endif //!RF_MATH_GEOMETRY_PACKRECTANGLE_HPP