#include "RPManager.h"

initData init();
bool UI(initData);

extern void scheduler()
{
	bool notend = true;
	initData itData;
	while (true) {
		itData = init();
		notend = UI(itData);
		if (!notend) {
			break;
		}
	}
	return;
}
