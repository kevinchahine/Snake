#pragma once

#include "BestFirstSolver.h"
#include "HamiltonianSolver.h"
#include "AdvancedSolver.h"

class HamiltonianBFSSolver : public AdvancedSolver<HamiltonianSolver, BestFirstSolver>
{
public:
	HamiltonianBFSSolver(const SnakeState& gameState);

	static bool uniaryOp(const SnakeState& gameState);
};

