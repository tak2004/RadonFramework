#ifndef RF_CORE_TYPES_STRING_HPP
#define RF_CORE_TYPES_STRING_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework { namespace Core { namespace Types {

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
class ALIGN(32) String
{
public:
    #pragma region Constructor and Destructor
    /// Default constructor which create an empty String.
    String();
                    
    /// Copy constructor which copy from an other StringBase object.
    String(const String& Copy);

    /// Generate a String with a size of StringSize(including 0 termination).
    explicit String(const Size StringSize);

    explicit String(const char Letter);

    template<int N>
    String(char const (&CString)[N])
    {
        String(&CString[0], N);
    }

    ~String();

    /** Special constructor to handle utf-8(mostly used by Linux API) and ascii.
    * Zero terminated c strings are the same type like StringBase
    * internal data type. This allow to transfer the ownership,
    * make an copy or share the same data.
    **/
    explicit String(const char* CString, const Size CStringSize,
           Common::DataManagment::Type Ownership=Common::DataManagment::Copy);

    /** \brief This constructor accept a C string without any information
    *          about size.
    *
    * The constructor will determine the size, length and create a copy.
    */
    static String UnsafeStringCreation(const char* CString);
    #pragma endregion

    #pragma region Operator
    /// Overload new operator to ensure String alignment.
    void* operator new(Size Bytes);
    /// Overload replacement new operator to ensure String alignment.
    void* operator new(Size Bytes, void* buffer);
    char operator[](const Size Index)const;
    char& operator[](const Size Index);
    bool operator==(const String& Other)const;

    template<int N>
    bool operator==(char const (&Other)[N])const;

    bool operator!=(const String& Other)const;
    String operator+(const String &Str)const;
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
    #pragma endregion

    #pragma region Properties
    /// Return the glyph count.
    UInt32 Length()const;

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

    /// UTF-8 can consists of multiple bytes for a character. 
    /// Use this to get the size instead of the character amount.
    Size Size()const;
    #pragma endregion

    #pragma region Methods
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
    Bool EndsWith(const String& Value)const;

    /** @brief Check if a String is part of this String.
      *
      * @return Return -1 if the String isn't part of this String else the start position.
      **/
    Int32 IndexOf(const String& Value)const;

    /** @brief Check if a String is part of this String after the position of StartAtIndex.
      *
      * @return Return -1 if the String isn't part of this String else the start position.
      **/
    Int32 IndexOf(const String& Value, const UInt32 StartAtIndex)const;

    /** @brief Check if a String is part of this String after the position of StartAtIndex till the number of Count steps is reached.
      *
      * StartAtIndex mark the start of the search and Count is the number of char's which will be tested.
      * StartAtIndex+Count is the last start position which will be checked.
      * @return Return -1 if the String isn't part of this String else the start position.
      **/
    Int32 IndexOf(const String& Value, const UInt32 StartAtIndex,
        const UInt32 Count)const;

    /** @brief Insert a String at the position AtIndex.
      *
      * @return Return the new String.
      **/
    String Insert(const UInt32 AtIndex, const String& Value);

    /** @brief Search the last positive sub String in a String.
      *
      * This function have the same behavior like IndexOf with the difference
      * that the search start on the end and stop on the start of the String.
      * @return Return -1 if there is no positive comparement else the position of the last sub String.
      **/
    Int32 LastIndexOf(const String& Value)const;

    /** @brief Search the last positive sub String in a String and start at StartAtIndex.
      *
      * This function have the same behavior like IndexOf with the difference
      * that the search start on the end and stop on the start of the String.
      * StartAtIndex move the stop mark because the function search from the end to the start.
      * @return Return -1 if there is no positive comparement else the position of the last sub String.
      **/
    Int32 LastIndexOf(const String& Value, const UInt32 StartAtIndex)const;

    /** @brief Search the last positive sub String in a String and start at StartAtIndex.
      *
      * This function have the same behavior like IndexOf with the difference
      * that the search start on the end and stop on the start of the String.
      * StartAtIndex move the stop mark because the function search from the end to the start.
      * Count move the start mark, which means StartAtIndex+Count is the first comparement.
      * @return Return -1 if there is no positive comparement else the position of the last sub String.
      **/
    Int32 LastIndexOf(const String& Value, const UInt32 StartAtIndex,
        const UInt32 Count)const;

    /** Returns a new string that right-aligns the characters in this
      * instance by padding them on the left with a specified Unicode
      * character, for a specified total length.
      **/
    String PadLeft(const UInt32 TotalWidth, const Char PaddingChar=' ')const;

    /** Returns a new string that left-aligns the characters in this
      * string by padding them on the right with a specified Unicode
      * character, for a specified total length.
      **/
    String PadRight(const UInt32 TotalWidth, const Char PaddingChar=' ')const;

    /** Deletes all the characters from this string beginning at a
      * specified position and continuing through the last position.
      **/
    String Remove(const UInt32 StartAtIndex)const;

    /** Deletes a specified number of characters from this instance
      * beginning at a specified position.
      **/
    String Remove(const UInt32 StartAtIndex, const UInt32 Count)const;

    /** Returns a new string in which all occurrences of a specified
      * Unicode character in this instance are replaced with another
      * specified Unicode character.
      **/
    String Replace(const RFTYPE::Char OldChar, const Char NewChar)const;

    /** Returns a new string in which all occurrences of a specified
      * string in the current instance are replaced with another
      * specified string.
      **/
    String Replace(const String& OldValue, const String& NewValue)const;

    /** Return a String vector that contains the substrings in this
      * instance that are delimited by char's contained by Delimiters.
      **/
    Memory::AutoPointerArray<String> Split(const String &Delimiters)const;

    /** Determines whether the beginning of this string instance
      * matches the specified string.
      **/
    Bool StartsWith(const String& Value)const;

    /** Retrieves a substring from this instance. The substring starts
      * at a specified character position and has a specified length.
      **/
    String SubString(const UInt32 StartIndex, const UInt32 Count)const;

    /** Removes all leading and trailing occurrences of a set of
      * characters specified from the TrimChars String.
      **/
    String Trim(const String& TrimChars)const;

    /** Removes all trailing occurrences of a set of characters
      * specified from the current String object TrimChars.
      **/
    String TrimStart(const String& TrimChars)const;

    /** Removes all leading occurrences of a set of characters
      * specified from the current String object TrimChars.
      **/
    String TrimEnd(const String& TrimChars)const;

    /** Check if both strings are equal.
      * The method return the position of the first difference, 0
      * if they are equal or -1 if they are unequal in length.
      **/
    Int32 Compare(const String& With)const;

        /// Convert a hex value, stored in this String instance, to a number.
    Int32 HexToDec()const;

    /** @brief This function allow to create a formatted String.
     *
     * The first parameter is the syntax of the new String, which
     * use following syntax: %[flags][width][.precision][length]specifier
     * For more information you can look at the manual of printf.
     * http://www.cplusplus.com/reference/clibrary/cstdio/printf/
     **/
    static String Format(const String &Str,...);

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

    /// Check if the String instance is empty.
    Bool IsEmpty()const;
    #pragma endregion
protected:
#pragma region Internal variables
    static const UInt32 BUFFER_SIZE = 27;

    union
    {//0 terminated to boost the speed
        FixString<BUFFER_SIZE> m_FixBuffer;
        DynamicString m_DynBuffer;
    };
    Common::DataManagment::Type m_DataManagment;
    RFTYPE::UInt32 m_Length;

    char* GetBuffer();
    const char* GetBuffer()const;
#pragma endregion
};

template<int N>
bool String::operator==(char const (&Other)[N])const
{
    String tmp(Other, N);
    return *this == tmp;
}

} } }

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

template<int N>
RFTYPE::String& operator<<(RFTYPE::String &Str, char const (&Other)[N])
{
    Str += String(Other, N);
    return Str;
}

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
