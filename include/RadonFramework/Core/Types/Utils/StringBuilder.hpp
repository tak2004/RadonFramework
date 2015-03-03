#ifndef RF_CORE_TYPES_UITLS_STRINGBUILDER_HPP
#define RF_CORE_TYPES_UITLS_STRINGBUILDER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Types { namespace Utils {

/** This class can be used to build strings without generating 
* garbage because this class use an own memory allocator to build all Strings.
**/
class StringBuilder
{
public:
    /// Constructor
    StringBuilder();
    /// Destructor
    ~StringBuilder();
    /// Can be used to append a formatted string.
    StringBuilder& AppendFormat(const RF_Type::String& Format, ...);
    /// Append a line break to the end of the string.
    StringBuilder& AppendLine();
    ///
    StringBuilder& Append(const RF_Type::String& Value);
    /// Remove all character.
    void Clear();
    /// Ensure to provide the specified capacity.
    void EnsureCapacity(const RF_Type::Size NewCapacity);
    /// 
    StringBuilder& Insert(const RF_Type::String& Value, const RF_Type::Size Index);
    ///
    StringBuilder& Remove(const RF_Type::Size Index, const RF_Type::Size GlyphCount);
    ///
    StringBuilder& Replace(const RF_Type::String& ThisString, 
        const RF_Type::String& ByString);

    /// Length of the string.
    RF_Type::Size Length()const;
    /// Size in bytes of the string.
    RF_Type::Size Size()const;
    /// Available bytes.
    RF_Type::Size Capacity()const;
    /** Return the internal buffer as C-string.
    * Use this method for data access only and you should know what your doing.
    **/
    RF_Type::Char* AsCString()const;
    ///
    Memory::AutoPointer<RF_Type::String> ToString()const;
protected:
    RF_Type::Char* m_Data;
    RF_Type::Size m_Size;
    RF_Type::Size m_Length;
};

} } } }

#ifndef RF_SHORTHAND_NAMESPACE_COREUTIL
#define RF_SHORTHAND_NAMESPACE_COREUTIL
namespace RF_CoreUtil = RadonFramework::Core::Types::Utils;
#endif

#endif // RF_CORE_TYPES_UITLS_STRINGBUILDER_HPP