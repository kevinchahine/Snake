#pragma once

#include <iostream>
#include <queue>

#include "Position.h"

/*
	begin()						end()

			  |-- Head is actually at the BACK of the queue
			  v
	  T T T T H
	  ^
	  |-- Tail is at the FRONT of the queue

	  T T T T H
		T T T T H	<-- Push back the new head and pop the old tail

	Head is at the rbegin()
*/
class Snake : public std::deque<Position>
{
public:
	Snake(size_t boardHeight, size_t boardWidth);
	Snake(const Snake&) = default;
	Snake(Snake&&) noexcept = default;
	~Snake() noexcept = default;

	Snake& operator=(const Snake&) = default;
	Snake& operator=(Snake&&) noexcept = default;

	// Returns true iff posision is somewhere on the snakes body.
	bool operator==(const Position& position) const;

	// Returns true iff snake bit itself.
	// Meaning the head hits one of its tail cells.
	bool bitItself() const;

	const Position& head() const;

	const Position& neck() const;

	const Position& tailTip() const;

	void resetHeadRandom();

	void resetHeadAt(Position headStartingPosition);

	bool isMoveUpLegal() const;
	bool isMoveDownLegal() const;
	bool isMoveLeftLegal() const;
	bool isMoveRightLegal() const;
	bool isMoveLegal(char direction) const;
	char getAnyLegalMove() const;

	bool isMoveUpSafe() const;
	bool isMoveDownSafe() const;
	bool isMoveLeftSafe() const;
	bool isMoveRightSafe() const;
	bool isMoveSafe(char move) const;
	
	void moveUpFast();
	void moveDownFast();
	void moveLeftFast();
	void moveRightFast();
	void moveFast(char direction);

	void moveUpIfLegal();
	void moveDownIfLegal();
	void moveLeftIfLegal();
	void moveRightIfLegal();
	void moveIfLegal(char direction);

	void growUpFast();
	void growDownFast();
	void growLeftFast();
	void growRightFast();
	void growFast(char direction);

	void growUpIfLegal();
	void growDownIfLegal();
	void growLeftIfLegal();
	void growRightIfLegal();
	void growIfLegal(char direction);

private:
	size_t boardHeight;
	size_t boardWidth;
};

