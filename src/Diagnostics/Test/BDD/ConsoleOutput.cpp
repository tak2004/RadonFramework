#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/Diagnostics/Test/BDD/ConsoleOutput.hpp"
#include "RadonFramework/System/IO/Console.hpp"

namespace RadonFramework::Diagnostics::Test::BDD {

void ConsoleOutput::WriteText(const RF_Type::String& Text) const
{
	RF_SysIO::Console::GetInstance().WriteColoredLine(Text, 
		RF_IO::ConsoleColor::Black, RF_IO::ConsoleColor::White);
}

void ConsoleOutput::WriteError(const RF_Type::String& Text) const
{
	RF_SysIO::Console::GetInstance().WriteColoredLine(Text, 
		RF_IO::ConsoleColor::Black, RF_IO::ConsoleColor::Red);
}

void ConsoleOutput::WriteSuccess(const RF_Type::String& Text) const
{
	RF_SysIO::Console::GetInstance().WriteColoredLine(Text, 
		RF_IO::ConsoleColor::Black, RF_IO::ConsoleColor::Green);
}

void ConsoleOutput::WriteFailure(const RF_Type::String& Text) const
{
	RF_SysIO::Console::GetInstance().WriteColoredLine(Text, 
		RF_IO::ConsoleColor::Black, RF_IO::ConsoleColor::Yellow);
}

void ConsoleOutput::WritePending(const RF_Type::String& Text) const
{
	RF_SysIO::Console::GetInstance().WriteColoredLine(Text, 
		RF_IO::ConsoleColor::Black, RF_IO::ConsoleColor::Cyan);
}

void ConsoleOutput::WriteSkipped(const RF_Type::String& Text) const
{
	RF_SysIO::Console::GetInstance().WriteColoredLine(Text, 
		RF_IO::ConsoleColor::Black, RF_IO::ConsoleColor::Magenta);
}

void ConsoleOutput::WriteStats(const RF_Type::String& Text) const
{
	RF_SysIO::Console::GetInstance().WriteColoredLine(Text, 
		RF_IO::ConsoleColor::Black, RF_IO::ConsoleColor::Cyan);
}

}