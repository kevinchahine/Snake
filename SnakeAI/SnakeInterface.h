#pragma once

#include <iostream>
#include <memory>
#include <stack>		// remove
#include <time.h>

#include <opencv2/opencv.hpp>

#include "SnakeGame.h"

#include "ControllerBase.h"

class SnakeInterface
{
public:
	SnakeInterface(size_t boardWidth, size_t boardHeight);

	void run();

	void setController(std::unique_ptr<ControllerBase>&& controllerPtr);
	
	SnakeGame m_gameState;

private:
	cv::Mat image;
	std::unique_ptr<ControllerBase> controllerPtr;
};

