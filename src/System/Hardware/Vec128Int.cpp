#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/Hardware/Vec128Int.hpp"
#include "RadonFramework/Collections/List.hpp"

namespace RadonFramework { namespace System { namespace Hardware {

void Vec128Load_SystemAPIDispatcher(RF_Type::Vec128Int32* Destination,
    const RF_Type::Vec128Int32* Source, const RF_Type::Size Elements)
{
    Vec128IntLoad = 0;
    DispatchVec128Int();
    Assert(Vec128IntLoad != Vec128Load_SystemAPIDispatcher &&
        Vec128IntLoad != 0, "Funtion was called and couldn't be dispatched");
    Vec128IntLoad(Destination, Source, Elements);
}

void Vec128SetInt32_SystemAPIDispatcher(RF_Type::Vec128Int32* Destination,
    const RF_Type::Int32 Source, const RF_Type::Size Elements)
{
    Vec128IntSetInt32 = 0;
    DispatchVec128Int();
    Assert(Vec128IntSetInt32 != Vec128SetInt32_SystemAPIDispatcher &&
        Vec128IntSetInt32 != 0, "Funtion was called and couldn't be dispatched");
    Vec128IntSetInt32(Destination, Source, Elements);
}

void Vec128CompareInt32_SystemAPIDispatcher(RF_Type::Vec128Int32* Destination,
    const RF_Type::Vec128Int32* SourceA, const RF_Type::Vec128Int32* SourceB,
    const RF_Type::Size Elements)
{
    Vec128IntCompareInt32 = 0;
    DispatchVec128Int();
    Assert(Vec128IntCompareInt32 != Vec128CompareInt32_SystemAPIDispatcher &&
        Vec128IntCompareInt32 != 0, "Funtion was called and couldn't be dispatched");
    Vec128IntCompareInt32(Destination, SourceA, SourceB, Elements);
}

void Vec128MaskInt8_SystemAPIDispatcher(RF_Type::Int32* Masks,
    const RF_Type::Vec128Int32* Source, const RF_Type::Size Elements)
{
    Vec128IntMaskInt8 = 0;
    DispatchVec128Int();
    Assert(Vec128IntMaskInt8 != Vec128MaskInt8_SystemAPIDispatcher &&
        Vec128IntMaskInt8 != 0, "Funtion was called and couldn't be dispatched");
    Vec128IntMaskInt8(Masks, Source, Elements);
}

RF_Type::Int32 Vec128IntFindInt32_SystemAPIDispatcher(
    const RF_Type::Vec128Int32* Source, RF_Type::Int32 Value)
{
    Vec128IntFindInt32 = 0;
    DispatchVec128Int();
    Assert(Vec128IntFindInt32 != Vec128IntFindInt32_SystemAPIDispatcher &&
        Vec128IntFindInt32 != 0, "Funtion was called and couldn't be dispatched");
    return Vec128IntFindInt32(Source, Value);
}

Vec128IntLoadCallback Vec128IntLoad;
Vec128IntSetInt32Callback Vec128IntSetInt32;
Vec128IntCompareInt32Callback Vec128IntCompareInt32;
Vec128IntMaskInt8Callback Vec128IntMaskInt8;
Vec128IntFindInt32Callback Vec128IntFindInt32;

void DispatchVec128Int()
{
#if RF_BUILD_INTRINSIC_SSE2
    extern void DispatchSSE2();
    DispatchSSE2();
#endif
#if RF_BUILD_INTRINSIC_NEON
    extern void DispatchNEON();
    DispatchNEON();
#endif
}

RF_Type::Bool IsVec128IntSuccessfullyDispatched()
{
    RF_Type::Bool result = true;
    result = result && Vec128IntLoad != Vec128Load_SystemAPIDispatcher && Vec128IntLoad != 0;
    result = result && Vec128IntSetInt32 != Vec128SetInt32_SystemAPIDispatcher && Vec128IntSetInt32 != 0;
    result = result && Vec128IntCompareInt32 != Vec128CompareInt32_SystemAPIDispatcher && Vec128IntCompareInt32 != 0;
    result = result && Vec128IntMaskInt8 != Vec128MaskInt8_SystemAPIDispatcher && Vec128IntMaskInt8 != 0;
    result = result && Vec128IntFindInt32 != Vec128IntFindInt32_SystemAPIDispatcher && Vec128IntFindInt32 != 0;
    return result;
}

void GetNotDispatchedVec128IntFunctions(RF_Collect::List<RF_Type::String>& Result)
{
    if(Vec128IntLoad == Vec128Load_SystemAPIDispatcher || Vec128IntLoad == 0)
        Result.AddLast("Vec128IntLoad");
    if(Vec128IntSetInt32 == Vec128SetInt32_SystemAPIDispatcher || Vec128IntSetInt32 == 0)
        Result.AddLast("Vec128IntSetInt32");
    if(Vec128IntCompareInt32 == Vec128CompareInt32_SystemAPIDispatcher || Vec128IntCompareInt32 == 0)
        Result.AddLast("Vec128IntCompareInt32");
    if(Vec128IntMaskInt8 == Vec128MaskInt8_SystemAPIDispatcher || Vec128IntMaskInt8 == 0)
        Result.AddLast("Vec128IntMaskInt8");
    if(Vec128IntFindInt32 == Vec128IntFindInt32_SystemAPIDispatcher || Vec128IntFindInt32 == 0)
        Result.AddLast("Vec128IntFindInt32");
}

} } }