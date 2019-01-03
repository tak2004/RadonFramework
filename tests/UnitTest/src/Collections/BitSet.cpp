#include <RadonFramework/Diagnostics/Test/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Test/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

#include <RadonFramework/Collections/BitSet.hpp>

using namespace RadonFramework::Memory;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Diagnostics::Test::UnitTest;

class BitSetTest:public TestSuite
{
public:
    BitSetTest()
    :TestSuite("RadonFramework::Collections::BitSet-Test"_rfs)
    {
        AddTest(MakeDelegate(this,&BitSetTest::Constructor),
            "BitSetTest::Constructor"_rfs,
            "Constructor"_rfs);

        AddTest(MakeDelegate(this,&BitSetTest::CopyConstructor),
            "BitSetTest::CopyConstructor"_rfs,
            "Copy constructor"_rfs);

        AddTest(MakeDelegate(this,&BitSetTest::AssignOperator),
            "BitSetTest::AssignOperator"_rfs,
            "Assign operator"_rfs);

        AddTest(MakeDelegate(this,&BitSetTest::AndAssignOperator),
            "BitSetTest::AndAssignOperator"_rfs,
            "Bit AND and assign operator"_rfs);

        AddTest(MakeDelegate(this,&BitSetTest::OrAssignOperator),
            "BitSetTest::OrAssignOperator"_rfs,
            "Bit OR and assign operator"_rfs);

        AddTest(MakeDelegate(this,&BitSetTest::XORAssignOperator),
            "BitSetTest::XORAssignOperator"_rfs,
            "Bit XOR and assign operator"_rfs);

        AddTest(MakeDelegate(this,&BitSetTest::LeftShiftAssignOperator),
            "BitSetTest::LeftShiftAssignOperator"_rfs,
            "Left shift and assign operator"_rfs);

        AddTest(MakeDelegate(this,&BitSetTest::RightShiftAssignOperator),
            "BitSetTest::RightShiftAssignOperator"_rfs,
            "Right shift and assign operator"_rfs);

        AddTest(MakeDelegate(this,&BitSetTest::LeftShiftOperator),
            "BitSetTest::LeftShiftOperator"_rfs,
            "Left shift operator"_rfs);

        AddTest(MakeDelegate(this,&BitSetTest::RightShiftOperator),
            "BitSetTest::RightShiftOperator"_rfs,
            "Right shift operator"_rfs);            

        AddTest(MakeDelegate(this,&BitSetTest::Set),
            "BitSetTest::Set"_rfs,
            "Set method"_rfs);            

        AddTest(MakeDelegate(this,&BitSetTest::Reset),
            "BitSetTest::Reset"_rfs,
            "Reset method"_rfs);            

        AddTest(MakeDelegate(this,&BitSetTest::Flip),
            "BitSetTest::Flip"_rfs,
            "Flip method"_rfs);            

        AddTest(MakeDelegate(this,&BitSetTest::InverseOperator),
            "BitSetTest::InverseOperator"_rfs,
            "Inverse operator"_rfs);            

        AddTest(MakeDelegate(this,&BitSetTest::SetIndex),
            "BitSetTest::SetIndex"_rfs,
            "Set method with index parameter"_rfs);            

        AddTest(MakeDelegate(this,&BitSetTest::ResetIndex),
            "BitSetTest::ResetIndex"_rfs,
            "Reset method with index parameter"_rfs);            

        AddTest(MakeDelegate(this,&BitSetTest::FlipIndex),
            "BitSetTest::FlipIndex"_rfs,
            "Flip method with index parameter"_rfs);     

        AddTest(MakeDelegate(this,&BitSetTest::Size),
            "BitSetTest::Size"_rfs,
            "Size method"_rfs);  

        AddTest(MakeDelegate(this,&BitSetTest::Count),
            "BitSetTest::Count"_rfs,
            "Count method"_rfs);  

        AddTest(MakeDelegate(this,&BitSetTest::Any),
            "BitSetTest::Any"_rfs,
            "Any method"_rfs);  

        AddTest(MakeDelegate(this,&BitSetTest::None),
            "BitSetTest::None"_rfs,
            "None method"_rfs);  

        AddTest(MakeDelegate(this,&BitSetTest::Test),
            "BitSetTest::Test"_rfs,
            "Test method"_rfs);  

        AddTest(MakeDelegate(this,&BitSetTest::ArrayAccessOperatorConst),
            "BitSetTest::ArrayAccessOperatorConst"_rfs,
            "Read only array access operator"_rfs);  

        AddTest(MakeDelegate(this,&BitSetTest::ArrayAccessOperator),
            "BitSetTest::ArrayAccessOperator"_rfs,
            "Array access operator"_rfs);  

        AddTest(MakeDelegate(this,&BitSetTest::EqualCompareOperator),
            "BitSetTest::EqualCompareOperator"_rfs,
            "Equal compare operator"_rfs);  

        AddTest(MakeDelegate(this,&BitSetTest::UnequalCompareOperator),
            "BitSetTest::UnequalCompareOperator"_rfs,
            "Uneqal compare operator"_rfs);  

        AddTest(MakeDelegate(this,&BitSetTest::AndOperator),
            "BitSetTest::AndOperator"_rfs,
            "And operator"_rfs); 

        AddTest(MakeDelegate(this,&BitSetTest::OrOperator),
            "BitSetTest::OrOperator"_rfs,
            "Or operator"_rfs); 

        AddTest(MakeDelegate(this,&BitSetTest::XOROperator),
            "BitSetTest::XOROperator"_rfs,
            "XOR operator"_rfs); 
    }

    Bool Constructor()
    {
        BitSet<31> bits1;
        BitSet<33> bits2;
        return (4==bits1.Size() && 5==bits2.Size() && 31==bits1.Count() &&
                33==bits2.Count() && bits1.None() && bits2.None());
    }

    Bool CopyConstructor()
    {
        BitSet<31> bits1;
        bits1.Set();
        BitSet<31> bits2(bits1);
        return (bits1.Any() && bits2.Any());
    }

    Bool AssignOperator()
    {
        BitSet<31> bits1;
        bits1.Set();
        BitSet<31> bits2;
        bits2=bits1;
        return (bits1.Any() && bits2.Any());
    }

    Bool AndAssignOperator()
    {
        BitSet<31> bits1;
        bits1.Set();
        BitSet<31> bits2;
        bits2&=bits1;
        BitSet<31> bits3(bits1);
        bits3&=bits1;
        return (bits2.None() && bits3.Any());
    }

    Bool OrAssignOperator()
    {
        BitSet<31> bits1;
        bits1.Set();
        BitSet<31> bits2;
        bits2|=bits1;
        bits1.Reset();
        BitSet<31> bits3(bits1);
        bits3|=bits1;
        return (bits2.Any() && bits3.None());
    }

    Bool XORAssignOperator()
    {
        BitSet<31> bits1;
        bits1.Set();
        BitSet<31> bits2;
        bits2^=bits1;
        bits1.Reset();
        BitSet<31> bits3(bits1);
        bits3^=bits1;
        bits1.Set();
        BitSet<31> bits4(bits1);
        bits4^=bits1;
        return (bits2.Any() && bits3.None() && bits4.None());
    }

    Bool LeftShiftAssignOperator()
    {
        BitSet<31> bits1;
        bits1.Set();
        bits1<<=31;
            
        BitSet<31> bits2;
        bits2.Set();
        bits2.Reset(29);
        bits2<<=24;

        BitSet<31> bits3;
        bits3.Set();
        bits3.Reset(29);
        bits3<<=16;

        BitSet<31> bits4;
        bits4.Set();
        bits4<<=30;
        return (bits1.None() && 
                bits2.Test(6) && !bits2.Test(7) && 
                bits3.Test(14) && !bits3.Test(15) && 
                bits4.Test(0) && !bits4.Test(1));
    }

    Bool RightShiftAssignOperator()
    {
        BitSet<31> bits1;
        bits1.Set();
        bits1>>=31;

        BitSet<31> bits2;
        bits2.Set();
        bits2.Reset(1);
        bits2>>=24;

        BitSet<31> bits3;
        bits3.Set();
        bits3.Reset(1);
        bits3>>=16;

        BitSet<31> bits4;
        bits4.Set();
        bits4>>=30;
        return (bits1.None() && 
                !bits2.Test(23) && bits2.Test(24) && 
                !bits3.Test(15) && bits3.Test(16) && 
                bits4.Test(30) && !bits4.Test(29));
    }

    Bool RightShiftOperator()
    {
        BitSet<31> bits1;
        bits1.Set();
        bits1=bits1>>4;
        return (!bits1.Test(3) && bits1.Test(4));
    }

    Bool LeftShiftOperator()
    {
        BitSet<31> bits1;
        bits1.Set();
        bits1=bits1<<4;
        return (!bits1.Test(27) && bits1.Test(26));
    }

    Bool Set()
    {
        BitSet<31> bits1;
        bits1.Set();
        return (bits1.Any());
    }

    Bool Flip()
    {
        BitSet<31> bits1;
        bits1.Flip();
        return (bits1.Any());
    }

    Bool InverseOperator()
    {
        BitSet<31> bits1;
        bits1=~bits1;
        return (bits1.Any());
    }

    Bool Reset()
    {
        BitSet<31> bits1;
        bits1.Set();
        bits1.Reset();
        return (bits1.None());
    }

    Bool SetIndex()
    {
        BitSet<31> bits1;
        bits1.Set(0);
        return (bits1.Test(0) && !bits1.Test(1));
    }

    Bool FlipIndex()
    {
        BitSet<31> bits1;
        bits1.Flip(0);
        return (bits1.Test(0) && !bits1.Test(1));
    }

    Bool ResetIndex()
    {
        BitSet<31> bits1;
        bits1.Set();
        bits1.Reset(0);
        return (!bits1.Test(0) && bits1.Test(1));
    }

    Bool Size()
    {
        BitSet<31> bits1;
        BitSet<24> bits2;
        return (bits1.Size()==4 && bits2.Size()==3);
    }

    Bool Count()
    {
        BitSet<31> bits1;
        BitSet<24> bits2;
        return (bits1.Count()==31 && bits2.Count()==24);
    }

    Bool Any()
    {
        BitSet<31> bits1;
        bits1.Set();
        BitSet<24> bits2;
        return (bits1.Any() && !bits2.Any());
    }

    Bool None()
    {
        BitSet<31> bits1;
        bits1.Set();
        BitSet<24> bits2;
        return (!bits1.None() && bits2.None());
    }

    Bool Test()
    {
        BitSet<31> bits1;
        bits1.Set(0);
        return (bits1.Test(0) && !bits1.Test(1));
    }

    Bool ArrayAccessOperatorConst()
    {
        BitSet<31> bits1;
        bits1.Set(0);            
        return (bits1[0] && !bits1[1]);
        //return false;
    }

    Bool ArrayAccessOperator()
    {
        BitSet<31> bits1;
        bits1[0]=true;            
        return (bits1.Test(0) && !bits1.Test(1));
    }

    Bool EqualCompareOperator()
    {            
        BitSet<31> bits1;
        bits1.Set(1);
        BitSet<31> bits2;
        bits2.Set(1);
        return (bits1==bits2);
    }

    Bool UnequalCompareOperator()
    {            
        BitSet<31> bits1;
        bits1.Set(1);
        BitSet<31> bits2;
        bits2.Set(0);
        return (bits1!=bits2);
    }

    Bool AndOperator()
    {            
        BitSet<31> bits1;
        bits1.Set(1);
        BitSet<31> bits2;
        bits2.Set(0);
        BitSet<31> bits3=bits1&bits2;
        return (bits3.None());
    }

    Bool OrOperator()
    {            
        BitSet<31> bits1;
        bits1.Set(1);
        BitSet<31> bits2;
        bits2.Set(0);
        BitSet<31> bits3=bits1|bits2;
        return (bits3.Test(0) && bits3.Test(1) && !bits3.Test(2));
    }

    Bool XOROperator()
    {            
        BitSet<31> bits1;
        bits1.Set(1);
        bits1.Set(2);
        BitSet<31> bits2;
        bits2.Set(0);
        bits2.Set(2);
        BitSet<31> bits3=bits1^bits2;
        return (bits3.Test(0) && bits3.Test(1) && !bits3.Test(2));
    }
};

BitSetTest collectionsGenericBitSetTestInstance;
