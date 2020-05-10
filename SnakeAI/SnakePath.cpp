#include "SnakePath.h"

using namespace std;

SnakePath::SnakePath(const SnakeState& startState) :
	destinationState(startState) {}

SnakePath::SnakePath(SnakeState&& startState) :
	destinationState(move(startState)) {}

std::ostream& operator<<(std::ostream& os, const SnakePath& path)
{
	copy(path.begin(), path.end(), ostream_iterator<char>(os, " "));

	return os;
}

const SnakeState& SnakePath::destinationSnakeState() const
{
	return destinationState;
}

bool SnakePath::isGoalState() const
{
	const Position & headPosition = destinationState.getSnake().head();
	const Position& applePosition = destinationState.getApple();

	return headPosition == applePosition;
}

void SnakePath::pushMove(char move)
{
	this->push_back(move);
	destinationState.moveFast(move);
}

void SnakePath::popMove()
{
	//char lastMove = this->front();

	//destinationState.undoMove(lastMove);
	//stringstream ss;
	//ss << "Don't use " << __FUNCTION__ << " until we make undo move methods\n";
	//throw std::exception(ss.str().c_str());

	if (this->empty() == false) {
		this->pop_front();
	}
}

char SnakePath::peekNextMove() const
{
	// Return next move if one exists. Otherwise return 'x'
	return (this->empty() == true ? 'x' : this->front());
}
