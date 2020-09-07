#include "CostlySnakePath.h"

using namespace std;

CostlySnakePath::CostlySnakePath(const SnakeGame& startingState) :
	SnakePath(startingState) {}

CostlySnakePath::CostlySnakePath(SnakeGame&& startingState) :
	SnakePath(move(startingState)) {}

bool CostlySnakePath::operator<(const CostlySnakePath& costlySnakePath) const
{
	// Made greater than on purpose so that "shorter" and "better" SnakePaths
	// will go first (nearer to top()) in priority_queues for the AStar algorithm
	// Favor shortest path
	return calcTotalCost() > costlySnakePath.calcTotalCost();
}

bool CostlySnakePath::operator==(const CostlySnakePath& costlySnakePath) const
{
	return this->calcTotalCost() == costlySnakePath.calcTotalCost();
}

int CostlySnakePath::calcCostFromStartCost() const
{
	return static_cast<int>(this->pathLength());
}

int CostlySnakePath::calcCostToDestination() const
{
	// Calculate Manhattan Distance from Snake Head to Apple
	const Position& p1 = this->destinationSnakeState().snake().head();
	const Position& p2 = this->destinationSnakeState().getApple();

	return static_cast<int>(
		std::abs(p1.row() - p2.row()) +		// calc vertical   distance
		std::abs(p1.col() - p2.col()));		// calc horizontal distance
}

int CostlySnakePath::calcTotalCost() const
{
	return calcCostFromStartCost() + calcCostToDestination();
}

uint64_t CostlySnakePath::hashValue() const
{
	uint64_t hash = 0;

	for (uint64_t i = 0; i < this->SnakePath::size(); i++) {
		char move = this->SnakePath::at(i);

		uint64_t id = 0;
		switch (move) {
		case 'w':	id = 1;	break;
		case 's':	id = 2; break;
		case 'a':	id = 3;	break;
		case 'd':	id = 4; break;
		default:	
			stringstream ss;
			ss << "Error: " << __FUNCTION__ << " line " << __LINE__
				<< ": unknown move found in CostlySnakePath. move = " << move << '\n';
			throw std::exception(ss.str().c_str());
		}

		hash += 4 * i + id;
	}

	return hash;
}
