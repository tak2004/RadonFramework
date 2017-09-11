#ifndef RF_DIAGNOSTICS_TEST_BDD_CONSOLEOUTPUT_HPP
#define RF_DIAGNOSTICS_TEST_BDD_CONSOLEOUTPUT_HPP

#include <RadonFramework/Diagnostics/Test/BDD/SpecificationOutput.hpp>

namespace RadonFramework::Diagnostics::Test::BDD {

class ConsoleOutput :public SpecificationOutput
{
public:
	void WriteText(const RF_Type::String& Text)const override;
	void WriteError(const RF_Type::String& Text)const override;
	void WriteSuccess(const RF_Type::String& Text)const override;
	void WriteFailure(const RF_Type::String& Text)const override;
	void WritePending(const RF_Type::String& Text)const override;
	void WriteSkipped(const RF_Type::String& Text)const override;
	void WriteStats(const RF_Type::String& Text)const override;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_BDD
#define RF_SHORTHAND_NAMESPACE_BDD
namespace RF_BDD = RadonFramework::Diagnostics::Test::BDD;
#endif

#endif // !RF_DIAGNOSTICS_TEST_BDD_CONSOLEOUTPUT_HPP
