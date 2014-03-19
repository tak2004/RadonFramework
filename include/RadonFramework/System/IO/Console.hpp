#ifndef RF_SYSTEM_IO_CONSOLE_HPP
#define RF_SYSTEM_IO_CONSOLE_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Core/Pattern/Singleton.hpp>
#include <RadonFramework/System/Threading/Mutex.hpp>
#include <RadonFramework/Net/FixedLengthString.hpp>
#include <RadonFramework/Core/Types/String.hpp>
#include <RadonFramework/Core/Types/Int64.hpp>
#include <RadonFramework/Core/Types/Int32.hpp>
#include <RadonFramework/Core/Types/Int16.hpp>
#include <RadonFramework/Core/Types/Int8.hpp>
#include <RadonFramework/Core/Types/UInt64.hpp>
#include <RadonFramework/Core/Types/UInt32.hpp>
#include <RadonFramework/Core/Types/UInt16.hpp>
#include <RadonFramework/Core/Types/UInt8.hpp>
#include <RadonFramework/Core/Pattern/Event.hpp>
#include <RadonFramework/IO/ConsoleColor.hpp>

namespace RadonFramework
{
    namespace IO{class LogChannel;}

    namespace System
    {
        namespace IO
        {
            enum ConsoleCommand{
                EndLine
            };

            class Console:public Singleton<Console>,public IObserver
            {
                public:
                    void ResetColor();
                    
                    void BackgroundColor(RadonFramework::IO::ConsoleColor::Type Color);

                    RadonFramework::IO::ConsoleColor::Type BackgroundColor();
                    
                    void ForegroundColor(RadonFramework::IO::ConsoleColor::Type Color);

                    RadonFramework::IO::ConsoleColor::Type ForegroundColor();

                    void WriteLine(char *Format,...);
                    void WriteLine(const char *Str);

                    void WriteColoredLine(const Core::Types::String &Str,
                        RadonFramework::IO::ConsoleColor::Type BackgroundColor,
                        RadonFramework::IO::ConsoleColor::Type ForegroundColor);
                    void WriteLine(const Core::Types::String &Str);
                    void WriteLine(const Core::Types::UInt8 &Number);
                    void WriteLine(const Core::Types::UInt16 &Number);
                    void WriteLine(const Core::Types::UInt32 &Number);
                    void WriteLine(const Core::Types::UInt64 &Number);
                    void WriteLine(const Core::Types::Int8 &Number);
                    void WriteLine(const Core::Types::Int16 &Number);
                    void WriteLine(const Core::Types::Int32 &Number);
                    void WriteLine(const Core::Types::Int64 &Number);
                    template<typename T,unsigned int Len> void WriteLine(const Net::FixedLengthString<T,Len>& Str);
                    
                    void NewLine();
                    bool IsBusy();
                protected:
                    friend class Singleton<Console>;
                    Console();
                    RadonFramework::IO::ConsoleColor::Type m_ForegroundColor;
                    RadonFramework::IO::ConsoleColor::Type m_BackgroundColor;
            };

            // C/C++ types
            Console& operator<<(Console& Con,bool& val);
            Console& operator<<(Console& Con,short& val);
            Console& operator<<(Console& Con,unsigned short& val);
            Console& operator<<(Console& Con,int& val);
            Console& operator<<(Console& Con,unsigned int& val);
            Console& operator<<(Console& Con,long& val);
            Console& operator<<(Console& Con,unsigned long& val);
            Console& operator<<(Console& Con,float& val);
            Console& operator<<(Console& Con,double& val);
            Console& operator<<(Console& Con,const void* val);

            Console& operator<<(Console& Con,char c);
            Console& operator<<(Console& Con,signed char c);
            Console& operator<<(Console& Con,unsigned char c);
            Console& operator<<(Console& Con,int c);

            Console& operator<<(Console& Con,const char* s);

            // RadonFramework types
            Console& operator<<(Console& Con,ConsoleCommand c);

            template<typename T,unsigned int Len>
            Console& operator<<(Console& Con,Net::FixedLengthString<T,Len>& c){
                Con<c.c_str();
                return Con;
            }

            template<typename T,unsigned int Len>
            void Console::WriteLine(const Net::FixedLengthString<T,Len>& Str)
            {
                WriteLine(Str.Str());
            }
        }
    }
}

#define CWrite RadonFramework::System::IO::Console::GetInstance().WriteLine

#endif // RF_SYSTEM_IO_CONSOLE_HPP
