#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/LogConsole.hpp"

using namespace RadonFramework::Core::Types;
using namespace RadonFramework::IO;
using namespace RadonFramework::Diagnostics;

void LogConsole::WriteInfo(const String& Text)
{ 
  //  Console::GetInstance().WriteColoredLine(Text,ConsoleColor::Black,ConsoleColor::Gray);
}

void LogConsole::WriteError(const String& Text)
{
    //Console::GetInstance().WriteColoredLine(Text,ConsoleColor::Black,ConsoleColor::DarkRed);
}

void LogConsole::WriteFatalError(const String& Text)
{
    //Console::GetInstance().WriteColoredLine(Text,ConsoleColor::Black,ConsoleColor::Red);
}

void LogConsole::WriteDebug(const String& Text)
{
    //Console::GetInstance().WriteColoredLine(Text,ConsoleColor::Black,ConsoleColor::DarkYellow);
}