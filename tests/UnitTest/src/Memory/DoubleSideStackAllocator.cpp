#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>
#include <RadonFramework/Memory/DoubleSideStackAllocator.hpp>

class DoubleSideStackAllocatorTest :public RF_Test::TestSuite
{
public:
    DoubleSideStackAllocatorTest()
    :TestSuite("RadonFramework::Memory::DoubleSideStack-Test")
    {
        AddTest(MakeDelegate(this, &DoubleSideStackAllocatorTest::Constructor),
            "DoubleSideStackAllocatorTest::Constructor", "Constructor");
        AddTest(MakeDelegate(this, &DoubleSideStackAllocatorTest::ClearBoth),
            "DoubleSideStackAllocatorTest::ClearBoth", "ClearBoth");
        AddTest(MakeDelegate(this, &DoubleSideStackAllocatorTest::PushPersistant),
            "DoubleSideStackAllocatorTest::PushPersistant", "PushPersistant");
        AddTest(MakeDelegate(this, &DoubleSideStackAllocatorTest::PushTemporary),
            "DoubleSideStackAllocatorTest::PushTemporary", "PushTemporary");
        AddTest(MakeDelegate(this, &DoubleSideStackAllocatorTest::PopPersistant),
            "DoubleSideStackAllocatorTest::PopPersistant", "PopPersistant");
        AddTest(MakeDelegate(this, &DoubleSideStackAllocatorTest::PopTemporary),
            "DoubleSideStackAllocatorTest::PopTemporary", "PopTemporary");
        AddTest(MakeDelegate(this, &DoubleSideStackAllocatorTest::PeekPersistant),
            "DoubleSideStackAllocatorTest::PeekPersistant", "PeekPersistant");
        AddTest(MakeDelegate(this, &DoubleSideStackAllocatorTest::PeekTemporary),
            "DoubleSideStackAllocatorTest::PeekTemporary", "PeekTemporary");
        AddTest(MakeDelegate(this, &DoubleSideStackAllocatorTest::PeekSizePersistant),
            "DoubleSideStackAllocatorTest::PeekSizePersistant", "PeekSizePersistant");
        AddTest(MakeDelegate(this, &DoubleSideStackAllocatorTest::PeekSizeTemporary),
            "DoubleSideStackAllocatorTest::PeekSizeTemporary", "PeekSizeTemporary");
    }

    RF_Type::Bool Constructor()
    {
        RF_Type::Bool result = false;
        RF_Mem::DoubleSideStackAllocator stack(4096);

        result = stack.CombinedStackSize() == 0 &&
            stack.ReservedSize() == 4096 &&
            stack.PersistantStackSize() == 0 &&
            stack.TemporaryStackSize() == 0 &&
            stack.FillZeroIfFreed() == false &&
            stack.FillZeroIfPoped() == false;
        return result;
    }

    RF_Type::Bool ClearBoth()
    {
        RF_Type::Bool result = false;
        RF_Mem::DoubleSideStackAllocator stack(4096);
        stack.PushPersistent(12);
        stack.PushTemporary(24);
        stack.ClearBoth();

        result = stack.CombinedStackSize() == 0 &&
            stack.PersistantStackSize() == 0 &&
            stack.TemporaryStackSize() == 0;

        return result;
    }

    RF_Type::Bool PushPersistant()
    {
        RF_Type::Bool result = false;
        RF_Mem::DoubleSideStackAllocator stack(4096);
        stack.PushPersistent(12);

        result = stack.CombinedStackSize() == 12 &&
            stack.PersistantStackSize() == 12;

        return result;
    }

    RF_Type::Bool PushTemporary()
    {
        RF_Type::Bool result = false;
        RF_Mem::DoubleSideStackAllocator stack(4096);
        stack.PushTemporary(12);

        result = stack.CombinedStackSize() == 12 &&
            stack.TemporaryStackSize() == 12;

        return result;
    }

    RF_Type::Bool PopPersistant()
    {
        RF_Type::Bool result = false;
        RF_Mem::DoubleSideStackAllocator stack(4096);
        stack.PushPersistent(12);
        stack.PopPersistent();

        result = stack.CombinedStackSize() == 0 &&
            stack.PersistantStackSize() == 0;

        return result;
    }

    RF_Type::Bool PopTemporary()
    {
        RF_Type::Bool result = false;
        RF_Mem::DoubleSideStackAllocator stack(4096);
        stack.PushTemporary(12);
        stack.PopTemporary();

        result = stack.CombinedStackSize() == 0 &&
            stack.TemporaryStackSize() == 0;

        return result;
    }

    RF_Type::Bool PeekPersistant()
    {
        RF_Type::Bool result;
        RF_Mem::DoubleSideStackAllocator stack(4096);
        result = stack.PeekPersistent() == 0;
        stack.PushPersistent(12);
        result &= stack.PeekPersistent() != 0;

        return result;
    }

    RF_Type::Bool PeekTemporary()
    {
        RF_Type::Bool result;
        RF_Mem::DoubleSideStackAllocator stack(4096);
        result = stack.PeekTemporary() == 0;
        stack.PushTemporary(12);
        result &= stack.PeekTemporary() != 0;

        return result;
    }

    RF_Type::Bool PeekSizePersistant()
    {
        RF_Type::Bool result;
        RF_Mem::DoubleSideStackAllocator stack(4096);
        result = stack.PeekSizePersistent() == 0;
        stack.PushPersistent(12);
        result &= stack.PeekSizePersistent() == 12;

        return result;
    }

    RF_Type::Bool PeekSizeTemporary()
    {
        RF_Type::Bool result;
        RF_Mem::DoubleSideStackAllocator stack(4096);
        result = stack.PeekSizeTemporary() == 0;
        stack.PushTemporary(12);
        result &= stack.PeekSizeTemporary() == 12;

        return result;
    }

    RF_Type::Bool ClearPersistant()
    {
        RF_Type::Bool result = false;
        RF_Mem::DoubleSideStackAllocator stack(4096);
        stack.PushPersistent(12);
        stack.ClearPersistent();

        result = stack.CombinedStackSize() == 0 &&
            stack.PersistantStackSize() == 0;

        return result;
    }

    RF_Type::Bool ClearTemporary()
    {
        RF_Type::Bool result = false;
        RF_Mem::DoubleSideStackAllocator stack(4096);
        stack.PushTemporary(12);
        stack.ClearTemporary();

        result = stack.CombinedStackSize() == 0 &&
            stack.TemporaryStackSize() == 0;

        return result;
    }
};  