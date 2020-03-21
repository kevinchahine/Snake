#pragma once

#include <thread>

#include "ControllerBase.h"

class UserController : public ControllerBase
{
public:
	UserController();

	virtual char getInput() override;

private:
	void initAsyncOp();

private:
	std::thread myThread;
	bool messageIsIn = false;
	char input = NULL;
};

