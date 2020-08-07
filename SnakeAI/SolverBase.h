#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>

#include "SnakeGame.h"

class SolverBase
{
public:
	SolverBase(const SnakeGame& m_gameState);

	virtual void reset() = 0;
	virtual char solve() = 0;
	
protected:
	// Reference view of current game state. As the game state changes
	// This reference will see those changes.
	const SnakeGame & m_gameState;
};

