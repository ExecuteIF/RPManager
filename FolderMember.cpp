#include "RPManager.h"

extern vector<string> getFileInFolder(string path)
{
	intptr_t Handle;
	struct _finddata_t FileInfo;
	vector<string> ans;
	string p;

	if ((Handle = _findfirst(p.assign(path).append("\\*").c_str(), &FileInfo)) == -1) {
		cerr << "Failed to find the following folder.";
		pause();
		exit(-3);
	}
	else {
		ans.push_back(FileInfo.name);
		while (_findnext(Handle, &FileInfo) == 0) {
			ans.push_back(FileInfo.name);
		}
		_findclose(Handle);
	}

	return ans;
}
