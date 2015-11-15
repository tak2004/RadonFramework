#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware/Vec128Int.hpp"
#include "RadonFramework/Collections/List.hpp"

namespace RadonFramework { namespace System { namespace Hardware {

void Load_SystemAPIDispatcher(RF_Type::Vec128Int32* Destination,
    const RF_Type::Vec128Int32* Source, const RF_Type::Size Elements)
{
    Load = 0;
    Dispatch();
    Assert(Load != Load_SystemAPIDispatcher &&
           Load != 0, "Funtion was called and couldn't be dispatched");
    Load(Destination, Source, Elements);
}

void SetInt32_SystemAPIDispatcher(RF_Type::Vec128Int32* Destination,
    const RF_Type::Int32 Source, const RF_Type::Size Elements)
{
    SetInt32 = 0;
    Dispatch();
    Assert(SetInt32 != SetInt32_SystemAPIDispatcher &&
           SetInt32 != 0, "Funtion was called and couldn't be dispatched");
    SetInt32(Destination, Source, Elements);
}

void CompareInt32_SystemAPIDispatcher(RF_Type::Vec128Int32* Destination,
    const RF_Type::Vec128Int32* SourceA, const RF_Type::Vec128Int32* SourceB,
    const RF_Type::Size Elements)
{
    CompareInt32 = 0;
    Dispatch();
    Assert(CompareInt32 != CompareInt32_SystemAPIDispatcher &&
           CompareInt32 != 0, "Funtion was called and couldn't be dispatched");
    CompareInt32(Destination, SourceA, SourceB, Elements);
}

void MaskInt8_SystemAPIDispatcher(RF_Type::Int32* Masks,
    const RF_Type::Vec128Int32* Source, const RF_Type::Size Elements)
{
    MaskInt8 = 0;
    Dispatch();
    Assert(MaskInt8 != MaskInt8_SystemAPIDispatcher &&
           MaskInt8 != 0, "Funtion was called and couldn't be dispatched");
    MaskInt8(Masks, Source, Elements);
}

LoadCallback Load;
SetInt32Callback SetInt32;
CompareInt32Callback CompareInt32;
MaskInt8Callback MaskInt8;

RF_Type::Bool IsSuccessfullyDispatched()
{
    RF_Type::Bool result = true;
    result = result && Load != Load_SystemAPIDispatcher && Load != 0;
    result = result && SetInt32 != SetInt32_SystemAPIDispatcher && SetInt32 != 0;
    result = result && CompareInt32 != CompareInt32_SystemAPIDispatcher && CompareInt32 != 0;
    result = result && MaskInt8 != MaskInt8_SystemAPIDispatcher && MaskInt8 != 0;
    return result;
}

void GetNotDispatchedFunctions(RF_Collect::List<RF_Type::String>& Result)
{
    if(Load == Load_SystemAPIDispatcher || Load == 0)
        Result.AddLast("Load");
    if(SetInt32 == SetInt32_SystemAPIDispatcher || SetInt32 == 0)
        Result.AddLast("SetInt32");
    if(CompareInt32 == CompareInt32_SystemAPIDispatcher || CompareInt32 == 0)
        Result.AddLast("CompareInt32");
    if(MaskInt8 == MaskInt8_SystemAPIDispatcher || MaskInt8 == 0)
        Result.AddLast("MaskInt8");
}

} } }