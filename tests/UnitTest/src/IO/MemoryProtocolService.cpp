#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/IO/MemoryProtocolService.hpp>
#include <RadonFramework/IO/ProtocolServiceLocator.hpp>

class MemoryProtocolServiceTest:public RF_UnitTest::TestSuite
{
public:
    MemoryProtocolServiceTest()
    :TestSuite("RadonFramework::IO::MemoryProtocolService-Test"_rfs)
    {
        AddTest(MakeDelegate(this,&MemoryProtocolServiceTest::GenerateResource),
            "MemoryProtocolServiceTest::GenerateResource"_rfs, "GenerateResource"_rfs);
        AddTest(MakeDelegate(this, &MemoryProtocolServiceTest::GetResource),
            "MemoryProtocolServiceTest::GetResource"_rfs, "GetResource"_rfs);
        AddTest(MakeDelegate(this, &MemoryProtocolServiceTest::RemoveResource),
            "MemoryProtocolServiceTest::RemoveResource"_rfs, "RemoveResource"_rfs);
    }

    void SetUp()
    {
        RF_IO::ProtocolServiceLocator::Register(RF_Mem::AutoPointer<RF_IO::ProtocolService>(new RF_IO::MemoryProtocolService("mem"_rfs)));
    }

    RF_Type::Bool GenerateResource()
    {   
        RF_Type::Bool result = true;     
        auto res=RF_IO::Resource::FromUri(RF_IO::Uri("mem://1"_rfs));
        result &= res;
        if(res)
        {
            result &= res->Exists();
            result &= res->GetSize() == 0;
            result &= res->IsReadable() == false;
            result &= res->IsWriteable() == true;
            result &= res->GetStream() != 0;
        }
        return result;
    }

    RF_Type::Bool GetResource()
    {
        auto resA = RF_IO::Resource::FromUri(RF_IO::Uri("mem://1"_rfs));
        auto resB = RF_IO::Resource::FromUri(RF_IO::Uri("mem://1"_rfs));
        RF_Type::Bool result = true;
        result &= resA;
        result &= resB;
        if(result)
        {
            result &= resA->GetStream() == resB->GetStream();
        }
        return result;
    }

    RF_Type::Bool RemoveResource()
    {
        RF_Type::Bool result = true;
        {
            auto resA = RF_IO::Resource::FromUri(RF_IO::Uri("mem://1"_rfs));
            result &= resA;
        }
        auto& protocol = RF_IO::ProtocolServiceLocator::Find("mem"_rfs);
        if(!RF_IO::ProtocolServiceLocator::IsNullService(protocol))
        {
            result &= protocol.Exists(RF_IO::Uri("mem://1"_rfs)) == false;
        }
        else
        {
            result = false;
        }
        return result;
    }
};

MemoryProtocolServiceTest MemoryProtocolServiceTestInstance;