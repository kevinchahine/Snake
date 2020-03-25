#pragma once

#include <iostream>

#include "SnakeState.h"

class SolverBase
{
public:
	SolverBase(const SnakeState& gameState);

	virtual void reset() = 0;
	virtual char solve() = 0;
	
protected:
	const SnakeState & gameState;
};

