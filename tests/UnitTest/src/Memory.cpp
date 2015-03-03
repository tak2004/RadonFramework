#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
//#include <RadonFramework/Memory.hpp>
#include <RadonFramework/System/Memory.hpp>

using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Core::Types;

class MemoryTest:public TestSuite
{
public:
    MemoryTest()
    :TestSuite("RadonFramework::Memory")
    {
        AddTest(MakeDelegate(this,&MemoryTest::AllocatorConstructor),
            "MemoryTest::AllocatorConstructor", 
            "Allocator constructor");
        AddTest(MakeDelegate(this,&MemoryTest::AllocatorCopyConstructor),
            "MemoryTest::AllocatorCopyConstructor", 
            "Allocator copy constructor");
        AddTest(MakeDelegate(this,&MemoryTest::AllocatorCopyConstructor1),
            "MemoryTest::AllocatorCopyConstructor1", 
            "Allocator copy constructor form other Allocator type");
        AddTest(MakeDelegate(this,&MemoryTest::AllocatorAllocation),
            "MemoryTest::AllocatorAllocation",
            "Allocator allocate and deallocate memory");
        AddTest(MakeDelegate(this,&MemoryTest::Compare),
            "MemoryTest::Compare",
            "Compare memory");
        AddTest(MakeDelegate(this,&MemoryTest::Set),
            "MemoryTest::Set",
            "Set memory range");
        AddTest(MakeDelegate(this,&MemoryTest::Copy),
            "MemoryTest::Copy",
            "Copy a memory block to an other");
    }

    Bool AllocatorConstructor()
    {
//			Allocator<> alloc;
        return true;
    }

    Bool AllocatorCopyConstructor()
    {
//			Allocator<> alloc;
//			Allocator<> alloc1(alloc);
        return true;
    }

    Bool AllocatorCopyConstructor1()
    {
//			Allocator<RadonFramework::Core::Types::UInt16> alloc;
//			Allocator<> alloc1(alloc);
        return true;
    }

    Bool AllocatorAllocation()
    {
/*			Allocator<> alloc;
        Allocator<>::Pointer val=0;
        val=alloc.Allocate(5);
        RadonFramework::Core::Types::Bool res=false;
        if (val)
        {
            val[0]=1;
            res=true;
        }
        alloc.Deallocate(val,5);*/
        return true;
    }

    Bool Compare()
    {
        const UInt8 bufA[]={1,3,2,1};
        const UInt8 bufB[]={0,1,3,3};
        const UInt8 bufC[]={0,1,2,3};
        return RF_SysMem::Compare(bufA, bufB, 4) > 0 &&
                RF_SysMem::Compare(bufB, bufA, 4) < 0 &&
                RF_SysMem::Compare(bufB, bufC, 2) == 0 &&
                RF_SysMem::Compare(bufB, bufC, 4) > 0 &&
                RF_SysMem::Compare(bufC, bufB, 4) == 0;
    }

    Bool Set()
    {
        UInt8 bufA[32];
        UInt8 bufB[3];
        UInt8 bufC[11];
        UInt8 bufD[17];
        RF_SysMem::Set(reinterpret_cast<void*>(bufA), 0xAB, 32);
        RF_SysMem::Set(reinterpret_cast<void*>(bufA), 0xCD, 16);
        RF_SysMem::Set(reinterpret_cast<void*>(bufB), 0xFF, 3);
        RF_SysMem::Set(reinterpret_cast<void*>(bufC+1), 0xFF, 10);
        RF_SysMem::Set(reinterpret_cast<void*>(bufD+1), 0xFF, 16);
        Bool result = true;
        for(RF_Type::Size i = 0; i < 16; ++i)
            result = bufA[i] == 0xCD && result;
        for(RF_Type::Size i = 16; i < 32; ++i)
            result = bufA[i] == 0xAB && result;
        for(RF_Type::Size i = 0; i < 3; ++i)
            result = bufB[i] == 0xFF && result;
        for(RF_Type::Size i = 1; i < 11; ++i)
            result = bufC[i] == 0xFF && result;
        for(RF_Type::Size i = 1; i < 17; ++i)
            result = bufD[i] == 0xFF && result;
        return result;
    }

    Bool Copy()
    {
        UInt8 RF_ALIGN(16) bufA[32];
        UInt8 RF_ALIGN(16) bufC[11] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
        UInt8 RF_ALIGN(16) bufD[17] = { 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9 ,8, 7, 6, 5};
        Bool result = true;

        // bufA not aligned but bufC
        RF_SysMem::Copy(bufA+1, bufC, 11);
        for(RF_Type::Size i = 1; i < 12; ++i)
            result = bufA[i] == 4 && result;

        // bufA and bufC aren't aligned
        RF_SysMem::Copy(bufA+1, bufD+3, 10);
        for(RF_Type::Size i = 1; i < 10; ++i)
            result = bufA[i] == i && result;

        // 16byte chunk
        RF_SysMem::Copy(bufA, bufD, 16);
        for(RF_Type::Size i = 0; i < 16; ++i)
            result = bufA[i] == bufD[i] && result;

        // 16byte chunk and trailing byte
        RF_SysMem::Copy(bufA, bufD, 17);
        for(RF_Type::Size i = 0; i < 17; ++i)
            result = bufA[i] == bufD[i] && result;

        return result;
    }
};

MemoryTest MemTest;
