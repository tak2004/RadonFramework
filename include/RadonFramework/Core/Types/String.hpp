#ifndef RF_CORE_TYPES_STRING_HPP
#define RF_CORE_TYPES_STRING_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Collections/ArrayEnumerator.hpp>

namespace RadonFramework
{
    namespace Core
    {
        namespace Types
        {
            /** @brief Standard String class.
              *
              * The String class use a 32Bit unsigned integer as length type(4294967295 characters as maximum).
              * This class consist of three variables, first m_Length, second m_Text
              * and third m_DataManagment.
              * The m_Text variable is a array of char which is 0 terminated.
              * The m_DataManagament specify how the data should be managed.
              * E.g. constant c-strings are global and can't be cleaned up but
              * if you want to work with them then you can specify the data as
              * UnmanagedInstance and the object don't try to clean it up.
              **/
            class String
            {
                public:
                    /// Default constructor which create an empty String.
                    String();
                    
                    /// Copy constructor which copy from an other StringBase object.
                    String(const String& Copy);

                    /// Copy cStringLength chars from cString.
                    String(const char* cString, 
                           RFTYPE::UInt32 cStringLength);
                    
                    /// Generate a String with a length of StringLength.
                    String(const RFTYPE::UInt32 StringLength);

                    String(const char Letter);

                    ~String();
                    
                    /** Special constructor to handle utf-8(mostly used by Linux API) and ascii.
                      * Zero terminated c strings are the same type like StringBase
                      * internal data type. This allow to transfer the ownership,
                      * make an copy or share the same data.
                      **/
                    String(const char* Str, 
                           Common::DataManagment::Type Ownership=Common::DataManagment::Copy);

                    /// Return the glyph count.
                    RFTYPE::UInt32 Length()const;

                    /** @brief Check if a string contains an other string.
                     *
                     * @return Return -1 if Str isn't contain or greater -1(position where the string was found).
                     *
                     **/
                    Int32 Contains(const String &Str)const;

                    /** @brief Check if a String end with an other String.
                      *
                      * @return Return true if the String ends with Value else false.
                      **/
                    RFTYPE::Bool EndsWith(const String& Value)const;

                    /** @brief Check if a String end with an other c string.
                      *
                      * @return Return true if the String ends with Value else false.
                      **/
                    RFTYPE::Bool EndsWith(const char* Value)const;

                    /** @brief Check if a String is part of this String.
                      *
                      * @return Return -1 if the String isn't part of this String else the start position.
                      **/
                    RFTYPE::Int32 IndexOf(const String& Value)const;

                    /** @brief Check if a c string is part of this String.
                      *
                      * @return Return -1 if the c string isn't part of this String else the start position.
                      **/
                    RFTYPE::Int32 IndexOf(const char* Value)const;

                    /** @brief Check if a String is part of this String after the position of StartAtIndex.
                      *
                      * @return Return -1 if the String isn't part of this String else the start position.
                      **/
                    RFTYPE::Int32 IndexOf(const String& Value,
                        const RFTYPE::UInt32 StartAtIndex)const;

                    /** @brief Check if a c string is part of this String after the position of StartAtIndex.
                      *
                      * @return Return -1 if the c string isn't part of this String else the start position.
                      **/
                    RFTYPE::Int32 IndexOf(const char* Value,
                        const RFTYPE::UInt32 StartAtIndex)const;

                    /** @brief Check if a String is part of this String after the position of StartAtIndex till the number of Count steps is reached.
                      *
                      * StartAtIndex mark the start of the search and Count is the number of char's which will be tested.
                      * StartAtIndex+Count is the last start position which will be checked.
                      * @return Return -1 if the String isn't part of this String else the start position.
                      **/
                    RFTYPE::Int32 IndexOf(const String& Value,
                        const RFTYPE::UInt32 StartAtIndex,
                        const RFTYPE::UInt32 Count)const;

                    /** @brief Check if a c string is part of this String after the position of StartAtIndex till the number of Count steps is reached.
                      *
                      * StartAtIndex mark the start of the search and Count is the number of char's which will be tested.
                      * StartAtIndex+Count is the last start position which will be checked.
                      * @return Return -1 if the c string isn't part of this String else the start position.
                      **/
                    RFTYPE::Int32 IndexOf(const char* Value,
                        const RFTYPE::UInt32 StartAtIndex,
                        const RFTYPE::UInt32 Count)const;

                    /** @brief Insert a String at the position AtIndex.
                      *
                      * @return Return the new String.
                      **/
                    String Insert(const RFTYPE::UInt32 AtIndex,
                                  const String& Value);

                    /** @brief Insert a c string at the position AtIndex.
                      *
                      * @return Return the new String.
                      **/
                    String Insert(const RFTYPE::UInt32 AtIndex,
                                  const char* Value);

                    /** @brief Search the last positive sub String in a String.
                      *
                      * This function have the same behavior like IndexOf with the difference
                      * that the search start on the end and stop on the start of the String.
                      * @return Return -1 if there is no positive comparement else the position of the last sub String.
                      **/
                    RFTYPE::Int32 LastIndexOf(const String& Value)const;

                    /** @brief Search the last positive sub c string in a String.
                      *
                      * This function have the same behavior like IndexOf with the difference
                      * that the search start on the end and stop on the start of the String.
                      * @return Return -1 if there is no positive comparement else the position of the last sub c string.
                      **/
                    RFTYPE::Int32 LastIndexOf(const char* Value)const;

                    /** @brief Search the last positive sub String in a String and start at StartAtIndex.
                      *
                      * This function have the same behavior like IndexOf with the difference
                      * that the search start on the end and stop on the start of the String.
                      * StartAtIndex move the stop mark because the function search from the end to the start.
                      * @return Return -1 if there is no positive comparement else the position of the last sub String.
                      **/
                    RFTYPE::Int32 LastIndexOf(const String& Value,
                        const RFTYPE::UInt32 StartAtIndex)const;

                    /** @brief Search the last positive sub c string in a String and start at StartAtIndex.
                      *
                      * This function have the same behavior like IndexOf with the difference
                      * that the search start on the end and stop on the start of the String.
                      * StartAtIndex move the stop mark because the function search from the end to the start.
                      * @return Return -1 if there is no positive comparement else the position of the last sub c string.
                      **/
                    RFTYPE::Int32 LastIndexOf(const char* Value,
                        const RFTYPE::UInt32 StartAtIndex)const;

                    /** @brief Search the last positive sub String in a String and start at StartAtIndex.
                      *
                      * This function have the same behavior like IndexOf with the difference
                      * that the search start on the end and stop on the start of the String.
                      * StartAtIndex move the stop mark because the function search from the end to the start.
                      * Count move the start mark, which means StartAtIndex+Count is the first comparement.
                      * @return Return -1 if there is no positive comparement else the position of the last sub String.
                      **/
                    RFTYPE::Int32 LastIndexOf(const String& Value,
                        const RFTYPE::UInt32 StartAtIndex,
                        const RFTYPE::UInt32 Count)const;

                    /** @brief Search the last positive sub c string in a String and start at StartAtIndex.
                      *
                      * This function have the same behavior like IndexOf with the difference
                      * that the search start on the end and stop on the start of the String.
                      * StartAtIndex move the stop mark because the function search from the end to the start.
                      * Count move the start mark, which means StartAtIndex+Count is the first comparement.
                      * @return Return -1 if there is no positive comparement else the position of the last sub c string.
                      **/
                    RFTYPE::Int32 LastIndexOf(const char* Value,
                        const RFTYPE::UInt32 StartAtIndex,
                        const RFTYPE::UInt32 Count)const;

                    /** Returns a new string that right-aligns the characters in this
                      * instance by padding them on the left with a specified Unicode
                      * character, for a specified total length.
                      **/
                    String PadLeft(const RFTYPE::UInt32 TotalWidth,
                        const RFTYPE::Char PaddingChar=' ')const;

                    /** Returns a new string that left-aligns the characters in this
                      * string by padding them on the right with a specified Unicode
                      * character, for a specified total length.
                      **/
                    String PadRight(const RFTYPE::UInt32 TotalWidth,
                        const RFTYPE::Char PaddingChar=' ')const;

                    /** Deletes all the characters from this string beginning at a
                      * specified position and continuing through the last position.
                      **/
                    String Remove(const RFTYPE::UInt32 StartAtIndex)const;

                    /** Deletes a specified number of characters from this instance
                      * beginning at a specified position.
                      **/
                    String Remove(const RFTYPE::UInt32 StartAtIndex,
                                  const RFTYPE::UInt32 Count)const;

                    /** Returns a new string in which all occurrences of a specified
                      * Unicode character in this instance are replaced with another
                      * specified Unicode character.
                      **/
                    String Replace(const RFTYPE::Char OldChar,
                                   const RFTYPE::Char NewChar)const;

                    /** Returns a new string in which all occurrences of a specified
                      * string in the current instance are replaced with another
                      * specified string.
                      **/
                    String Replace(const String& OldValue,
                                   const String& NewValue)const;

                    /** Return a String vector that contains the substrings in this
                      * instance that are delimited by char's contained by Delimiters.
                      **/
                    Memory::AutoPointerArray<String> Split(const String &Delimiters)const;

                    /** Return a String vector that contains the substrings in this
                      * instance that are delimited by char's contained by Delimiters.
                      **/
                    Memory::AutoPointerArray<String> Split(const Char* Delimiters)const;

                    /** Determines whether the beginning of this string instance
                      * matches the specified string.
                      **/
                    RFTYPE::Bool StartsWith(const String& AString)const;

                    /** Retrieves a substring from this instance. The substring starts
                      * at a specified character position and has a specified length.
                      **/
                    String SubString(const RFTYPE::UInt32 StartIndex,
                                     const RFTYPE::UInt32 Count)const;

                    /** Removes all leading and trailing occurrences of a set of
                      * characters specified from the TrimChars String.
                      **/
                    String Trim(const String& TrimChars=" ")const;

                    /** Removes all trailing occurrences of a set of characters
                      * specified from the current String object TrimChars.
                      **/
                    String TrimStart(const String& TrimChars=" ")const;

                    /** Removes all leading occurrences of a set of characters
                      * specified from the current String object TrimChars.
                      **/
                    String TrimEnd(const String& TrimChars=" ")const;

                    /** Check if both strings are equal.
                      * The method return the position of the first difference, 0
                      * if they are equal or -1 if they are unequal in length.
                      **/
                    RFTYPE::Int32 Compare(const String& With)const;

                    char operator[](const MemoryRange Index)const;
                    char& operator[](const MemoryRange Index);
                    bool operator==(const String& Other)const;
                    bool operator==(const char* Other)const;
                    bool operator!=(const String& Other)const;
                    bool operator!=(const char* Other)const;
                    String operator+(const String &Str)const;
                    String operator+(const char* Str)const;
                    String operator+(const Char Character)const;
                    /// Append "true" or "false" on the string.
                    String operator+(const Bool& Value)const;
                    String operator+(const Int8 Number)const;
                    String operator+(const Int16 Number)const;
                    String operator+(const Int32 Number)const;
                    String operator+(const Int64 Number)const;
                    String operator+(const UInt8 Number)const;
                    String operator+(const UInt16 Number)const;
                    String operator+(const UInt32 Number)const;
                    String operator+(const UInt64 Number)const;
                    String& operator+=(const char *Str);
                    String& operator+=(const Char Character);
                    String& operator+=(const String& Str);
                    String& operator+=(const Bool& Value);
                    String& operator+=(const Int8 Number);
                    String& operator+=(const Int16 Number);
                    String& operator+=(const Int32 Number);
                    String& operator+=(const Int64 Number);
                    String& operator+=(const UInt8 Number);
                    String& operator+=(const UInt16 Number);
                    String& operator+=(const UInt32 Number);
                    String& operator+=(const UInt64 Number);
                    String& operator=(const char *Str);
                    String& operator=(const Char Character);
                    String& operator=(const String &Other);
                    String& operator=(const Bool& Value);
                    String& operator=(const Int8 Number);
                    String& operator=(const Int16 Number);
                    String& operator=(const Int32 Number);
                    String& operator=(const Int64 Number);
                    String& operator=(const UInt8 Number);
                    String& operator=(const UInt16 Number);
                    String& operator=(const UInt32 Number);
                    String& operator=(const UInt64 Number);

                    /** \brief This function return a c string which isn't editable.
                      *
                      * \return This function return the pointer of the string in this class.
                      *
                      * Attemption: Don't change the Data of this pointer and don't typecast it to "char*".
                      *             Because this data point on the buffer of this String class and isn't a copy.
                      *             The reason for this function is to provide a very fast interface to C based
                      *             libraries like Operating System API's.
                      **/
                    char const* c_str()const;
                    
                    /// Convert a hex value, stored in this String instance, to a number.
                    Int32 HexToDec()const;

                    /** @brief This function allow to create a formatted String.
                      *
                      * The first parameter is the syntax of the new String, which
                      * use following syntax: %[flags][width][.precision][length]specifier
                      * For more information you can look at the manual of printf.
                      * http://www.cplusplus.com/reference/clibrary/cstdio/printf/
                      **/
                    static String Format(const char* Str=0,...);
                    static String Format(const String &Str,...);
                    static RFTYPE::UInt32 Format(
                        Memory::AutoPointerArray<RFTYPE::UInt8>& Buffer, 
                        const RFTYPE::UInt32 BufferBoundaryStart, 
                        const RFTYPE::UInt32 BufferBoundaryEnd,
                        const char* Str=0,...);
                    static RFTYPE::UInt32 Format(
                        Memory::AutoPointerArray<RFTYPE::UInt8>& Buffer,
                        const RFTYPE::UInt32 BufferBoundaryStart, 
                        const RFTYPE::UInt32 BufferBoundaryEnd,
                        const String &Str,...);
                    static String Format(const char* Str, va_list argptr);

                    /// Convert all lower case to upper case chars.
                    void ToUpper();
                    /// Convert all upper case to lower case chars.
                    void ToLower();

                    /// Check if the String instance contain a number.
                    Bool IsNumber()const;

                    /// Check if the String instance contain a floatingpoint number.
                    Bool IsFloatingpointNumber()const;

                    /// Check if the String instance contain a boolean.
                    Bool IsBoolean()const;

                    void Swap(String& Other);

                    virtual Memory::AutoPointer<Collections::ArrayEnumerator<Char> > GetEnumerator();

                    /// Check if the String instance is empty.
                    Bool IsEmpty()const;

                    /// UTF-8 can use multiple bytes for a character. Use this to get the size instead of the character amount.
                    Size Size()const;
                protected:
                    RadonFramework::Memory::AutoPointerArray<Char> m_Text;//0 terminated to boost the speed
                    Common::DataManagment::Type m_DataManagment;
                    RFTYPE::UInt32 m_Length;
            };
        }
    }
}

//OtherType to String
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Int8 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Int16 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Int32 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Int64 &Self);

RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::UInt8 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::UInt16 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::UInt32 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::UInt64 &Self);

RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Float32 &Self);
RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Float64 &Self);

RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::Char &Self);

RFTYPE::String& operator<<(RFTYPE::String &Str, const char *c_str);

RFTYPE::String& operator<<(RFTYPE::String &Str, const RFTYPE::String &Self);

//String to OtherType
RFTYPE::Int8& operator<<(RFTYPE::Int8 &Self, const RFTYPE::String &Str);
RFTYPE::Int16& operator<<(RFTYPE::Int16 &Self, const RFTYPE::String &Str);
RFTYPE::Int32& operator<<(RFTYPE::Int32 &Self, const RFTYPE::String &Str);
RFTYPE::Int64& operator<<(RFTYPE::Int64 &Self, const RFTYPE::String &Str);

RFTYPE::UInt8& operator<<(RFTYPE::UInt8 &Self, const RFTYPE::String &Str);
RFTYPE::UInt16& operator<<(RFTYPE::UInt16 &Self, const RFTYPE::String &Str);
RFTYPE::UInt32& operator<<(RFTYPE::UInt32 &Self, const RFTYPE::String &Str);
RFTYPE::UInt64& operator<<(RFTYPE::UInt64 &Self, const RFTYPE::String &Str);

RFTYPE::Float32& operator<<(RFTYPE::Float32 &Self, const RFTYPE::String &Str);
RFTYPE::Float64& operator<<(RFTYPE::Float64 &Self, const RFTYPE::String &Str);
#endif // RF_CORE_TYPES_STRING_HPP
