#include "RPManager.h"

/// <summary>
/// display loading
/// </summary>
/// <param name="delay">delay per change(ms)</param>
/// <param name="cnt">how many cycles per time</param>
/// <param name="total">how many times, use -1 to rotate perminately</param>
/// <param name="targetchr">use what as targetchr</param>
extern void loading(int delay, int cnt, int total, char targetchr)
{
	char loadlist_chr[4] = {
	'-'		,
	'\\'	,
	'|'		,
	'/'
	};

	printf(".");
	for (int i = 0; (total < 0) ? (true) : (i < total); ++i) {
		for (int j = 0; j < cnt; ++j) {
			printf("\b%c", loadlist_chr[j % 4]);
			Sleep(delay);
		}
		printf("\b%c.", targetchr);
	}
	printf("\b");
}
