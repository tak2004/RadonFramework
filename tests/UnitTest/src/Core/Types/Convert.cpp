#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <string.h>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Memory;

class ConvertTest:public TestSuite
{
    public:
        ConvertTest()
        :TestSuite("RadonFramework::Core::Types::Convert-Test")
        {
            AddTest(MakeDelegate(this,&ConvertTest::StringToBool),"StringToBool");
            AddTest(MakeDelegate(this,&ConvertTest::StringToInt8),"StringToInt8");
            AddTest(MakeDelegate(this,&ConvertTest::StringToInt16),"StringToInt16");
            AddTest(MakeDelegate(this,&ConvertTest::StringToInt32),"StringToInt32");
            AddTest(MakeDelegate(this,&ConvertTest::StringToInt64),"StringToInt64");
            AddTest(MakeDelegate(this,&ConvertTest::StringToUInt8),"StringToUInt8");
            AddTest(MakeDelegate(this,&ConvertTest::StringToUInt16),"StringToUInt16");
            AddTest(MakeDelegate(this,&ConvertTest::StringToUInt32),"StringToUInt32");
            AddTest(MakeDelegate(this,&ConvertTest::StringToUInt64),"StringToUInt64");
            AddTest(MakeDelegate(this,&ConvertTest::StringToFloat32),"StringToFloat32");
            AddTest(MakeDelegate(this,&ConvertTest::StringToFloat64),"StringToFloat64");
            AddTest(MakeDelegate(this,&ConvertTest::Int8ToString),"Int8ToString");
            AddTest(MakeDelegate(this,&ConvertTest::Int16ToString),"Int16ToString");
            AddTest(MakeDelegate(this,&ConvertTest::Int32ToString),"Int32ToString");
            AddTest(MakeDelegate(this,&ConvertTest::Int64ToString),"Int64ToString");
            AddTest(MakeDelegate(this,&ConvertTest::UInt8ToString),"UInt8ToString");
            AddTest(MakeDelegate(this,&ConvertTest::UInt16ToString),"UInt16ToString");
            AddTest(MakeDelegate(this,&ConvertTest::UInt32ToString),"UInt32ToString");
            AddTest(MakeDelegate(this,&ConvertTest::UInt64ToString),"UInt64ToString");
            AddTest(MakeDelegate(this,&ConvertTest::Float32ToString),"Float32ToString");
            AddTest(MakeDelegate(this,&ConvertTest::Float64ToString),"Float64ToString");
        }

        RadonFramework::Core::Types::Bool StringToBool()
        {
            String str("true");
            String str1("nobool");
            Bool a,b=false,c,d;
            c=Convert::ToBool(str,a);
            d=Convert::ToBool(str1,b);
            return c && d==false && a && b==false;
        }

        RadonFramework::Core::Types::Bool StringToInt8()
        {
            String str("1");
            String str1("128");
            Bool a,b;
            Int8 c,d=127;
            a=Convert::ToInt8(str,c);
            b=Convert::ToInt8(str1,d);
            return a && b==false && c==1 && d==127;
        }

        RadonFramework::Core::Types::Bool StringToInt16()
        {
            String str("1");
            String str1("noval");
            Bool a,b;
            Int16 c,d=127;
            a=Convert::ToInt16(str,c);
            b=Convert::ToInt16(str1,d);
            return a && b==false && c==1 && d==127;
        }

        RadonFramework::Core::Types::Bool StringToInt32()
        {
            String str("1");
            String str1("noval");
            Bool a,b;
            Int32 c,d=127;
            a=Convert::ToInt32(str,c);
            b=Convert::ToInt32(str1,d);
            return a && b==false && c==1 && d==127;
        }

        RadonFramework::Core::Types::Bool StringToInt64()
        {
            String str("1");
            String str1("noval");
            Bool a,b;
            Int64 c,d=127;
            a=Convert::ToInt64(str,c);
            b=Convert::ToInt64(str1,d);
            return a && b==false && c==1 && d==127;
        }

        RadonFramework::Core::Types::Bool StringToUInt8()
        {
            String str("1");
            String str1("257");
            Bool a,b;
            UInt8 c,d=127;
            a=Convert::ToUInt8(str,c);
            b=Convert::ToUInt8(str1,d);
            return a && b==false && c==1 && d==127;
        }

        RadonFramework::Core::Types::Bool StringToUInt16()
        {
            String str("1");
            String str1("noval");
            Bool a,b;
            UInt16 c,d=127;
            a=Convert::ToUInt16(str,c);
            b=Convert::ToUInt16(str1,d);
            return a && b==false && c==1 && d==127;
        }

        RadonFramework::Core::Types::Bool StringToUInt32()
        {
            String str("1");
            String str1("noval");
            Bool a,b;
            UInt32 c,d=127;
            a=Convert::ToUInt32(str,c);
            b=Convert::ToUInt32(str1,d);
            return a && b==false && c==1 && d==127;
        }

        RadonFramework::Core::Types::Bool StringToUInt64()
        {
            String str("1");
            String str1("noval");
            Bool a,b;
            UInt64 c,d=127;
            a=Convert::ToUInt64(str,c);
            b=Convert::ToUInt64(str1,d);
            return a && b==false && c==1 && d==127;
        }

        RadonFramework::Core::Types::Bool StringToFloat32()
        {
            String str("1.0");
            String str1("noval");
            Bool a,b;
            Float32 c,d=127.0;
            a=Convert::ToFloat32(str,c);
            b=Convert::ToFloat32(str1,d);
            return a && b==false && c==1 && d==127.0;
        }

        RadonFramework::Core::Types::Bool StringToFloat64()
        {
            String str("1.0");
            String str1("noval");
            Bool a,b;
            Float64 c,d=127.0;
            a=Convert::ToFloat64(str,c);
            b=Convert::ToFloat64(str1,d);
            return a && b==false && c==1 && d==127.0;
        }

        RadonFramework::Core::Types::Bool Int8ToString()
        {
            String str("-127");
            String str1("127");
            String strA,strB;
            Int8 a=Int8Min;
            Int8 b=Int8Max;
            strA=Convert::ToString(a);
            strB=Convert::ToString(b);
            return strA==str && strB==str1;
        }

        RadonFramework::Core::Types::Bool Int16ToString()
        {
            String str("-32767");
            String str1("32767");
            String strA,strB;
            Int16 a=Int16Min;
            Int16 b=Int16Max;
            strA=Convert::ToString(a);
            strB=Convert::ToString(b);
            return strA==str && strB==str1;
        }

        RadonFramework::Core::Types::Bool Int32ToString()
        {
            String str("-2147483648");
            String str1("2147483647");
            String strA,strB;
            Int32 a=Int32Min;
            Int32 b=Int32Max;
            strA=Convert::ToString(a);
            strB=Convert::ToString(b);
            return strA==str && strB==str1;
        }

        RadonFramework::Core::Types::Bool Int64ToString()
        {
            String str("-9223372036854775808");
            String str1("9223372036854775807");
            String strA,strB;
            Int64 a=Int64Min;
            Int64 b=Int64Max;
            strA=Convert::ToString(a);
            strB=Convert::ToString(b);
            return strA==str && strB==str1;
        }

        RadonFramework::Core::Types::Bool UInt8ToString()
        {
            String str("0");
            String str1("255");
            String strA,strB;
            UInt8 a=UInt8Min;
            UInt8 b=UInt8Max;
            strA=Convert::ToString(a);
            strB=Convert::ToString(b);
            return strA==str && strB==str1;
        }

        RadonFramework::Core::Types::Bool UInt16ToString()
        {
            String str("0");
            String str1("65535");
            String strA,strB;
            UInt16 a=UInt16Min;
            UInt16 b=UInt16Max;
            strA=Convert::ToString(a);
            strB=Convert::ToString(b);
            return strA==str && strB==str1;
        }

        RadonFramework::Core::Types::Bool UInt32ToString()
        {
            String str("0");
            String str1("4294967295");
            String strA,strB;
            UInt32 a=UInt32Min;
            UInt32 b=UInt32Max;
            strA=Convert::ToString(a);
            strB=Convert::ToString(b);
            return strA==str && strB==str1;
        }

        RadonFramework::Core::Types::Bool UInt64ToString()
        {
            String str("0");
            String str1("18446744073709551615");
            String strA,strB;
            UInt64 a=UInt64Min;
            UInt64 b=UInt64Max;
            strA=Convert::ToString(a);
            strB=Convert::ToString(b);
            return strA==str && strB==str1;
        }

        RadonFramework::Core::Types::Bool Float32ToString()
        {
            String str("-1.000000");
            String str1("1.000000");
            String strA,strB;
            Float32 a=-1;
            Float32 b=1;
            strA=Convert::ToString(a);
            strB=Convert::ToString(b);
            return strA==str && strB==str1;
        }

        RadonFramework::Core::Types::Bool Float64ToString()
        {
            String str("-1.000000");
            String str1("1.000000");
            String strA,strB;
            Float64 a=-1;
            Float64 b=1;
            strA=Convert::ToString(a);
            strB=Convert::ToString(b);
            return strA==str && strB==str1;
        }
};

ConvertTest ConvertTestInstance;
