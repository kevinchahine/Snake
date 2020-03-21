#pragma once

#include <iostream>

#include <opencv2/opencv.hpp>

#include "Apple.h"
#include "Snake.h"
#include "SnakeBoard.h"

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

	void init();

	void reset();

	GAME_STATE update();

private:
	SnakeBoard board;
	Snake snake;
	Apple apple;
	cv::Mat image;
};

