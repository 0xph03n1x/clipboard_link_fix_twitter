#pragma once

std::string FixTwitterLink(std::string clipboard_string)
{
    std::string fix = "vx";
    std::string fixed_link = clipboard_string.insert(8, fix);

    return fixed_link;
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
