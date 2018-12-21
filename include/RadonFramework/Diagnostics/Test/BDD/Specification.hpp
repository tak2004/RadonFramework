#ifndef RF_DIAGNOSTICS_TEST_BDD_SPECIFICATION_HPP
#define RF_DIAGNOSTICS_TEST_BDD_SPECIFICATION_HPP

#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/HashList.hpp>
#include <RadonFramework/Core/Types/String.hpp>

namespace RadonFramework::Diagnostics::Test::BDD
{
class SpecificationOutput;

class Specification
{
public:
  Specification(const RF_Type::String& Rule);
  Specification(const Specification& Copy);

  void AddFunction(
      const RF_Type::String& Name,
      RF_Type::Bool (*Function)(const RF_Collect::Array<RF_Type::String>&));
  void Test() const;
  void Generate(const SpecificationOutput& Output) const;

  const RF_Type::Bool IsSyntaxCorrect() const;

private:
  class FunctionInformation
  {
  public:
    RF_Type::String Name;
    RF_Type::Bool (*Callback)(const RF_Collect::Array<RF_Type::String>&);
    RF_Collect::Array<RF_Type::String> Parameters;
  };
  RF_Collect::HashList m_FunctionLookup;
  RF_Collect::Array<FunctionInformation> m_Functions;
  RF_Type::Bool m_IsSyntaxCorrect;
};

}  // namespace RadonFramework::Diagnostics::Test::BDD

#ifndef RF_SHORTHAND_NAMESPACE_BDD
#define RF_SHORTHAND_NAMESPACE_BDD
namespace RF_BDD = RadonFramework::Diagnostics::Test::BDD;
#endif

RF_BDD::Specification
operator"" _rfsp(const char* SpecificationData, size_t SpecificationLenght);

#endif  //! RF_DIAGNOSTICS_TEST_BDD_SPECIFICATION_HPP
