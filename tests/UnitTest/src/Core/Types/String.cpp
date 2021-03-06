#include <RadonFramework/Diagnostics/Test/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Test/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <string.h>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Test::UnitTest;
using namespace RadonFramework::Memory;

class PortableStringTest:public TestSuite
{
public:
    PortableStringTest()
    :TestSuite("RadonFramework::Core::Types::String-Test"_rfs)
    {
        AddTest(MakeDelegate(this,&PortableStringTest::DefaultConstructor),
            "PortableStringTest::DefaultConstructor"_rfs, "StringDefaultConstructor"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::CopyConstructor),
            "PortableStringTest::CopyConstructor"_rfs, "StringCopyConstructor"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::LiteralConstructor),
            "PortableStringTest::LiteralConstructor"_rfs, "StringLiteralConstructor"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::CharWithLengthConstructor),
            "PortableStringTest::CharWithLengthConstructor"_rfs, "StringCharWithLengthConstructor"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::ByteSizeConstructor),
            "PortableStringTest::ByteSizeConstructor"_rfs, "StringByteSizeConstructor"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::UnsafeStringCreation),
            "PortableStringTest::UnsafeStringCreation"_rfs, "StringUnsafeStringCreation"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::Swap),
            "PortableStringTest::Swap"_rfs, "StringSwap"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::Length),
            "PortableStringTest::Length"_rfs, "StringLength"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::Contains),
            "PortableStringTest::Contains"_rfs, "StringContains"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::EndsWithPChar),
            "PortableStringTest::EndsWithPChar"_rfs, "StringEndsWithPChar"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::EndsWithString),
            "PortableStringTest::EndsWithString"_rfs, "StringEndsWithString"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::IndexOfString),
            "PortableStringTest::IndexOfString"_rfs, "StringIndexOfString"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::IndexOfChar),
            "PortableStringTest::IndexOfChar"_rfs, "StringIndexOfChar"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::IndexOfStringStart),
            "PortableStringTest::IndexOfStringStart"_rfs, "StringIndexOfStringStart"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::IndexOfCharStart),
            "PortableStringTest::IndexOfCharStart"_rfs, "StringIndexOfCharStart"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::IndexOfStringStartStop),
            "PortableStringTest::IndexOfStringStartStop"_rfs, "StringIndexOfStringStartStop"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::IndexOfCharStartStop),
            "PortableStringTest::IndexOfCharStartStop"_rfs, "StringIndexOfCharStartStop"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::InsertString),
            "PortableStringTest::InsertString"_rfs, "StringInsertString"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::InsertPChar),
            "PortableStringTest::InsertPChar"_rfs, "StringInsertPChar"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::LastIndexOfString),
            "PortableStringTest::LastIndexOfString"_rfs, "StringLastIndexOfString"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::LastIndexOfChar),
            "PortableStringTest::LastIndexOfChar"_rfs, "StringLastIndexOfChar"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::LastIndexOfStringStart),
            "PortableStringTest::LastIndexOfStringStart"_rfs, "StringLastIndexOfStringStart"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::LastIndexOfCharStart),
            "PortableStringTest::LastIndexOfCharStart"_rfs, "StringLastIndexOfCharStart"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::LastIndexOfStringStartStop),
            "PortableStringTest::LastIndexOfStringStartStop"_rfs, "StringLastIndexOfStringStartStop"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::LastIndexOfCharStartStop),
            "PortableStringTest::LastIndexOfCharStartStop"_rfs, "StringLastIndexOfCharStartStop"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::PadLeft),
            "PortableStringTest::PadLeft"_rfs, "StringPadLeft"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::PadRight),
            "PortableStringTest::PadRight"_rfs, "StringPadRight"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::Remove),
            "PortableStringTest::Remove"_rfs, "StringRemove"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::RemoveCount),
            "PortableStringTest::RemoveCount"_rfs, "StringRemoveCount"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::ReplaceChar),
            "PortableStringTest::ReplaceChar"_rfs, "StringReplaceChar"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::ReplaceString),
            "PortableStringTest::ReplaceString"_rfs, "StringReplaceString"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::SplitByPChar),
            "PortableStringTest::SplitByPChar"_rfs, "StringSplitByPChar"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::SplitByString),
            "PortableStringTest::SplitByString"_rfs, "StringSplitByString"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::StartsWith),
            "PortableStringTest::StartsWith"_rfs, "StringStartsWith"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::SubString),
            "PortableStringTest::SubString"_rfs, "StringSubString"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::Trim),
            "PortableStringTest::Trim"_rfs, "StringTrim"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::TrimEnd),
            "PortableStringTest::TrimEnd"_rfs, "StringTrimEnd"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::TrimStart),
            "PortableStringTest::TrimStart"_rfs, "StringTrimStart"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::ConstListOperator),
            "PortableStringTest::ConstListOperator"_rfs, "StringConstListOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::ReferenceListOperator),
            "PortableStringTest::ReferenceListOperator"_rfs, "StringReferenceListOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::EqualStringOperator),
            "PortableStringTest::EqualStringOperator"_rfs, "StringEqualStringOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::EqualPCharOperator),
            "PortableStringTest::EqualPCharOperator"_rfs, "StringEqualPCharOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::UnequalStringOperator),
            "PortableStringTest::UnequalStringOperator"_rfs, "StringUnequalStringOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::UnequalPCharOperator),
            "PortableStringTest::UnequalPCharOperator"_rfs, "StringUnequalPCharOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddStringOperator),
            "PortableStringTest::AddStringOperator"_rfs, "StringAddStringOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddPCharOperator),
            "PortableStringTest::AddPCharOperator"_rfs, "StringAddPCharOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddCharOperator),
            "PortableStringTest::AddCharOperator"_rfs, "StringAddCharOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddBoolOperator),
            "PortableStringTest::AddBoolOperator"_rfs, "StringAddBoolOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddInt8Operator),
            "PortableStringTest::AddInt8Operator"_rfs, "StringAddInt8Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddInt16Operator),
            "PortableStringTest::AddInt16Operator"_rfs, "StringAddInt16Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddInt32Operator),
            "PortableStringTest::AddInt32Operator"_rfs, "StringAddInt32Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddInt64Operator),
            "PortableStringTest::AddInt64Operator"_rfs, "StringAddInt64Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddUInt8Operator),
            "PortableStringTest::AddUInt8Operator"_rfs, "StringAddUInt8Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddUInt16Operator),
            "PortableStringTest::AddUInt16Operator"_rfs, "StringAddUInt16Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddUInt32Operator),
            "PortableStringTest::AddUInt32Operator"_rfs, "StringAddUInt32Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddUInt64Operator),
            "PortableStringTest::AddUInt64Operator"_rfs, "StringAddUInt64Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddAssignStringOperator),
            "PortableStringTest::AddAssignStringOperator"_rfs, "StringAddAssignStringOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddAssignPCharOperator),
            "PortableStringTest::AddAssignPCharOperator"_rfs, "StringAddAssignPCharOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddAssignCharOperator),
            "PortableStringTest::AddAssignCharOperator"_rfs, "StringAddAssignCharOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddAssignBoolOperator),
            "PortableStringTest::AddAssignBoolOperator"_rfs, "StringAddAssignBoolOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddAssignInt8Operator),
            "PortableStringTest::AddAssignInt8Operator"_rfs, "StringAddAssignInt8Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddAssignInt16Operator),
            "PortableStringTest::AddAssignInt16Operator"_rfs, "StringAddAssignInt16Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddAssignInt32Operator),
            "PortableStringTest::AddAssignInt32Operator"_rfs, "StringAddAssignInt32Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddAssignInt64Operator),
            "PortableStringTest::AddAssignInt64Operator"_rfs, "StringAddAssignInt64Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddAssignUInt8Operator),
            "PortableStringTest::AddAssignUInt8Operator"_rfs, "StringAddAssignUInt8Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddAssignUInt16Operator),
            "PortableStringTest::AddAssignUInt16Operator"_rfs, "StringAddAssignUInt16Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddAssignUInt32Operator),
            "PortableStringTest::AddAssignUInt32Operator"_rfs, "StringAddAssignUInt32Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AddAssignUInt64Operator),
            "PortableStringTest::AddAssignUInt64Operator"_rfs, "StringAddAssignUInt64Operator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::AssignStringOperator),
            "PortableStringTest::AssignStringOperator"_rfs, "StringAssignStringOperator"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::ConvertToPChar),
            "PortableStringTest::ConvertToPChar"_rfs, "StringConvertToPChar"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::HexToDec),
            "PortableStringTest::HexToDec"_rfs, "StringHexToDec"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::ToUpper),
            "PortableStringTest::ToUpper"_rfs, "StringToUpper"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::ToLower),
            "PortableStringTest::ToLower"_rfs, "StringToLower"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::Compare),
            "PortableStringTest::Compare"_rfs, "StringCompare"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::IsNumber),
            "PortableStringTest::IsNumber"_rfs, "StringIsNumber"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::IsFloatingpointNumber),
            "PortableStringTest::IsFloatingpointNumber"_rfs, "StringIsFloatingpointNumber"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::IsBoolean),
            "PortableStringTest::IsBoolean"_rfs, "StringIsBoolean"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::Size),
            "PortableStringTest::Size"_rfs, "StringSize"_rfs);
        AddTest(MakeDelegate(this,&PortableStringTest::IsEmpty),
            "PortableStringTest::IsEmpty"_rfs, "IsEmpty"_rfs);
    }

    RadonFramework::Core::Types::Bool DefaultConstructor()
    {
        String str;
        return str.Length()==0;
    }

    RadonFramework::Core::Types::Bool LiteralConstructor()
    {
        String str("hi");
        String str1("This is a very long text which don't fit into the locale buffer.");
        return str.Length()==2 && str[0]=='h' && str[1]=='i' && str.Size() == 3 &&
            str1.Length() == 64 && str1.Size() == 65;
    }

    RadonFramework::Core::Types::Bool CopyConstructor()
    {
        String unmanagedStr("This is a very long text which don't fit into the locale buffer.");
        RF_Type::Size bytes = 32;
        String dynamicStr(bytes);
        String localeStr("",3);
            
        String testStr1(dynamicStr);
        String testStr2(localeStr);
        String testStr3(unmanagedStr);

        return testStr1.Length() == 31 && testStr1[0] == ' ' &&
            testStr1.Size() == 32 && 
            testStr2.Length() == 0 && testStr2.Size() == 0 &&
            testStr3.Length() == 64 && testStr3.Size() == 65;
    }

    RadonFramework::Core::Types::Bool CharWithLengthConstructor()
    {
        char* str1="hiho";
        String str(str1,2);
        String str2(str1,5);
        return str.Length() == 2 && str.Size() == 3 && str2.Length() == 4 &&
            str2.Size() == 5 && str2[0] == 'h' && str2[1] == 'i' && 
            str2[2] == 'h' && str2[3] == 'o' && str1[0] == 'h' && str1[1] == 'i';
    }

    RadonFramework::Core::Types::Bool ByteSizeConstructor()
    {
        RF_Type::Size bytes = 3;
        String str(bytes);
        String str1("  ");
        RF_Type::Size dynamicByteSize = 33;
        String str2(dynamicByteSize);
        return str.Length() == 2 && str == str1 && str.Size() == bytes &&
            str2.Length() == 32 && str2.Size() == 33;
    }

    RadonFramework::Core::Types::Bool UnsafeStringCreation()
    {
        String str=String::UnsafeStringCreation("hiho");
        return str.Length() == 4 && str[0] == 'h' && str[1] == 'i' &&
            str[2] == 'h' && str[3] == 'o';
    }

    RadonFramework::Core::Types::Bool Swap()
    {
        String str("hiho");
        String unmanagedStr("This is a very long text which don't fit into the locale buffer.");
        String str1;
        RF_Type::Size bytes = 32;
        String str2(bytes);

        str1.Swap(str);
        return str1.Length() == 4 && str1[0] == 'h' && str1[1] == 'i' && 
            str1[2] == 'h' && str1[3] == 'o' && str.Length() == 0 &&
            str.Size() == 0;
    }

    RadonFramework::Core::Types::Bool Length()
    {
        String str("test");
        return str.Length()==4;
    }

    RadonFramework::Core::Types::Bool Contains()
    {
        String str("test");
        String str1("test");
        String str2("tset");
        String str3("123test456");
        RadonFramework::Core::Types::Int32 res=str.Contains(str1);
        RadonFramework::Core::Types::Int32 res1=str.Contains(str2);
        RadonFramework::Core::Types::Int32 res2=str3.Contains(str);
        return res==0 && res1==-1 && res2==3;
    }

    RadonFramework::Core::Types::Bool EndsWithPChar()
    {
        String str("123test456");
        return str.EndsWith("456"_rfs)==true && str.EndsWith("45"_rfs)==false;
    }

    RadonFramework::Core::Types::Bool EndsWithString()
    {
        String str("123test456");
        String str1("456");
        String str2("45");
        return str.EndsWith(str1)==true && str.EndsWith(str2)==false;
    }

    RadonFramework::Core::Types::Bool IndexOfString()
    {
        String str("test");
        String str1("test");
        String str2("tset");
        String str3("123testtest456");
        RadonFramework::Core::Types::Int32 res=str.IndexOf(str1);
        RadonFramework::Core::Types::Int32 res1=str.IndexOf(str2);
        RadonFramework::Core::Types::Int32 res2=str3.IndexOf(str);
        return res==0 && res1==-1 && res2==3;
    }

    RadonFramework::Core::Types::Bool IndexOfChar()
    {
        String str("test");
        String str3("123testtest456");
        RadonFramework::Core::Types::Int32 res=str.IndexOf("test"_rfs);
        RadonFramework::Core::Types::Int32 res1=str.IndexOf("tset"_rfs);
        RadonFramework::Core::Types::Int32 res2=str3.IndexOf("test"_rfs);
        return res==0 && res1==-1 && res2==3;
    }

    RadonFramework::Core::Types::Bool IndexOfStringStart()
    {
        String str("1test");
        String str1("test");
        String str2("tset");
        String str3("123testtest456");
        RadonFramework::Core::Types::Int32 res=str.IndexOf(str1,1);
        RadonFramework::Core::Types::Int32 res1=str.IndexOf(str2,1);
        RadonFramework::Core::Types::Int32 res2=str3.IndexOf(str1,2);
        RadonFramework::Core::Types::Int32 res3=str3.IndexOf(str1,8);
        return res==1 && res1==-1 && res2==3 && res3==-1;
    }

    RadonFramework::Core::Types::Bool IndexOfCharStart()
    {
        String str("1test");
        String str3("123testtest456");
        RadonFramework::Core::Types::Int32 res=str.IndexOf("test"_rfs,1);
        RadonFramework::Core::Types::Int32 res1=str.IndexOf("tset"_rfs,1);
        RadonFramework::Core::Types::Int32 res2=str3.IndexOf("test"_rfs,2);
        RadonFramework::Core::Types::Int32 res3=str3.IndexOf("test"_rfs,8);
        return res==1 && res1==-1 && res2==3 && res3==-1;
    }

    RadonFramework::Core::Types::Bool IndexOfStringStartStop()
    {
        String str("1test1");
        String str1("test");
        String str2("tset");
        String str3("123testtest456");
        RadonFramework::Core::Types::Int32 res=str.IndexOf(str1,1,4);
        RadonFramework::Core::Types::Int32 res1=str.IndexOf(str2,1,4);
        RadonFramework::Core::Types::Int32 res2=str3.IndexOf(str1,3,4);
        RadonFramework::Core::Types::Int32 res3=str3.IndexOf(str1,3,3);
        return res==1 && res1==-1 && res2==3 && res3==-1;
    }

    RadonFramework::Core::Types::Bool IndexOfCharStartStop()
    {
        String str("1test1");
        String str3("123testtest456");
        RadonFramework::Core::Types::Int32 res=str.IndexOf("test"_rfs,1,4);
        RadonFramework::Core::Types::Int32 res1=str.IndexOf("tset"_rfs,1,4);
        RadonFramework::Core::Types::Int32 res2=str3.IndexOf("test"_rfs,3,4);
        RadonFramework::Core::Types::Int32 res3=str3.IndexOf("test"_rfs,3,3);
        return res==1 && res1==-1 && res2==3 && res3==-1;
    }

    RadonFramework::Core::Types::Bool InsertString()
    {
        String str("test");
        String str1("123test456");
        String str2("test123456");
        String str3("123456");
        String str4("123456test");
        Bool result1 = str3.Insert(3,str)==str1;
        Bool result2 = str3.Insert(0,str)==str2;
        Bool result3 = str3.Insert(6,str)==str4;
        return result1 && result2 && result3;
    }

    RadonFramework::Core::Types::Bool InsertPChar()
    {
        String str1("123test456");
        String str2("test123456");
        String str3("123456");
        String str4("123456test");
        Bool result1 = str3.Insert(3,"test"_rfs)==str1;
        Bool result2 = str3.Insert(0,"test"_rfs)==str2;
        Bool result3 = str3.Insert(6,"test"_rfs)==str4;
        return result1 && result2 && result3;
    }

    RadonFramework::Core::Types::Bool LastIndexOfString()
    {
        String str("test");
        String str1("test");
        String str2("tset");
        String str3("123testtest456");
        RadonFramework::Core::Types::Int32 res=str.LastIndexOf(str1);
        RadonFramework::Core::Types::Int32 res1=str.LastIndexOf(str2);
        RadonFramework::Core::Types::Int32 res2=str3.LastIndexOf(str);
        return res==0 && res1==-1 && res2==7;
    }

    RadonFramework::Core::Types::Bool LastIndexOfChar()
    {
        String str("test");
        String str3("123testtest456");
        RadonFramework::Core::Types::Int32 res=str.LastIndexOf("test"_rfs);
        RadonFramework::Core::Types::Int32 res1=str.LastIndexOf("tset"_rfs);
        RadonFramework::Core::Types::Int32 res2=str3.LastIndexOf("test"_rfs);
        return res==0 && res1==-1 && res2==7;
    }

    RadonFramework::Core::Types::Bool LastIndexOfStringStart()
    {
        String str("1test");
        String str1("test");
        String str2("tset");
        String str3("123testtest456");
        RadonFramework::Core::Types::Int32 res=str.LastIndexOf(str1,1);
        RadonFramework::Core::Types::Int32 res1=str.LastIndexOf(str2,1);
        RadonFramework::Core::Types::Int32 res2=str3.LastIndexOf(str1,2);
        RadonFramework::Core::Types::Int32 res3=str3.LastIndexOf(str1,8);
        return res==1 && res1==-1 && res2==7 && res3==-1;
    }

    RadonFramework::Core::Types::Bool LastIndexOfCharStart()
    {
        String str("1test");
        String str3("123testtest456");
        RadonFramework::Core::Types::Int32 res=str.LastIndexOf("test"_rfs,1);
        RadonFramework::Core::Types::Int32 res1=str.LastIndexOf("tset"_rfs,1);
        RadonFramework::Core::Types::Int32 res2=str3.LastIndexOf("test"_rfs,2);
        RadonFramework::Core::Types::Int32 res3=str3.LastIndexOf("test"_rfs,8);
        return res==1 && res1==-1 && res2==7 && res3==-1;
    }

    RadonFramework::Core::Types::Bool LastIndexOfStringStartStop()
    {
        String str("1test1");
        String str1("test");
        String str2("tset");
        String str3("123testtest456");
        RadonFramework::Core::Types::Int32 res=str.LastIndexOf(str1,1,4);
        RadonFramework::Core::Types::Int32 res1=str.LastIndexOf(str2,1,4);
        RadonFramework::Core::Types::Int32 res2=str3.LastIndexOf(str1,7,4);
        RadonFramework::Core::Types::Int32 res3=str3.LastIndexOf(str1,3,3);
        return res==1 && res1==-1 && res2==7 && res3==-1;
    }

    RadonFramework::Core::Types::Bool LastIndexOfCharStartStop()
    {
        String str("1test1");
        String str3("123testtest456");
        RadonFramework::Core::Types::Int32 res=str.LastIndexOf("test"_rfs,1,4);
        RadonFramework::Core::Types::Int32 res1=str.LastIndexOf("tset"_rfs,1,4);
        RadonFramework::Core::Types::Int32 res2=str3.LastIndexOf("test"_rfs,7,4);
        RadonFramework::Core::Types::Int32 res3=str3.LastIndexOf("test"_rfs,3,3);
        return res==1 && res1==-1 && res2==7 && res3==-1;
    }

    RadonFramework::Core::Types::Bool PadLeft()
    {
        String str("a=b+c");
        String str1(" a=b+c");
        String str2(".a=b+c");

        Bool result1 = str.PadLeft(6)==str1;
        Bool result2 = str.PadLeft(1)==str;
        Bool result3 = str.PadLeft(5)==str;
        Bool result4 = str.PadLeft(6,'.')==str2;
        return result1 && result2 && result3 && result4;
    }

    RadonFramework::Core::Types::Bool PadRight()
    {
        String str("a=b+c");
        String str1("a=b+c ");
        String str2("a=b+c.");

        Bool result1 = str.PadRight(6)==str1;
        Bool result2 = str.PadRight(1)==str;
        Bool result3 = str.PadRight(5)==str;
        Bool result4 = str.PadRight(6,'.')==str2;
        return result1 && result2 && result3 && result4;
    }

    RadonFramework::Core::Types::Bool Remove()
    {
        String str("a=b+c+d-e");
        String str1("a=b");
        String str2("");

        Bool result1 = str.Remove(3)==str1;
        Bool result2 = str.Remove(9)==str;
        Bool result3 = str.Remove(0)==str2;
        return result1 && result2 && result3;
    }

    RadonFramework::Core::Types::Bool RemoveCount()
    {
        String str("a=b+c+d-e");
        String str1("a=b");
        String str2("");
        String str3("a=b-e");

        Bool result1 = str.Remove(3,6)==str1;
        Bool result2 = str.Remove(9,1)==str;
        Bool result3 = str.Remove(0,9)==str2;
        Bool result4 = str.Remove(3,4)==str3;
        return result1 && result2 && result3 && result4;
    }

    RadonFramework::Core::Types::Bool ReplaceChar()
    {
        String str("a=b+c+d-e");
        String str1("a=d+c+d-e");
        String str2("a=b+c+d-d");

        Bool result1 = str.Replace('b','d')==str1;
        Bool result2 = str.Replace('e','d')==str2;
        Bool result3 = str.Replace('f','a')==str;
        return result1 && result2 && result3;
    }

    RadonFramework::Core::Types::Bool ReplaceString()
    {
        String str("Boo");
        String stra("Bo");
        String strb("B");
        String strc("Ba");
        String str1("Bao");

        Bool result1 = str.Replace(stra,strb)==strb;
        Bool result2 = str.Replace(stra,strc)==str1;
        Bool result3 = str.Replace(stra,stra)==str;
        return result1 && result2 && result3;
    }

    RadonFramework::Core::Types::Bool SplitByPChar()
    {
        String str("a=b+c");
        StringSet list=str.Split("=+"_rfs);
        String empty;
        String notEmpty("foo/bar");
        String delimeterAtStart("/foo/bar");
        String delimeterAtEnd("foo/bar/");
        String delimiterAtStartAndEnd("/foo/bar/");
        RF_Type::Bool result = true;
        result &= empty.Split("/"_rfs).Count() == 0;
        result &= notEmpty.Split("/"_rfs).Count() == 2;
        result &= delimeterAtStart.Split("/"_rfs).Count() == 2;
        result &= delimeterAtEnd.Split("/"_rfs).Count() == 2;
        result &= delimiterAtStartAndEnd.Split("/"_rfs).Count() == 2;
        result &= list.Count() == 3;
        result &= list[0] == "a" && list[1] == "b" && list[2] == "c";
        return result;
    }

    RadonFramework::Core::Types::Bool SplitByString()
    {
        String str("a=b+c");
        String delimiters("=+");
        StringSet list1 = str.Split(delimiters);
        return list1.Count()==3 && list1[0]=="a" && list1[1]=="b" && list1[2]=="c";
    }

    RadonFramework::Core::Types::Bool StartsWith()
    {
        String str("<b>This is bold text</b>");
        return str.StartsWith("<"_rfs) && str.StartsWith("<b>"_rfs);
    }

    RadonFramework::Core::Types::Bool SubString()
    {
        String str("<b>This is bold text</b>");
        String str1("This is bold text");
        String str2("</b>");

        Bool result1 = str.SubString(3,17)==str1;
        Bool result2 = str.SubString(0,0)==String();
        Bool result3 = str.SubString(20,5)==String();
        Bool result4 = str.SubString(20,4)==str2;
        return result1 && result2 && result3 && result4;
    }

    RadonFramework::Core::Types::Bool Trim()
    {
        String str("  Hello  ");
        String str1("...Hello   ");
        String str2("Hello");

        Bool result1 = str.Trim(" "_rfs)==str2;
        Bool result2 = str1.Trim(" ."_rfs)==str2;
        return result1 && result2;
    }

    RadonFramework::Core::Types::Bool TrimStart()
    {
        String str("  Hello");
        String str1(". . Hello");
        String str2("Hello");

        Bool result1 = str.TrimStart(" "_rfs)==str2;
        Bool result2 = str1.TrimStart(" ."_rfs)==str2;
        return result1 && result2;
    }

    RadonFramework::Core::Types::Bool TrimEnd()
    {
        String str("Hello  ");
        String str1("Hello. . ");
        String str2("Hello");

        Bool result1 = str.TrimEnd(" "_rfs)==str2;
        Bool result2 = str1.TrimEnd(" ."_rfs)==str2;
        return result1 && result2;
    }

    RadonFramework::Core::Types::Bool ConstListOperator()
    {
        String str("012");
        return str[0]=='0' && str[1]=='1' && str[2]=='2';
    }

    RadonFramework::Core::Types::Bool ReferenceListOperator()
    {
        String str("012");
        str[0]='1';
        str[1]='2';
        str[2]='3';
        return str[0]=='1' && str[1]=='2' && str[2]=='3';
    }

    RadonFramework::Core::Types::Bool EqualStringOperator()
    {
        String str("012");
        String str1("123");
        String str2("012");
        return str==str2 && !(str==str1);
    }

    RadonFramework::Core::Types::Bool EqualPCharOperator()
    {
        String str("012");
        return str == "012" && !(str == "123");
    }

    RadonFramework::Core::Types::Bool UnequalStringOperator()
    {
        String str("012");
        String str1("123");
        String str2("012");
        return str!=str1 && !(str!=str2);
    }

    RadonFramework::Core::Types::Bool UnequalPCharOperator()
    {
        String str("012");
        return str != "123" && !(str != "012");
    }

    RadonFramework::Core::Types::Bool AddStringOperator()
    {
        String str("012");
        String str1("456");
        String str2("012456");

        Bool result = str+str1==str2;
        return result;
    }

    RadonFramework::Core::Types::Bool AddPCharOperator()
    {
        String str("012");
        String str2("012456");

        Bool result1 = str + "456" == str2;
        return result1;
    }

    RadonFramework::Core::Types::Bool AddCharOperator()
    {
        String str("012");
        String str2("0123");
        const char c='3';

        Bool result = str+c == str2;
        return result;
    }

    RadonFramework::Core::Types::Bool AddBoolOperator()
    {
        String str("012");
        String str2("012true");
        const Bool b=true;
        return str+b==str2;
    }

    RadonFramework::Core::Types::Bool AddInt8Operator()
    {
        String str("012");
        String str2("01234");
        const Int8 i=34;
        return str+i==str2;
    }

    RadonFramework::Core::Types::Bool AddInt16Operator()
    {
        String str("012");
        String str2("01234");
        const Int16 i=34;
        return str+i==str2;
    }

    RadonFramework::Core::Types::Bool AddInt32Operator()
    {
        String str("012");
        String str2("01234");
        const Int32 i=34;
        return str+i==str2;
    }

    RadonFramework::Core::Types::Bool AddInt64Operator()
    {
        String str("012");
        String str2("01234");
        const Int64 i=34;
        return str+i==str2;
    }

    RadonFramework::Core::Types::Bool AddUInt8Operator()
    {
        String str("012");
        String str2("01234");
        const UInt8 i=34;
        return str+i==str2;
    }

    RadonFramework::Core::Types::Bool AddUInt16Operator()
    {
        String str("012");
        String str2("01234");
        const UInt16 i=34;
        return str+i==str2;
    }

    RadonFramework::Core::Types::Bool AddUInt32Operator()
    {
        String str("012");
        String str2("01234");
        const UInt32 i=34;
        return str+i==str2;
    }

    RadonFramework::Core::Types::Bool AddUInt64Operator()
    {
        String str("012");
        String str2("01234");
        const UInt64 i=34;
        return str+i==str2;
    }

    RadonFramework::Core::Types::Bool AddAssignStringOperator()
    {
        String str("123");
        String str1("456");
        String str2("123456");
        str+=str1;
        return str==str2;
    }

    RadonFramework::Core::Types::Bool AddAssignPCharOperator()
    {
        String str("123");
        String str2("123456");

        Bool result = (str+="456") == str2;
        return result;
    }

    RadonFramework::Core::Types::Bool AddAssignCharOperator()
    {
        String str("123");
        const char c='4';
        String str2("1234");
        
        Bool result = (str+=c) == str2;
        return result;
    }

    RadonFramework::Core::Types::Bool AddAssignBoolOperator()
    {
        String str("123");
        const Bool b=true;
        String str2("123true");
        str+=b;
        return str==str2;
    }

    RadonFramework::Core::Types::Bool AddAssignInt8Operator()
    {
        String str("123");
        const Int8 i=45;
        String str2("12345");
        str+=i;
        return str==str2;
    }

    RadonFramework::Core::Types::Bool AddAssignInt16Operator()
    {
        String str("123");
        const Int16 i=45;
        String str2("12345");
        str+=i;
        return str==str2;
    }

    RadonFramework::Core::Types::Bool AddAssignInt32Operator()
    {
        String str("123");
        const Int32 i=45;
        String str2("12345");
        str+=i;
        return str==str2;
    }

    RadonFramework::Core::Types::Bool AddAssignInt64Operator()
    {
        String str("123");
        const Int64 i=45;
        String str2("12345");
        str+=i;
        return str==str2;
    }

    RadonFramework::Core::Types::Bool AddAssignUInt8Operator()
    {
        String str("123");
        const UInt8 i=45;
        String str2("12345");
        str+=i;
        return str==str2;
    }

    RadonFramework::Core::Types::Bool AddAssignUInt16Operator()
    {
        String str("123");
        const UInt16 i=45;
        String str2("12345");
        str+=i;
        return str==str2;
    }

    RadonFramework::Core::Types::Bool AddAssignUInt32Operator()
    {
        String str("123");
        const UInt32 i=45;
        String str2("12345");
        str+=i;
        return str==str2;
    }

    RadonFramework::Core::Types::Bool AddAssignUInt64Operator()
    {
        String str("123");
        const UInt64 i=45;
        String str2("12345");
        str+=i;
        return str==str2;
    }

    RadonFramework::Core::Types::Bool AssignStringOperator()
    {
        String str("123");
        String str1("456");
        str=str1;
        return str==str1;
    }

    RadonFramework::Core::Types::Bool ConvertToPChar()
    {
        String str("123");
        char const* str1;
        char* str2="123";
        str1=str.c_str();
        return strcmp(str1,str2)==0;
    }
        
    RadonFramework::Core::Types::Bool HexToDec()
    {
        String str("0xff");
        Int32 i=str.HexToDec();
        return i==255;
    }

    RadonFramework::Core::Types::Bool ToUpper()
    {
        String str("abc");
        String str1("ABC");
        str.ToUpper();
        return str==str1;
    }

    RadonFramework::Core::Types::Bool ToLower()
    {
        String str("ABC");
        String str1("abc");
        str.ToLower();
        return str==str1;
    }

    RadonFramework::Core::Types::Bool Compare()
    {
        String str("aaa");
        String str1("abc");
        String str2("cb");
        Int32 a,b,c;
        a=str.Compare(str);
        b=str.Compare(str1);
        c=str.Compare(str2);
        return a==0 && b==2 && c==-1;
    }

    RadonFramework::Core::Types::Bool IsNumber()
    {
        String str("127");
        String str1("nonumber");
        return str.IsNumber() && !str1.IsNumber();
    }

    RadonFramework::Core::Types::Bool IsFloatingpointNumber()
    {
        String str("127.0");
        String str1("nonumber");
        return str.IsFloatingpointNumber() && !str1.IsFloatingpointNumber();
    }

    RadonFramework::Core::Types::Bool IsBoolean()
    {
        String str("true");
        String str1("nobool");
        return str.IsBoolean() && !str1.IsBoolean();
    }

    RadonFramework::Core::Types::Bool Size()
    {
        RF_Type::Size bytes = 32;
        String dynamicStringSize(bytes);
        String fixedStringSize("hi");
        return dynamicStringSize.Size()==32 && fixedStringSize.Size() == 3;
    }

    RadonFramework::Core::Types::Bool IsEmpty()
    {
        String empty;
        String notEmpty("hi");
        return empty.IsEmpty() == true && notEmpty.IsEmpty() == false;
    }
};

PortableStringTest PortableStringTestInstance;

