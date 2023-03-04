#include <Windows.h>
#include <iostream>
#include "FixLink.h"
#include "CheckWindowName.h"
#pragma once

void BailOut(const char* msg)
{
    fprintf(stderr, "Exiting: %s\n", msg);
    exit(1);
}

void getClipboard()
{
    HANDLE clipboard_data;

    if (!OpenClipboard(NULL))
        BailOut("Can't open clipboard");

    clipboard_data = GetClipboardData(CF_TEXT);

    char* clipboard_string = static_cast<char*>(GlobalLock(clipboard_data));
    GlobalUnlock(clipboard_data);

    if (clipboard_string == nullptr)
        BailOut("nullptr error");

    std::cout << "Clipboard string: " << clipboard_string << std::endl;

    if (clipboard_string != NULL)
    {
        bool twLink_check = IsTwitter(clipboard_string);

        if (twLink_check)
        {
            std::string FixedLink = FixTwitterLink(clipboard_string);
            std::cout << "Fixed: " << FixTwitterLink(clipboard_string) << std::endl;

            const char* output = FixedLink.c_str();
            const size_t link_len = strlen(output) + 1;

            std::cout << "Output value: " << output << std::endl;


            HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, link_len);

            if (hMem != NULL)
            {
                LPVOID dst = GlobalLock(hMem);

                if (dst != NULL)
                {
                    memcpy(dst, output, link_len);
                    GlobalUnlock(hMem);
                    OpenClipboard(0);
                    EmptyClipboard();
                    SetClipboardData(CF_TEXT, hMem);
                }
            }
        }
    }


    CloseClipboard();

}