#include "RPManager.h"

void unZip(string, string);

void change(initData idata, int id) {
	mk::config cfg;
	cfg.open("RPManager.cfg");
	if (id == -1) {
		cmd("xcopy /Y /S /F .\\RPManager\\vanilla\\*.assets .\\SCPSL_Data\\");
		cfg.writeStr("RPNow", "ORIG");
		goto end;
	}
	unZip(".\\RPManager\\resourcepacks\\" + idata.resourcepacks[id], ".\\SCPSL_Data\\");
	cfg.writeStr("RPNow", idata.resourcepacks[id]);

end:
	cfg.close();
}
