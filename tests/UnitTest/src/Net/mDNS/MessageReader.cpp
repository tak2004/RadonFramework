#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Net/mDNS/MessageReader.hpp>

class MessageReaderTest:public RF_UnitTest::TestSuite
{
public:
    MessageReaderTest()
    :TestSuite("RadonFramework::Net::mDNS::MessageReader-Test"_rfs)
    {
        AddTest(MakeDelegate(this,&MessageReaderTest::CreateTempFile),
            "MessageReaderTest::CreateTempFile"_rfs, "CreateTempFile"_rfs);
    }

    RF_Type::Bool CreateTempFile()
    {
        RF_Type::UInt8 MSG[] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00, 0x00, 0x00,
            0x00, 0x06, 0x52, 0x6f, 0x6f, 0x6d, 0x2d, 0x31, 0x05, 0x6c, 0x6f,
            0x63, 0x61, 0x6c, 0x00, 0x00, 0x01, 0x00, 0x01, 0xc0, 0x0c, 0x00,
            0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x78, 0x00, 0x04, 0xc0, 0xa8,
            0xb2, 0x0b, 0xc0, 0x0c, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
            0x78, 0x00, 0x04, 0xa9, 0xfe, 0x4f, 0x17
        };
        auto StringCompressionAndPointer=RF_Mem::AutoPointerArray<RF_Type::UInt8>(sizeof(MSG));
        RF_SysMem::Copy(StringCompressionAndPointer.Get(), MSG, StringCompressionAndPointer.Count());

        RF_Type::Bool result = true;
        RF_mDNS::MessageReader reader;
        reader.Reset(StringCompressionAndPointer);
        result &= reader.ReadHeader();
        result &= reader.ReadQuestions();
        result &= reader.ReadAnswers();
        result &= reader.Answers().Count() == 2;
        result &= reader.Questions().Count() == 1;
        return result;
    }
};

MessageReaderTest MessageReaderTestInstance;