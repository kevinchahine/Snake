#pragma once

#include <memory>

#include "ControllerBase.h"
#include "SnakeState.h"
#include "SolverBase.h"

class AIController : public ControllerBase
{
public:
	AIController(SnakeState& gameState, std::unique_ptr<SolverBase> && solverPtr);

	virtual char getInput() override;

private:
	SnakeState& gameState;

	std::unique_ptr<SolverBase> solverPtr;
};

