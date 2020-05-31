#pragma once

#include "AStarSolver.h"

class ReverseAStarSolver : public AStarSolverTemplate<std::greater<CostlySnakePath>>
{
public:
	ReverseAStarSolver(const SnakeState& gameState) :
		AStarSolverTemplate<std::greater<CostlySnakePath>>(gameState) {}

};

