#pragma once

#include "AStarSolver.h"

class ReverseAStarSolver : public AStarSolverTemplate<std::greater<CostlySnakePath>>
{
public:
	ReverseAStarSolver(const SnakeGame& m_gameState) :
		AStarSolverTemplate<std::greater<CostlySnakePath>>(m_gameState) {}

};

