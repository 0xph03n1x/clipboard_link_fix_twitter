#include <iostream>
#include <Windows.h>
#include <regex>
#include <string>

void BailOut(const char* msg)
{
    fprintf(stderr, "Exiting: %s\n", msg);
    exit(1);
}

void NullPointerErr(const char* msg)
{
    fprintf(stderr, "Exiting: %s\n", msg);
    exit(1);
}

BOOL IsTwitter(std::string clipboard_data)
{
    if (std::regex_match(clipboard_data, std::regex(("https://twitter.com/.*"))))
    {
        std::cout << "Twitter link" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Not twitter link" << std::endl;
        return false;
    }
}

std::string FixTwitterLink(std::string clipboard_string)
{
    std::string fix = "vx";
    std::string fixed_link = clipboard_string.insert(8, fix);
    
    return fixed_link;
}

int main()
{
    HANDLE clipboard_data;

    if (!OpenClipboard(NULL))
        BailOut("Can't open clipboard");

    clipboard_data = GetClipboardData(CF_TEXT);

    printf("Clipboard data: %s\n", (char*)clipboard_data);

    char* clipboard_string = static_cast<char*>(GlobalLock(clipboard_data));

    if (clipboard_string == nullptr)
        NullPointerErr("nullptr error");
    
    std::cout << "Clipboard string: " << clipboard_string << std::endl;

    if (clipboard_string != NULL) {
        bool twLink_check = IsTwitter(clipboard_string);
        if (twLink_check) {
            std::string FixedLink = FixTwitterLink(clipboard_string);
            std::cout << "Fixed: " << FixTwitterLink(clipboard_string) << std::endl;
            /* OpenClipboard() -> Change with SetClipboardData()
            Figure out how to work with the memory - https://stackoverflow.com/questions/1264137/how-to-copy-string-to-clipboard-in-c
            
            SetClipboardData(CF_TEXT, FixedLink);
            std::cout << "Modified: " << GetClipboardData(CF_TEXT) << std::endl;
            
            */
        }
    }


    CloseClipboard();

    return 0;
}
