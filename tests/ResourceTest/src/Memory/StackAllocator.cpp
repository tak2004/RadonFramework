#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/IO/File.hpp>
#include "RadonFramework/Core/Common/DataManagment.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"
#include "RadonFramework/Time/ScopeTimer.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/Memory/StackAllocator.hpp"
#include <new>

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Common;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Memory;
using namespace RadonFramework::IO;
using namespace RadonFramework::Time;

class StackAllocatorTest:public TestSuite
{
public:
    static const UInt32 INTALLOCATIONS=10000000;
    static const UInt32 STUCTALLOCATIONS=10000000;
    static const UInt32 CLASSALLOCATIONS=10000000;

    struct PODStruct
    {
        float a;
        int b;
        char c;
    };

    class NoPOD
    {
    public:
        NoPOD():b(9),d(0){}
        float a;
        int b;
        char c;
        void* d;
    };

    AutoPointerArray<int*> allocatedIntList;
    AutoPointerArray<PODStruct*> allocatedPODList;
    AutoPointerArray<NoPOD*> allocatedNoPODList;
    Size pageSize;
    Size reserveBytesForIntStack;
    Size reserveBytesForPODStack;
    Size reserveBytesForNoPODStack;

    StackAllocatorTest()
        :TestSuite("RadonFramework::Memory::StackAllocator")
    {
        AddTest(MakeDelegate(this,&StackAllocatorTest::DoCPlusPlusAllocation), "StackAllocatorTest::DoCPlusPlusAllocation", "Allocate int with c++ new/delete 10000000x");
        AddTest(MakeDelegate(this,&StackAllocatorTest::DoStackAllocation),"StackAllocatorTest::DoStackAllocation","Allocate int from StackAllocator 10000000x");
        AddTest(MakeDelegate(this,&StackAllocatorTest::DoCPlusPlusAllocationPOD),"StackAllocatorTest::DoCPlusPlusAllocationPOD","Allocate POD struct with c++ new/delete 10000000x");
        AddTest(MakeDelegate(this,&StackAllocatorTest::DoStackAllocationPOD),"StackAllocatorTest::DoStackAllocationPOD","Allocate POD struct from StackAllocator 10000000x");
        AddTest(MakeDelegate(this,&StackAllocatorTest::DoCPlusPlusAllocationNoPOD),"StackAllocatorTest::DoCPlusPlusAllocationNoPOD","Allocate a class with c++ new/delete 10000000x");
        AddTest(MakeDelegate(this,&StackAllocatorTest::DoStackAllocationNoPOD),"StackAllocatorTest::DoStackAllocationNoPOD","Allocate a class from StackAllocator 10000000x");
    }

    void SetUp()
    {
        allocatedIntList=AutoPointerArray<int*>(new int*[INTALLOCATIONS], INTALLOCATIONS);
        allocatedPODList=AutoPointerArray<PODStruct*>(new PODStruct*[STUCTALLOCATIONS], STUCTALLOCATIONS);
        allocatedNoPODList=AutoPointerArray<NoPOD*>(new NoPOD*[CLASSALLOCATIONS], CLASSALLOCATIONS);
        pageSize=RF_SysMem::GetPageSize();
        reserveBytesForIntStack=(((sizeof(int)+sizeof(Size))*INTALLOCATIONS)/pageSize+1)*pageSize;
        reserveBytesForPODStack=(((sizeof(PODStruct)+sizeof(Size))*STUCTALLOCATIONS)/pageSize+1)*pageSize;
        reserveBytesForNoPODStack=(((sizeof(NoPOD)+sizeof(Size))*CLASSALLOCATIONS)/pageSize+1)*pageSize;
    }

    Bool DoCPlusPlusAllocation()
    {
        for (UInt32 i=0;i<INTALLOCATIONS;++i)
            allocatedIntList[i]=new int;
        for(UInt32 i=0;i<INTALLOCATIONS;++i)
            delete allocatedIntList[i];
        return true;
    }

    Bool DoStackAllocation()
    {
        StackAllocator stackAllocator(reserveBytesForIntStack);
        for (UInt32 i=0;i<INTALLOCATIONS;++i)
            stackAllocator.Push(sizeof(int));
        return true;
    }

    Bool DoCPlusPlusAllocationPOD()
    {
        for (UInt32 i=0;i<STUCTALLOCATIONS;++i)
            allocatedPODList[i]=new PODStruct;
        for(UInt32 i=0;i<STUCTALLOCATIONS;++i)
            delete allocatedPODList[i];
        return true;
    }

    Bool DoStackAllocationPOD()
    {
        StackAllocator stackAllocator(reserveBytesForPODStack);
        for (UInt32 i=0;i<STUCTALLOCATIONS;++i)
            stackAllocator.Push(sizeof(PODStruct));
        return true;
    }

    Bool DoCPlusPlusAllocationNoPOD()
    {
        for (UInt32 i=0;i<CLASSALLOCATIONS;++i)
            allocatedNoPODList[i]=new NoPOD;
        for(UInt32 i=0;i<CLASSALLOCATIONS;++i)
            delete allocatedNoPODList[i];
        return true;
    }

    Bool DoStackAllocationNoPOD()
    {
        StackAllocator stackAllocator(reserveBytesForNoPODStack);
        for (UInt32 i=0;i<CLASSALLOCATIONS;++i)
        {
            void* p=stackAllocator.Push(sizeof(NoPOD));
            NoPOD* obj=new(p) NoPOD;
        }
        for (UInt32 i=0;i<CLASSALLOCATIONS;++i)
        {
            NoPOD* p=reinterpret_cast<NoPOD*>(stackAllocator.Peek());
            p->~NoPOD();
            stackAllocator.Pop();
        }
        return true;
    }
};

//StackAllocatorTest StackAllocatorTestInstance;