#ifndef RF_DRAWING_NATIVESHAPE_HPP
#define RF_DRAWING_NATIVESHAPE_HPP

#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Memory/PointerID.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/Pair.hpp>

namespace RadonFramework { namespace Drawing {

/* This class 
 *
 **/
class NativeShape
{
public:
    /// A handle represent a faster access token to a related State ID.
    typedef RF_Type::UInt32 Handle;
    enum class PredefinedHandles:Handle
    {
        Invalid=65535
    };
    /// A ID will be used to identify a byte code block.
    typedef RF_Type::UInt16 ID;
    enum class PredefinedIDs:ID
    {
        Startup = 0,
        Shutdown = 1,
        Invalid = 65535
    };
    /// Each byte code segment is related to an State and can be identified and located by it.
    struct State
    {
        /// Byte code entry identifier.
        ID Identifier;
        /// Size of the byte code
        RF_Type::UInt16 ByteCodeSize;
    };

    NativeShape();
    NativeShape(const NativeShape& Copy);
    NativeShape& operator=(const NativeShape& Other);
    ~NativeShape();

    void AssignByteCode(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Move);
    
    void AssignByteCode(RF_Mem::AutoPointerArray<RF_Type::UInt8>&& Move);

    void AddState(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data);

    Handle GetCodeHandle(const ID ByID);

    template<typename T>
    void MapVariable(RF_Type::UInt64 Hash, T Value);

    void AssignDataStream(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Stream);

    void Execute(const Handle AHandle);

    // Step through all optimizations.
    void Optimize();

    void StripeOutUnchangedRegisterMoves();
protected:
    RF_Type::UInt16* m_EntryTableSize;
    State* m_EntryTable;
    RF_Type::UInt8* m_ByteCodeBlock;
    RF_Mem::AutoPointerArray<RF_Type::UInt8> m_Data;
    typedef RF_Collect::Array<RF_Collect::Pair<State*, RF_Type::UInt32> > HandleDataList;
    HandleDataList m_HandleDataList;
};

template<typename T>
void NativeShape::MapVariable(RF_Type::UInt64 Hash, T Value)
{

}

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_NATIVESHAPE_HPP