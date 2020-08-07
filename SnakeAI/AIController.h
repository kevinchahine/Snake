#pragma once

#include <memory>

#include "ControllerBase.h"
#include "SnakeGame.h"
#include "SolverBase.h"

class AIController : public ControllerBase
{
public:
	AIController(SnakeGame& m_gameState, std::unique_ptr<SolverBase> && solverPtr, int delayMilliSec = 50);

	virtual void reset() override;

	virtual char getInput() override;
	
	// Delay after every call to getInput()
	// Units: milliSec
	void setDelay(int delay) { this->delayMilliSec = delay; }
	
	// Delay after every call to getInput()
	// Units: milliSec
	int getDelay() const { return delayMilliSec; }

private:
	SnakeGame& m_gameState;

	std::unique_ptr<SolverBase> solverPtr;

	// delay before returning from getInput().
	// Should only be used by AIController
	int delayMilliSec;
};

