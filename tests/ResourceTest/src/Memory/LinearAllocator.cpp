#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp"
#include "RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp"
#include "RadonFramework/Core/Pattern/Delegate.hpp"
#include "RadonFramework/Core/Common/DataManagment.hpp"
#include "RadonFramework/Time/TimeSpan.hpp"
#include "RadonFramework/Time/ScopeTimer.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/Memory/LinearAllocator.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Core::Common;
using namespace RadonFramework::Diagnostics::Debugging::UnitTest;
using namespace RadonFramework::Memory;
using namespace RadonFramework::Time;

class LinearAllocatorTest:public TestSuite
{
public:
    static const UInt32 BLOBALLOCATIONS=1000;

    typedef UInt8 Blob[4096];

    Size pageSize;
    Size reserveBytes;

    LinearAllocatorTest()
    :TestSuite("RadonFramework::Memory::LinearAllocator")
    {
        AddTest(MakeDelegate(this,&LinearAllocatorTest::AllocationThroughput),"Test linear allocator allocation throughput(4MB)");
    }

    void SetUp()
    {
        pageSize=RFMEM::GetPageSize();
        reserveBytes=((sizeof(Blob)*BLOBALLOCATIONS)/pageSize+1)*pageSize;
    }

    Bool AllocationThroughput()
    {
        LinearAllocator* allocator = LinearAllocator::CreateInstance(reserveBytes);
        for (UInt32 i=0; i<BLOBALLOCATIONS; ++i)
            allocator->Allocate(sizeof(Blob));
        allocator->ClearInstance();
        LinearAllocator::FreeInstance(allocator);
        return true;
    }
};

LinearAllocatorTest LinearAllocatorTestInstance;