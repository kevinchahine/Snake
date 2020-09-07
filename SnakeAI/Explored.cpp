#include "Explored.h"

using namespace std;

#include "SnakeGame.h"

bool Explored::contains(const SnakeGame& visitedSnakeState) const
{
	// 1.) Get hash that uniquely identifies the visited state.
	// Calculated using snake positions and m_apple
	uint64_t hash = visitedSnakeState.snake().hashValue();

	// 2.) Find hash in set
	auto matchingHashIt = this->find(hash);

	// 3.) Did we find a match?
	return matchingHashIt != this->end();
}

void Explored::insert(const SnakeGame& visitedSnakeState)
{
	this->set<uint64_t>::insert(visitedSnakeState.snake().hashValue());
}

