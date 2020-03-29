#pragma once

#include <iostream>
#include <sstream>
#include <memory>

#include <opencv2/opencv.hpp>

#include "Apple.h"
#include "Snake.h"
#include "SnakeBoard.h"

#include "ControllerBase.h"

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

	GAME_STATE update(char controlInput);

	const SnakeBoard::index& getNRows() const;
	const SnakeBoard::index& getNCols() const;

	GAME_STATE calcGameState();
	GAME_STATE getGameState() const;

	const SnakeBoard& getSnakeBoard() const;

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

protected:
	GAME_STATE gameState;
	SnakeBoard board;
	Snake snake;
	Apple apple;
};

