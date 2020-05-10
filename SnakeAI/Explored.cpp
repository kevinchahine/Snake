#include "Explored.h"

using namespace std;

bool Explored::contains(const SnakeState& visitedSnakeState) const
{
	// 1.) Get hash that uniquely identifies the visited state.
	// Calculated using snake positions and apple
	uint64_t hash = visitedSnakeState.getSnake().hashValue();

	// 2.) Find hash in set
	auto matchingHashIt = this->find(hash);

	// 3.) Did we find a match?
	return matchingHashIt != this->end();
}

void Explored::insert(const SnakeState& visitedSnakeState)
{
	this->set<uint64_t>::insert(visitedSnakeState.getSnake().hashValue());
}
