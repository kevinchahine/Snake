#pragma once

#include "AStarSolver.h"

class ReverseAStarSolver : public AStarSolverTemplate<std::less<CostlySnakePath>>
{
public:
	ReverseAStarSolver(const SnakeState& gameState);

};

