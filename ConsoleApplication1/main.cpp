#include <iostream>
#include <Windows.h>
#include <regex>
#include <string>

void BailOut(const char* msg)
{
    fprintf(stderr, "Exiting: %s\n", msg);
    exit(1);
}


BOOL IsTwitter(std::string clipboard_data)
{
    if (std::regex_match(clipboard_data, std::regex(("https://twitter.com/.*"))))
    {
        std::cout << "Twitter link detected. Changing..." << std::endl;
        return true;
    }
    else if(std::regex_match(clipboard_data, std::regex(("https://vxtwitter.com/.*"))))
    {
        std::cout << "Modified Twitter link detected. No changes needed." << std::endl;
        return false;
    }
    else
    {
        std::cout << "Not a twitter link." << std::endl;
        return false;
    }
}

std::string FixTwitterLink(std::string clipboard_string)
{
    std::string fix = "vx";
    std::string fixed_link = clipboard_string.insert(8, fix);
    
    return fixed_link;
}

// Figure out how to check if foreground window is discord -> check clipboard
//void CheckWindowName()
//{
//    HWND foreground = GetForegroundWindow();
//    if (foreground)
//    {
//        WCHAR window_title[256];
//        GetWindowText(foreground, window_title, 256);
//        std::cout << "Window title " << window_title << std::endl;
//    }
//
//}

int main()
{
    //CheckWindowName();

    HANDLE clipboard_data;

    if (!OpenClipboard(NULL))
        BailOut("Can't open clipboard");

    clipboard_data = GetClipboardData(CF_TEXT);

    printf("Clipboard data: %s\n", (char*)clipboard_data);

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

    return 0;
}
