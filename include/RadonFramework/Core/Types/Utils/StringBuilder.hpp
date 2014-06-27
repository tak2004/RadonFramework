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
    StringBuilder& AppendFormat(const RFTYPE::String& Format, ...);
    /// Append a line break to the end of the string.
    StringBuilder& AppendLine();
    ///
    StringBuilder& Append(const RFTYPE::String& Value);
    /// Remove all character.
    void Clear();
    /// Ensure to provide the specified capacity.
    void EnsureCapacity(const RFTYPE::Size NewCapacity);
    /// 
    StringBuilder& Insert(const RFTYPE::String& Value, const RFTYPE::Size Index);
    ///
    StringBuilder& Remove(const RFTYPE::Size Index, const RFTYPE::Size GlyphCount);
    ///
    StringBuilder& Replace(const RFTYPE::String& ThisString, 
        const RFTYPE::String& ByString);

    /// Length of the string.
    RFTYPE::Size Length()const;
    /// Size in bytes of the string.
    RFTYPE::Size Size()const;
    /// Available bytes.
    RFTYPE::Size Capacity()const;
    /** Return the internal buffer as C-string.
    * Use this method for data access only and you should know what your doing.
    **/
    RFTYPE::Char* AsCString()const;
    ///
    Memory::AutoPointer<RFTYPE::String> ToString()const;
protected:
    RFTYPE::Char* m_Data;
    RFTYPE::Size m_Size;
    RFTYPE::Size m_Length;
};

} } } }

#endif // RF_CORE_TYPES_UITLS_STRINGBUILDER_HPP