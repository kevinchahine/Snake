#pragma once

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

#include <boost/container/static_vector.hpp>

class Apple;
class Snake;

#include "Position.h"
#include "Board.h"

#include "ControllerBase.h"

class SnakeGame
{
public:
	enum class GAME_STATE : uint8_t {
		CONTINUE,	// Still going, but snake did not eat apple in previous turn
		JUST_ATE,	// Means snake ate apple in previous turn.
		GAME_OVER,
		WON,
		ERROR,
	};

public:
	SnakeGame(size_t boardWidth, size_t boardHeight);
	SnakeGame(const SnakeGame&) = default;
	SnakeGame(SnakeGame&&) noexcept = default;
	~SnakeGame() noexcept = default;
	SnakeGame& operator=(const SnakeGame&) = default;
	SnakeGame& operator=(SnakeGame&&) noexcept = default;

	bool operator==(const SnakeGame& left) const;
	bool operator<(const SnakeGame& left) const;
	size_t operator()() const;

	void init();

	void reset();
	void reset(const Position& snakeStartingPos, const Position & appleStartingPos);

	const Board::index& getNRows() const;
	const Board::index& getNCols() const;
	size_t getNCells() const;

	GAME_STATE getGameState() const;

	const Board& board() const;
	const Snake& snake() const;
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

	// === A Legal move will not hit any walls nor move backwards ===
	void moveUpIfLegal();
	void moveDownIfLegal();
	void moveLeftIfLegal();
	void moveRightIfLegal();
	void moveIfLegal(char direction);

	void moveAppleRandomly();
	void moveAppleTo(const Position& newApplePos);

	void print(std::ostream & os = std::cout) const;

protected:
	GAME_STATE calcGameState();

protected:
	Board m_board;
	Snake m_snake;
	Apple m_apple;
	GAME_STATE m_state = GAME_STATE::CONTINUE;
};

