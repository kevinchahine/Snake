#pragma once

#include <iostream>

#include "SnakeEngine.h"

class SolverBase
{
public:
	SolverBase(const SnakeEngine& engine);

	virtual char solve() = 0;

protected:
	const SnakeEngine & engine;
};

