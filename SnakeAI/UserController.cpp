#include "UserController.h"
#include <Windows.h>
#include <opencv2/opencv.hpp>

UserController::UserController()
{
	initAsyncOp();
}

char UserController::getInput()
{
	Sleep(400);

	return input;
}

void UserController::initAsyncOp()
{
	auto promptUserInput = [&]() {
		while (this->input != 'x') {
			std::cout << "Enter move wasd: ";
			std::cin >> this->input;
		}};

	myThread = std::thread{ promptUserInput };
}


