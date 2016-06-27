#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Text/StringBuilder.hpp>

using namespace RadonFramework::Text;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Memory;

class StringBuilderTest:public TestSuite
{
public:
    StringBuilderTest()
    :TestSuite("RadonFramework::Core::Types::StringBuilder-Test"_rfs)
    {
        AddTest(MakeDelegate(this,&StringBuilderTest::DefaultConstructor),
            "StringBuilderTest::DefaultConstructor"_rfs, "StringBuilderDefaultConstructor"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::Destructor),
            "StringBuilderTest::Destructor"_rfs, "StringBuilderDestructor"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::AppendFormat),
            "StringBuilderTest::AppendFormat"_rfs, "StringBuilderAppendformat"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::AppendLine),
            "StringBuilderTest::AppendLine"_rfs, "StringBuilderAppendLine"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::Append),
            "StringBuilderTest::Append"_rfs, "StringBuilderAppend"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::Clear),
            "StringBuilderTest::Clear"_rfs, "StringBuilderClear"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::EnsureCapacity),
            "StringBuilderTest::EnsureCapacity"_rfs, "StringBuilderEnsureCapacity"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::Insert),
            "StringBuilderTest::Insert"_rfs, "StringBuilderInsert"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::Remove),
            "StringBuilderTest::Remove"_rfs, "StringBuilderRemove"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::Replace),
            "StringBuilderTest::Replace"_rfs, "StringBuilderReplace"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::Length),
            "StringBuilderTest::Length"_rfs, "StringBuilderLength"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::Size),
            "StringBuilderTest::Size"_rfs, "StringBuilderSize"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::Capacity),
            "StringBuilderTest::Capacity"_rfs, "StringBuilderCapacity"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::AsCString),
            "StringBuilderTest::AsCString"_rfs, "StringBuilderAsCString"_rfs);
        AddTest(MakeDelegate(this,&StringBuilderTest::ToString),
            "StringBuilderTest::ToString"_rfs, "StringBuilderToString"_rfs);
    }

    RF_Type::Bool DefaultConstructor()
    {
        StringBuilder builder;
        return builder.AsCString() == 0 && builder.Length() == 0 && 
            builder.Size() == 0 && builder.Capacity() == 0;
    }

    RF_Type::Bool Destructor()
    {
        StringBuilder builder;
        builder.~StringBuilder();
        return builder.AsCString() == 0 && builder.Length() == 0 && 
            builder.Size() == 0 && builder.Capacity() == 0;
    }

    RF_Type::Bool AppendFormat()
    {
        StringBuilder builder;
        builder.AppendFormat("Hello %s!"_rfs, "World"_rfs);
        return builder.Length() == 12 && builder.Size() == 13 &&
            builder.Capacity() >= 13 && builder.AsCString() != 0;
    }

    RF_Type::Bool AppendLine()
    {
        StringBuilder builder;
        builder.AppendLine();
        return builder.Length() == 0 && builder.Size() == 1 &&
            builder.Capacity() >= 1 && builder.AsCString() != 0 &&
            builder.AsCString()[0] == '\0';
    }

    RF_Type::Bool Append()
    {
        StringBuilder builder;
        builder.Append("Hi"_rfs);
        return builder.Length() == 2 && builder.Size() == 3 &&
            builder.Capacity() >= 3 && builder.AsCString() != 0 &&
            builder.AsCString()[0] == 'H' && builder.AsCString()[1] == 'i' &&
            builder.AsCString()[2] == '\0';
    }

    RF_Type::Bool Clear()
    {
        StringBuilder builder;
        builder.Append("test"_rfs);
        RF_Type::Size capacity = builder.Capacity();
        builder.Clear();
        return builder.Capacity() == capacity && builder.Size() == 0 &&
            builder.Length() == 0;
    }

    RF_Type::Bool EnsureCapacity()
    {
        StringBuilder builder;
        builder.EnsureCapacity(1024);
        return builder.Capacity() >= 1024;
    }

    RF_Type::Bool Insert()
    {
        StringBuilder builder;
        builder.Insert("Hello !"_rfs,0);
        builder.Insert("World"_rfs, 6);
        return builder.Length() == 12 && builder.Size() == 13 &&
            builder.Capacity() >= 13 && builder.AsCString()[6] == 'W' &&
            builder.AsCString()[11] == '!';
    }

    RF_Type::Bool Remove()
    {
        StringBuilder builder;
        builder.Append("Hello World!"_rfs);
        builder.Remove(6, 5);
        return builder.Length() == 7 && builder.Size() == 8 &&
            builder.Capacity() >= 8 && builder.AsCString()[6] == '!';
    }

    RF_Type::Bool Replace()
    {
        StringBuilder builder;
        builder.Append("Hello W!"_rfs);
        builder.Replace("W"_rfs, "World"_rfs);
        return builder.Length() == 12 && builder.Size() == 13 &&
            builder.Capacity() >= 13 && builder.AsCString()[7] == 'o';
    }

    RF_Type::Bool Length()
    {
        StringBuilder builder;
        builder.Append("Hi"_rfs);
        return builder.Length() == 2;
    }

    RF_Type::Bool Size()
    {
        StringBuilder builder;
        builder.Append("Hi"_rfs);
        return builder.Size() == 3;
    }

    RF_Type::Bool Capacity()
    {
        StringBuilder builder;
        builder.EnsureCapacity(1024);
        return builder.Capacity() >= 1024;
    }

    RF_Type::Bool AsCString()
    {
        StringBuilder builder;
        builder.Append("Hi"_rfs);
        return builder.AsCString()[0] == 'H' && builder.AsCString()[1] == 'i';
    }

    RF_Type::Bool ToString()
    {
        StringBuilder builder;
        builder.Append("hi"_rfs);
        auto result = builder.ToString();
        return result->Size() == 3 && result->Length() == 2;
    }
};

StringBuilderTest StringBuilderTestInstance;