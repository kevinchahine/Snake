#pragma once

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

#include <opencv2/opencv.hpp>

#include <boost/container/static_vector.hpp>

#include "Apple.h"
#include "Snake.h"
#include "SnakeBoard.h"

#include "ControllerBase.h"

// TODO: Make a class called Undoable that takes care of undoing moves and inherite SnakeState from it.
class SnakeState
{
public:
	enum class GAME_STATE : uint8_t {
		CONTINUE,
		GAME_OVER,
		WON,
	};

public:
	SnakeState(size_t boardWidth, size_t boardHeight);
	SnakeState(const SnakeState&) = default;
	SnakeState(SnakeState&&) noexcept = default;
	~SnakeState() noexcept = default;
	SnakeState& operator=(const SnakeState&) = default;
	SnakeState& operator=(SnakeState&&) noexcept = default;

	bool operator==(const SnakeState& left) const;
	bool operator<(const SnakeState& left) const;
	size_t operator()() const;

	void init();

	void reset();
	void reset(const Position& snakeStartingPos, const Position & appleStartingPos);

	GAME_STATE moveSnake(char controlInput);

	const Board::index& getNRows() const;
	const Board::index& getNCols() const;
	size_t getNCells() const;

	GAME_STATE calcGameState();
	GAME_STATE getCurrentState() const;

	const Board& getBoard() const;
	const Snake& getSnake() const;
	const Apple& getApple() const;

	// === A Legal move will not hit any walls nor move backwards ===
	bool isMoveUpLegal() const;
	bool isMoveDownLegal() const;
	bool isMoveLeftLegal() const;
	bool isMoveRightLegal() const;
	bool isMoveLegal(char direction) const;
	char getAnyLegalMove() const;

	// === A Safe move will not move into the snakes tail ===
	bool isMoveUpSafe() const;
	bool isMoveDownSafe() const;
	bool isMoveLeftSafe() const;
	bool isMoveRightSafe() const;
	bool isMoveSafe(char direction) const;
	char getAnySafeMove() const;

	// === Legal and Safe ===
	// Finds a move that is both legal and safe. 
	// If no move is both legal and safe then it returns a legal move
	// (This move will make the snake bit itself.)
	char getAnyLegalAndSafeMove() const;
	boost::container::static_vector<char, 3> getAllLegalAndSafeMoves() const;

	void moveUpFast();
	void moveDownFast();
	void moveLeftFast();
	void moveRightFast();
	void moveFast(char direction);

	// === Forces growing. Does not account for eating apple. Not intended for regular gameplay ===
	// === Use move***Fast() or move***IfLegal() for regular gameplay ===
	void growUpFast();
	void growDownFast();
	void growLeftFast();
	void growRightFast();
	void growFast(char direction);

	// === A Legal move will not hit any walls nor move backwards ===
	void moveUpIfLegal();
	void moveDownIfLegal();
	void moveLeftIfLegal();
	void moveRightIfLegal();
	void moveIfLegal(char direction);

	// Undoes a move by moving the snake backwards so that the snakes tail is at lastTailPos.
	// Works for undoing move and grow operations. Make sure lastTailPos is adjacent to the current tail
	// Do not call if snake.size() <= 2 or errors will occur
	void undoMoveSafe();

	void moveAppleRandomly();
	void moveAppleTo(const Position& newApplePos);
	bool appleIsEaten() const;

protected:
	GAME_STATE gameState;
	Board board;
	Snake snake;
	Apple apple;

	// Used for undoing moves
	std::vector<Apple> applePositions;
	std::vector<Position> snakePositions;
};

