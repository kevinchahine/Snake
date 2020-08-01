#pragma once

#include <iostream>

class ControllerBase
{
public:
	virtual void reset() = 0;

	virtual char getInput() = 0;
};

