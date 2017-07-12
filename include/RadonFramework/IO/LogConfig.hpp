#ifndef RF_DIAGNOSTICS_LOGCONFIG_HPP
#define RF_DIAGNOSTICS_LOGCONFIG_HPP
#if _MSC_VER > 1000
#pragma once
#endif

#include <RadonFramework/Diagnostics/Appender.hpp>
#include <RadonFramework/Memory/AutoPointerArray.hpp>
#include <RadonFramework/Memory/AutoPointer.hpp>
#include <RadonFramework/Collections/Array.hpp>
#include <RadonFramework/Collections/Pair.hpp>

namespace RadonFramework::Diagnostics {
        
struct LogConfigData
{
    RF_Type::Bool IsInfoEnabled;
    RF_Type::Bool IsErrorEnabled;
    RF_Type::Bool IsFatalErrorEnabled;
    RF_Type::Bool IsDebugEnabled;
    RF_Type::UInt32 AppenderCount;
    RF_Type::UInt64 AppenderPointerOffset;
};

class LogConfig
{
public:
    LogConfig();
    LogConfig(const LogConfig& Copy);
    ~LogConfig();
    LogConfig& operator=(const LogConfig& Other);
    void Configure();
    // Reader functionality
    RF_Type::Bool ReadFromBinaryData(Memory::AutoPointerArray<RF_Type::UInt8> Data);
    RF_Type::Bool IsInfoEnabled()const;
    RF_Type::Bool IsErrorEnabled()const;
    RF_Type::Bool IsFatalErrorEnabled()const;
    RF_Type::Bool IsDebugEnabled()const;
    RF_Type::UInt32 AppenderCount()const;
    RF_Type::UInt32 GetAppenderID(RF_Type::UInt32 Index)const;
    Memory::AutoPointer<Appender> GenerateAppender(RF_Type::UInt32 AppenderID);
    Memory::AutoPointer<Collections::Array<Memory::AutoPointer<Appender> > > GenerateAppenders();
    // Writer functionality
    void SetInfoEnabled(RF_Type::Bool NewValue);
    void SetErrorEnabled(RF_Type::Bool NewValue);
    void SetFatalErrorEnabled(RF_Type::Bool NewValue);
    void SetDebugEnabled(RF_Type::Bool NewValue);
    void SetAppenders(const Collections::Array<RF_Type::UInt32>& AppenderIDs);
    Memory::AutoPointerArray<RF_Type::UInt8> GenerateBinaryData();
    static Collections::Array<Collections::Pair<RF_Type::UInt32,Appender* (*)()> > AppenderLookupTable;
protected:
    Memory::AutoPointer<LogConfigData> m_Data;
    RF_Type::UInt32* m_AppenderIDs;
};

}

#endif // RF_DIAGNOSTICS_LOGCONFIG_HPP
