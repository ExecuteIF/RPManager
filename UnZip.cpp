#include "RPManager.h"

extern void unZip(string file, string to) {
	cmd(".\\RPManager\\7z.exe x " + file + " -o" + to + " -aoa");
}
