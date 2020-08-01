#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>

#include "SnakeState.h"

class SolverBase
{
public:
	SolverBase(const SnakeState& gameState);

	virtual void reset() = 0;
	virtual char solve() = 0;
	
protected:
	// Reference view of current game state. As the game state changes
	// This reference will see those changes.
	const SnakeState & gameState;
};

