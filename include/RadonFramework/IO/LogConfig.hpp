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

namespace RadonFramework
{
	namespace Diagnostics
	{
        struct LogConfigData
        {
            RFTYPE::Bool IsInfoEnabled;
            RFTYPE::Bool IsErrorEnabled;
            RFTYPE::Bool IsFatalErrorEnabled;
            RFTYPE::Bool IsDebugEnabled;
            RFTYPE::UInt32 AppenderCount;
            RFTYPE::UInt64 AppenderPointerOffset;
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
                RFTYPE::Bool ReadFromBinaryData(Memory::AutoPointerArray<RFTYPE::UInt8> Data);
                RFTYPE::Bool IsInfoEnabled()const;
                RFTYPE::Bool IsErrorEnabled()const;
                RFTYPE::Bool IsFatalErrorEnabled()const;
                RFTYPE::Bool IsDebugEnabled()const;
                RFTYPE::UInt32 AppenderCount()const;
                RFTYPE::UInt32 GetAppenderID(RFTYPE::UInt32 Index)const;
                Memory::AutoPointer<Appender> GenerateAppender(RFTYPE::UInt32 AppenderID);
                Memory::AutoPointer<Collections::Array<Memory::AutoPointer<Appender> > > GenerateAppenders();
                // Writer functionality
                void SetInfoEnabled(RFTYPE::Bool NewValue);
                void SetErrorEnabled(RFTYPE::Bool NewValue);
                void SetFatalErrorEnabled(RFTYPE::Bool NewValue);
                void SetDebugEnabled(RFTYPE::Bool NewValue);
                void SetAppenders(const Collections::Array<RFTYPE::UInt32>& AppenderIDs);
                Memory::AutoPointerArray<RFTYPE::UInt8> GenerateBinaryData();
                static Collections::Array<Collections::Pair<RFTYPE::UInt32,Appender* (*)()> > AppenderLookupTable;
            protected:
                Memory::AutoPointer<LogConfigData> m_Data;
                RFTYPE::UInt32* m_AppenderIDs;
		};
	}
}

#endif // RF_DIAGNOSTICS_LOGCONFIG_HPP
