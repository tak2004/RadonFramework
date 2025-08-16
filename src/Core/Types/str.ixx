export module rf.core.types:str;
export import :memory;

export namespace rf {
/// String literals are read-only views which are known at compile time.
    template<class T, size N> struct StringLiteral {
        using StoringType = T;
        /// Number of elements to compose the string. It's not the length!
        static constexpr auto elements = N;
        static constexpr auto bytes = sizeof(T) * N;

        constexpr StringLiteral(const T(&String)[N]) noexcept : value(String) {}
        const T(&value)[N];
    };

template<size N> struct strlit:public StringLiteral<ansi,N>{
  constexpr strlit(const char (&String)[N]) noexcept : StringLiteral(String) {}
};

template<size N> struct utf8lit:public StringLiteral<utf8,N>{
  constexpr utf8lit(const char (&String)[N]) noexcept : StringLiteral(String) {}
};

template<size N> struct utf16lit:public StringLiteral<utf16,N>{
  constexpr utf16lit(const char (&String)[N]) noexcept : StringLiteral(String) {}
};

template<size N> struct utf32lit:public StringLiteral<utf32,N>{
  constexpr utf32lit(const char (&String)[N]) noexcept : StringLiteral(String) {}
};

template<size N> struct wcharlit:public StringLiteral<wchar,N>{
  constexpr wcharlit(const char (&String)[N]) noexcept : StringLiteral(String) {}
};

/// The class is a read-only view on a text buffer(e.g. string literal).
/// It consists of a read-only pointer into the buffer and a size in bytes.
/// It's a lightweight structure for text processing and designed to be used on
/// stack. A write operation on a string view is generating a
/// copy(copy-on-write).

// ANSI string view is a special case of UTF-8 string view.
// One byte equals a glyph.
struct strview {
  constptr address;
  size bytes;
};
// Between one and six bytes equal a glyph.
struct utf8view {
  constptr address;
  size bytes;
};
// Two or four bytes equal a glyph.
struct utf16view {
  constptr address;
  size bytes;
};
// Four bytes equal a glyph.
struct utf32view {
  constptr address;
  size bytes;
};
// Multibyte encoding with up to 16 bytes pre glyph.
struct wcharview {
  constptr address;
  size bytes;
};

/// Memory dense and basic implementation of string processing and ownership.
/// If you need a more complex implementation use the text type.
struct str {
  size bytes() const {
    if (this->inMemory.flags.isInMemory == false)
      return 31 - this->inObject.bytesLeft;
    else
      return this->inMemory.used;
  }
  char *c_str() const {
    if (this->inMemory.flags.isInMemory == false)
      return (char *)this->inObject.data;
    else
      return (char *)this->inMemory.memory.address;
  }

private:
  union {
    struct {
      mem memory;
      size used;
      struct {
        u8 reserved[7];
        u8 unused : 6;
        u8 shouldDelete : 1;
        u8 isInMemory : 1;
      } flags;
    } inMemory;
    struct {
      u8 data[31];
      u8 bytesLeft : 7;
      u8 isInMemory : 1;
    } inObject;
  };
};
} // namespace rf