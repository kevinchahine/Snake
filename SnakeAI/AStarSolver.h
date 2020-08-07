#pragma once

#include "AStarSolverTemplate.h"

class AStarSolver : public AStarSolverTemplate<std::less<CostlySnakePath>> 
{
public:
	AStarSolver(const SnakeGame& m_gameState) :
		AStarSolverTemplate<std::less<CostlySnakePath>>(m_gameState) {}

};
