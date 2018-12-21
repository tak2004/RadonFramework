#include "RadonFramework/Diagnostics/Test/BDD/Specification.hpp"
#include "RadonFramework/Collections/Algorithm/ForEach.hpp"
#include "RadonFramework/Collections/List.hpp"
#include "RadonFramework/IO/Log.hpp"
#include "RadonFramework/Math/Hash/Hash32.hpp"
#include "RadonFramework/Text/Tokenizer.hpp"
#include "RadonFramework/precompiled.hpp"

namespace RadonFramework::Diagnostics::Test::BDD
{
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

  RF_Type::Bool IsSyntaxCorrect() const;
  const RF_Collect::List<RF_Type::Size>& GetVariableOffsets() const;
  const RF_Collect::List<RF_Type::String>& GetFunctionNames() const;
  const RF_Collect::List<TestCase>& GetTestCases() const;

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

  void ParseGerkin();
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

  for(; m_Cursor < m_Text->Length(); ++m_Cursor)
  {
    if(!CheckVariableStart() || !CheckVariableEnd() || !CheckFunction() ||
       !CheckLineContext())
    {
      break;
    }
  }

  if(m_IsSyntaxCorrect)
  {
    m_Text = nullptr;
    result = true;
  }
  else
  {  // Syntax error: make a local copy of the text to avoid access violation
    m_Text = &m_TextCopy;
    m_TextCopy = Text;
  }
  return result;
}

RF_Type::Bool SpecificationParser::IsSyntaxCorrect() const
{
  return m_IsSyntaxCorrect;
}

const RF_Collect::List<RF_Type::Size>&
SpecificationParser::GetVariableOffsets() const
{
  return m_VariableOffsets;
}

const RF_Collect::List<RF_Type::String>&
SpecificationParser::GetFunctionNames() const
{
  return m_FunctionNames;
}

const RF_Collect::List<RadonFramework::Diagnostics::Test::BDD::TestCase>&
SpecificationParser::GetTestCases() const
{
  return m_TestCases;
}

class FeatureLine : public RF_Text::Token
{
public:
  RF_Type::Size Start;
  RF_Type::Size Count;

  virtual void Print() { RF_IO::LogInfo("Featureline: %llu %llu", Start, Count); }
  static RF_Type::UInt16 ID;
};

RF_Type::UInt16 FeatureLine::ID = 1111;

class FeatureLineRule : public RF_Text::Visitor
{
public:
  virtual RF_Type::Bool Visit(const TokenNode& AToken) override
  {
    if(AToken.Data() && AToken.Data()->Type == RF_Text::CodePart::ID)
    {
      auto* code = reinterpret_cast<RF_Text::CodePart*>(AToken.Data().Get());
      RF_Type::String codeview(
          reinterpret_cast<char*>(Code->Get() + code->Start), code->Count,
          RF_Core::DataManagment::UnmanagedInstance);
      if(codeview.StartsWith(Name))
      {
        auto newToken = RF_Mem::AutoPointer<FeatureLine>(new FeatureLine);
        newToken->Start = code->Start;
        newToken->Count = code->Count;
        newToken->Type = FeatureLine::ID;
        ReplaceToken(AToken, RF_Mem::AutoPointer<RF_Text::Token>(newToken));
      }
    }
    return true;
  }

  RF_Type::String Name;
};

class ScenarioLine : public RF_Text::Token
{
public:
  RF_Type::Size Start;
  RF_Type::Size Count;

  virtual void Print() { RF_IO::LogInfo("Scenario: %llu %llu", Start, Count); }
  static RF_Type::UInt16 ID;
};

RF_Type::UInt16 ScenarioLine::ID = 1112;

class ScenarioLineRule : public RF_Text::Visitor
{
public:
  virtual RF_Type::Bool Visit(const TokenNode& AToken) override
  {
    if(AToken.Data() && AToken.Data()->Type == RF_Text::CodePart::ID)
    {
      auto* code = reinterpret_cast<RF_Text::CodePart*>(AToken.Data().Get());
      RF_Type::String codeview(
          reinterpret_cast<char*>(Code->Get() + code->Start), code->Count,
          RF_Core::DataManagment::UnmanagedInstance);
      if(codeview.StartsWith(Name))
      {
        auto newToken = RF_Mem::AutoPointer<ScenarioLine>(new ScenarioLine);
        newToken->Start = code->Start;
        newToken->Count = code->Count;
        newToken->Type = ScenarioLine::ID;
        ReplaceToken(AToken, RF_Mem::AutoPointer<RF_Text::Token>(newToken));
      }
    }
    return true;
  }

  RF_Type::String Name;
};

class ScenarioOutline : public RF_Text::Token
{
public:
  RF_Type::Size Start;
  RF_Type::Size Count;

  virtual void Print()
  {
    RF_IO::LogInfo("Scenario outline: %llu %llu", Start, Count);
  }
  static RF_Type::UInt16 ID;
};

RF_Type::UInt16 ScenarioOutline::ID = 1113;

class ScenarioOutlineRule : public RF_Text::Visitor
{
public:
  virtual RF_Type::Bool Visit(const TokenNode& AToken) override
  {
    if(AToken.Data() && AToken.Data()->Type == RF_Text::CodePart::ID)
    {
      auto* code = reinterpret_cast<RF_Text::CodePart*>(AToken.Data().Get());
      RF_Type::String codeview(
          reinterpret_cast<char*>(Code->Get() + code->Start), code->Count,
          RF_Core::DataManagment::UnmanagedInstance);
      if(codeview.StartsWith(Name))
      {
        auto newToken =
            RF_Mem::AutoPointer<ScenarioOutline>(new ScenarioOutline);
        newToken->Start = code->Start;
        newToken->Count = code->Count;
        newToken->Type = ScenarioOutline::ID;
        ReplaceToken(AToken, RF_Mem::AutoPointer<RF_Text::Token>(newToken));
      }
    }
    return true;
  }

  RF_Type::String Name;
};

class ExampleRule : public RF_Text::Visitor
{
public:
  virtual RF_Type::Bool Visit(const TokenNode& AToken) override
  {
    return false;
  }
};

class Background : public RF_Text::Token
{
public:
  RF_Type::Size Start;
  RF_Type::Size Count;

  virtual void Print()
  {
    RF_IO::LogInfo("Background: %llu %llu", Start, Count);
  }
  static RF_Type::UInt16 ID;
};

RF_Type::UInt16 Background::ID = 1114;

class BackgroundRule : public RF_Text::Visitor
{
public:
  virtual RF_Type::Bool Visit(const TokenNode& AToken) override
  {
    if(AToken.Data() && AToken.Data()->Type == RF_Text::CodePart::ID)
    {
      auto* code = reinterpret_cast<RF_Text::CodePart*>(AToken.Data().Get());
      RF_Type::String codeview(
          reinterpret_cast<char*>(Code->Get() + code->Start), code->Count,
          RF_Core::DataManagment::UnmanagedInstance);
      if(codeview == Name)
      {
        auto newToken = RF_Mem::AutoPointer<Background>(new Background);
        newToken->Start = code->Start;
        newToken->Count = code->Count;
        newToken->Type = Background::ID;
        ReplaceToken(AToken, RF_Mem::AutoPointer<RF_Text::Token>(newToken));
      }
    }
    return true;
  }

  RF_Type::String Name;
};

class Step : public RF_Text::Token
{
public:
  RF_Type::Size Start;
  RF_Type::Size Count;

  virtual void Print() { RF_IO::LogInfo("Step: %llu %llu", Start, Count); }
  static RF_Type::UInt16 ID;
};

RF_Type::UInt16 Step::ID = 1116;

class StepRule : public RF_Text::Visitor
{
public:
  virtual RF_Type::Bool Visit(const TokenNode& AToken) override
  {
    if(AToken.Data() && AToken.Data()->Type == RF_Text::CodePart::ID)
    {
      auto* code = reinterpret_cast<RF_Text::CodePart*>(AToken.Data().Get());
      RF_Type::String codeview(
          reinterpret_cast<char*>(Code->Get() + code->Start), code->Count,
          RF_Core::DataManagment::UnmanagedInstance);
      RF_Type::Size indent = 0;
      for(; indent < codeview.Length(); indent++)
      {
        if(codeview[indent] != ' ' && codeview[indent] != '\t')
        {
          break;
        }
      }
      if(codeview.IndexOf(Given, indent, Given.Length()) < code->Count ||
         codeview.IndexOf(When, indent, When.Length()) < code->Count ||
         codeview.IndexOf(Then, indent, Then.Length()) < code->Count ||
         codeview.IndexOf(Or, indent, Or.Length()) < code->Count ||
         codeview.IndexOf(And, indent, And.Length()) < code->Count ||
         codeview.IndexOf(But, indent, But.Length()) < code->Count)
      {
        auto newToken = RF_Mem::AutoPointer<Step>(new Step);
        newToken->Start = code->Start;
        newToken->Count = code->Count;
        newToken->Type = Step::ID;
        ReplaceToken(AToken, RF_Mem::AutoPointer<RF_Text::Token>(newToken));
      }
    }
    return true;
  }

  RF_Type::String Given, When, Then, Or, And, But;
};

class TableRow : public RF_Text::Token
{
public:
  RF_Type::Size Start;
  RF_Type::Size Count;

  virtual void Print() { RF_IO::LogInfo("TableRow: %llu %llu", Start, Count); }
  static RF_Type::UInt16 ID;
};

RF_Type::UInt16 TableRow::ID = 1117;

class TableLineRule : public RF_Text::Visitor
{
public:
  virtual RF_Type::Bool Visit(const TokenNode& AToken) override
  {
    if(AToken.Data() && AToken.Data()->Type == RF_Text::CodePart::ID)
    {
      auto* code = reinterpret_cast<RF_Text::CodePart*>(AToken.Data().Get());
      RF_Type::String codeview(
          reinterpret_cast<char*>(Code->Get() + code->Start), code->Count,
          RF_Core::DataManagment::UnmanagedInstance);
      RF_Type::Size indent = 0;
      for(; indent < codeview.Length(); indent++)
      {
        if(codeview[indent] != ' ' && codeview[indent] != '\t')
        {
          break;
        }
      }
      if(codeview[indent] == '|')
      {
        auto newToken = RF_Mem::AutoPointer<TableRow>(new TableRow);
        newToken->Start = code->Start;
        newToken->Count = code->Count;
        newToken->Type = TableRow::ID;
        ReplaceToken(AToken, RF_Mem::AutoPointer<RF_Text::Token>(newToken));
      }
    }
    return true;
  }
};

class Tags : public RF_Text::Token
{
public:
  RF_Type::Size Start;
  RF_Type::Size Count;

  virtual void Print() { RF_IO::LogInfo("Tags: %llu %llu", Start, Count); }
  static RF_Type::UInt16 ID;
};

RF_Type::UInt16 Tags::ID = 1115;

class TagRule : public RF_Text::Visitor
{
public:
  virtual RF_Type::Bool Visit(const TokenNode& AToken) override
  {
    if(AToken.Data() && AToken.Data()->Type == RF_Text::CodePart::ID)
    {
      auto* code = reinterpret_cast<RF_Text::CodePart*>(AToken.Data().Get());
      RF_Type::String codeview(
          reinterpret_cast<char*>(Code->Get() + code->Start), code->Count,
          RF_Core::DataManagment::UnmanagedInstance);
      RF_Type::Size indent = 0;
      for(; indent < codeview.Length(); indent++)
      {
        if(codeview[indent] != ' ' && codeview[indent] != '\t')
        {
          break;
        }
      }
      if(codeview[indent] == '@')
      {
        auto tags = codeview.Split(" "_rfs);
        for(auto i = 0; i < tags.Count(); ++i)
        {
          if(!tags[i].StartsWith('@'))
          {
            return false;
          }
        }

        auto newToken = RF_Mem::AutoPointer<Tags>(new Tags);
        newToken->Start = code->Start;
        newToken->Count = code->Count;
        newToken->Type = Tags::ID;
        ReplaceToken(AToken, RF_Mem::AutoPointer<RF_Text::Token>(newToken));
      }
    }
    return true;
  }
};

class LanguageRule : public RF_Text::Visitor
{
public:
  virtual RF_Type::Bool Visit(const TokenNode& AToken) override { return true; }
};

class CommentRule : public RF_Text::Visitor
{
public:
  virtual RF_Type::Bool Visit(const TokenNode& AToken) override { return true; }
};

class Feature : public RF_Text::Token
{
public:
  virtual void Print() { RF_IO::LogInfo("Feature:"); }
  static RF_Type::UInt16 ID;
};

RF_Type::UInt16 Feature::ID = 1118;

class FeatureRule : public RF_Text::Visitor
{
public:
  virtual RF_Type::Bool Visit(const TokenNode& AToken) override
  {
    if(AToken.Data() && AToken.Data()->Type == FeatureLine::ID)
    {
      const TokenNode* tagNode = nullptr;
      if(AToken.Prev() && AToken.Prev()->Data() &&
         AToken.Prev()->Data()->Type == Tags::ID)
      {
        tagNode = AToken.Prev();
      }
      if(tagNode)
      {
        MoveTokens(AToken, *AToken.Prev(), *tagNode);
      }

      auto newToken = RF_Mem::AutoPointer<Feature>(new Feature);
      newToken->Type = Feature::ID;
      ReplaceToken(AToken, RF_Mem::AutoPointer<RF_Text::Token>(newToken));
    }
    return true;
  }

  RF_Type::String Name;
};

class RemoveClutter : public RF_Text::Visitor
{
public:
  virtual RF_Type::Bool Visit(const TokenNode& AToken) override
  {
    if(AToken.Data() && AToken.Data()->Type == RF_Text::Delimiter::ID)
    {
      if(AToken.Prev() && AToken.Prev()->Data() &&
         AToken.Prev()->Data()->Type != RF_Text::Delimiter::ID)
      {
        DeleteToken(AToken);
      }
    }
    return true;
  }
};

void SpecificationParser::ParseGerkin()
{
  RF_Text::Tokenizer tokenizer;
  tokenizer.Delimiter("\n"_rfs);

  tokenizer.AddRule(RF_Mem::AutoPointer<RF_Text::Visitor>(new RemoveClutter));

  RF_Mem::AutoPointer<FeatureLineRule> featureLine(new FeatureLineRule);
  featureLine->Name = "Feature:"_rfs;
  tokenizer.AddRule(RF_Mem::AutoPointer<RF_Text::Visitor>(featureLine));

  RF_Mem::AutoPointer<ScenarioLineRule> scenarioLine(new ScenarioLineRule);
  scenarioLine->Name = "Scenario:"_rfs;
  tokenizer.AddRule(RF_Mem::AutoPointer<RF_Text::Visitor>(scenarioLine));

  RF_Mem::AutoPointer<ScenarioOutlineRule> scenarioOutline(
      new ScenarioOutlineRule);
  scenarioOutline->Name = "Scenario Outline:"_rfs;
  tokenizer.AddRule(RF_Mem::AutoPointer<RF_Text::Visitor>(scenarioOutline));

  RF_Mem::AutoPointer<BackgroundRule> background(new BackgroundRule);
  background->Name = "Background:"_rfs;
  tokenizer.AddRule(RF_Mem::AutoPointer<RF_Text::Visitor>(background));

  tokenizer.AddRule(RF_Mem::AutoPointer<RF_Text::Visitor>(new TagRule));
  RF_Mem::AutoPointer<StepRule> step(new StepRule);
  step->When = "When "_rfs;
  step->Then = "Then "_rfs;
  step->Given = "Given "_rfs;
  step->And = "And "_rfs;
  step->But = "But "_rfs;
  tokenizer.AddRule(RF_Mem::AutoPointer<RF_Text::Visitor>(step));

  tokenizer.AddRule(RF_Mem::AutoPointer<RF_Text::Visitor>(new TableLineRule));
  tokenizer.AddRule(RF_Mem::AutoPointer<RF_Text::Visitor>(new FeatureRule));
  tokenizer.AddRule(RF_Mem::AutoPointer<RF_Text::Visitor>(new ExampleRule));
  tokenizer.AddRule(RF_Mem::AutoPointer<RF_Text::Visitor>(new LanguageRule));
  tokenizer.AddRule(RF_Mem::AutoPointer<RF_Text::Visitor>(new CommentRule));

  RF_Mem::AutoPointerArray<RF_Type::UInt8> text(m_Text->Size());
  text.Copy(m_Text->ByteData(), m_Text->Size());
  tokenizer.Process(text);
  tokenizer.Print();
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
  ParseGerkin();
}

RF_Type::Bool SpecificationParser::CheckLineContext()
{
  RF_Type::Bool result = true;
  if((*m_Text)[m_Cursor] == '\n')
  {
    m_Lineendings.AddLast(m_Cursor);
    if(m_EncounteredFunctions > 1)
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
  if((*m_Text)[m_Cursor] == '{')
  {
    if(m_IsVariableClosed)
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
  if((*m_Text)[m_Cursor] == '}')
  {
    if(!m_IsVariableClosed)
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
  if((*m_Text)[m_Cursor] == '$')
  {
    if(m_IsVariableClosed)
    {
      m_FunctionOffsets.AddLast(m_Cursor);
      RF_Type::String name;
      auto postCursor = m_Cursor + 1;
      while(postCursor != m_Text->Size() && (*m_Text)[postCursor] != ' ' &&
            (*m_Text)[postCursor] != '\n')
      {
        ++postCursor;
      }

      if(postCursor > m_Cursor)
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
: m_IsSyntaxCorrect(true)
{
  SpecificationParser parser;
  parser.ParseFromText(Rule);

  if(parser.IsSyntaxCorrect())
  {
    RF_Hash::Hash32 hashFunction;
    m_FunctionLookup.Reserve(parser.GetTestCases().Count());
    m_Functions.Resize(parser.GetTestCases().Count());
    for(auto i = 0; i < m_Functions.Count(); ++i)
    {
      m_Functions(i).Callback = nullptr;
      m_Functions(i).Name = parser.GetTestCases()[i].FunctionName;
      m_Functions(i).Parameters.Resize(
          parser.GetTestCases()[i].Parameters.Count());
      for(auto j = 0; j < parser.GetTestCases()[i].Parameters.Count(); ++j)
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
  for(auto& Entry : m_Functions)
  {
    hashFunction.FromString(Entry.Name);
    m_FunctionLookup.Add(hashFunction.GetHash(), &Entry);
  }
}

const RF_Type::Bool Specification::IsSyntaxCorrect() const
{
  return m_IsSyntaxCorrect;
}

void Specification::AddFunction(
    const RF_Type::String& Name,
    RF_Type::Bool (*Function)(const RF_Collect::Array<RF_Type::String>&))
{
  RF_Hash::Hash32 hashFunction;
  hashFunction.FromString(Name);
  void* pointer = nullptr;
  if(m_FunctionLookup.Get(hashFunction.GetHash(), pointer))
  {
    FunctionInformation* functionInformation =
        reinterpret_cast<FunctionInformation*>(pointer);
    functionInformation->Callback = Function;
  }
}

void Specification::Test() const
{
  RF_Algo::ForEach(m_Functions, [](const auto& Element) {
    if(Element->Callback(Element->Parameters))
    {
      RF_IO::LogInfo("%s: true", Element->Name.c_str());
    }
    else
    {
      RF_IO::LogError("%s: false", Element->Name.c_str());
    }
  });
}

void Specification::Generate(const SpecificationOutput& Output) const {}

}  // namespace RadonFramework::Diagnostics::Test::BDD

RadonFramework::Diagnostics::Test::BDD::Specification
operator"" _rfsp(const char* SpecificationData, size_t SpecificationLenght)
{
  RF_Type::String text(SpecificationData, SpecificationLenght);
  return RadonFramework::Diagnostics::Test::BDD::Specification(text);
}