#include <iostream>
#include <Windows.h>
#include <regex>
#include <string>
#include <fstream>
#include "FixLink.h"
#include "CheckWindowName.h"
#include "ModClipboard.h"

int main()
{

    while (!(CheckWindowName()))
    {
        Sleep(1000);
    }

    getClipboard();

    Sleep(10000);

    return main();
}
