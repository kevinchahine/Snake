#include "UserController.h"

#include <time.h>
#include <Windows.h>
#include <conio.h>	// for _kbhit() and _getch()

using namespace std;

UserController::UserController()
{
	initAsyncOp();
}

UserController::~UserController() noexcept
{
	// Tell thread to stop what its doing and return
	terminate();
}

void UserController::reset()
{
}

char UserController::getInput()
{
	clock_t delayMilliSec = 200;
	
	// block until delay has passed
	//Sleep(delayMilliSec);
	clock_t stopTime = clock() + delayMilliSec;
	while (clock() < stopTime);
	
	if (_kbhit()) {
		input = _getch();

		input = tolower(input);

		return input;
	}

	return input;
}

void UserController::terminate()
{
	// When thread reads this in its loop, it will return and close itself
	stopFlag = true;
}

void UserController::initAsyncOp()
{
	auto promptUserInput = [&]() {
		// Prompt user for keyboard hit
		std::cout << "\nEnter move wasd: ";

		// Keep accepting user inputs until user enters an 'x'
		// Or the stopFlag is set to true
		do {
			// Check to see if user hit the keyboard (non-blocking)
			if (_kbhit()) {
				// What key did user hit (_getch() is blocking) 
				this->input = _getch();

				// Prompt user for keyboard hit
				std::cout << "\nEnter move wasd: ";
			}
		} while (this->input != 'x' && stopFlag == false);
	};

	// Kick of thread
	myThread = std::thread{ promptUserInput };
}


