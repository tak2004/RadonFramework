#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/IO/File.hpp>
#include "RadonFramework/Core/Common/DataManagment.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"
#include "RadonFramework/Time/ScopeTimer.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/Memory/LinearAllocator.hpp"
#include "RadonFramework/Memory/HeapAllocator.hpp"
#include <new>

class LinearAllocatorTest:public RF_UnitTest::TestSuite
{
public:
    static const RF_Type::UInt32 INTALLOCATIONS = 10000000;
    static const RF_Type::UInt32 STUCTALLOCATIONS = 10000000;
    static const RF_Type::UInt32 CLASSALLOCATIONS = 10000000;

    using LinearAllocator = RF_Mem::LinearAllocator<RF_Mem::HeapAllocator, 4096, 16>;

    struct PODStruct
    {
        float a;
        int b;
        char c;
    };

    class NoPOD
    {
    public:
        NoPOD():b(9), d(0)
        {
        }
        float a;
        int b;
        char c;
        void* d;
    };

    RF_Mem::AutoPointerArray<int*> allocatedIntList;
    RF_Mem::AutoPointerArray<PODStruct*> allocatedPODList;
    RF_Mem::AutoPointerArray<NoPOD*> allocatedNoPODList;
    RF_Type::Size pageSize;
    RF_Type::Size reserveBytesForIntStack;
    RF_Type::Size reserveBytesForPODStack;
    RF_Type::Size reserveBytesForNoPODStack;

    LinearAllocatorTest()
    :TestSuite("RadonFramework::Memory::LinearAllocator"_rfs)
    {
        AddTest(MakeDelegate(this, &LinearAllocatorTest::DoCPlusPlusAllocation),
            "LinearAllocatorTest::DoCPlusPlusAllocation"_rfs,
            "Allocate int with c++ new/delete 10000000x"_rfs);
        AddTest(MakeDelegate(this, &LinearAllocatorTest::DoLinearAllocation),
            "LinearAllocatorTest::DoLinearAllocation"_rfs,
            "Allocate int from LinearAllocator 10000000x"_rfs);
        AddTest(MakeDelegate(this, &LinearAllocatorTest::DoCPlusPlusAllocationPOD),
            "LinearAllocatorTest::DoCPlusPlusAllocationPOD"_rfs,
            "Allocate POD struct with c++ new/delete 10000000x"_rfs);
        AddTest(MakeDelegate(this, &LinearAllocatorTest::DoLinearAllocationPOD),
            "LinearAllocatorTest::DoLinearAllocationPOD"_rfs,
            "Allocate POD struct from LinearAllocator 10000000x"_rfs);
        AddTest(MakeDelegate(this, &LinearAllocatorTest::DoCPlusPlusAllocationNoPOD),
            "LinearAllocatorTest::DoCPlusPlusAllocationNoPOD"_rfs,
            "Allocate a class with c++ new/delete 10000000x"_rfs);
        AddTest(MakeDelegate(this, &LinearAllocatorTest::DoLinearAllocationNoPOD),
            "LinearAllocatorTest::DoLinearAllocationNoPOD"_rfs,
            "Allocate a class from LinearAllocator 10000000x"_rfs);
    }

    void SetUp()
    {
        allocatedIntList = RF_Mem::AutoPointerArray<int*>(new int*[INTALLOCATIONS], INTALLOCATIONS);
        allocatedPODList = RF_Mem::AutoPointerArray<PODStruct*>(new PODStruct*[STUCTALLOCATIONS], STUCTALLOCATIONS);
        allocatedNoPODList = RF_Mem::AutoPointerArray<NoPOD*>(new NoPOD*[CLASSALLOCATIONS], CLASSALLOCATIONS);
        pageSize = RF_SysMem::GetPageSize();
        reserveBytesForIntStack = (((sizeof(int) + sizeof(RF_Type::Size))*INTALLOCATIONS) / pageSize + 1)*pageSize;
        reserveBytesForPODStack = (((sizeof(PODStruct) + sizeof(RF_Type::Size))*STUCTALLOCATIONS) / pageSize + 1)*pageSize;
        reserveBytesForNoPODStack = (((sizeof(NoPOD) + sizeof(RF_Type::Size))*CLASSALLOCATIONS) / pageSize + 1)*pageSize;
    }

    RF_Type::Bool DoCPlusPlusAllocation()
    {
        for(RF_Type::UInt32 i = 0; i < INTALLOCATIONS; ++i)
            allocatedIntList[i] = new int;
        for(RF_Type::UInt32 i = 0; i < INTALLOCATIONS; ++i)
            delete allocatedIntList[i];
        return true;
    }

    RF_Type::Bool DoLinearAllocation()
    {
        LinearAllocator linearAllocator(reserveBytesForIntStack);
        for(RF_Type::UInt32 i = 0; i < INTALLOCATIONS; ++i)
            linearAllocator.Allocate(sizeof(int));
        return true;
    }

    RF_Type::Bool DoCPlusPlusAllocationPOD()
    {
        for(RF_Type::UInt32 i = 0; i < STUCTALLOCATIONS; ++i)
            allocatedPODList[i] = new PODStruct;
        for(RF_Type::UInt32 i = 0; i < STUCTALLOCATIONS; ++i)
            delete allocatedPODList[i];
        return true;
    }

    RF_Type::Bool DoLinearAllocationPOD()
    {
        LinearAllocator linearAllocator(reserveBytesForPODStack);
        for(RF_Type::UInt32 i = 0; i < STUCTALLOCATIONS; ++i)
            linearAllocator.Allocate(sizeof(PODStruct));
        return true;
    }

    RF_Type::Bool DoCPlusPlusAllocationNoPOD()
    {
        for(RF_Type::UInt32 i = 0; i < CLASSALLOCATIONS; ++i)
            allocatedNoPODList[i] = new NoPOD;
        for(RF_Type::UInt32 i = 0; i < CLASSALLOCATIONS; ++i)
            delete allocatedNoPODList[i];
        return true;
    }

    RF_Type::Bool DoLinearAllocationNoPOD()
    {
        LinearAllocator linearAllocator(reserveBytesForNoPODStack);

        RF_Mem::MemoryBlock blocks[CLASSALLOCATIONS];
        for(RF_Type::UInt32 i = 0; i < CLASSALLOCATIONS; ++i)
        {
            blocks[i] = linearAllocator.Allocate(sizeof(NoPOD));
            NoPOD* obj = new(blocks[i].Data) NoPOD;
        }
        for(RF_Type::UInt32 i = 0; i < CLASSALLOCATIONS; ++i)
        {
            NoPOD* p = reinterpret_cast<NoPOD*>(blocks[i].Data);
            p->~NoPOD();
        }
        linearAllocator.DeallocateAll();
        return true;
    }
};

LinearAllocatorTest LinearAllocatorTestInstance;