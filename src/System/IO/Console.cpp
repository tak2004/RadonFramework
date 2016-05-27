#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/System/IO/Console.hpp"
#include "RadonFramework/Threading/Scopelock.hpp"
#include "RadonFramework/IO/Log.hpp"
#include "RadonFramework/Defines.hpp"
#include "RadonFramework/IO/Uri.hpp"
#include <stdio.h>
#include <stdarg.h>

namespace RFT=RadonFramework::Threading;
using namespace RadonFramework::IO;
using namespace RadonFramework::System::IO;
using namespace RadonFramework::Core::Types;

static RadonFramework::System::Threading::Mutex m_Busy;

#if defined(RF_WINDOWS)
#include <windows.h>

HANDLE RF_CONSOLE_HANDLE;
WORD RF_CONSOLE_OLDCOLORATTRS;

WORD ImplementationMapFromColor(const Bool& Foreground, const ConsoleColor::Type Color)
{
    WORD col=static_cast<WORD>(Color);
    if (false==Foreground)
        col=col<<4;
    return col;
}

ConsoleColor::Type ImplementationMapToColor(const bool Foreground, const WORD Color)
{
    WORD col=Color;
    if (false==Foreground)
        col=col >> 4;
    col=col & 15;
    return static_cast<ConsoleColor::Type>(col);
}

void ImplementationInit(ConsoleColor::Type& ForegroundColor, 
                        ConsoleColor::Type& BackgroundColor)
{
    RF_CONSOLE_HANDLE=GetStdHandle ( STD_OUTPUT_HANDLE );

    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(RF_CONSOLE_HANDLE, &csbiInfo);
    RF_CONSOLE_OLDCOLORATTRS = csbiInfo.wAttributes;
    ForegroundColor=ImplementationMapToColor(true,RF_CONSOLE_OLDCOLORATTRS);
    BackgroundColor=ImplementationMapToColor(false,RF_CONSOLE_OLDCOLORATTRS);
}

void ImplementationSetColor(ConsoleColor::Type Foreground, ConsoleColor::Type Background)
{
    SetConsoleTextAttribute(RF_CONSOLE_HANDLE,ImplementationMapFromColor(true,Foreground)
                            | ImplementationMapFromColor(false,Background));
}

void ImplementationResetColor()
{
    SetConsoleTextAttribute(RF_CONSOLE_HANDLE,RF_CONSOLE_OLDCOLORATTRS);
}
#endif

#if defined(RF_UNIX)
void ImplementationInit(ConsoleColor::Type& ForegroundColor, 
                        ConsoleColor::Type& BackgroundColor)
{

}

void ImplementationSetColor(ConsoleColor::Type Foreground, ConsoleColor::Type Background)
{

}

void ImplementationResetColor()
{

}
#endif

Console::Console()
{
    ImplementationInit(m_ForegroundColor,m_BackgroundColor);
}

void Console::ResetColor()
{
    ImplementationResetColor();
}
                    
void Console::BackgroundColor(ConsoleColor::Type Color)
{
    if (Color!=m_BackgroundColor)
    {
        m_BackgroundColor=Color;
        ImplementationSetColor(m_ForegroundColor,m_BackgroundColor);
    }
}

ConsoleColor::Type Console::BackgroundColor()
{
    return m_BackgroundColor;
}
                    
void Console::ForegroundColor(ConsoleColor::Type Color)
{
    if (Color!=m_ForegroundColor)
    {
        m_ForegroundColor=Color;
        ImplementationSetColor(m_ForegroundColor,m_BackgroundColor);
    }
}

ConsoleColor::Type Console::ForegroundColor()
{
    return m_ForegroundColor;
}

Console& RadonFramework::System::IO::operator<<(Console& Con,bool& val){
    RF_Type::String str;
    str=Convert::ToString(val);
    fputs(str.c_str(),stdout);
    return Con;
}
Console& RadonFramework::System::IO::operator<<(Console& Con,short& val){
    RF_Type::String str; 
    str=Convert::ToString(static_cast<Bool>(val));
    fputs(str.c_str(),stdout);
    return Con;
}
Console& RadonFramework::System::IO::operator<<(Console& Con,unsigned short& val){
    RF_Type::String str;
    str=Convert::ToString(static_cast<Int16>(val));
    fputs(str.c_str(),stdout);
    return Con;
}
Console& RadonFramework::System::IO::operator<<(Console& Con,int& val){
    RF_Type::String str;
    str=Convert::ToString(static_cast<Int32>(val));
    fputs(str.c_str(),stdout);
    return Con;
}
Console& RadonFramework::System::IO::operator<<(Console& Con,unsigned int& val){
    RF_Type::String str;
    str=Convert::ToString(static_cast<UInt32>(val));
    fputs(str.c_str(),stdout);
    return Con;
}
Console& RadonFramework::System::IO::operator<<(Console& Con,long& val){
    RF_Type::String str;
    str=Convert::ToString(static_cast<Int32>(val));
    fputs(str.c_str(),stdout);
    return Con;
}
Console& RadonFramework::System::IO::operator<<(Console& Con,unsigned long& val){
    RF_Type::String str;
    str=Convert::ToString(static_cast<UInt32>(val));
    fputs(str.c_str(),stdout);
    return Con;
}
Console& RadonFramework::System::IO::operator<<(Console& Con,float& val){
    RF_Type::String str=Convert::ToString(val);
    fputs(str.c_str(),stdout);
    return Con;
}
Console& RadonFramework::System::IO::operator<<(Console& Con,double& val){
    RF_Type::String str=Convert::ToString(val);
    fputs(str.c_str(),stdout);
    return Con;
}

Console& RadonFramework::System::IO::operator<<(Console& Con,const void* val){
    RF_Type::String str;
    str=RF_Type::String::Format("%p"_rfs,val);
    fputs(str.c_str(),stdout);
    return Con;
}

Console& RadonFramework::System::IO::operator<<(Console& Con,char c){
    RF_Type::String str;
    str=Convert::ToString(c);
    fputs(str.c_str(),stdout);
    return Con;
}
Console& RadonFramework::System::IO::operator<<(Console& Con,signed char c){
    RF_Type::String str;
    str=Convert::ToString(c);
    fputs(str.c_str(),stdout);
    return Con;
}
Console& RadonFramework::System::IO::operator<<(Console& Con,unsigned char c){
    RF_Type::String str;
    str=Convert::ToString(c);
    fputs(str.c_str(),stdout);
    return Con;
}
Console& RadonFramework::System::IO::operator<<(Console& Con,int c){
    RF_Type::String str;
    str=Convert::ToString(static_cast<Int32>(c));
    fputs(str.c_str(),stdout);
    return Con;
}
Console& RadonFramework::System::IO::operator<<(Console& Con,ConsoleCommand c){
    switch (c)
    {
        case EndLine:
            printf("\n");
    };
    return Con;
}

Console& RadonFramework::System::IO::operator<<(Console& Con,const char* s){
    fputs(s,stdout);
    return Con;
}

void RadonFramework::System::IO::Console::WriteColoredLine(const RF_Type::String &Str,
                        RF_IO::ConsoleColor::Type BackgroundColor,
                        RF_IO::ConsoleColor::Type ForegroundColor)
{
    RFT::Scopelock lock(m_Busy);
    if (m_BackgroundColor!=BackgroundColor)
        m_BackgroundColor=BackgroundColor;
    if (m_ForegroundColor!=ForegroundColor)
        m_ForegroundColor=ForegroundColor;
    ImplementationSetColor(ForegroundColor,BackgroundColor);
    printf("%s\n", Str.c_str());
}

void RadonFramework::System::IO::Console::WriteLine(const RF_Type::String &Str)
{
    RFT::Scopelock lock(m_Busy);
    printf("%s\n",Str.c_str());
}

void RadonFramework::System::IO::Console::WriteLine(const Core::Types::UInt8 &Number)
{
    RFT::Scopelock lock(m_Busy);
    RF_Type::String str;
    str=Convert::ToString(Number);
    printf("%s\n",str.c_str());
}

void RadonFramework::System::IO::Console::WriteLine(const Core::Types::UInt16 &Number)
{
    RFT::Scopelock lock(m_Busy);
    RF_Type::String str;
    str=Convert::ToString(Number);
    printf("%s\n",str.c_str());
}

void RadonFramework::System::IO::Console::WriteLine(const Core::Types::UInt32 &Number)
{
    RFT::Scopelock lock(m_Busy);
    RF_Type::String str;
    str=Convert::ToString(Number);
    printf("%s\n",str.c_str());
}

void RadonFramework::System::IO::Console::WriteLine(const Core::Types::UInt64 &Number)
{
    RFT::Scopelock lock(m_Busy);
    RF_Type::String str;
    str=Convert::ToString(Number);
    printf("%s\n",str.c_str());
}

void RadonFramework::System::IO::Console::WriteLine(const Core::Types::Int8 &Number)
{
    RFT::Scopelock lock(m_Busy);
    RF_Type::String str;
    str=Convert::ToString(Number);
    printf("%s\n",str.c_str());
}

void RadonFramework::System::IO::Console::WriteLine(const Core::Types::Int16 &Number)
{
    RFT::Scopelock lock(m_Busy);
    RF_Type::String str;
    str=Convert::ToString(Number);
    printf("%s\n",str.c_str());
}

void RadonFramework::System::IO::Console::WriteLine(const Core::Types::Int32 &Number)
{
    RFT::Scopelock lock(m_Busy);
    RF_Type::String str;
    str=Convert::ToString(Number);
    printf("%s\n",str.c_str());
}

void RadonFramework::System::IO::Console::WriteLine(const Core::Types::Int64 &Number)
{
    RFT::Scopelock lock(m_Busy);
    RF_Type::String str;
    str=Convert::ToString(Number);
    printf("%s\n",str.c_str());
}

void RadonFramework::System::IO::Console::WriteLine(char *Format,...)
{
    RFT::Scopelock lock(m_Busy);
    va_list args;
    va_start( args, Format );
    vprintf(Format, args);
    va_end(args);
    printf("\n");
}

void RadonFramework::System::IO::Console::WriteLine(const char* Str)
{
    RFT::Scopelock lock(m_Busy);
    printf("%s\n",Str);
}

void RadonFramework::System::IO::Console::NewLine()
{
    RFT::Scopelock lock(m_Busy);
    printf("\n");
}

bool RadonFramework::System::IO::Console::IsBusy()
{
    return m_Busy.IsLocked();
}
