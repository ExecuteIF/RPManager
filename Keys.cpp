#include "RPManager.h"

/// <summary>
    /// check if key <KEYCODE> is down
    /// use KEY_??? instead keycode will be more
    /// convient
    /// </summary>
    /// <param name="KeyCode"></param>
    /// <returns>if the key is down then return true</returns>
extern bool keyDown(int KeyCode)
{
    return KEY_DOWN(KeyCode);
}
