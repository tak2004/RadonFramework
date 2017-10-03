#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Drawing/BasicRenderFunction.hpp"

namespace RadonFramework::Drawing {

AbstractRenderer::Dispatcher UpdateBuffer::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher GenerateBuffer::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher RenderObject::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher DestroyBuffer::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher GenerateProgram::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher GenerateMaterial::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher DestroyProgram::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher GenerateObject::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher DestroyObject::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher AssignBufferToObject::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher GenerateTexture::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher UpdateTexture::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher DestroyTexture::DispatchFunction = nullptr;
AbstractRenderer::Dispatcher AssignTextureToMaterial::DispatchFunction = nullptr;

}