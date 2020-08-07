#pragma once

#include "SolverBase.h"

class HamiltonianSolver : public SolverBase
{
public:
	HamiltonianSolver(const SnakeGame& m_gameState);

	virtual void reset() override;

	virtual char solve() override;

	static bool isSolution(const SnakeGame& game);

protected:
	SnakeGame search() const;

	void initializeCycle();

	// Initializes cycle based on current snake state
	// returns true iff a hamiltonian cycle was found
	std::vector<char> initializeCycleDynamic();

	// Initializes validMoves vector to match the snakes current position.
	// Starting with the snakes tail moving up to the head, it appends all the moves that will 
	// trace the snakes body.
	// validMoves will be modified to contain the moves that would follow the snakes body 
	// from the tail to its head.
	// Starts by clearing the vector of its contents.
	// Should be called on an empty vector that is resized to the size of the game board
	void initializeValidMoves(std::vector<boost::container::static_vector<char, 3>> & validMoves, const Snake & snake) const;

protected:
	BoardTemplate<char> hamiltonianCycle;

	class UnitTestHamiltonianSolver;
	friend UnitTestHamiltonianSolver;
};

