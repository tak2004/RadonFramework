#ifndef RF_DIAGNOSTICS_TEST_BDD_CONSOLEOUTPUT_HPP
#define RF_DIAGNOSTICS_TEST_BDD_CONSOLEOUTPUT_HPP

#include <RadonFramework/Diagnostics/Test/BDD/SpecificationOutput.hpp>

namespace RadonFramework::Diagnostics::Test::BDD
{
class ConsoleOutput : public SpecificationOutput
{
public:
  void WriteText(const Core::Types::String& Text) const override;
  void WriteError(const Core::Types::String& Text) const override;
  void WriteSuccess(const Core::Types::String& Text) const override;
  void WriteFailure(const Core::Types::String& Text) const override;
  void WritePending(const Core::Types::String& Text) const override;
  void WriteSkipped(const Core::Types::String& Text) const override;
  void WriteStats(const Core::Types::String& Text) const override;
};

}  // namespace RadonFramework::Diagnostics::Test::BDD

#ifndef RF_SHORTHAND_NAMESPACE_BDD
#define RF_SHORTHAND_NAMESPACE_BDD
namespace RF_BDD = RadonFramework::Diagnostics::Test::BDD;
#endif

#endif  // !RF_DIAGNOSTICS_TEST_BDD_CONSOLEOUTPUT_HPP
