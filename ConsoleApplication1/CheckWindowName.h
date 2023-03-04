#pragma once

bool DiscordWindow(std::string cWindow)
{
    bool window_checker = std::regex_match(cWindow, std::regex(".* - Discord"));
    return window_checker;
}

bool CheckWindowName()
{
    HWND foreground = GetForegroundWindow();
    if (foreground)
    {
        char window_title[256];
        GetWindowTextA(foreground, window_title, 256);
        bool IsDiscord = DiscordWindow(window_title);
        std::string scWindow = std::string(window_title);

        return IsDiscord;
    }

}
