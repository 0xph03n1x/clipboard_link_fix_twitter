#include <iostream>
#include <Windows.h>
#include <regex>
#include <string>
#include <fstream>

void BailOut(const char* msg)
{
    fprintf(stderr, "Exiting: %s\n", msg);
    exit(1);
}

bool IsTwitter(std::string clipboard_data)
{
    if (std::regex_match(clipboard_data, std::regex(("https://twitter.com/.*"))))
    {
        std::cout << "Twitter link detected. Changing..." << std::endl;
        return true;
    }
    else if (std::regex_match(clipboard_data, std::regex(("https://vxtwitter.com/.*"))))
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

void write_text_to_log_file(const std::string& text)
{
    std::ofstream log_file(".\\output.txt", std::ios_base::out | std::ios_base::app);
    log_file << text << "\n";
}

// Figure out how to check if foreground window is discord -> check clipboard
std::string CheckWindowName()
{
    HWND foreground = GetForegroundWindow();
    if (foreground)
    {
        char window_title[256];
        GetWindowText(foreground, window_title, 256);
        std::cout << "Window title: " << window_title << std::endl;

        std::string title_log = "Window title: " + (std::string)window_title;
        write_text_to_log_file(title_log);

        return window_title;

    }

}

bool DiscordWindow(std::string cWindow)
{

    if (std::regex_match(cWindow, std::regex(".*Discord")))
    {
        std::cout << "Got a match\n" << std::endl;
        return true;
    }
    else
    {
        std::cout << "No match\n" << std::endl;
        return false;
    }
}

int main()
{
    Sleep(5000);
    std::string window_title = CheckWindowName();
    bool res = DiscordWindow(window_title);

    while (res = false)
    {
        CheckWindowName();
        std::cout << window_title << std::endl;
        if (window_title != window_title)
            window_title = window_title;
        res = DiscordWindow(window_title);
        Sleep(3000);
    }

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
