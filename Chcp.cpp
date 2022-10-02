#include "RPManager.h"

/// <summary>
/// change the encoding of the page
/// e.g. chcp(ESC_CHCP_UNICODE)...
/// enter location for specified encoding(without this step the console may not
/// display the correct text in others' computers).
/// </summary>
/// <param name="type">chcp type</param>
extern void chcp(string type)
{
    cmd("chcp " + type + ">nul");
    return;
}
