#ifndef RF_CONVERTERPLUGIN_PLUGIN_H
#define RF_CONVERTERPLUGIN_PLUGIN_H

struct PluginVersion
{
    unsigned int Minor;
    unsigned int Major;
};
    
typedef unsigned int (*PluginCallback)(void* vm, const unsigned int parameterCount, const struct PluginInfo& info);

struct BasicInfo
{
    char Name[32];
    PluginCallback Callback;
};

typedef void (*FreePlugin)(struct PluginInfo& Info);

struct PluginInfo
{   
    // parameter managment
    typedef bool (*IsNumberFunction)(void* vm, int stackIndex);
    typedef bool (*IsStringFunction)(void* vm, int stackIndex);
    typedef bool (*IsIntegerFunction)(void* vm, int stackIndex);
    typedef double (*GetNumberFunction)(void* vm, int stackIndex);
    typedef const char* (*GetStringFunction)(void* vm, int stackIndex);
    typedef int (*GetIntegerFunction)(void* vm, int stackIndex);
    typedef void (*PushNumberFunction)(void* vm, double value);
    typedef void (*PushStringFunction)(void* vm, const char* value);
    typedef void (*PushIntegerFunction)(void* vm, int value);

    PluginVersion Version;
    char Name[32];
    unsigned int ProcessorFunctionCount;
    const BasicInfo* ProcessingFunctions;
    FreePlugin FreeCallback;
    void* UserData;

    IsNumberFunction IsNumber;
    IsStringFunction IsString;
    IsIntegerFunction IsInteger;
    GetNumberFunction GetNumber;
    GetStringFunction GetString;
    GetIntegerFunction GetInteger;
    PushNumberFunction PushNumber;
    PushStringFunction PushString;
    PushIntegerFunction PushInteger;
};

typedef void (*InitPlugin)(PluginInfo& Info);

#endif // RF_CONVERTERPLUGIN_PLUGIN_H