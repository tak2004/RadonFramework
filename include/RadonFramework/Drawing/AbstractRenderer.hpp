#ifndef RF_DRAWING_ABSTRACTRENDERER_HPP
#define RF_DRAWING_ABSTRACTRENDERER_HPP
#if _MSC_VER > 1000
#pragma once
#endif  // _MSC_VER > 1000

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/CommandBucket.hpp>
#include <RadonFramework/Math/Geometry/Size2D.hpp>

namespace RadonFramework::Drawing
{
class Path2D;

enum class BasicRenderFunctionType : RF_Type::UInt32
{
  GenerateObject,
  DestroyObject,
  RenderObject,
  GenerateBuffer,
  DestroyBuffer,
  UpdateBuffer,
  AssignBufferToObject,
  GenerateMaterial,
  DestroyMaterial,
  GenerateProgram,
  DestroyProgram,
  GenerateTexture,
  UpdateTexture,
  DestroyTexture,
  AssignTextureToMaterial
};

class AbstractRenderer
{
public:
  using Dispatcher = void (*)(void* Command);
  virtual void Generate(const RF_Geo::Size2Df& FrameSize) = 0;
  virtual void StartFrame() = 0;
  virtual void EndFrame() = 0;
  virtual RF_Type::UInt32
  Process(RF_Type::UInt32 EntityId, const Path2D& Path) = 0;
  /// Consume the current queues and execute them.
  virtual void Draw() = 0;
  virtual void ResizedViewport(const RF_Geo::Size2Df& NewSize) = 0;
  void ResizeQueueCount(const RF_Type::Size NewValue);
  RF_Type::Size GetQueueCount() const;
  RF_Collect::CommandBucket<>* GetQueue(const RF_Type::Size Index);
  void DispatchAllFunctions();
  /// This returns very basic functions which should be delivered.
  virtual Dispatcher GetGeneralPurposeDispatcher(
      const BasicRenderFunctionType Identifier) const = 0;
  /// This returns special functions which can be implemented with custom
  /// renderer.
  virtual Dispatcher
  GetCustomDispatcher(const RF_Type::UInt32 Identifier) const = 0;

protected:
  RF_Collect::Array<RF_Collect::CommandBucket<>> m_Buckets;
};

inline void AbstractRenderer::ResizeQueueCount(const RF_Type::Size NewValue)
{
  m_Buckets.Resize(NewValue);
}

inline RF_Type::Size AbstractRenderer::GetQueueCount() const
{
  return m_Buckets.Count();
}

inline RF_Collect::CommandBucket<>*
AbstractRenderer::GetQueue(const RF_Type::Size Index)
{
  return m_Buckets.Count() < Index ? nullptr : &m_Buckets(Index);
}

}  // namespace RadonFramework::Drawing

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif  // !RF_DRAWING_ABSTRACTRENDERER_HPP
