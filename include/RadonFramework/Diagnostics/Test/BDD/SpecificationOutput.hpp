#ifndef RF_DIAGNOSTICS_TEST_BDD_SPECIFICATIONOUTPUT_HPP
#define RF_DIAGNOSTICS_TEST_BDD_SPECIFICATIONOUTPUT_HPP

namespace RadonFramework::Core::Types
{
class String;
}

namespace RadonFramework::Diagnostics::Test::BDD
{
class SpecificationOutput
{
public:
  virtual void WriteText(const Core::Types::String& Text) const = 0;
  virtual void WriteError(const Core::Types::String& Text) const = 0;
  virtual void WriteSuccess(const Core::Types::String& Text) const = 0;
  virtual void WriteFailure(const Core::Types::String& Text) const = 0;
  virtual void WritePending(const Core::Types::String& Text) const = 0;
  virtual void WriteSkipped(const Core::Types::String& Text) const = 0;
  virtual void WriteStats(const Core::Types::String& Text) const = 0;
};

}  // namespace RadonFramework::Diagnostics::Test::BDD

#ifndef RF_SHORTHAND_NAMESPACE_BDD
#define RF_SHORTHAND_NAMESPACE_BDD
namespace RF_BDD = RadonFramework::Diagnostics::Test::BDD;
#endif

#endif  //! RF_DIAGNOSTICS_TEST_BDD_SPECIFICATIONOUTPUT_HPP