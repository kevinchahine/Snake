#pragma once

#include <memory>

#include "ControllerBase.h"
#include "SnakeEngine.h"
#include "SolverBase.h"

class AIController : public ControllerBase
{
public:
	AIController(SnakeEngine& engine, std::unique_ptr<SolverBase> && solverPtr);

	virtual char getInput() override;

private:
	SnakeEngine& engine;

	std::unique_ptr<SolverBase> solverPtr;
};

