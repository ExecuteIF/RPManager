#include "RPManager.h"

extern void setConsoleSize(int x, int y)
{
    cmd("mode con cols=" + to_string(x) + " lines=" + to_string(y));
}

/// <summary>
/// show cursor on the console?
/// </summary>
/// <param name="state">true: show; false: dont show</param>
/// <returns>N/A</returns>
extern void showCursor(bool state)
{
    // get buffer handle
    HANDLE hOutput;
    COORD coord = { 0, 0 };
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    // set visibility of the cursor
    CONSOLE_CURSOR_INFO cci = { 1,state };
    SetConsoleCursorInfo(hOutput, &cci);
}
