#include "RadonFramework/precompiled.hpp"
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTestResult.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/Collector.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;

void UnitTest::AddCollector( Collector& ACollector )
{
    Collector* collector=&ACollector;
	m_Collector.AddLast(collector);
}

void UnitTest::RegisterTestSuide( TestSuite* ATestSuite )
{
	m_TestSuites.AddLast(ATestSuite);
}

void UnitTest::Run()
{
	for (UInt32 i=0;i<m_TestSuites.Size();++i)
	{
        m_TestSuites[i]->SetUp();
		for (UInt32 k=0;k<m_Collector.Size();++k)
			m_Collector[k]->CreateSuite(m_TestSuites[i]->Name());

		for (UInt32 j=0;j<m_TestSuites[i]->TestCount();++j)
		{
			AutoPointer<UnitTestResult> res;
		    res=m_TestSuites[i]->ProcessTests(j);
			for (UInt32 k=0;k<m_Collector.Size();++k)
				m_Collector[k]->ProcessResult(*res);
		}	
	}
	
}
