export module rf.core.types:str;
export import :memory;

export namespace rf {
/// String literals are read-only views which are known at compile time.
struct strlit {};
struct utf8lit {};
struct utf16lit {};
struct utf32lit {};
struct wcharlit {};

/// The class is a read-only view on a text buffer(e.g. string literal).
/// It consists of a read-only pointer into the buffer and a size in bytes.
/// It's a lightweight structure for text processing and designed to be used on
/// stack. A write operation on a string view is generating a
/// copy(copy-on-write).

// ASCII string view is a special case of UTF-8 string view.
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