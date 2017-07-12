#ifndef RF_SYSTEM_IO_DEBUGGER_HPP
#define RF_SYSTEM_IO_DEBUGGER_HPP
#if _MSC_VER > 1000
#pragma once
#endif

namespace RadonFramework::System::IO {

class Debugger:public RF_Pattern::Singleton<Debugger>
{
public:
    void WriteLine(const RF_Type::String &Str);
protected:
    friend class RF_Pattern::Singleton<Debugger>;
    Debugger();
};

}

#endif // RF_SYSTEM_IO_DEBUGGER_HPP
