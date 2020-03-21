#pragma once

#include <iostream>

#include <opencv2/opencv.hpp>

#include "Apple.h"
#include "Snake.h"
#include "SnakeBoard.h"

class SnakeEngine
{
public:
	SnakeEngine(size_t boardWidth, size_t boardHeight);

	void init();

	void reset();

	void update();

private:
	SnakeBoard board;
	Snake snake;
	Apple apple;
	cv::Mat image;
};

