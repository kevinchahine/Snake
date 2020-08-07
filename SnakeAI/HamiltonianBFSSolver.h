#pragma once

#include "BestFirstSolver.h"
#include "HamiltonianSolver.h"
#include "AdvancedSolver.h"

class HamiltonianBFSSolver : public AdvancedSolver<HamiltonianSolver, BestFirstSolver>
{
public:
	HamiltonianBFSSolver(const SnakeGame& m_gameState);

	static bool uniaryOp(const SnakeGame& m_gameState);
};

