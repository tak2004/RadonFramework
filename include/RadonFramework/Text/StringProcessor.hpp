#ifndef RF_TEXT_STRINGPROCESSOR_HPP
#define RF_TEXT_STRINGPROCESSOR_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Types/Bool.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>

namespace RadonFramework::Text
{
template <class StringProcessingPolicy>
class StringProcessor
{
public:
    typedef typename StringProcessingPolicy::StorageType ProcessorStorage;

  // Constructor and destructor.
  StringProcessor();
  ~StringProcessor();

  /** Initialize the string processor and the necessary
   * data, used by the algorithm.
   * Return false if there is an problem else true.
   * If the parameter Copy is set to true a copy of Text
   * will be generated else it use Text directly.
   */
  RF_Type::Bool Init(RF_Type::String& Text,
                     const RF_Type::UInt32 Position,
                     const RF_Type::Bool CopyText = true);

  /** Do the string operation on the next match.
   * Return -1 if there is no match anymore else the
   * position in the processed text.
   */
  RF_Type::Int32 DoNext();

  /** Do the string operation on the previous match.
   * Return -1 if there is no match anymore else the
   * position in the processed text.
   */
  RF_Type::Int32 DoPrev();

  /** Do the string operation on all matches.
   * Return the count of matches.
   */
  RF_Type::Int32 DoAll();

  /** Do the string operation on all matches.
   * Return the count of matches and indices
   */
  RF_Type::Int32 DoAll(RF_Mem::AutoPointerArray<RF_Type::UInt32>& Indices);

  /// Reset the processing and start from beginning.
  void Reset(const RF_Type::UInt32 Position);

  /// Return the processed text.
  RF_Type::String& ProcessedText() const;

  /** Return true if this object hold an own copy of the
   * source string else false.
   */
  RF_Type::Bool HoldCopy() const;

  /// Return the storage of the processing policy.
  ProcessorStorage& Storage();

protected:
  ProcessorStorage m_Storage;
  RF_Type::String* m_Text;
  RF_Type::Bool m_Copy;
};

template <class StringProcessorPolicy>
StringProcessor<StringProcessorPolicy>::StringProcessor()
: m_Text(0), m_Copy(true)
{
  m_Text = new RF_Type::String();
}

template <class StringProcessorPolicy>
StringProcessor<StringProcessorPolicy>::~StringProcessor()
{
  if(m_Copy)
    delete m_Text;
}

template <class StringProcessorPolicy>
RF_Type::Bool
StringProcessor<StringProcessorPolicy>::Init(RF_Type::String& Text,
                                             const RF_Type::UInt32 Position,
                                             const RF_Type::Bool CopyText)
{
  // clean up if necessary
  if(m_Copy)
    delete m_Text;

  // init new values
  m_Copy = CopyText;
  if(m_Copy)
    m_Text = new RF_Type::String(Text);
  else
    m_Text = &Text;

  // let the policy run
  return StringProcessorPolicy::Init(*m_Text, Position, &m_Storage);
}

template <class StringProcessorPolicy>
RF_Type::Int32 StringProcessor<StringProcessorPolicy>::DoNext()
{
  return StringProcessorPolicy::DoNext(*m_Text, &m_Storage);
}

template <class StringProcessorPolicy>
RF_Type::Int32 StringProcessor<StringProcessorPolicy>::DoAll()
{
  return StringProcessorPolicy::DoAll(*m_Text, &m_Storage);
}

template <class StringProcessorPolicy>
RF_Type::Int32 StringProcessor<StringProcessorPolicy>::DoAll(
    RF_Mem::AutoPointerArray<RF_Type::UInt32>& Indices)
{
  return StringProcessorPolicy::DoAll(Indices, *m_Text, &m_Storage);
}

template <class StringProcessorPolicy>
void StringProcessor<StringProcessorPolicy>::Reset(
    const RF_Type::UInt32 Position)
{
  StringProcessorPolicy::Reset(*m_Text, Position, &m_Storage);
}

template <class StringProcessorPolicy>
RF_Type::String& StringProcessor<StringProcessorPolicy>::ProcessedText() const
{
  return *m_Text;
}

template <class StringProcessorPolicy>
RF_Type::Bool StringProcessor<StringProcessorPolicy>::HoldCopy() const
{
  return m_Copy;
}

template <class StringProcessorPolicy>
typename StringProcessor<StringProcessorPolicy>::ProcessorStorage&
StringProcessor<StringProcessorPolicy>::Storage()
{
  return m_Storage;
}

}  // namespace RadonFramework::Text

#ifndef RF_SHORTHAND_NAMESPACE_TEXT
#define RF_SHORTHAND_NAMESPACE_TEXT
namespace RF_Text = RadonFramework::Text;
#endif

#endif  // RF_TEXT_STRINGPROCESSOR_HPP
