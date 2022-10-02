#include "RPManager.h"

void setConsoleSize(int, int);
void chcp(string);
void showCursor(bool);
void loading(int, int, int, char);
bool setTextColor(int);
vector<string> getFileInFolder(string);
filePath filePathSegmentingHelper(string);
void setConsoleColor(char, char);
bool outputNF(string, int, int);

inline void done(int tabs) {
	for (int i = 0; i < tabs; ++i) {
		printf("\t");
	}

	cout << "[  ";
	setTextColor(ESC_COLOR_GREEN);
	cout << "OK";
	setTextColor(ESC_COLOR_PUREWHITE);
	cout << "  ]\n";
}

inline void fail(int tabs) {
	for (int i = 0; i < tabs; ++i) {
		printf("\t");
	}

	cout << "[ ";
	setTextColor(ESC_COLOR_RED);
	cout << "FAIL";
	setTextColor(ESC_COLOR_PUREWHITE);
	cout << " ]\n";
}

extern initData init()
{
	// init console window
	cmd("title LOADING");
	cout << "PLZ WAIT...";
	setConsoleSize(100, 30);
	setConsoleColor(ESC_CONSOLE_COLOR_WHITE, ESC_CONSOLE_COLOR_BLACK);
	showCursor(false);
	chcp(ESC_CHCP_UNICODE);
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode &= ~ENABLE_INSERT_MODE;
	mode &= ~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin, mode);
	static bool firstload = true;

	cout << "\t\tCopyrights 2022(c) ExL Studios\n";
	cout << "\t\tProgrammer(s): Executif; Harasune_Rinnku\n";
	cout << "\t\tFollow GNU GPL v3\n";
	cout << "\t\tFor source code and official updates, Go https://github.com/ExecuteIF/RPManager\n";
	cout << "\t\tThis program has NO relation to the NW studio and Unity.\n\n";

	if (firstload) {
		loading(50, 8, 6, '.');
		firstload = false;
	}
	cout << "\n";

	cout << "Initializing...";
	//loading(100, 4, 3, '.');
	done(4);
	cmd("title RPManager");
	if (firstload) {
		Sleep(100);
	}

	// scan for resourcepacks
	cout << "Scanning for resourcepacks...";
	//loading(150, 4, 3, '.');
	done(2);
	cout << "\n";
	vector<string> file_list = getFileInFolder("RPManager\\resourcepacks");
	initData rps;
	for (int i = 0; i < file_list.size(); ++i) {
		clog << "\t" << file_list[i] << "\n";

		// check whether it is a zip file
		if (file_list[i].length() < 4) {
			continue;
		}
		if (file_list[i][file_list[i].length() - 4] != '.') {
			continue;
		}
		if ((file_list[i][file_list[i].length() - 3] != 'z') && (file_list[i][file_list[i].length() - 3] != 'Z')) {
			continue;
		}
		if ((file_list[i][file_list[i].length() - 2] != 'i') && (file_list[i][file_list[i].length() - 2] != 'I')) {
			continue;
		}
		if ((file_list[i][file_list[i].length() - 1] != 'p') && (file_list[i][file_list[i].length() - 1] != 'P')) {
			continue;
		}
		rps.resourcepacks.push_back(file_list[i]);
	}
	if (firstload) {
		Sleep(100);
	}

	cout << "Verifying...";
	//loading(150, 4, 3, '.');
	done(4);
	for (int i = 0; i < rps.resourcepacks.size(); ++i) {
		clog << "\t" << rps.resourcepacks[i] << "\n";
	}
	if (firstload) {
		Sleep(100);
	}

	cout << "Reading config...";
	done(3);
	mk::config cfg;
	cout << "\tOpen config file...";
	bool firstrun = false;
	cfg.open("RPManager.cfg");
	if (!cfg.is_open()) {
		fail(2);
		pause();
		exit(-4);
	}
	rps.config.allowedFolders = cfg.readStr("AllowedFolders");
	firstrun = cfg.readBool("FirstRun");
	if (firstrun) {
		cfg.writeBool("FirstRun", false);
	}
	rps.config.RPNow = cfg.readStr("RPNow");
	done(2);
	outputNF("RPManager.cfg", 10, -1);
	cfg.close();

	if (firstrun == true) {
		cout << "Preparing for first run...\n";
		cmd("xcopy /Y /S /F .\\SCPSL_Data\\*.assets .\\RPManager\\vanilla");
	}
	if (firstload) {
		Sleep(100);
	}

	// end init
	cls();
	return rps;
}
