#ifndef RF_IO_LOG_HPP
#define RF_IO_LOG_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Appender.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <stdarg.h>

namespace RadonFramework
{
    namespace IO
    {
        class Log
        {
            public:
                static void WriteInfo(Memory::AutoPointer<RFTYPE::String>& Text);
                static void WriteError(Memory::AutoPointer<RFTYPE::String>& Text);
                static void WriteFatalError(Memory::AutoPointer<RFTYPE::String>& Text);
                static void WriteDebug(Memory::AutoPointer<RFTYPE::String>& Text);
                static void AddAppender(Memory::AutoPointer<Diagnostics::Appender>& Value);
                static void AddAppenders(Memory::AutoPointer<Collections::Array<Memory::AutoPointer<Diagnostics::Appender> > >& Values);
                static void ReplaceAppenders(Memory::AutoPointer<Collections::Array<Memory::AutoPointer<Diagnostics::Appender> > >& Values);
                static void RemoveAppender(const Diagnostics::Appender& Value);

                static RFTYPE::Bool IsInfoEnabled;
                static RFTYPE::Bool IsErrorEnabled;
                static RFTYPE::Bool IsFatalErrorEnabled;
                static RFTYPE::Bool IsDebugEnabled;
            protected:
                static void PoolLogInfoTask(void* Data);
                static void PoolLogErrorTask(void* Data);
                static void PoolLogFatalErrorTask(void* Data);
                static void PoolLogDebugTask(void* Data);

                static Collections::Array<Memory::AutoPointer<Diagnostics::Appender> > m_Appender;
        };

        inline void LogInfo(const char* Str,...)
        {
            if (RadonFramework::IO::Log::IsInfoEnabled)
            {
                RadonFramework::Memory::AutoPointer<RFTYPE::String> ptr(new RFTYPE::String());
                va_list argp;
                va_start(argp, Str);
                RFTYPE::String str=RFTYPE::String::Format(RFTYPE::String::UnsafeStringCreation(Str), argp);
                va_end(argp);
                ptr->Swap(str); RadonFramework::IO::Log::WriteInfo(ptr);
            }
        }

        inline void LogError(const char* Str,...)
        {
            if (RadonFramework::IO::Log::IsErrorEnabled)
            {
                RadonFramework::Memory::AutoPointer<RFTYPE::String> ptr(new RFTYPE::String());
                va_list argp;
                va_start(argp, Str);
                RFTYPE::String str=RFTYPE::String::Format(RFTYPE::String::UnsafeStringCreation(Str), argp);
                va_end(argp);
                ptr->Swap(str); RadonFramework::IO::Log::WriteError(ptr);
            }
        }

        inline void LogFatalError(const char* Str,...)
        {
            if (RadonFramework::IO::Log::IsFatalErrorEnabled)
            {
                RadonFramework::Memory::AutoPointer<RFTYPE::String> ptr(new RFTYPE::String());
                va_list argp;
                va_start(argp, Str);
                RFTYPE::String str=RFTYPE::String::Format(RFTYPE::String::UnsafeStringCreation(Str), argp);
                va_end(argp);
                ptr->Swap(str); RadonFramework::IO::Log::WriteFatalError(ptr);
            }
        }

        inline void LogDebug(char* Str,...)
        {
            if (RadonFramework::IO::Log::IsDebugEnabled)
            {
                RadonFramework::Memory::AutoPointer<RFTYPE::String> ptr(new RFTYPE::String());
                va_list argp;
                va_start(argp, Str);
                RFTYPE::String str=RFTYPE::String::Format(RFTYPE::String::UnsafeStringCreation(Str), argp);
                va_end(argp);
                ptr->Swap(str); RadonFramework::IO::Log::WriteDebug(ptr);
            }
        }
    }
}

#endif // RF_IO_LOG_HPP