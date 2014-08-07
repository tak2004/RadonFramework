#ifndef RF_DRAWING_NATIVESHAPE_HPP
#define RF_DRAWING_NATIVESHAPE_HPP

#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Memory/PointerID.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/Pair.hpp>

namespace RadonFramework { namespace Drawing {

class NativeShape
{
public:
    /// A handle represent a faster access token to a related Entry ID.
    typedef RF_Type::UInt32 Handle;
    enum PredefinedHandles{
        INVALID_HANDLE=65535
    };
    /// A ID will be used to identify a byte code block.
    typedef RF_Type::UInt16 ID;
    enum PredefinedIDs{
        INVALID_ID=65535
    };
    /// Each byte code segment is related to a Entry and can be identified and located by it.
    struct Entry
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

    void AssignByteCode(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Data,
        const ID StartupID=INVALID_ID, const ID ShutdownID=INVALID_ID);

    Handle GetCodeHandle(const ID ByID);

    void Execute(const Handle AHandle);

    // Step through all optimizations.
    void Optimize();

    void StripeOutUnchangedRegisterMoves();
protected:
    RF_Type::UInt16* m_EntryTableSize;
    Entry* m_EntryTable;
    RF_Type::UInt8* m_ByteCodeBlock;                
    RF_Mem::AutoPointerArray<RF_Type::UInt8> m_Data;
    typedef RF_Collect::Array<RF_Collect::Pair<Entry*,RF_Type::UInt32> > HandleDataList;
    HandleDataList m_HandleDataList;
};

} }

#ifndef RF_SHORTHAND_NAMESPACE_DRAW
#define RF_SHORTHAND_NAMESPACE_DRAW
namespace RF_Draw = RadonFramework::Drawing;
#endif

#endif // RF_DRAWING_NATIVESHAPE_HPP