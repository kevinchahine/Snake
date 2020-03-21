#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#include "SnakeEngine.h"

int main()
{
	// Initialize random number generator
	srand(time(NULL));

	try {
		SnakeEngine engine{ 10, 15 };

		engine.init();

		while (true) {
			engine.update();
		}
	}
	catch (std::exception & e) {
		cout << "Exception caught in " << __FUNCTION__ << ": "
			<< e.what() << '\n';
	}

	//cout << "Press any key to continue . . .";
	//cin.get();
	return 0;
}
