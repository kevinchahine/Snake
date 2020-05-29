#pragma once

#include "AStarSolverTemplate.h"

class AStarSolver : public AStarSolverTemplate<std::less<CostlySnakePath>> 
{
public:
	AStarSolver(const SnakeState& gameState);

};
