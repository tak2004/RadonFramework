namespace RaspberryPi2b {

RF_Type::Bool GetCacheInfo(CacheInfo& Info, RF_Type::UInt32 Index)
{
    if(Index == 0)
    {
        Info.LineSize = 32;
        Info.LineCount = 128;
        Info.Size = 16384;
        Info.Level = 1;
        Info.Associativity = CacheAssociativity::_4WaySetAssociative;
        Info.UsedAs = CacheUseCase::Data;
    }
    if(Index == 1)
    {
        Info.LineSize = 32;
        Info.LineCount = 128;
        Info.Size = 16384;
        Info.Level = 1;
        Info.Associativity = CacheAssociativity::_4WaySetAssociative;
        Info.UsedAs = CacheUseCase::Code;
    }
}

RF_Type::Int32 GetCacheCount()
{
    return 2;
}

}

void Dispatch_HardwareRaspberryPi2b()
{
    GetCacheCount = RaspberryPi2b::GetCacheCount;
    GetCacheInfo = RaspberryPi2b::GetCacheInfo;
}

#define Dispatch_HardwareSpecificHost Dispatch_HardwareRaspberryPi2b