#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/IO/File.hpp>
#include "RadonFramework/Core/Common/DataManagment.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"
#include "RadonFramework/Time/ScopeTimer.hpp"
#include "RadonFramework/Core/Types/StringUtils/StringProcessor.hpp"
#include "RadonFramework/Core/Policies/StringProcessor/BruteForce.hpp"
#include "RadonFramework/Core/Policies/StringProcessor/Horspool.hpp"
#include "RadonFramework/Core/Policies/StringProcessor/KnuthMorrisPratt.hpp"
#include "RadonFramework/Core/Policies/StringProcessor/ShiftAnd.hpp"
#include "RadonFramework/Core/Policies/StringProcessor/SkipSearch.hpp"
#include "RadonFramework/Core/Policies/StringProcessor/Sunday.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Common;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Memory;
using namespace RadonFramework::IO;
using namespace RadonFramework::Time;
using namespace RadonFramework::Core::Policies::StringProcessor;

const char* LONGERTEXT=
    "The term ‘research’ has been viewed with mystique by many people. \
    It is seen to be the preserve of academicians and professional \
    elite. In most people’s minds, the word ‘research’ conjures up the \
    image of a scholar, laboratory work, university or other ‘academic’ \
    setting. But research is simply the process of asking questions and \
    answering them by survey or experiment in an organized way. It \
    should not be confined to academicians alone. Every thinking person \
    has the capacity and should do research. The fundamental \
    requirement for research is an enquiring mind in order to recognize \
    that there are questions that need answers. The quest for knowledge \
    then is the basic idea behind research.\
    \
    The acquisition of knowledge is a continuous process from birth; an \
    individual exploring the environment and asking questions. \
    Information is provided by parents, associates and teachers. It is \
    supplemented by books, magazines, newspaper, journals and the \
    media. As an individual’s knowledge increases, questions become \
    more complex and answers are sought from experts, reference books \
    and specialized journals. Research is the examination of these \
    limits of knowledge; assessing what is known up to that point, \
    defining unanswered questions and devising ways of answering them \
    in an organized and meaningful way.\
    \
    Research has been defined differently by different people. It is \
    perhaps best understood through a clear description of its key \
    characteristics. A few definitions are presented below followed by \
    the key characteristics. Research is a systematic, formal, rigorous \
    and precise process employed to gain solutions to problems or to \
    discover and interpret new facts and relationships. \
    (Waltz and Bausell, 1981). Research is the process of looking for \
    a specific answer to a specific question in an organized, \
    objective, reliable way. (Payton, 1979).\
    \
    Research is systematic, controlled, empirical and critical \
    investigation of hypothetical propositions about the presumed \
    relations among natural phenomena. (Kerlinger, 1973). Research is \
    the pursuit of truth with the help of study, observation, \
    comparison and experiment; the search for knowledge through \
    objective and systematic method of finding solutions to a problem \
    (Kothari, 2006).\
    \
    When these definitions are consolidated, it can be said that \
    research is the systematic activity directed towards objectively \
    investigating specific problems in order to discover the \
    relationships between and among variables. It seeks to answer \
    specific questions.";

class StringProcessorTest:public TestSuite
{
public:
    String txt;

    StringProcessorTest()
    :TestSuite("RadonFramework::Core::Types::StringUtils")
    {
        txt=String(LONGERTEXT, DataManagment::UnmanagedInstance);
        AddTest(MakeDelegate(this,&StringProcessorTest::DoBruteforce),"StringProcessorTest::DoBruteforce", "Bruteforce search");
        AddTest(MakeDelegate(this,&StringProcessorTest::DoHorspool),"StringProcessorTest::DoHorspool", "Horspool search");
        AddTest(MakeDelegate(this,&StringProcessorTest::DoKnuthMorrisPratt), "StringProcessorTest::DoKnuthMorrisPratt", "KnuthMorrisPratt search");
        AddTest(MakeDelegate(this,&StringProcessorTest::DoShiftAnd), "StringProcessorTest::DoShiftAnd", "ShiftAnd search");
        AddTest(MakeDelegate(this,&StringProcessorTest::DoSkipSearch), "StringProcessorTest::DoSkipSearch", "SkipSearch search");
        AddTest(MakeDelegate(this,&StringProcessorTest::DoSunday), "StringProcessorTest::DoSunday", "Sunday search");
    }

    Bool DoBruteforce()
    {
        Int32 count;
        StringProcessor<BruteForce> proc;
        proc.Storage().Search="knowledge";
        proc.Init(txt,0,false);
        count=proc.DoAll();//5 matches
        return true;
    }

    Bool DoHorspool()
    {
        Int32 count;
        StringProcessor<Horspool> proc;
        proc.Storage().Search="knowledge";
        proc.Init(txt,0,false);
        count=proc.DoAll();//5 matches
        return true;
    }

    Bool DoKnuthMorrisPratt()
    {
        Int32 count;
        StringProcessor<KnuthMorrisPratt> proc;
        proc.Storage().Search="knowledge";
        proc.Init(txt,0,false);
        count=proc.DoAll();//5 matches
        return true;
    }

    Bool DoShiftAnd()
    {
        Int32 count;
        StringProcessor<ShiftAnd> proc;
        proc.Storage().Search="knowledge";
        proc.Init(txt,0,false);
        count=proc.DoAll();//5 matches
        return true;
    }

    Bool DoSkipSearch()
    {
        Int32 count;
        StringProcessor<SkipSearch> proc;
        proc.Storage().Search="knowledge";
        proc.Init(txt,0,false);
        count=proc.DoAll();//5 matches
        return true;
    }

    Bool DoSunday()
    {
        Int32 count;
        StringProcessor<Sunday> proc;
        proc.Storage().Search="knowledge";
        proc.Init(txt,0,false);
        count=proc.DoAll();//5 matches
        return true;
    }
};

StringProcessorTest StringProcessorTestInstance;