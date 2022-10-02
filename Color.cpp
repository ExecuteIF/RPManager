#include "RPManager.h"

extern int spawnRandom(int min, int max)
{
    random_device seed;
    ranlux48 engine(seed());
    uniform_int_distribution<> distrib(min, max);

    int _bds = distrib(engine);
    return _bds;
}

    /// <summary>
    /// Validate the random value for changing the console color
    /// </summary>
    /// <param name="input">not valid char</param>
    /// <returns>valid char</returns>
extern char RandomProc4Console(char input)
{
    if (input == 'R')
    {
        input = spawnRandom(0, 15);
        switch (input)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            input += '0';
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            input -= 10;
            input += 'A';
            break;
        }
    }
    return input;
}

extern void setConsoleColor(char foreground, char background)
{
    if (foreground == 'R')
    {
        foreground = RandomProc4Console(foreground);
    }
    if (background == 'R')
    {
        background = RandomProc4Console(background);
    }
    cmd("color " + background + foreground);
}

extern bool setTextColor(int color)
{
    bool flag = true;
    switch (color)
    {
    case 0:
        fx_private_setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    case 1:
        fx_private_setColor(FOREGROUND_RED);
        break;
    case 2:
        fx_private_setColor(FOREGROUND_GREEN);
        break;
    case 3:
        fx_private_setColor(FOREGROUND_BLUE);
        break;
    case 4:
        fx_private_setColor(FOREGROUND_RED | FOREGROUND_GREEN);
        break;
    case 5:
        fx_private_setColor(FOREGROUND_RED | FOREGROUND_BLUE);
        break;
    case 6:
        fx_private_setColor(FOREGROUND_GREEN | FOREGROUND_BLUE);
        break;
    case 7:
        return(setTextColor(spawnRandom(0, 6)));
    case 255:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
        break;
    default:
        flag = false;
        break;
    }
    return !flag;
}
