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
            Core::Types::Bool IsInfoEnabled;
            Core::Types::Bool IsErrorEnabled;
            Core::Types::Bool IsFatalErrorEnabled;
            Core::Types::Bool IsDebugEnabled;
            Core::Types::UInt32 AppenderCount;
            Core::Types::UInt64 AppenderPointerOffset;
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
                Core::Types::Bool ReadFromBinaryData(Memory::AutoPointerArray<Core::Types::UInt8> Data);
                Core::Types::Bool IsInfoEnabled()const;
                Core::Types::Bool IsErrorEnabled()const;
                Core::Types::Bool IsFatalErrorEnabled()const;
                Core::Types::Bool IsDebugEnabled()const;
                Core::Types::UInt32 AppenderCount()const;
                Core::Types::UInt32 GetAppenderID(Core::Types::UInt32 Index)const;
                Memory::AutoPointer<Appender> GenerateAppender(Core::Types::UInt32 AppenderID);
                Memory::AutoPointer<Collections::Array<Memory::AutoPointer<Appender> > > GenerateAppenders();
                // Writer functionality
                void SetInfoEnabled(Core::Types::Bool NewValue);
                void SetErrorEnabled(Core::Types::Bool NewValue);
                void SetFatalErrorEnabled(Core::Types::Bool NewValue);
                void SetDebugEnabled(Core::Types::Bool NewValue);
                void SetAppenders(const Collections::Array<Core::Types::UInt32>& AppenderIDs);
                Memory::AutoPointerArray<Core::Types::UInt8> GenerateBinaryData();
                static Collections::Array<Collections::Pair<Core::Types::UInt32,Appender* (*)()> > AppenderLookupTable;
            protected:
                Memory::AutoPointer<LogConfigData> m_Data;
                Core::Types::UInt32* m_AppenderIDs;
		};
	}
}

#endif // RF_DIAGNOSTICS_LOGCONFIG_HPP
