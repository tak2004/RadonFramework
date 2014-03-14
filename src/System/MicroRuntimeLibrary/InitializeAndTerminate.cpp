#include "RadonFramework/precompiled.hpp"

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#include <windows.h>

typedef void (__cdecl *_PVFV)();
extern _PVFV __xc_a[], __xc_z[]; // Constructors and initialize functions

// more information at http://msdn.microsoft.com/en-us/library/bb918180.aspx
#pragma data_seg(".CRT$XCA") // start of ctor section
_PVFV __xc_a[] = {0};
#pragma data_seg(".CRT$XCZ") // end of ctor section
_PVFV __xc_z[] = {0};

extern "C" 
{
    static _PVFV *atExitList = 0;
    static unsigned int maxAtExitEntries = 0;
    static unsigned int curAtExitEntries = 0;

    // C function to ensure the cleanup of global initialized data.
    int atexit(_PVFV func)
    {
        if (curAtExitEntries < maxAtExitEntries)
        {
            atExitList[curAtExitEntries++] = func; 
            return 0;
        }

        return -1;
    }

    // Will be assigned to every virtual function.
    int _purecall()
    {
        ExitProcess((UINT)-1);
    }

    // Will be called by mainCRTStartup().
    void _init_atexit()
    {
        maxAtExitEntries = 128;
        atExitList = (_PVFV*)HeapAlloc(GetProcessHeap(), 0, sizeof(_PVFV*)*(maxAtExitEntries));
    }

    // Call all global/static/const initialization functions(often constructors).
    void _initterm(_PVFV *pfbegin, _PVFV *pfend)
    {
        while (pfbegin < pfend)
        {
            if (*pfbegin != 0)
                (**pfbegin)();
            ++pfbegin;
        }
    }

    // Clean up: Call all destructor and cleanup routines specified at atexit call.
    void _doexit()
    {
        if (curAtExitEntries)
        {
            _initterm(atExitList, atExitList + curAtExitEntries);
        }
    }
}

extern void main();

extern "C" void __chkstk(void)
{
}

extern "C" void mainCRTStartup()
{
    _init_atexit();
    _initterm(__xc_a, __xc_z);
    main();
    _doexit();
    ExitProcess(0);
}