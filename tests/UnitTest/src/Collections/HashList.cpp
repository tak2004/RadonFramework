#include <RadonFramework/precompiled.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/TestSuite.hpp>
#include <RadonFramework/Diagnostics/Debugging/UnitTest/UnitTest.hpp>
#include <RadonFramework/Core/Pattern/Delegate.hpp>

#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Collections/AutoVector.hpp>
#include <RadonFramework/Collections/HashList.hpp>
#include <type_traits>

class TestAllocator:public RadonFramework::Core::Policies::ValueAllocator
{
public:
    void* Allocate(RF_Type::Size Bytes, RF_Type::Size Alignment)
    {
        void* result = 0;
        auto memoryBlock = RF_Mem::AutoPointerArray<RF_Type::UInt8>(Bytes);
        result = memoryBlock.Get();
        memory.PushBack(memoryBlock);
        return result;
    }
    void* Reallocate(void* Ptr, RF_Type::Size NewBytes)
    {
        return 0;
    }
    void Free(void* Memory)
    {
        for(RF_Type::Size i = 0; i < memory.Count(); ++i)
        {
            if(memory[i] == Memory)
            {
                memory.Erase(i);
                break;
            }
        }
    }

    RF_Collect::AutoVector<RF_Type::UInt8> memory;
};

class HashListTest:public RF_UnitTest::TestSuite
{
public:
    HashListTest()
    :TestSuite("RadonFramework::Collections::HashList-Test"_rfs)
    {
        AddTest(MakeDelegate(this, &HashListTest::Constructor),
            "HashListTest::Constructor"_rfs, "Constructor"_rfs);
        AddTest(MakeDelegate(this, &HashListTest::Destructor),
            "HashListTest::Destructor"_rfs, "Destructor"_rfs);
        AddTest(MakeDelegate(this, &HashListTest::ContainsKey),
            "HashListTest::ContainsKey"_rfs, "ContainsKey"_rfs);
        AddTest(MakeDelegate(this, &HashListTest::Clear),
            "HashListTest::Clear"_rfs, "Clear"_rfs);
        AddTest(MakeDelegate(this, &HashListTest::Count),
            "HashListTest::Count"_rfs, "Count"_rfs);
        AddTest(MakeDelegate(this, &HashListTest::Capacity),
                "HashListTest::Capacity"_rfs, "Capacity"_rfs);
        AddTest(MakeDelegate(this, &HashListTest::Get),
            "HashListTest::Get"_rfs, "Get"_rfs);
        AddTest(MakeDelegate(this, &HashListTest::Add),
                "HashListTest::Add"_rfs, "Add"_rfs);
        AddTest(MakeDelegate(this, &HashListTest::Erase),
            "HashListTest::Erase"_rfs, "Erase"_rfs);
        AddTest(MakeDelegate(this, &HashListTest::GetEmptyKey),
            "HashListTest::GetEmptyKey"_rfs, "GetEmptyKey"_rfs);
        AddTest(MakeDelegate(this, &HashListTest::Clone),
            "HashListTest::Clone"_rfs, "Clone"_rfs);
        AddTest(MakeDelegate(this, &HashListTest::Grow),
                "HashListTest::Grow"_rfs, "Grow"_rfs);
        AddTest(MakeDelegate(this, &HashListTest::EnsureCopyProtection),
            "HashListTest::EnsureCopyProtection"_rfs, "EnsureCopyProtection"_rfs);
    }

    RF_Type::Bool Constructor()
    {
        RF_Type::Bool result = true;
        TestAllocator testAllocator;
        RF_Collect::HashList defaultConstructor;
        RF_Collect::HashList preAllocatedConstructor(1);
        RF_Collect::HashList hashList(&testAllocator, 1);
        result &= defaultConstructor.Capacity() == 0;
        result &= defaultConstructor.Count() == 0;
        result &= preAllocatedConstructor.Capacity() >= 1;
        result &= preAllocatedConstructor.Count() == 0;
        result &= hashList.Capacity() >= 1;
        result &= hashList.Count() == 0;
        result &= testAllocator.memory.Count() > 0;
        return result;
    }

    RF_Type::Bool Destructor()
    {
        RF_Type::Bool result = true;
        TestAllocator testAllocator;
        RF_Collect::HashList* hashList= new RF_Collect::HashList(&testAllocator, 1);
        delete hashList;
        result &= testAllocator.memory.Count() == 0;
        return result;
    }

    RF_Type::Bool ContainsKey()
    {
        RF_Type::Bool result = true;
        RF_Collect::HashList hashList;
        int v = 5;
        result &= hashList.Add(9, &v) == true;
        result &= hashList.ContainsKey(9) == true;
        result &= hashList.ContainsKey(10) == false;
        return result;
    }

    RF_Type::Bool Clear()
    {
        RF_Type::Bool result = true;
        RF_Collect::HashList hashList;
        int v = 5;
        result &= hashList.Add(9, &v) == true;
        result &= hashList.Count() == 1;
        hashList.Clear();
        result &= hashList.Count() == 0;
        hashList.Clear();
        result &= hashList.Count() == 0;
        return result;
    }

    RF_Type::Bool Count()
    {
        RF_Type::Bool result = true;
        RF_Collect::HashList hashList(1);
        result &= hashList.Count() == 0;
        result &= hashList.Add(9,0) == true;
        result &= hashList.Count() == 1;
        return result;
    }

    RF_Type::Bool Capacity()
    {
        RF_Type::Bool result = true;
        RF_Collect::HashList hashList;
        result &= hashList.Capacity() == 0;
        result &= hashList.Add(9, 0) == true;
        result &= hashList.Capacity() > 0;
        return result;
    }

    RF_Type::Bool Add()
    {
        RF_Type::Bool result = true;
        RF_Collect::HashList hashList;
        int v = 5;        
        void* o = 0;
        result &= hashList.Add(9, &v) == true;
        result &= hashList.Get(9, o) == true;
        result &= o == &v;
        result &= hashList.Add(9+hashList.Capacity(), &v) == true;
        result &= hashList.Add(9, &v) == false;
        return result;
    }

    RF_Type::Bool Grow()
    {
        RF_Type::Bool result = true;
        RF_Collect::HashList hashList;

        result &= hashList.Count() == 0;
        result &= hashList.Capacity() == 0;

        RF_Type::Size lastCapacity = hashList.Capacity();
        hashList.Add(9, 0);

        result &= hashList.Count() == 1;
        result &= hashList.Capacity() > lastCapacity;
        lastCapacity = hashList.Capacity();

        for (RF_Type::Size i = 0; i < 5000; ++i)
        {
            hashList.Add(9+i, 0);
        }

        result &= hashList.Count() == 5000;
        result &= hashList.Capacity() > lastCapacity;
        return result;
    }

    RF_Type::Bool Get()
    {
        RF_Type::Bool result = true;
        RF_Collect::HashList hashList;
        int v = 5;
        void* o = 0;
        result &= hashList.Add(9, &v) == true;
        result &= hashList.Get(9, o) == true;
        result &= o == &v;
        result &= hashList.Get(10, o) == false;
        return result;
    }

    RF_Type::Bool Erase()
    {
        RF_Type::Bool result = true;
        RF_Collect::HashList hashList;
        int v = 5;
        hashList.Add(9, &v);
        result &= hashList.ContainsKey(9) == true;
        hashList.Erase(9);
        result &= hashList.ContainsKey(9) == false;
        hashList.Erase(9);
        result &= hashList.ContainsKey(9) == false;
        return result;
    }

    RF_Type::Bool GetEmptyKey()
    {
        RF_Collect::HashList hashList;
        return hashList.GetEmptyKey() == 0;
    }

    RF_Type::Bool Clone()
    {
        RF_Type::Bool result = true;
        RF_Collect::HashList hashList;
        RF_Collect::HashList hashListClone;
        int v = 5;
        hashListClone.Add(5, &v);
        result &= hashListClone.Count() == 1;
        result &= hashListClone.Capacity() >= 1;
        hashListClone.Clone(hashList);
        result &= hashListClone.Count() == 0;
        result &= hashListClone.Capacity() == 0;
        return result;
    }

    RF_Type::Bool EnsureCopyProtection()
    {
        RF_Type::Bool result = std::is_copy_assignable<RF_Collect::HashList>::value == false;
        #if !__GNUG__ && __GNUC__ < 5
            result &= std::is_trivially_copy_assignable<RF_Collect::HashList>::value == false;
        #endif
        result &= std::is_nothrow_copy_assignable<RF_Collect::HashList>::value == false;
        result &= std::is_move_assignable<RF_Collect::HashList>::value == false;
        #if !__GNUG__ && __GNUC__ < 5
            result &= std::is_trivially_move_assignable<RF_Collect::HashList>::value == false;
        #endif
        result &= std::is_nothrow_move_assignable<RF_Collect::HashList>::value == false;
        result &= std::is_copy_constructible<RF_Collect::HashList>::value == false;
        #if !__GNUG__ && __GNUC__ < 5
            result &= std::is_trivially_copy_constructible<RF_Collect::HashList>::value == false;
        #endif
        result &= std::is_nothrow_copy_constructible<RF_Collect::HashList>::value == false;
        result &= std::is_move_constructible<RF_Collect::HashList>::value == false;
        #if !__GNUG__ && __GNUC__ < 5
            result &= std::is_trivially_move_constructible<RF_Collect::HashList>::value == false;
        #endif
        result &= std::is_nothrow_move_constructible<RF_Collect::HashList>::value == false;
        return result;
    }
};

HashListTest HashListTestInstance;
