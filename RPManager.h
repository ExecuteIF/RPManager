#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <thread>

#include <exception>

#include <windows.h>
#include <io.h>

#include "mikuFile.h"

using namespace std;

#define _Esc_maxn 1024

#define cmd(str) system(((string)str).c_str())
#define cls() system("cls")
#define pause() system("pause")
#define fx_private_setColor(dat) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | dat);
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)

class filePath
{
public:
    string fullPath;					// C:\users\admin\desktop\target.txt
    string fullPathWithQuotes;			// "C:\users\admin\desktop\target.txt"

    string onlyPath;					// C:\users\admin\desktop
    string onlyPathHoweverWithQuotes;	// "C:\users\admin\desltop"

    string onlyFileName;				// target.txt
    string onlyfileSuffix;				// txt
    string fileNameWithSuffix;			// target

    bool relativePath = false;			// TRUE: ./target.txt      FALSE: C:\users\admin\desktop\target.txt
    string driver;						// C(if is relativePath is false)
};
/// <summary>
/// the recommend struct for containing the path of a folder
/// </summary>
class folderPath
{
public:
    string fullPath;					// C:\users\admin\desktop
    string fullPathHoweverWithQuotes;	// "C:\users\admin\desktop"
    string pathWithoutSelf;				// C:\users\admin
    string self;						// desktop

    bool relativePath = false;			// TRUE: ./desktop      FALSE: C:\users\admin\desktop\desktop
    string driver;						// C(if is relativePath is false)
};

struct __ICFG {
    bool firstrun;
    string allowedFolders;
    string lang;
    string RPNow;
};
struct __IDATA {
    vector<string> resourcepacks;         // resourcepack list
    struct __ICFG config;
};
typedef struct __IDATA initData;

// perm colors
#define ESC_CONSOLE_COLOR_BLACK			'0'
#define ESC_CONSOLE_COLOR_BLUE			'1'
#define ESC_CONSOLE_COLOR_GREEN			'2'
#define ESC_CONSOLE_COLOR_LIME			'3'
#define ESC_CONSOLE_COLOR_RED			'4'
#define ESC_CONSOLE_COLOR_PURPLE	    '5'
#define ESC_CONSOLE_COLOR_YELLOW	    '6'
#define ESC_CONSOLE_COLOR_WHITE			'7'
#define ESC_CONSOLE_COLOR_GRAY			'8'
#define ESC_CONSOLE_COLOR_AZURE			'9'
#define ESC_CONSOLE_COLOR_LITE_GREEN	'A'
#define ESC_CONSOLE_COLOR_CYAN			'B'
#define ESC_CONSOLE_COLOR_LITE_RED		'C'
#define ESC_CONSOLE_COLOR_LITE_PURPLE	'D'
#define ESC_CONSOLE_COLOR_LITE_YELLOW	'E'
#define ESC_CONSOLE_COLOR_PURE_WHITE	'F'
#define ESC_CONSOLE_COLOR_RANDOM        'R'

// text colors
#define ESC_COLOR_PUREWHITE				0
#define	ESC_COLOR_RED					1
#define ESC_COLOR_GREEN					2
#define ESC_COLOR_BLUE					3
#define ESC_COLOR_YELLOW		    	4
#define ESC_COLOR_PURPLE			    5
#define ESC_COLOR_CYAN					6
#define ESC_COLOR_RANDOM                7

// chcp
#define ESC_CHCP_US                     "437"
#define ESC_CHCP_MULT                   "850"
#define ESC_CHCP_SLAVIC                 "852"
#define ESC_CHCP_CYRILLIC               "855"
#define ESC_CHCP_TURKISH                "857"
#define ESC_CHCP_PORTUGUESE             "860"
#define ESC_CHCP_ICELANDIC              "861"
#define ESC_CHCP_CANADIAN               "863"
#define ESC_CHCP_NORDIC                 "865"
#define ESC_CHCP_RUSSIAN                "866"
#define ESC_CHCP_MGREEK                 "869"
#define ESC_CHCP_CHINESE                "936"
#define ESC_CHCP_ANSI                   "65000"
#define ESC_CHCP_UNICODE                "65001"
#define ___EscDef___ true

#define MSG_BEEP                0xFFFFFFFF
#define MSG_OK                  0x00000000L
#define MSG_ICONERROR           0x00000010L
#define MSG_ICONSTOP            0x00000010L
#define MSG_ICONHAND            0x00000010L
#define MSG_ICONQUESTION        0x00000020L
#define MSG_ICONEXCLAMATION     0x00000030L
#define MSG_ICONWARNING         0x00000030L
#define MSG_ICONASTERISK        0x00000040L
#define MSG_ICONINFORMATION     0x00000040L

#define MSGBeeps true
