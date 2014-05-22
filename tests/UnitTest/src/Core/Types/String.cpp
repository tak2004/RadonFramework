#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <string.h>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Memory;

class PortableStringTest:public TestSuite
{
    public:
        PortableStringTest()
        :TestSuite("RadonFramework::Core::Types::String-Test")
        {
            AddTest(MakeDelegate(this,&PortableStringTest::DefaultConstructor),"StringDefaultConstructor");
            AddTest(MakeDelegate(this,&PortableStringTest::CopyConstructor),"StringCopyConstructor");
            AddTest(MakeDelegate(this,&PortableStringTest::CharConstructor),"StringCharConstructor");
            AddTest(MakeDelegate(this,&PortableStringTest::CharWithLengthConstructor),"StringCharWithLengthConstructor");
            AddTest(MakeDelegate(this,&PortableStringTest::WithLengthConstructor),"StringWithLengthConstructor");
            AddTest(MakeDelegate(this,&PortableStringTest::Length),"StringLength");
            AddTest(MakeDelegate(this,&PortableStringTest::Contains),"StringContains");
            AddTest(MakeDelegate(this,&PortableStringTest::EndsWithPChar),"StringEndsWithPChar");
            AddTest(MakeDelegate(this,&PortableStringTest::EndsWithString),"StringEndsWithString");
            AddTest(MakeDelegate(this,&PortableStringTest::IndexOfString),"StringIndexOfString");
            AddTest(MakeDelegate(this,&PortableStringTest::IndexOfChar),"StringIndexOfChar");
            AddTest(MakeDelegate(this,&PortableStringTest::IndexOfStringStart),"StringIndexOfStringStart");
            AddTest(MakeDelegate(this,&PortableStringTest::IndexOfCharStart),"StringIndexOfCharStart");
            AddTest(MakeDelegate(this,&PortableStringTest::IndexOfStringStartStop),"StringIndexOfStringStartStop");
            AddTest(MakeDelegate(this,&PortableStringTest::IndexOfCharStartStop),"StringIndexOfCharStartStop");
            AddTest(MakeDelegate(this,&PortableStringTest::InsertString),"StringInsertString");
            AddTest(MakeDelegate(this,&PortableStringTest::InsertPChar),"StringInsertPChar");
            AddTest(MakeDelegate(this,&PortableStringTest::LastIndexOfString),"StringLastIndexOfString");
            AddTest(MakeDelegate(this,&PortableStringTest::LastIndexOfChar),"StringLastIndexOfChar");
            AddTest(MakeDelegate(this,&PortableStringTest::LastIndexOfStringStart),"StringLastIndexOfStringStart");
            AddTest(MakeDelegate(this,&PortableStringTest::LastIndexOfCharStart),"StringLastIndexOfCharStart");
            AddTest(MakeDelegate(this,&PortableStringTest::LastIndexOfStringStartStop),"StringLastIndexOfStringStartStop");
            AddTest(MakeDelegate(this,&PortableStringTest::LastIndexOfCharStartStop),"StringLastIndexOfCharStartStop");
            AddTest(MakeDelegate(this,&PortableStringTest::PadLeft),"StringPadLeft");
            AddTest(MakeDelegate(this,&PortableStringTest::PadRight),"StringPadRight");
            AddTest(MakeDelegate(this,&PortableStringTest::Remove),"StringRemove");
            AddTest(MakeDelegate(this,&PortableStringTest::RemoveCount),"StringRemoveCount");
            AddTest(MakeDelegate(this,&PortableStringTest::ReplaceChar),"StringReplaceChar");
            AddTest(MakeDelegate(this,&PortableStringTest::ReplaceString),"StringReplaceString");
            AddTest(MakeDelegate(this,&PortableStringTest::SplitByPChar),"StringSplitByPChar");
            AddTest(MakeDelegate(this,&PortableStringTest::SplitByString),"StringSplitByString");
            AddTest(MakeDelegate(this,&PortableStringTest::StartsWith),"StringStartsWith");
            AddTest(MakeDelegate(this,&PortableStringTest::SubString),"StringSubString");
            AddTest(MakeDelegate(this,&PortableStringTest::Trim),"StringTrim");
            AddTest(MakeDelegate(this,&PortableStringTest::TrimEnd),"StringTrimEnd");
            AddTest(MakeDelegate(this,&PortableStringTest::TrimStart),"StringTrimStart");
            AddTest(MakeDelegate(this,&PortableStringTest::ConstListOperator),"StringConstListOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::ReferenceListOperator),"StringReferenceListOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::EqualStringOperator),"StringEqualStringOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::EqualPCharOperator),"StringEqualPCharOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::UnequalStringOperator),"StringUnequalStringOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::UnequalPCharOperator),"StringUnequalPCharOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddStringOperator),"StringAddStringOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddPCharOperator),"StringAddPCharOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddCharOperator),"StringAddCharOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddBoolOperator),"StringAddBoolOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddInt8Operator),"StringAddInt8Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddInt16Operator),"StringAddInt16Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddInt32Operator),"StringAddInt32Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddInt64Operator),"StringAddInt64Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddUInt8Operator),"StringAddUInt8Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddUInt16Operator),"StringAddUInt16Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddUInt32Operator),"StringAddUInt32Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddUInt64Operator),"StringAddUInt64Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddAssignStringOperator),"StringAddAssignStringOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddAssignPCharOperator),"StringAddAssignPCharOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddAssignCharOperator),"StringAddAssignCharOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddAssignBoolOperator),"StringAddAssignBoolOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddAssignInt8Operator),"StringAddAssignInt8Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddAssignInt16Operator),"StringAddAssignInt16Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddAssignInt32Operator),"StringAddAssignInt32Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddAssignInt64Operator),"StringAddAssignInt64Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddAssignUInt8Operator),"StringAddAssignUInt8Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddAssignUInt16Operator),"StringAddAssignUInt16Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddAssignUInt32Operator),"StringAddAssignUInt32Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AddAssignUInt64Operator),"StringAddAssignUInt64Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AssignStringOperator),"StringAssignStringOperator");            
            AddTest(MakeDelegate(this,&PortableStringTest::AssignPCharOperator),"StringAssignPCharOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::AssignCharOperator),"StringAssignCharOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::AssignBoolOperator),"StringAssignBoolOperator");
            AddTest(MakeDelegate(this,&PortableStringTest::AssignInt8Operator),"StringAssignInt8Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AssignInt16Operator),"StringAssignInt16Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AssignInt32Operator),"StringAssignInt32Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AssignInt64Operator),"StringAssignInt64Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AssignUInt8Operator),"StringAssignUInt8Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AssignUInt16Operator),"StringAssignUInt16Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AssignUInt32Operator),"StringAssignUInt32Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::AssignUInt64Operator),"StringAssignUInt64Operator");
            AddTest(MakeDelegate(this,&PortableStringTest::ConvertToPChar),"StringConvertToPChar");
            AddTest(MakeDelegate(this,&PortableStringTest::HexToDec),"StringHexToDec");
            AddTest(MakeDelegate(this,&PortableStringTest::ToUpper),"StringToUpper");
            AddTest(MakeDelegate(this,&PortableStringTest::ToLower),"StringToLower");
            AddTest(MakeDelegate(this,&PortableStringTest::Compare),"StringCompare");
            AddTest(MakeDelegate(this,&PortableStringTest::IsNumber),"StringIsNumber");
            AddTest(MakeDelegate(this,&PortableStringTest::IsFloatingpointNumber),"StringIsFloatingpointNumber");
            AddTest(MakeDelegate(this,&PortableStringTest::IsBoolean),"StringIsBoolean");
        }

        RadonFramework::Core::Types::Bool DefaultConstructor()
        {
            String str;
            return str.Length()==0;
        }

        RadonFramework::Core::Types::Bool CopyConstructor()
        {
            String str1("hi");
            String str(str1);
            return str.Length()==2 && str[0]=='h' && str[1]=='i';
        }
        
        RadonFramework::Core::Types::Bool CharConstructor()
        {
            String str("hi");
            return str.Length()==2 && str[0]=='h' && str[1]=='i';
        }

        RadonFramework::Core::Types::Bool CharWithLengthConstructor()
        {
            char* str1="hiho";
            String str(str1,2);
            return str.Length()==2 && str[0]=='h' && str[1]=='i';
        }

        RadonFramework::Core::Types::Bool WithLengthConstructor()
        {
            RFTYPE::Size bytes = 3;
            String str(bytes);
            String str1("  ");
            return str.Length()==2 && str==str1;
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
            return str.EndsWith("456")==true && str.EndsWith("45")==false;
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
            RadonFramework::Core::Types::Int32 res=str.IndexOf("test");
            RadonFramework::Core::Types::Int32 res1=str.IndexOf("tset");
            RadonFramework::Core::Types::Int32 res2=str3.IndexOf("test");
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
            RadonFramework::Core::Types::Int32 res=str.IndexOf("test",1);
            RadonFramework::Core::Types::Int32 res1=str.IndexOf("tset",1);
            RadonFramework::Core::Types::Int32 res2=str3.IndexOf("test",2);
            RadonFramework::Core::Types::Int32 res3=str3.IndexOf("test",8);
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
            RadonFramework::Core::Types::Int32 res=str.IndexOf("test",1,4);
            RadonFramework::Core::Types::Int32 res1=str.IndexOf("tset",1,4);
            RadonFramework::Core::Types::Int32 res2=str3.IndexOf("test",3,4);
            RadonFramework::Core::Types::Int32 res3=str3.IndexOf("test",3,3);
            return res==1 && res1==-1 && res2==3 && res3==-1;
        }

        RadonFramework::Core::Types::Bool InsertString()
        {
            String str("test");
            String str1("123test456");
            String str2("test123456");
            String str3("123456");
            String str4("123456test");
            return str3.Insert(3,str)==str1 && str3.Insert(0,str)==str2 && str3.Insert(6,str)==str4;
        }

        RadonFramework::Core::Types::Bool InsertPChar()
        {
            String str("test");
            String str1("123test456");
            String str2("test123456");
            String str3("123456");
            String str4("123456test");
            return str3.Insert(3,"test")==str1 && str3.Insert(0,"test")==str2 && str3.Insert(6,"test")==str4;
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
            RadonFramework::Core::Types::Int32 res=str.LastIndexOf("test");
            RadonFramework::Core::Types::Int32 res1=str.LastIndexOf("tset");
            RadonFramework::Core::Types::Int32 res2=str3.LastIndexOf("test");
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
            RadonFramework::Core::Types::Int32 res=str.LastIndexOf("test",1);
            RadonFramework::Core::Types::Int32 res1=str.LastIndexOf("tset",1);
            RadonFramework::Core::Types::Int32 res2=str3.LastIndexOf("test",2);
            RadonFramework::Core::Types::Int32 res3=str3.LastIndexOf("test",8);
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
            RadonFramework::Core::Types::Int32 res=str.LastIndexOf("test",1,4);
            RadonFramework::Core::Types::Int32 res1=str.LastIndexOf("tset",1,4);
            RadonFramework::Core::Types::Int32 res2=str3.LastIndexOf("test",7,4);
            RadonFramework::Core::Types::Int32 res3=str3.LastIndexOf("test",3,3);
            return res==1 && res1==-1 && res2==7 && res3==-1;
        }

        RadonFramework::Core::Types::Bool PadLeft()
        {
            String str("a=b+c");
            String str1(" a=b+c");
            String str2(".a=b+c");

            return str.PadLeft(6)==str1 && str.PadLeft(1)==str &&
                   str.PadLeft(str.Length())==str && str.PadLeft(6,'.')==str2;
        }

        RadonFramework::Core::Types::Bool PadRight()
        {
            String str("a=b+c");
            String str1("a=b+c ");
            String str2("a=b+c.");

            return str.PadRight(6)==str1 && str.PadRight(1)==str &&
                str.PadRight(str.Length())==str && str.PadRight(6,'.')==str2;
        }

        RadonFramework::Core::Types::Bool Remove()
        {
            String str("a=b+c+d-e");
            String str1("a=b");
            String str2("");
            return str.Remove(3)==str1 && str.Remove(9)==str && str.Remove(0)==str2;
        }

        RadonFramework::Core::Types::Bool RemoveCount()
        {
            String str("a=b+c+d-e");
            String str1("a=b");
            String str2("");
            String str3("a=b-e");
            return str.Remove(3,6)==str1 && str.Remove(9,1)==str &&
                   str.Remove(0,9)==str2 && str.Remove(3,4)==str3;
        }

        RadonFramework::Core::Types::Bool ReplaceChar()
        {
            String str("a=b+c+d-e");
            String str1("a=d+c+d-e");
            String str2("a=b+c+d-d");
            return str.Replace('b','d')==str1 && str.Replace('e','d')==str2 && str.Replace('f','a')==str;
        }

        RadonFramework::Core::Types::Bool ReplaceString()
        {
            String str("Boo");
            String stra("Bo");
            String strb("B");
            String strc("Ba");
            String str1("Bao");
            return str.Replace(stra,strb)==strb && str.Replace(stra,strc)==str1 && str.Replace(stra,stra)==str;
        }

        RadonFramework::Core::Types::Bool SplitByPChar()
        {
            String str("a=b+c");
            AutoPointerArray<String> list=str.Split("=+");
            return list.Count()==3 && list[0]=="a" && list[1]=="b" && list[2]=="c";
        }

        RadonFramework::Core::Types::Bool SplitByString()
        {
            String str("a=b+c");
            String delimiters("=+");
            AutoPointerArray<String> list1=str.Split(delimiters);
            return list1.Count()==3 && list1[0]=="a" && list1[1]=="b" && list1[2]=="c";
        }

        RadonFramework::Core::Types::Bool StartsWith()
        {
            String str("<b>This is bold text</b>");
            return str.StartsWith("<") && str.StartsWith("<b>");
        }

        RadonFramework::Core::Types::Bool SubString()
        {
            String str("<b>This is bold text</b>");
            String str1("This is bold text");
            return str.SubString(3,17)==str1 && str.SubString(0,0)==String() && str.SubString(20,5)==String();
        }

        RadonFramework::Core::Types::Bool Trim()
        {
            String str("  Hello  ");
            String str1("...Hello   ");
            String str2("Hello");
            return str.Trim("")==str2 && str1.Trim(" .")==str2;
        }

        RadonFramework::Core::Types::Bool TrimStart()
        {
            String str("  Hello");
            String str1(". . Hello");
            String str2("Hello");
            return str.TrimStart("")==str2 && str1.TrimStart(" .")==str2;
        }

        RadonFramework::Core::Types::Bool TrimEnd()
        {
            String str("Hello  ");
            String str1("Hello. . ");
            String str2("Hello");
            return str.TrimEnd("")==str2 && str1.TrimEnd(" .")==str2;
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
            return str+str1==str2;
        }

        RadonFramework::Core::Types::Bool AddPCharOperator()
        {
            String str("012");
            String str2("012456");
            const char* pc="456";
            return str+pc==str2;
        }

        RadonFramework::Core::Types::Bool AddCharOperator()
        {
            String str("012");
            String str2("0123");
            const char c='3';
            return str+c==str2;
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
            char* str1="456";
            String str2("123456");
            str+=str1;
            return str==str2;
        }

        RadonFramework::Core::Types::Bool AddAssignCharOperator()
        {
            String str("123");
            const char c='4';
            String str2("1234");
            str+=c;
            return str==str2;
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

        RadonFramework::Core::Types::Bool AssignPCharOperator()
        {
            String str("123");
            char* str1="456";
            String str2("456");
            str=str1;
            return str==str2;
        }

        RadonFramework::Core::Types::Bool AssignBoolOperator()
        {
            String str("123");
            const Bool b=true;
            String str2("true");
            str=b;
            return str==str2;
        }

        RadonFramework::Core::Types::Bool AssignCharOperator()
        {
            String str("123");
            const char c='4';
            String str2("4");
            str=c;
            return str==str2;
        }

        RadonFramework::Core::Types::Bool AssignInt8Operator()
        {
            String str("123");
            const Int8 i=4;
            String str2("4");
            str=i;
            return str==str2;
        }

        RadonFramework::Core::Types::Bool AssignInt16Operator()
        {
            String str("123");
            const Int16 i=4;
            String str2("4");
            str=i;
            return str==str2;
        }

        RadonFramework::Core::Types::Bool AssignInt32Operator()
        {
            String str("123");
            const Int32 i=4;
            String str2("4");
            str=i;
            return str==str2;
        }

        RadonFramework::Core::Types::Bool AssignInt64Operator()
        {
            String str("123");
            const Int64 i=4;
            String str2("4");
            str=i;
            return str==str2;
        }

        RadonFramework::Core::Types::Bool AssignUInt8Operator()
        {
            String str("123");
            const UInt8 i=4;
            String str2("4");
            str=i;
            return str==str2;
        }

        RadonFramework::Core::Types::Bool AssignUInt16Operator()
        {
            String str("123");
            const UInt16 i=4;
            String str2("4");
            str=i;
            return str==str2;
        }

        RadonFramework::Core::Types::Bool AssignUInt32Operator()
        {
            String str("123");
            const UInt32 i=4;
            String str2("4");
            str=i;
            return str==str2;
        }

        RadonFramework::Core::Types::Bool AssignUInt64Operator()
        {
            String str("123");
            const UInt64 i=4;
            String str2("4");
            str=i;
            return str==str2;
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
};

PortableStringTest PortableStringTestInstance;

