#pragma once

#include <iostream>

#include "SnakeEngine.h"

class SolverBase
{
public:
	SolverBase(const SnakeEngine& engine);

	virtual char solve() = 0;

	bool isMoveUpSafe() const;
	bool isMoveDownSafe() const;
	bool isMoveLeftSafe() const;
	bool isMoveRightSafe() const;
	bool isMoveSafe(char move) const;

protected:
	const SnakeEngine & engine;
};

