#include "RPManager.h"

void scheduler();

int main(int argc, char* argv[])
{
	try {
		scheduler();
	}
	catch (string errInfo) {
		cerr << errInfo << endl;
		pause();
		return -1;
	}
	catch (exception& e) {
		cerr << "Standard exception: " << e.what() << endl;
		pause();
		return -2;
	}
	return 0;
}
