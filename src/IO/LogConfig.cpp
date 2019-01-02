#include "RadonFramework/precompiled.hpp"
#include "RadonFramework/IO/LogConfig.hpp"
#include "RadonFramework/IO/Log.hpp"
#include "RadonFramework/Diagnostics/Debugging/Assert.hpp"

using namespace RadonFramework::Diagnostics;
using namespace RadonFramework::Collections;
using namespace RadonFramework::Core::Types;
using namespace RadonFramework::Memory;
using namespace RadonFramework::IO;

Array<Pair<UInt32,Appender* (*)()> > LogConfig::AppenderLookupTable;

LogConfig::LogConfig()
:m_Data(new LogConfigData)
,m_AppenderIDs(0)
{    
    RF_SysMem::Set(m_Data.Get(),0,sizeof(LogConfigData));
}

LogConfig::LogConfig(const LogConfig& Copy)
{
    *this=Copy;
}

LogConfig::~LogConfig()
{    
}

LogConfig& LogConfig::operator=(const LogConfig& Other)
{
    UInt32 size=Other.AppenderCount()*sizeof(UInt32)+sizeof(LogConfigData);
    AutoPointerArray<UInt8> binary(size);
    RF_SysMem::Copy(binary.Get(),Other.m_Data.Get(),size);

    m_Data.Reset(reinterpret_cast<LogConfigData*>(binary.Release().Ptr));
    if (m_Data->AppenderCount)
        m_AppenderIDs=reinterpret_cast<UInt32*>(reinterpret_cast<UInt8*>(m_Data.Get())+m_Data->AppenderPointerOffset);
    else
        m_AppenderIDs=0;
    return *this;
}

void LogConfig::Configure()
{
    Log::IsDebugEnabled=m_Data->IsDebugEnabled;
    Log::IsInfoEnabled=m_Data->IsInfoEnabled;
    Log::IsErrorEnabled=m_Data->IsErrorEnabled;
    Log::IsFatalErrorEnabled=m_Data->IsFatalErrorEnabled;
    AutoPointer<Array<AutoPointer<Appender> > > appenders = GenerateAppenders();
    Log::ReplaceAppenders(appenders);
}

Bool LogConfig::ReadFromBinaryData(AutoPointerArray<UInt8> Data)
{
    if (sizeof(LogConfigData)<=Data.Size())
    {
        m_Data.Reset(reinterpret_cast<LogConfigData*>(Data.Release().Ptr));
        if (m_Data->AppenderCount)
            m_AppenderIDs=reinterpret_cast<UInt32*>(reinterpret_cast<UInt8*>(m_Data.Get())+m_Data->AppenderPointerOffset);
        else
            m_AppenderIDs=0;
        return true;
    }
    return false;
}

Bool LogConfig::IsInfoEnabled()const
{
    return m_Data->IsInfoEnabled;
}

Bool LogConfig::IsErrorEnabled()const
{
    return m_Data->IsErrorEnabled;
}

Bool LogConfig::IsFatalErrorEnabled()const
{
    return m_Data->IsFatalErrorEnabled;
}

Bool LogConfig::IsDebugEnabled()const
{
    return m_Data->IsDebugEnabled;
}

UInt32 LogConfig::AppenderCount()const
{
    return m_Data->AppenderCount;
}

UInt32 LogConfig::GetAppenderID(UInt32 Index)const
{
    RF_ASSERT(Index<m_Data->AppenderCount,);
    return m_AppenderIDs[Index];
}

AutoPointer<Appender> LogConfig::GenerateAppender(UInt32 AppenderID)
{
    for(UInt32 i=0;i<AppenderLookupTable.Count();++i)
        if (AppenderLookupTable(i).First==AppenderID)
            return AutoPointer<Appender>(AppenderLookupTable(i).Second());
    return AutoPointer<Appender>();
}

AutoPointer<Array<AutoPointer<Appender> > > LogConfig::GenerateAppenders()
{
    AutoPointer<Array<AutoPointer<Appender> > > result(new Array<AutoPointer<Appender> >(m_Data->AppenderCount));
    UInt32 misses=0,len=m_Data->AppenderCount;
    for (UInt32 i=0;i<len;++i)
    {
        (*result)(i-misses)=GenerateAppender(m_AppenderIDs[i]);
        if (0==(*result)(i-misses))//check if the appender wasn't found
        {
            LogError("Can't find the specified Appender(ID=%d).",m_AppenderIDs[i]);            
            ++misses;
        }
    }

    if (misses>0)
        (*result).Resize(len-misses);

    return result;
}

void LogConfig::SetInfoEnabled(Bool NewValue)
{
    m_Data->IsInfoEnabled=NewValue;
}

void LogConfig::SetErrorEnabled(Bool NewValue)
{
    m_Data->IsErrorEnabled=NewValue;
}

void LogConfig::SetFatalErrorEnabled(Bool NewValue)
{
    m_Data->IsFatalErrorEnabled=NewValue;
}

void LogConfig::SetDebugEnabled(Bool NewValue)
{
    m_Data->IsDebugEnabled=NewValue;
}

void LogConfig::SetAppenders(const Array<UInt32>& AppenderIDs)
{
    Size size=AppenderIDs.Count()*sizeof(UInt32)+sizeof(LogConfigData);
    AutoPointerArray<UInt8> data(size);

    RF_SysMem::Copy(data.Get(),m_Data.Get(),sizeof(LogConfigData));
    m_Data.Reset(reinterpret_cast<LogConfigData*>(data.Release().Ptr));
    m_Data->AppenderCount=static_cast<UInt32>(AppenderIDs.Count());
    m_Data->AppenderPointerOffset=sizeof(LogConfigData);
    if (m_Data->AppenderCount)
    {
        m_AppenderIDs=reinterpret_cast<UInt32*>(reinterpret_cast<UInt8*>(m_Data.Get())+m_Data->AppenderPointerOffset);
        RF_SysMem::Copy(m_AppenderIDs,&AppenderIDs(0),sizeof(UInt32)*m_Data->AppenderCount);
    }
    else
        m_AppenderIDs=0;
}

AutoPointerArray<UInt8> LogConfig::GenerateBinaryData()
{
    Size size=m_Data->AppenderCount*sizeof(UInt32)+sizeof(LogConfigData);
    AutoPointerArray<UInt8> result(size);
    RF_SysMem::Copy(result.Get(),m_Data.Get(),size);
    return result;
}
