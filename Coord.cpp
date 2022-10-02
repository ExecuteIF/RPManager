#include "RPManager.h"

extern HANDLE getHandle()
{
    return GetStdHandle(STD_OUTPUT_HANDLE);
}

extern COORD getCursorPos()
{
    COORD ans = { 0,0 };
    HANDLE hConsole = getHandle();
    CONSOLE_SCREEN_BUFFER_INFO inf;
    if (GetConsoleScreenBufferInfo(hConsole, &inf))
    {
        ans.X = inf.dwCursorPosition.X;
        ans.Y = inf.dwCursorPosition.Y;

    }
    return ans;
}

/// <summary>
/// goto a coord of the console
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
extern void gotoxy(int x, int y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)x, (short)y });
}
