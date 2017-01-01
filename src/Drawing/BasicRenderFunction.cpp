#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/BasicRenderFunction.hpp"

namespace RadonFramework { namespace Drawing {

AbstractRenderer::Dispatcher UpdateBuffer::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher GenerateBuffer::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher RenderObject::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher DestroyBuffer::DispatchFunction = nullptr;

} }