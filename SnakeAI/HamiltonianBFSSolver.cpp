#include "HamiltonianBFSSolver.h"

HamiltonianBFSSolver::HamiltonianBFSSolver(const SnakeGame& m_gameState) :
	AdvancedSolver<HamiltonianSolver, BestFirstSolver>(
		m_gameState, uniaryOp)
{
}

bool HamiltonianBFSSolver::uniaryOp(const SnakeGame& m_gameState)
{
	// Calculate the number of empty spaces
	int numCells = static_cast<int>(m_gameState.getNCells());
	int nEmpty = numCells - static_cast<int>(m_gameState.snake().size());
	
	return (static_cast<float>(nEmpty) / numCells) < 0.5;
}
