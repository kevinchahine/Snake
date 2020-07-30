#pragma once

#include <iostream>
#include <sstream>
#include <queue>

#include "Position.h"

/*
	Snake head	-	The head of the snake
	Snake neck -	One position before its head
	Snake tail -	All the cells of the snake except for the head
	Snake tailtip -	Only the very tip of the tail. Opposite the head
	Snake body -	The entire snake head and tail

	begin()						end()

			  |-- Head is actually at the BACK of the queue
			  v
	  T T T T H
	  ^
	  |-- Tail is at the FRONT of the queue

	  T T T T H
		T T T T H	<-- Push back the new head and pop the old tail

	Head is at the rbegin()

	head()			- returns position of head
	end()			- returns iterator that points 1 past the head
	back()			- returns position of head 
	push_back(p)	- moves head to the position of p

	tailTip()
	begin()
	front()
	pop_front() moves tail forward
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
	// Simply calls isOnSnake()
	bool operator==(const Position& position) const;

	friend std::ostream& operator<<(std::ostream& os, const Snake& snake);

	// Returns true iff snake bit itself.
	// Meaning the head hits one of its tail cells.
	bool bitItself() const;

	// Determines if position is somewhere on the snakes body.
	bool isOnSnake(const Position& position) const;

	const Position& head() const;

	const Position& neck() const;

	const Position& tailTip() const;
	
	void resetHeadRandom();

	void resetHeadAt(Position headStartingPosition);

	// Legal moves are moves where you don't hit the wall or move back into
	// your neck.
	bool isMoveUpLegal() const;
	bool isMoveDownLegal() const;
	bool isMoveLeftLegal() const;
	bool isMoveRightLegal() const;
	bool isMoveLegal(char direction) const;
	char getAnyLegalMove() const;

	void moveUpFast();
	void moveDownFast();
	void moveLeftFast();
	void moveRightFast();
	void moveFast(char direction);
	
	// Move if it will not hit wall or the snakes neck
	void moveUpIfLegal();
	void moveDownIfLegal();
	void moveLeftIfLegal();
	void moveRightIfLegal();
	void moveIfLegal(char direction);
	void moveAnyLegal();
	
	void growUpFast();
	void growDownFast();
	void growLeftFast();
	void growRightFast();
	void growFast(char direction);

	// Grow if it will not hit wall or the snakes neck
	void growUpIfLegal();
	void growDownIfLegal();
	void growLeftIfLegal();
	void growRightIfLegal();
	void growIfLegal(char direction);
	void growAnyLegal();

	// Undoes a move by moving the snake backwards so that the snakes tail is at lastTailPos.
	// Works for undoing move and grow operations. Make sure lastTailPos is adjacent to the current tail
	// position or the snake will become detached.
	void undoMove(const Position& lastTailPos);

	uint64_t hashValue() const;

private:
	size_t boardHeight;
	size_t boardWidth;
};

