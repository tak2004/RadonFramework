#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Core/Types/Utils/StringBuilder.hpp>

using namespace RadonFramework::Core::Types::Utils;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Memory;

class StringBuilderTest:public TestSuite
{
public:
    StringBuilderTest()
    :TestSuite("RadonFramework::Core::Types::StringBuilder-Test")
    {
        AddTest(MakeDelegate(this,&StringBuilderTest::DefaultConstructor),
            "StringBuilderTest::DefaultConstructor", "StringBuilderDefaultConstructor");
        AddTest(MakeDelegate(this,&StringBuilderTest::Destructor),
            "StringBuilderTest::Destructor", "StringBuilderDestructor");
        AddTest(MakeDelegate(this,&StringBuilderTest::AppendFormat),
            "StringBuilderTest::AppendFormat", "StringBuilderAppendformat");
        AddTest(MakeDelegate(this,&StringBuilderTest::AppendLine),
            "StringBuilderTest::AppendLine", "StringBuilderAppendLine");
        AddTest(MakeDelegate(this,&StringBuilderTest::Append),
            "StringBuilderTest::Append", "StringBuilderAppend");
        AddTest(MakeDelegate(this,&StringBuilderTest::Clear),
            "StringBuilderTest::Clear", "StringBuilderClear");
        AddTest(MakeDelegate(this,&StringBuilderTest::EnsureCapacity),
            "StringBuilderTest::EnsureCapacity", "StringBuilderEnsureCapacity");
        AddTest(MakeDelegate(this,&StringBuilderTest::Insert),
            "StringBuilderTest::Insert", "StringBuilderInsert");
        AddTest(MakeDelegate(this,&StringBuilderTest::Remove),
            "StringBuilderTest::Remove", "StringBuilderRemove");
        AddTest(MakeDelegate(this,&StringBuilderTest::Replace),
            "StringBuilderTest::Replace", "StringBuilderReplace");
        AddTest(MakeDelegate(this,&StringBuilderTest::Length),
            "StringBuilderTest::Length", "StringBuilderLength");
        AddTest(MakeDelegate(this,&StringBuilderTest::Size),
            "StringBuilderTest::Size", "StringBuilderSize");
        AddTest(MakeDelegate(this,&StringBuilderTest::Capacity),
            "StringBuilderTest::Capacity", "StringBuilderCapacity");
        AddTest(MakeDelegate(this,&StringBuilderTest::AsCString),
            "StringBuilderTest::AsCString", "StringBuilderAsCString");
        AddTest(MakeDelegate(this,&StringBuilderTest::ToString),
            "StringBuilderTest::ToString", "StringBuilderToString");
    }

    RFTYPE::Bool DefaultConstructor()
    {
        StringBuilder builder;
        return builder.AsCString() == 0 && builder.Length() == 0 && 
            builder.Size() == 0 && builder.Capacity() == 0;
    }

    RFTYPE::Bool Destructor()
    {
        StringBuilder builder;
        builder.~StringBuilder();
        return builder.AsCString() == 0 && builder.Length() == 0 && 
            builder.Size() == 0 && builder.Capacity() == 0;
    }

    RFTYPE::Bool AppendFormat()
    {
        StringBuilder builder;
        builder.AppendFormat("Hello %s!", "World");
        return builder.Length() == 12 && builder.Size() == 13 &&
            builder.Capacity() >= 13 && builder.AsCString() != 0;
    }

    RFTYPE::Bool AppendLine()
    {
        StringBuilder builder;
        builder.AppendLine();
        return builder.Length() == 0 && builder.Size() == 1 &&
            builder.Capacity() >= 1 && builder.AsCString() != 0 &&
            builder.AsCString()[0] == '\0';
    }

    RFTYPE::Bool Append()
    {
        StringBuilder builder;
        builder.Append("Hi");
        return builder.Length() == 2 && builder.Size() == 3 &&
            builder.Capacity() >= 3 && builder.AsCString() != 0 &&
            builder.AsCString()[0] == 'H' && builder.AsCString()[1] == 'i' &&
            builder.AsCString()[2] == '\0';
    }

    RFTYPE::Bool Clear()
    {
        StringBuilder builder;
        builder.Append("test");
        RFTYPE::Size capacity = builder.Capacity();
        builder.Clear();
        return builder.Capacity() == capacity && builder.Size() == 0 &&
            builder.Length() == 0;
    }

    RFTYPE::Bool EnsureCapacity()
    {
        StringBuilder builder;
        builder.EnsureCapacity(1024);
        return builder.Capacity() >= 1024;
    }

    RFTYPE::Bool Insert()
    {
        StringBuilder builder;
        builder.Insert("Hello !",0);
        builder.Insert("World", 6);
        return builder.Length() == 12 && builder.Size() == 13 &&
            builder.Capacity() >= 13 && builder.AsCString()[6] == 'W' &&
            builder.AsCString()[11] == '!';
    }

    RFTYPE::Bool Remove()
    {
        StringBuilder builder;
        builder.Append("Hello World!");
        builder.Remove(6, 5);
        return builder.Length() == 7 && builder.Size() == 8 &&
            builder.Capacity() >= 8 && builder.AsCString()[6] == '!';
    }

    RFTYPE::Bool Replace()
    {
        StringBuilder builder;
        builder.Append("Hello W!");
        builder.Replace("W", "World");
        return builder.Length() == 12 && builder.Size() == 13 &&
            builder.Capacity() >= 13 && builder.AsCString()[7] == 'o';
    }

    RFTYPE::Bool Length()
    {
        StringBuilder builder;
        builder.Append("Hi");
        return builder.Length() == 2;
    }

    RFTYPE::Bool Size()
    {
        StringBuilder builder;
        builder.Append("Hi");
        return builder.Size() == 3;
    }

    RFTYPE::Bool Capacity()
    {
        StringBuilder builder;
        builder.EnsureCapacity(1024);
        return builder.Capacity() >= 1024;
    }

    RFTYPE::Bool AsCString()
    {
        StringBuilder builder;
        builder.Append("Hi");
        return builder.AsCString()[0] == 'H' && builder.AsCString()[1] == 'i';
    }

    RFTYPE::Bool ToString()
    {
        StringBuilder builder;
        builder.Append("hi");
        auto result = builder.ToString();
        return result->Size() == 3 && result->Length() == 2;
    }
};

StringBuilderTest StringBuilderTestInstance;