#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#include "SnakeInterface.h"
#include "ControllerBase.h"
#include "UserController.h"
#include "AIController.h"

int main()
{
	// Initialize random number generator
	srand(time(NULL));

	try {
		SnakeInterface gameInterface{ 10, 10 };

		gameInterface.setController(std::make_unique<AIController>(gameInterface.engine));
		//gameInterface.setController(std::make_unique<UserController>());

		gameInterface.start();
	}
	catch (std::exception & e) {
		cout << "Exception caught in " << __FUNCTION__ << ": "
			<< e.what() << '\n';
	}

	cout << "Press any key to continue . . .";
	cin.get();
	cin.get();
	return 0;
}
