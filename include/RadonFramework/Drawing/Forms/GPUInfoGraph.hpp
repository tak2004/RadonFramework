#ifndef RF_DRAWING_FORMS_GPUINFOGRAPH_HPP
#define RF_DRAWING_FORMS_GPUINFOGRAPH_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Profiling/GPUServiceLocator.hpp>
#include <RadonFramework/Drawing/Forms/Control.hpp>

namespace RadonFramework::Forms
{
class GPUInfoGraph : public Control
{
public:
  GPUInfoGraph(Control* Parent = nullptr);
  void SetInfo(RF_Prof::GPUService::ValueSymbol Which);
  RF_Prof::GPUService::ValueSymbol GetInfo() const;
  void Animate(const RF_Type::UInt64 Now) override;
  void RebuildVisuals() override;

protected:
  RF_Type::String m_Text;
  RF_Prof::GPUService* m_Service;
  RF_Prof::GPUService::ValueSymbol m_Info;
  RF_Collect::Array<RF_Type::Float32> m_DataPoints;
  RF_Type::Size m_DataOffset;
  RF_Type::UInt64 m_NextUpdate;
  RF_Draw::Fill m_TextFill;
  RF_Draw::Fill m_GraphFill;
  RF_Draw::Fill m_GraphBackgroundFill;
  RF_Draw::Stroke m_GraphBackgroundStroke;
};

}  // namespace RadonFramework::Forms

#ifndef RF_SHORTHAND_NAMESPACE_FORM
#define RF_SHORTHAND_NAMESPACE_FORM
namespace RF_Form = RadonFramework::Forms;
#endif  // RF_SHORTHAND_NAMESPACE_FORM

#endif  // RF_DRAWING_FORMS_GPUINFOGRAPH_HPP