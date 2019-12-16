#include "RadonFramework/Core/Types/String.hpp"
#include "RadonFramework/Core/Types/Int64.hpp"
#include "RadonFramework/Core/Types/UInt64.hpp"
#include "RadonFramework/Core/Types/Float64.hpp"
#include "RadonFramework/Memory/AutoPointerArray.hpp"
#include "RadonFramework/System/Memory.hpp"
#include "RadonFramework/System/String.hpp"

using namespace RadonFramework::Memory;
using namespace RadonFramework::Collections;

namespace RadonFramework::Core::Types
{
String::String()
{
  m_FixBuffer[0] = 0;
  m_FixBuffer.SetSize(0);
  m_DataManagment = DataManagment::Copy;
  m_Length = 0;
}

String::String(const String& Copy)
{
  m_DataManagment=DataManagment::Copy;
  m_Length=0;
  m_FixBuffer.SetSize(0);
  // if the length of Copy is 0 we don't have to do anything
  if(Copy.Length() > 0)
  {
    // take the calculated length from Copy
    m_Length = Copy.m_Length;

    if(Copy.m_DataManagment != DataManagment::Copy)
    {
      m_DataManagment = Copy.m_DataManagment;
      if(Copy.m_DataManagment == DataManagment::UnmanagedInstance)
      {  // clone it
        m_DynBuffer = Copy.m_DynBuffer;
      }
      else
      {  // create a copy
        m_DynBuffer.m_Buffer = new UInt8[Copy.m_DynBuffer.m_Size];
        m_DynBuffer.m_Size = Copy.m_DynBuffer.m_Size;
        RF_SysMem::Copy(static_cast<void*>(m_DynBuffer.Raw()),
                        static_cast<const void*>(Copy.m_DynBuffer.Raw()),
                        m_DynBuffer.m_Size);
      }
    }
    else
    {  // locale copy
      RF_SysMem::Copy(static_cast<void*>(m_FixBuffer.Raw()),
                      static_cast<const void*>(Copy.m_FixBuffer.Raw()),
                      BUFFER_SIZE);
      m_FixBuffer.SetSize(Copy.m_FixBuffer.GetSize());
    }
  }
}

String::String(const char* cString,
               const RF_Type::Size cStringSize,
               DataManagment Ownership)
: m_DataManagment(Ownership)
{
  if(cString != 0 && cStringSize > 0)
  {
    m_Length =
        RF_SysStr::Length(reinterpret_cast<const UInt8*>(cString), cStringSize);
    RF_Type::Size bytesInUse = RF_SysStr::CStringSizeOf(
        reinterpret_cast<const UInt8*>(cString), cStringSize);
    switch(m_DataManagment)
    {
      case DataManagment::Copy:
        if(bytesInUse <= BUFFER_SIZE)
        {
          const RF_Type::Size TERMINATION = 1;
          RF_SysMem::Copy(static_cast<void*>(m_FixBuffer.Raw()),
                          static_cast<const void*>(cString),
                          bytesInUse - TERMINATION);

          m_FixBuffer[bytesInUse - TERMINATION] = '\0';
          m_FixBuffer.SetSize(bytesInUse);
        }
        else
        {
          m_DataManagment = DataManagment::AllocateAndCopy;
          m_DynBuffer.m_Buffer = new UInt8[bytesInUse];
          m_DynBuffer.m_Size = bytesInUse;
          RF_SysMem::Copy(m_DynBuffer.Raw(), cString, m_DynBuffer.m_Size);
        }
        break;
      case DataManagment::TransfereOwnership:
        m_DataManagment = DataManagment::AllocateAndCopy;
      case DataManagment::UnmanagedInstance:
        m_DynBuffer.m_Buffer =
            reinterpret_cast<UInt8*>(const_cast<char*>(cString));
        m_DynBuffer.m_Size = bytesInUse;
        break;
    }
  }
  else
  {
    m_Length = 0;
    m_FixBuffer[0] = '\0';
    m_FixBuffer.SetSize(0);
    m_DataManagment = DataManagment::Copy;
  }
}

String::String(const RF_Type::Size StringSize)
: m_DataManagment(DataManagment::Copy)
{
  m_Length = StringSize - 1;
  if(StringSize <= BUFFER_SIZE)
  {
    if(StringSize > 0)
    {
      RF_SysMem::Set(static_cast<void*>(m_FixBuffer.Raw()), ' ', m_Length);
      m_FixBuffer[m_Length] = 0;
    }
    else
    {
      m_FixBuffer[0] = 0;
    }
    m_FixBuffer.SetSize(StringSize);
  }
  else
  {
    m_DataManagment = DataManagment::AllocateAndCopy;
    m_DynBuffer.m_Buffer = new UInt8[StringSize];
    m_DynBuffer.m_Size = StringSize;
    RF_SysMem::Set(static_cast<void*>(m_DynBuffer.Raw()), ' ', m_Length);
    m_DynBuffer[m_Length] = '\0';
  }
}

// String::String(RF_Mem::AutoPointerArray<RF_Type::UInt8>& Memory,
//    RF_Common::DataManagment Ownership /*=
//    RF_Common::DataManagment::TransfereOwnership*/)
//{
//    switch(Ownership)
//    {
//        case RadonFramework::Core::Common::DataManagment::Copy:
//        case RadonFramework::Core::Common::DataManagment::AllocateAndCopy:
//        case RadonFramework::Core::Common::DataManagment::UnmanagedInstance:
//            *this=String(reinterpret_cast<const char*>(Memory.Get()),
//            Memory.Size(), Ownership); break;
//        case RadonFramework::Core::Common::DataManagment::TransfereOwnership:
//        {
//            auto data = Memory.Release();
//            *this=String(reinterpret_cast<const char*>(data.Ptr), data.Count,
//            Ownership); break;
//        }
//    }
//}

String::~String()
{
  if(m_DataManagment == DataManagment::AllocateAndCopy)
  {
    delete[] m_DynBuffer.m_Buffer;
    m_DynBuffer.m_Size = 0;
  }
}

String
String::UnsafeStringCreation(const char* CString, DataManagment Ownership)
{
  String result;
  RF_Type::Size size = 0;
  const char* stringEnd = CString;
  for(; *stringEnd != '\0'; ++stringEnd, ++size)
  {
  }
  result = String(CString, size + 1, Ownership);
  return result;
}

void* String::operator new(size_t Bytes)
{
  return RF_SysMem::Allocate(Bytes, sizeof(String));
}

void* String::operator new(size_t Bytes, void* Buffer)
{
  UInt8* p = static_cast<UInt8*>(Buffer);
  p += Bytes;
  return static_cast<void*>(p);
}

void String::operator delete(void* Buffer)
{
  RF_SysMem::Free(Buffer);
}

RF_Type::UInt32 String::Length() const
{
  return m_Length;
}

void String::Clear()
{
  if(m_DataManagment == DataManagment::Copy)
  {
    m_FixBuffer.SetSize(0);
  }
  else
  {
    m_DynBuffer.Free();
  }
  m_Length = 0;
}

RF_Type::Int32 String::Contains(const String& Str) const
{
  const int TERMINATION = 1;
  if(Size() < Str.Size())
    return -1;

  return IndexOf(Str, 0, Size() - TERMINATION);
}

RF_Type::Bool String::EndsWith(const String& Value) const
{
  // this test is faster as in the method with char*
  if(Value.Size() > Size())
    return false;

  const int TERMINATION = 1;
  const UInt8* buffer = GetBuffer();
  Int32 j = Value.Size() - TERMINATION;
  for(UInt32 i = Size() - TERMINATION; i >= 0; --i)
  {
    if(buffer[i] == Value[j])
      --j;
    else
      return false;

    if(j == -1)
      return true;
  }
  return false;
}

RF_Type::Int32 String::IndexOf(const String& Value) const
{
  const int TERMINATION = 1;
  return IndexOf(Value, 0, Size() - TERMINATION);
}

RF_Type::Int32
String::IndexOf(const String& Value, const RF_Type::UInt32 StartAtIndex) const
{
  const int TERMINATION = 1;
  return IndexOf(Value, StartAtIndex, Size() - TERMINATION - StartAtIndex);
}

RF_Type::Int32 String::IndexOf(const RF_Type::String& Value,
                               const RF_Type::UInt32 StartAtIndex,
                               const RF_Type::UInt32 Count) const
{
  const int TERMINATION = 1;
  RF_Type::Int32 result = -1;

  if(Value.m_Length > Count)
    return result;

  if(!CanGlyphsBeCompared(Value))
    return result;

  const UInt8* buffer = GetBuffer();
  RF_Type::Size processedGlyphs = MoveByGlyphs(buffer, StartAtIndex);
  if(processedGlyphs < StartAtIndex)
    return result;

  const RF_Type::UInt8* firstHit =
      RF_SysStr::Find(buffer, Size() - TERMINATION - (buffer - GetBuffer()),
                      Value.GetBuffer(), Value.Size() - TERMINATION);

  if(firstHit != 0)
  {
    result = RF_SysStr::Length(buffer, firstHit - buffer) + StartAtIndex;
  }
  return result;
}

RF_Type::String
String::Insert(const RF_Type::UInt32 AtIndex, const RF_Type::String& Value)
{
  const int TERMINATION = 1;
  RF_Type::Size byteSize = Size() + Value.Size() - TERMINATION;
  String str(byteSize);

  RF_Type::UInt8* buffer = str.GetBuffer();

  if(AtIndex > 0)
    RF_SysMem::Copy(buffer, GetBuffer(), AtIndex);

  RF_SysMem::Copy(buffer + AtIndex, Value.GetBuffer(), Value.Size());
  if(Size() > 0 && AtIndex < Size() - TERMINATION)
    RF_SysMem::Copy(buffer + AtIndex + Value.Size() - TERMINATION,
                    GetBuffer() + AtIndex, Size() - AtIndex);

  return str;
}

RF_Type::Int32 String::LastIndexOf(const String& Value) const
{
  if(Size() < Value.Size())
    return -1;

  return LastIndexOf(Value, 0, Size());
}

RF_Type::Int32 String::LastIndexOf(const RF_Type::String& Value,
                                   const RF_Type::UInt32 StartAtIndex) const
{
  if(m_Length - StartAtIndex < Value.m_Length)
    return -1;

  return LastIndexOf(Value, StartAtIndex, Size() - StartAtIndex);
}

RF_Type::Int32 String::LastIndexOf(const RF_Type::String& Value,
                                   const RF_Type::UInt32 StartAtIndex,
                                   const RF_Type::UInt32 Count) const
{
  const int TERMINATION = 1;
  if(Count + TERMINATION < Value.Size())
    return -1;

  if(m_Length == 0)
    return -1;

  const RF_Type::UInt8* buffer = GetBuffer();

  const RF_Type::UInt8* value = Value.GetBuffer();

  const RF_Type::UInt8* v = value;
  const RF_Type::UInt8* p = buffer + (Size() - Value.Size());
  const RF_Type::UInt8* searchp = p;
  const RF_Type::UInt8* vend = value + Value.Size() - TERMINATION;
  const RF_Type::UInt8* pend = buffer + StartAtIndex - 1;

  for(; p != pend; --p, searchp = p)
  {
    while(v != vend && *searchp == *v)  // compare func
    {
      ++searchp;
      ++v;
    }

    if(v == vend)  // finished search
      return static_cast<Int32>(MemoryRange(p - buffer));
    else
      v = value;  // reset v for next search
  }
  return -1;
}

String String::PadLeft(const RF_Type::UInt32 TotalWidth,
                       const RF_Type::Char PaddingChar) const
{
  if(TotalWidth < m_Length)
    return *this;

  RF_Type::Size byteSize = Size() + (TotalWidth - m_Length);
  String str(byteSize);
  UInt32 offset = TotalWidth - m_Length;
  const RF_Type::UInt8* buffer = GetBuffer();

  RF_Type::UInt8* strBuffer = str.GetBuffer();

  if(PaddingChar != ' ' && offset > 0)
    RF_SysMem::Set(strBuffer, PaddingChar, offset);

  RF_SysMem::Copy(strBuffer + offset, buffer, Size());
  return str;
}

String String::PadRight(const RF_Type::UInt32 TotalWidth,
                        const RF_Type::Char PaddingChar) const
{
  const int TERMINATION = 1;
  if(TotalWidth < m_Length)
    return *this;

  RF_Type::Size byteSize = Size() + (TotalWidth - m_Length);
  String str(byteSize);
  UInt32 offset = TotalWidth - m_Length;
  const RF_Type::UInt8* buffer = GetBuffer();

  RF_Type::UInt8* strBuffer = str.GetBuffer();

  if(PaddingChar != ' ' && offset > 0)
    RF_SysMem::Set(strBuffer + Size() - TERMINATION, PaddingChar, offset);
  RF_SysMem::Copy(strBuffer, buffer, Size() - TERMINATION);
  return str;
}

String String::Remove(const RF_Type::UInt32 StartAtIndex) const
{
  if(StartAtIndex == 0)
    return String();

  const RF_Type::UInt8* buffer = GetBuffer();

  String str(reinterpret_cast<const char*>(buffer), StartAtIndex);
  return str;
}

String String::Remove(const RF_Type::UInt32 StartAtIndex,
                      const RF_Type::UInt32 Count) const
{
  const int TERMINATION = 1;
  if(StartAtIndex == 0)
    return String();

  if(StartAtIndex >= Size() || Count == 0)
    return *this;

  if(Size() - StartAtIndex - TERMINATION <= Count)
    return Remove(StartAtIndex);

  const RF_Type::UInt8* buffer = GetBuffer();

  UInt32 sc = StartAtIndex + Count;
  RF_Type::Size byteSize = Size() - Count;
  String str(byteSize);
  RF_Type::UInt8* dstBuffer = str.GetBuffer();

  RF_SysMem::Copy(dstBuffer, buffer, StartAtIndex);
  RF_SysMem::Copy(dstBuffer + StartAtIndex, buffer + sc, Size() - sc);
  return str;
}

String
String::Replace(const RF_Type::Char OldChar, const RF_Type::Char NewChar) const
{
  String str(*this);
  RF_Type::UInt8* p = str.GetBuffer();

  for(UInt32 i = 0; i < m_Length; ++i)
    if(p[i] == OldChar)
      p[i] = NewChar;
  return str;
}

String String::Replace(const String& OldValue, const String& NewValue) const
{
  if(OldValue.m_Length == 0 || OldValue == NewValue ||
     OldValue.m_Length > m_Length)
    return *this;

  String str(*this);
  Int32 ind = 0;
  Int32 diff = OldValue.m_Length - NewValue.m_Length;

  while((ind = str.IndexOf(OldValue)) > -1)
  {
    if(OldValue.m_Length == NewValue.m_Length)
    {
      RF_SysMem::Copy(str.GetBuffer() + ind, NewValue.GetBuffer(),
                      NewValue.m_Length);
    }
    else
    {
      RF_Mem::AutoPointerArray<char> p(str.m_Length - diff + 1);
      p.Get()[str.m_Length - diff] = 0;

      if(ind != 0)
      {
        RF_SysMem::Copy(p.Get(), str.GetBuffer(), ind);
      }
      RF_SysMem::Copy(p.Get() + ind, NewValue.GetBuffer(), NewValue.m_Length);
      if(ind + OldValue.m_Length != str.m_Length)
      {
        RF_SysMem::Copy(p.Get() + ind + NewValue.m_Length,
                        str.GetBuffer() + (ind + OldValue.m_Length),
                        str.m_Length - ind - OldValue.m_Length);
      }
      str = String(p.Get(), p.Size());
    }
  }
  return str;
}

StringSet String::Split(const String& Delimiters) const
{
  const int TERMINATION = 1;
  StringSet list;
  if(m_Length != 0)
  {
    const RF_Type::UInt8* p = GetBuffer();
    RF_Type::Size hits = 1, end = Size() - TERMINATION - 1;

    for(RF_Type::Size i = 0; i < Size() - TERMINATION; ++i)
    {
      for(RF_Type::Size j = 0; j < Delimiters.Size() - TERMINATION; ++j)
      {
        if(p[i] == Delimiters[j] && i != 0 && i != end)
        {
          ++hits;
          break;
        }
      }
    }

    list = StringSet(StringView(c_str(), Size()), hits);
    hits = 0;
    RF_Type::Size lasthit = 0;

    // if first glyph is a delimiter
    for(RF_Type::Size j = 0; j < Delimiters.Size() - TERMINATION; ++j)
    {
      if(p[0] == Delimiters[j])
      {
        ++lasthit;
        break;
      }
    }

    for(RF_Type::Size i = 0; i < Size() - TERMINATION; ++i)
    {
      for(RF_Type::Size j = 0; j < Delimiters.Size() - TERMINATION; ++j)
      {
        if(p[i] == Delimiters[j] && i != 0 && i != end)
        {
          list.Set(hits, lasthit, i - lasthit);
          lasthit = i + 1;
          ++hits;
          break;
        }
      }
    }

    // if last glyph is no delimiter
    if(lasthit < Size() - TERMINATION)
    {
      list.Set(hits, lasthit, Size() - lasthit);
    }
  }
  return list;
}

RF_Type::Bool String::StartsWith(const String& AString) const
{
  if(AString.m_Length > m_Length || AString.m_Length == 0)
    return false;
  return RF_SysMem::Compare(GetBuffer(), AString.GetBuffer(),
                            AString.m_Length) == 0
             ? true
             : false;
}

String String::SubString(const RF_Type::UInt32 StartIndex,
                         const RF_Type::UInt32 Count) const
{
  const int TERMINATION = 1;
  if(StartIndex + Count > m_Length || Count == 0)
    return String();
  String str(Count + TERMINATION);

  const RF_Type::UInt8* buffer = GetBuffer();
  RF_Type::Size processedGlyphs = MoveByGlyphs(buffer, StartIndex);
  if(processedGlyphs < StartIndex)
    return String();

  RF_SysMem::Copy(str.GetBuffer(), buffer, Count);
  str.GetBuffer()[Count] = '\0';
  return str;
}

String String::Trim(const String& TrimChars) const
{
  return TrimStart(TrimChars).TrimEnd(TrimChars);
}

String String::TrimStart(const String& TrimChars) const
{
  Bool foundone;
  UInt32 i = 0;
  for(; i < Size(); ++i)
  {
    foundone = false;
    for(UInt32 j = 0; j < TrimChars.m_Length; ++j)
    {
      if(GetBuffer()[i] == TrimChars[j])
      {
        foundone = true;
      }
    }

    if(!foundone)
      break;
  }
  String str(reinterpret_cast<const char*>(GetBuffer()) + i, Size() - i);
  return str;
}

String String::TrimEnd(const String& TrimChars) const
{
  Bool foundone;
  UInt32 i = 0;
  if(Size() > 2)
  {
    i = Size() - 2;
    for(; i >= 0; --i)
    {
      foundone = false;
      for(UInt32 j = 0; j < TrimChars.m_Length; ++j)
      {
        if(GetBuffer()[i] == TrimChars[j])
        {
          foundone = true;
        }
      }

      if(!foundone)
        break;
    }
  }
  String str(reinterpret_cast<const char*>(GetBuffer()), i + 1);
  return str;
}

RF_Type::Int32 String::Compare(const String& With) const
{
  if(m_Length == With.m_Length)
  {
    for(UInt32 i = 0; i < m_Length; ++i)
    {
      if((*this)[i] == With[i])
      {
      }
      else
      {
        return i + 1;
      }
    }
  }
  else
    return -1;
  return 0;
}

RF_Type::UInt8 String::operator[](const RF_Type::Size Index) const
{
  RF_ASSERT(Index <= Size() && Index >= 0, "Out of bound.");
  return *(GetBuffer() + Index);
}

RF_Type::UInt8& String::operator[](const RF_Type::Size Index)
{
  RF_ASSERT(Index <= Size() && Index >= 0, "Out of bound");
  return *(GetBuffer() + Index);
}

const RF_Type::UInt8* String::operator()(const RF_Type::Size ElementIndex) const
{
  RF_ASSERT(ElementIndex <= Size() && ElementIndex >= 0, "Out of bound");
  const RF_Type::UInt8* result = GetBuffer();
  MoveByGlyphs(result, ElementIndex);
  return result;
}

RF_Type::UInt8* String::operator()(const RF_Type::Size ElementIndex)
{
  RF_ASSERT(ElementIndex <= Size() && ElementIndex >= 0, "Out of bound");
  const RF_Type::UInt8* result = GetBuffer();
  MoveByGlyphs(result, ElementIndex);
  return const_cast<RF_Type::UInt8*>(result);
}

bool String::operator==(const String& Other) const
{
  if(m_Length != Other.m_Length)
  {
    return false;
  }

  for(UInt32 i = 0; i < m_Length; i++)
  {
    if(GetBuffer()[i] != Other.GetBuffer()[i])
    {
      return false;
    }
  }
  return true;
}

bool String::operator!=(const String& Other) const
{
  if(Other.m_Length != m_Length)
  {
    return true;
  }

  for(UInt32 i = 0; i < m_Length; ++i)
  {
    if(GetBuffer()[i] != Other.GetBuffer()[i])
    {
      return true;
    }
  }
  return false;
}

String String::operator+(const String& Str) const
{
  const int TERMINATION = 1;
  if(Length() + Str.Length())
  {
    RF_Type::Size bytes = Size() + Str.Size();

    if(Str.Length() > 0 && Length() > 0)
    {  // we only need one termination symbol
      --bytes;
    }

    String str(bytes);

    if(Length() > 0)
    {
      RF_SysMem::Copy(const_cast<char*>(str.c_str()), c_str(), Size());
    }

    if(Str.Length() > 0 && Length() > 0)
    {
      RF_SysMem::Copy(const_cast<char*>(str.c_str() + Size() - TERMINATION),
                      Str.c_str(), Str.Size());
    }
    else
    {
      RF_SysMem::Copy(const_cast<char*>(str.c_str()), Str.c_str(), Str.Size());
    }

    return str;
  }
  return String();
}

String& String::operator+=(const String& Str)
{
  if(Str.m_Length > 0)
  {
    RF_Type::Size bytes = m_Length + Str.m_Length + 1;
    String newStr(bytes);

    if(m_Length > 0)
      RF_SysMem::Copy(newStr.GetBuffer(), GetBuffer(), m_Length);
    RF_SysMem::Copy(newStr.GetBuffer() + m_Length, Str.GetBuffer(),
                    Str.m_Length + 1);
    Swap(newStr);
  }
  return *this;
}

String& String::operator=(const String& Other)
{
  m_DataManagment = Other.m_DataManagment;
  m_Length = Other.m_Length;
  if(Other.m_DataManagment == DataManagment::Copy)
  {  // Other is a locale buffer
    RF_SysMem::Copy(m_FixBuffer.Raw(), Other.m_FixBuffer.Raw(), BUFFER_SIZE);
    m_FixBuffer.SetSize(Other.m_FixBuffer.GetSize());
  }
  else
  {
    m_DynBuffer.m_Size = Other.m_DynBuffer.m_Size;
    m_DynBuffer.m_Buffer = new UInt8[m_DynBuffer.m_Size];
    RF_SysMem::Copy(m_DynBuffer.Raw(), Other.m_DynBuffer.Raw(),
                    m_DynBuffer.m_Size);
  }
  return *this;
}

char const* String::c_str() const
{
  return reinterpret_cast<char const*>(GetBuffer());
}

const RF_Type::UInt8* String::ByteData() const
{
  return GetBuffer();
}

RF_Type::Int32 String::HexToDec() const
{
  Int64 val;
  RF_SysStr::ToInt64(*this, 16, val);
  return val;
}

String String::Format(const String Str, ...)
{
  va_list argp;
  va_start(argp, Str);

  String result;
  result = String::FormatStrict(Str, argp);

  va_end(argp);
  return result;
}

String String::FormatStrict(const String& Str, va_list ArgumentList)
{
  RF_Mem::AutoPointerArray<char> out;
  RF_Mem::AutoPointerArray<char> dynBuf;
  Int32 byteLen = 0;
  Int32 buflen = 0;
  while(byteLen == buflen || byteLen == -1)
  {
    buflen += 256;
    dynBuf = RF_Mem::AutoPointerArray<char>(buflen);
    byteLen = RF_SysStr::Format(reinterpret_cast<UInt8*>(dynBuf.Get()),
                                buflen - 1, Str, ArgumentList);
  }
  out = RF_Mem::AutoPointerArray<char>(byteLen + 1);
  RF_SysMem::Copy(out.Get(), dynBuf.Get(), byteLen);
  out.Get()[byteLen] = 0;

  return String(out.Release().Ptr, byteLen, DataManagment::TransfereOwnership);
}

RF_Type::String& String::ToUpper()
{
  RF_SysStr::ToUpper(*this);
  return *this;
}

RF_Type::String String::ToUpper() const
{
  auto result = *this;
  RF_SysStr::ToUpper(result);
  return result;
}

RF_Type::String& String::ToLower()
{
  RF_SysStr::ToLower(*this);
  return *this;
}

RF_Type::String String::ToLower() const
{
  auto result = *this;
  RF_SysStr::ToLower(result);
  return result;
}

RF_Type::Bool String::IsNumber() const
{
  for(UInt32 i = 0; i < m_Length; ++i)
  {
    if(GetBuffer()[i] >= 48 && GetBuffer()[i] <= 57)
    {
    }
    else
    {
      return false;
    }
  }
  return true;
}

RF_Type::Bool String::IsFloatingpointNumber() const
{
  for(UInt32 i = 0; i < m_Length; ++i)
    if((GetBuffer()[i] >= 48 && GetBuffer()[i] <= 57) || GetBuffer()[i] == '.')
    {
    }
    else
      return false;
  return true;
}

RF_Type::Bool String::IsBoolean() const
{
  static const String TRUE("true", sizeof("true"));
  static const String FALSE("false", sizeof("false"));
  String lowerCase = *this;
  lowerCase.ToLower();
  return lowerCase == TRUE || lowerCase == FALSE;
}

void String::Swap(String& Other)
{
  RF_ASSERT(&Other != this, "It's not allowed to use Swap with itself!");
  // make a copy of this to tmp;
  String tmp;
  if(m_Length > 0)
  {
    tmp.m_DataManagment = m_DataManagment;
    tmp.m_Length = m_Length;
    if(m_DataManagment == DataManagment::Copy)
    {
      RF_SysMem::Copy(tmp.m_FixBuffer.Raw(), m_FixBuffer.Raw(), BUFFER_SIZE);
      tmp.m_FixBuffer.SetSize(m_FixBuffer.GetSize());
    }
    else
    {
      tmp.m_DynBuffer.m_Buffer = m_DynBuffer.m_Buffer;
      tmp.m_DynBuffer.m_Size = m_DynBuffer.m_Size;
      // ensure to not leak memory
      m_DynBuffer.m_Size = 0;
      m_DynBuffer.m_Buffer = 0;
    }
  }

  // copy Other to this
  m_DataManagment = Other.m_DataManagment;
  m_Length = Other.m_Length;
  if(Other.m_DataManagment == DataManagment::Copy)
  {  // Other use a locale buffer
    RF_SysMem::Copy(m_FixBuffer.Raw(), Other.m_FixBuffer.Raw(), BUFFER_SIZE);
    m_FixBuffer.SetSize(Other.m_FixBuffer.GetSize());
  }
  else
  {
    m_DynBuffer.m_Buffer = Other.m_DynBuffer.m_Buffer;
    m_DynBuffer.m_Size = Other.m_DynBuffer.m_Size;
    // ensure to not leak memory
    Other.m_DynBuffer.m_Buffer = 0;
    Other.m_DynBuffer.m_Size = 0;
  }

  // move tmp to Other
  Other.m_DataManagment = tmp.m_DataManagment;
  Other.m_Length = tmp.m_Length;
  if(tmp.m_DataManagment == DataManagment::Copy)
  {  // tmp use a locale buffer
    if(tmp.m_Length > 0)
    {
      RF_SysMem::Copy(Other.m_FixBuffer.Raw(), tmp.m_FixBuffer.Raw(),
                      BUFFER_SIZE);
    }
    else
    {
      Other.m_FixBuffer[0] = '\0';
    }
    Other.m_FixBuffer.SetSize(tmp.m_FixBuffer.GetSize());
  }
  else
  {
    Other.m_DynBuffer.m_Buffer = tmp.m_DynBuffer.m_Buffer;
    Other.m_DynBuffer.m_Size = tmp.m_DynBuffer.m_Size;
    // ensure to not leak memory
    tmp.m_DynBuffer.m_Buffer = 0;
    tmp.m_DynBuffer.m_Size = 0;
  }
}

RF_Type::UInt8* String::GetBuffer()
{
  if(m_DataManagment == DataManagment::Copy)
    return m_FixBuffer.Raw();
  else
    return m_DynBuffer.Raw();
}

const RF_Type::UInt8* String::GetBuffer() const
{
  if(m_DataManagment == DataManagment::Copy)
    return m_FixBuffer.Raw();
  else
    return m_DynBuffer.Raw();
}

RF_Type::Bool String::IsEmpty() const
{
  return Size() == 0;
}

RF_Type::Size String::Size() const
{
  if(m_DataManagment == DataManagment::Copy)
    return m_FixBuffer.GetSize();
  else
    return m_DynBuffer.GetSize();
}

RF_Type::Bool String::IsASCII() const
{
  return Size() - 1 == m_Length;
}

RF_Type::Bool String::CanGlyphsBeCompared(const String& Other) const
{
  return IsASCII() == Other.IsASCII();
}

RF_Type::Size String::MoveByGlyphs(RF_Type::UInt8 const*& Buffer,
                                   const RF_Type::Size Glyphs) const
{
  RF_Type::Size glyphsLeft = Glyphs;
  if(Buffer != NULL && GetBuffer() + Size() > Buffer && Buffer >= GetBuffer())
  {
    while(Buffer[0] != '\0' && glyphsLeft > 0)
    {
      RF_Type::Size glyphSize = 0;
      ++Buffer;
      --glyphsLeft;
    }
  }
  return Glyphs - glyphsLeft;
}

RF_Type::Size String::GetLength(const RF_Type::UInt8* CString,
                                const RF_Type::Size CStringByteSize)
{
  return RF_SysStr::Length(CString, CStringByteSize);
}

String String::operator+(const StringView& Other) const
{
  const int TERMINATION = 1;
  if(Length() + Other.Length())
  {
    RF_Type::Size bytes = Size() + Other.Length();

    if(Other.Length() > 0 && Length() > 0)
    {  // we only need one termination symbol
      --bytes;
    }

    String str(bytes);

    if(Length() > 0)
    {
      RF_SysMem::Copy(const_cast<char*>(str.c_str()), c_str(), Size());
    }

    if(Other.Length() > 0 && Length() > 0)
    {
      RF_SysMem::Copy(const_cast<char*>(str.c_str() + Size() - TERMINATION),
                      Other.Data(), Other.Length());
    }
    else
    {
      RF_SysMem::Copy(const_cast<char*>(str.c_str()), Other.Data(),
                      Other.Length());
    }

    return str;
  }
  return String();
}

String::String(const StringView& Copy) : m_DataManagment(DataManagment::Copy)
{
  m_Length = Copy.Length();
  if(Copy.Length() <= BUFFER_SIZE)
  {
    if(Copy.Length() > 0)
    {
      RF_SysMem::Copy(static_cast<void*>(m_FixBuffer.Raw()), Copy.Data(),
                      m_Length);
      m_FixBuffer[m_Length] = 0;
    }
    else
    {
      m_FixBuffer[0] = 0;
    }
    m_FixBuffer.SetSize(Copy.Length()+1);
  }
  else
  {
    m_DataManagment = DataManagment::AllocateAndCopy;
    m_DynBuffer.m_Buffer = new UInt8[Copy.Length()];
    m_DynBuffer.m_Size = Copy.Length()+1;
    RF_SysMem::Copy(static_cast<void*>(m_DynBuffer.Raw()), Copy.Data(),
                    m_Length);
    m_DynBuffer[m_Length] = '\0';
  }
}

}  // namespace RadonFramework::Core::Types

RF_Type::String operator"" _rfs(const char* Data, size_t Size)
{
  return RF_Type::String(Data, Size + 1);
}