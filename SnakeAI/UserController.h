#pragma once

#include <thread>

#include "ControllerBase.h"

class UserController : public ControllerBase
{
public:
	UserController();
	virtual ~UserController() noexcept;

	virtual char getInput() override;
	
	// Stops ongoing thread
	void terminate();

private:
	void initAsyncOp();

private:
	std::thread myThread;
	bool messageIsIn = false;
	char input = 'p';
	bool stopFlag = false;
};

