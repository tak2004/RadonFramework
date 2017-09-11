#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Test/BDD/Specification.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/Math/Hash/Hash32.hpp"
#include "RadonFramework/Collections/Algorithm/ForEach.hpp"
#include "RadonFramework/IO/Log.hpp"

namespace RadonFramework::Diagnostics::Test::BDD {

class TestCase
{
public:
	RF_Type::String FunctionName;
	RF_Collect::List<RF_Type::String> Parameters;
};

class SpecificationParser
{
public:
	RF_Type::Bool ParseFromText(const RF_Type::String& Text);

	RF_Type::Bool IsSyntaxCorrect()const;
	const RF_Collect::List<RF_Type::Size>& GetVariableOffsets()const;
	const RF_Collect::List<RF_Type::String>& GetFunctionNames()const;
	const RF_Collect::List<TestCase>& GetTestCases()const;
private:
	RF_Type::String m_TextCopy;
	const RF_Type::String* m_Text;
	RF_Type::Size m_LastHit;
	RF_Type::Size m_Cursor;
	RF_Type::Size m_EncounteredVariables;
	RF_Type::Size m_EncounteredFunctions;
	RF_Collect::List<RF_Type::Bool> m_IsTest;
	RF_Collect::List<RF_Type::Size> m_Lineendings;
	RF_Collect::List<RF_Type::Size> m_VariableOffsets;
	RF_Collect::List<RF_Type::Size> m_FunctionOffsets;
	RF_Collect::List<RF_Type::String> m_FunctionNames;
	RF_Collect::List<RF_Type::String> m_Parameters;
	RF_Collect::List<TestCase> m_TestCases;
	RF_Type::Bool m_IsVariableClosed;
	RF_Type::Bool m_IsSyntaxCorrect;

	void Init(const RF_Type::String& Text);
	RF_Type::Bool CheckLineContext();
	RF_Type::Bool CheckVariableStart();
	RF_Type::Bool CheckVariableEnd();
	RF_Type::Bool CheckFunction();
};

RF_Type::Bool SpecificationParser::ParseFromText(const RF_Type::String& Text)
{
	RF_Type::Bool result = false;

	Init(Text);

	for (; m_Cursor < m_Text->Length(); ++m_Cursor)
	{
		if (!CheckVariableStart() || !CheckVariableEnd() || !CheckFunction() ||
			!CheckLineContext())
		{
			break;
		}
	}

	if (m_IsSyntaxCorrect)
	{
		m_Text = nullptr;
		result = true;
	}
	else
	{// Syntax error: make a local copy of the text to avoid access violation
		m_Text = &m_TextCopy;
		m_TextCopy = Text;
	}
	return result;
}

RF_Type::Bool SpecificationParser::IsSyntaxCorrect() const
{
	return m_IsSyntaxCorrect;
}

const RF_Collect::List<RF_Type::Size>& SpecificationParser::GetVariableOffsets() const
{
	return m_VariableOffsets;
}

const RF_Collect::List<RF_Type::String>& SpecificationParser::GetFunctionNames() const
{
	return m_FunctionNames;
}

const RF_Collect::List<RadonFramework::Diagnostics::Test::BDD::TestCase>& SpecificationParser::GetTestCases() const
{
	return m_TestCases;
}

void SpecificationParser::Init(const RF_Type::String& Text)
{
	m_TextCopy.Clear();
	m_Text = &Text;
	m_LastHit = RF_Type::SizeMax;
	m_IsVariableClosed = true;
	m_IsSyntaxCorrect = true;
	m_Cursor = 0;
	m_EncounteredVariables = 0;
	m_EncounteredFunctions = 0;
	m_IsTest.Clear();
	m_Lineendings.Clear();
	m_VariableOffsets.Clear();
	m_FunctionNames.Clear();
	m_FunctionOffsets.Clear();
	m_Parameters.Clear();
	m_TestCases.Clear();
}

RF_Type::Bool SpecificationParser::CheckLineContext()
{
	RF_Type::Bool result = true;
	if ((*m_Text)[m_Cursor] == '\n')
	{
		m_Lineendings.AddLast(m_Cursor);
		if (m_EncounteredFunctions > 1)
		{
			result = false;
		}
		else
		{
			m_IsTest.AddLast(m_EncounteredFunctions == 1);
		}
		m_EncounteredFunctions = 0;
	}
	return result;
}

RF_Type::Bool SpecificationParser::CheckVariableStart()
{
	RF_Type::Bool result = true;
	if ((*m_Text)[m_Cursor] == '{')
	{
		if (m_IsVariableClosed)
		{
			m_IsVariableClosed = false;
			m_LastHit = m_Cursor;
		}
		else
		{
			m_IsSyntaxCorrect = false;
			result = false;
		}
	}
	return result;
}

RF_Type::Bool SpecificationParser::CheckVariableEnd()
{
	RF_Type::Bool result = true;
	if ((*m_Text)[m_Cursor] == '}')
	{
		if (!m_IsVariableClosed)
		{
			m_IsVariableClosed = true;
			m_VariableOffsets.AddLast(m_LastHit);
			auto name = m_Text->SubString(m_LastHit + 1, m_Cursor - m_LastHit - 1);
			m_Parameters.AddLast(name);
			++m_EncounteredVariables;
		}
		else
		{
			m_IsSyntaxCorrect = false;
			result = false;
		}
	}
	return result;
}

RF_Type::Bool SpecificationParser::CheckFunction()
{
	RF_Type::Bool result = true;
	if ((*m_Text)[m_Cursor] == '$')
	{
		if (m_IsVariableClosed)
		{
			m_FunctionOffsets.AddLast(m_Cursor);
			RF_Type::String name;
			auto postCursor = m_Cursor + 1;
			while (postCursor != m_Text->Size() &&
				(*m_Text)[postCursor] != ' ' &&
				(*m_Text)[postCursor] != '\n')
			{
				++postCursor;
			}

			if (postCursor > m_Cursor)
			{
				name = m_Text->SubString(m_Cursor + 1, postCursor - m_Cursor - 1);
				m_FunctionNames.AddLast(name);
				auto& entry = m_TestCases.CreateElementAtEnd();
				entry.FunctionName = name;
				entry.Parameters.AddList(m_Parameters);
				m_Parameters.Clear();
				++m_EncounteredFunctions;
			}
			else
			{
				m_IsSyntaxCorrect = false;
				result = false;
			}
		}
		else
		{
			m_IsSyntaxCorrect = false;
			result = false;
		}
	}
	return result;
}

Specification::Specification(const RF_Type::String& Rule)
:m_IsSyntaxCorrect(true)
{
	SpecificationParser parser;
	parser.ParseFromText(Rule);

	if (parser.IsSyntaxCorrect())
	{
		RF_Hash::Hash32 hashFunction;
		m_FunctionLookup.Reserve(parser.GetTestCases().Count());
		m_Functions.Resize(parser.GetTestCases().Count());
		for (auto i = 0; i < m_Functions.Count(); ++i)
		{
			m_Functions(i).Callback = nullptr;
			m_Functions(i).Name = parser.GetTestCases()[i].FunctionName;
			m_Functions(i).Parameters.Resize(parser.GetTestCases()[i].Parameters.Count());
			for (auto j = 0; j < parser.GetTestCases()[i].Parameters.Count(); ++j)
			{
				m_Functions(i).Parameters(j) = parser.GetTestCases()[i].Parameters[j];
			}
			hashFunction.FromString(m_Functions(i).Name);
			m_FunctionLookup.Add(hashFunction.GetHash(), &m_Functions(i));
		}
	}
}

Specification::Specification(const Specification& Copy)
{
	m_Functions = Copy.m_Functions;
	m_IsSyntaxCorrect = Copy.m_IsSyntaxCorrect;

	RF_Hash::Hash32 hashFunction;
	for (auto& Entry : m_Functions)
	{
		hashFunction.FromString(Entry.Name);
		m_FunctionLookup.Add(hashFunction.GetHash(), &Entry);
	}
}

const RF_Type::Bool Specification::IsSyntaxCorrect() const
{
	return m_IsSyntaxCorrect;
}

void Specification::AddFunction(const RF_Type::String& Name, 
	RF_Type::Bool(*Function)(const RF_Collect::Array<RF_Type::String>&))
{
	RF_Hash::Hash32 hashFunction;
	hashFunction.FromString(Name);
	void* pointer = nullptr;
	if (m_FunctionLookup.Get(hashFunction.GetHash(), pointer))
	{
		FunctionInformation* functionInformation = reinterpret_cast<FunctionInformation*>(pointer);
		functionInformation->Callback = Function;
	}
}

void Specification::Test() const
{
	RF_Algo::ForEach(m_Functions, [](const auto& Element)
	{
		if (Element->Callback(Element->Parameters))
		{
			RF_IO::LogInfo("%s: true", Element->Name.c_str());
		}
		else
		{
			RF_IO::LogError("%s: false", Element->Name.c_str());
		}
	});
}

void Specification::Generate(const RF_BDD::SpecificationOutput& Output) const
{

}

}

RF_BDD::Specification operator"" _rfsp(const char* SpecificationData,
	size_t SpecificationLenght)
{
	RF_Type::String text(SpecificationData, SpecificationLenght);
	return RF_BDD::Specification(text);
}