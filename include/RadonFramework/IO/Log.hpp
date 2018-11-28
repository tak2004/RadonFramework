#ifndef RF_IO_LOG_HPP
#define RF_IO_LOG_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <stdarg.h>
#include <RadonFramework/BuildInfo.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Diagnostics/Appender.hpp>

namespace RadonFramework::IO
{
class Log
{
public:
  static void WriteInfo(Memory::AutoPointer<RF_Type::String>& Text);
  static void WriteError(Memory::AutoPointer<RF_Type::String>& Text);
  static void WriteFatalError(Memory::AutoPointer<RF_Type::String>& Text);
  static void WriteDebug(Memory::AutoPointer<RF_Type::String>& Text);
  static void AddAppender(Memory::AutoPointer<Diagnostics::Appender>& Value);
  static void
  AddAppenders(Memory::AutoPointer<Collections::Array<
                   Memory::AutoPointer<Diagnostics::Appender>>>& Values);
  static void
  ReplaceAppenders(Memory::AutoPointer<Collections::Array<
                       Memory::AutoPointer<Diagnostics::Appender>>>& Values);
  static void RemoveAppender(const Diagnostics::Appender& Value);

  static RF_Type::Bool IsInfoEnabled;
  static RF_Type::Bool IsErrorEnabled;
  static RF_Type::Bool IsFatalErrorEnabled;
  static RF_Type::Bool IsDebugEnabled;

protected:
  static void PoolLogInfoTask(void* Data);
  static void PoolLogErrorTask(void* Data);
  static void PoolLogFatalErrorTask(void* Data);
  static void PoolLogDebugTask(void* Data);

  static Collections::Array<Memory::AutoPointer<Diagnostics::Appender>>
      m_Appender;
};

inline void LogInfo(const char* Str, ...)
{
  if(Log::IsInfoEnabled)
  {
    RF_Mem::AutoPointer<RF_Type::String> ptr(new RF_Type::String());
    va_list argp;
    va_start(argp, Str);
    RF_Type::String str = RF_Type::String::FormatStrict(
        RF_Type::String::UnsafeStringCreation(Str), argp);
    va_end(argp);
    ptr->Swap(str);
    Log::WriteInfo(ptr);
  }
}

inline void LogError(const char* Str, ...)
{
  if(Log::IsErrorEnabled)
  {
    RF_Mem::AutoPointer<RF_Type::String> ptr(new RF_Type::String());
    va_list argp;
    va_start(argp, Str);
    RF_Type::String str = RF_Type::String::FormatStrict(
        RF_Type::String::UnsafeStringCreation(Str), argp);
    va_end(argp);
    ptr->Swap(str);
    Log::WriteError(ptr);
  }
}

inline void LogFatalError(const char* Str, ...)
{
  if(Log::IsFatalErrorEnabled)
  {
    RF_Mem::AutoPointer<RF_Type::String> ptr(new RF_Type::String());
    va_list argp;
    va_start(argp, Str);
    RF_Type::String str = RF_Type::String::FormatStrict(
        RF_Type::String::UnsafeStringCreation(Str), argp);
    va_end(argp);
    ptr->Swap(str);
    Log::WriteFatalError(ptr);
  }
}

inline void LogDebug(const char* Str, ...)
{
  if(Log::IsDebugEnabled)
  {
    RF_Mem::AutoPointer<RF_Type::String> ptr(new RF_Type::String());
    va_list argp;
    va_start(argp, Str);
    RF_Type::String str = RF_Type::String::FormatStrict(
        RF_Type::String::UnsafeStringCreation(Str), argp);
    va_end(argp);
    ptr->Swap(str);
    Log::WriteDebug(ptr);
  }
}

inline void LogDebugBuild(const char* Str, ...)
{
  if(BuildInfo::CompileForDebugging == BuildInfo::DebugMode::True)
  {
    RF_Mem::AutoPointer<RF_Type::String> ptr(new RF_Type::String());
    va_list argp;
    va_start(argp, Str);
    RF_Type::String str = RF_Type::String::FormatStrict(
        RF_Type::String::UnsafeStringCreation(Str), argp);
    va_end(argp);
    ptr->Swap(str);
    Log::WriteDebug(ptr);
  }
}

}  // namespace RadonFramework::IO

#ifndef RF_SHORTHAND_NAMESPACE_IO
#define RF_SHORTHAND_NAMESPACE_IO
namespace RF_IO = RadonFramework::IO;
#endif

#endif  // RF_IO_LOG_HPP