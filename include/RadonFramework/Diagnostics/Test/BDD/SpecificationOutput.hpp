#ifndef RF_DIAGNOSTICS_TEST_BDD_SPECIFICATIONOUTPUT_HPP
#define RF_DIAGNOSTICS_TEST_BDD_SPECIFICATIONOUTPUT_HPP

namespace RadonFramework::Diagnostics::Test::BDD {

class SpecificationOutput
{
public:
	virtual void WriteText(const RF_Type::String& Text)const = 0;
	virtual void WriteError(const RF_Type::String& Text)const = 0;
	virtual void WriteSuccess(const RF_Type::String& Text)const = 0;
	virtual void WriteFailure(const RF_Type::String& Text)const = 0;
	virtual void WritePending(const RF_Type::String& Text)const = 0;
	virtual void WriteSkipped(const RF_Type::String& Text)const = 0;
	virtual void WriteStats(const RF_Type::String& Text)const = 0;
};

}

#ifndef RF_SHORTHAND_NAMESPACE_BDD
#define RF_SHORTHAND_NAMESPACE_BDD
namespace RF_BDD = RadonFramework::Diagnostics::Test::BDD;
#endif

#endif //!RF_DIAGNOSTICS_TEST_BDD_SPECIFICATIONOUTPUT_HPP