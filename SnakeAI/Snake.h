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

	const Position& head() const;

	const Position& neck() const;

	void resetHeadRandom();

	void resetHeadAt(Position headStartingPosition);

	bool isMoveUpValid();
	bool isMoveDownValid();
	bool isMoveLeftValid();
	bool isMoveRightValid();

	void moveUpFast();
	void moveDownFast();
	void moveLeftFast();
	void moveRightFast();

	void moveUpValid();
	void moveDownValid();
	void moveLeftValid();
	void moveRightValid();

	void growUpFast();
	void growDownFast();
	void growLeftFast();
	void growRightFast();

	void growUpValid();
	void growDownValid();
	void growLeftValid();
	void growRightValid();

private:
	size_t boardHeight;
	size_t boardWidth;
};

