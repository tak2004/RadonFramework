/*
#include <stdio.h>
#include <windows.h>

extern "C"
{

//_flag values (not the ones used by the normal CRT
#define _FILE_TEXT		0x0001
#define _FILE_EOF		0x0002
#define _FILE_ERROR		0x0004

size_t fwrite(const void* buffer, size_t size, size_t count, FILE* fileStream)
{
    DWORD bw = 0, bw2 = 0;

    if (size*count == 0)
        return 0;

    HANDLE hFile = fileStream->_base;
    int textMode = fileStream->_flag & _FILE_TEXT;

    // Text-mode translation is always ANSI!
    if (textMode)			// text mode -> translate LF -> CRLF
    {
        const char *src = (const char*)buffer;
        size_t startpos = 0, i = 0;
        for (i = 0; i < size*count; i++)
        {
            if (src[i] != '\n')
                continue;
            if (i > 0 && src[i-1] == '\r')		// don't translate CRLF
                continue;

            if (i > startpos)
            {
                WriteFile(hFile, &src[startpos], i-startpos, &bw2, 0);
                bw += bw2;
            }

            const char *crlf = "\r\n";
            WriteFile(hFile, crlf, 2, &bw2, 0);
            bw++;		// one '\n' written

            startpos = i+1;
        }

        if (i > startpos)
        {
            WriteFile(hFile, &src[startpos], i-startpos, &bw2, 0);
            bw += bw2;
        }
    }
    else
        WriteFile(hFile, buffer, (DWORD)(size*count), &bw, 0);
    return bw/size;
}

}*/