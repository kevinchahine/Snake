#pragma once

class ControllerBase
{
public:
	virtual void reset() = 0;

	virtual char getInput() = 0;
};

