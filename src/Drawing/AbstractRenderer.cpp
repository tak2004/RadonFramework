#include "RadonFramework/Drawing/AbstractRenderer.hpp"
#include "RadonFramework/Drawing/BasicRenderFunction.hpp"

namespace RadonFramework::Drawing {

void AbstractRenderer::DispatchAllFunctions()
{
    RF_Draw::GenerateBuffer::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::GenerateBuffer);
    RF_Draw::DestroyBuffer::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::DestroyBuffer);
    RF_Draw::UpdateBuffer::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::UpdateBuffer);
    RF_Draw::AssignBufferToObject::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::AssignBufferToObject);
    RF_Draw::GenerateObject::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::GenerateObject);
    RF_Draw::DestroyObject::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::DestroyObject);
    RF_Draw::RenderObject::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::RenderObject);
    RF_Draw::GenerateProgram::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::GenerateProgram);
    RF_Draw::DestroyProgram::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::DestroyProgram);
    RF_Draw::GenerateMaterial::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::GenerateMaterial);
    RF_Draw::GenerateTexture::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::GenerateTexture);
    RF_Draw::UpdateTexture::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::UpdateTexture);
    RF_Draw::DestroyTexture::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::DestroyTexture);
    RF_Draw::AssignTextureToMaterial::DispatchFunction = GetGeneralPurposeDispatcher(RF_Draw::BasicRenderFunctionType::AssignTextureToMaterial);
}

}