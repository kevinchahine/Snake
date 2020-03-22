#pragma once

#include <iostream>
#include <memory>

#include <opencv2/opencv.hpp>

#include "Apple.h"
#include "Snake.h"
#include "SnakeBoard.h"

#include "ControllerBase.h"

class SnakeEngine
{
public:
	enum class GAME_STATE : uint8_t {
		CONTINUE,
		GAME_OVER,
		WON,
	};
public:
	SnakeEngine(size_t boardWidth, size_t boardHeight);
	SnakeEngine(const SnakeEngine&) = default;
	SnakeEngine(SnakeEngine&&) noexcept = default;
	~SnakeEngine() noexcept = default;
	SnakeEngine& operator=(const SnakeEngine&) = default;
	SnakeEngine& operator=(SnakeEngine&&) noexcept = default;

	bool operator==(const SnakeEngine& left) const;
	bool operator<(const SnakeEngine& left) const;

	void init();

	void reset();

	GAME_STATE update(char controlInput);

public:
	GAME_STATE currGameState;
	SnakeBoard board;
	Snake snake;
	Apple apple;
};

