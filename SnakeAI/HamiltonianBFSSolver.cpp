#include "HamiltonianBFSSolver.h"

HamiltonianBFSSolver::HamiltonianBFSSolver(const SnakeState& gameState) :
	AdvancedSolver<HamiltonianSolver, BestFirstSolver>(
		gameState, uniaryOp)
{
}

bool HamiltonianBFSSolver::uniaryOp(const SnakeState& gameState)
{
	// Calculate the number of empty spaces
	int numCells = gameState.getNCells();
	int nEmpty = numCells - gameState.getSnake().size();
	
	return (static_cast<float>(nEmpty) / numCells) < 0.5;
}
