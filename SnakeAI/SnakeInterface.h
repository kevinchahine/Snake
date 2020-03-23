#pragma once

#include <iostream>
#include <memory>
#include <time.h>

#include <opencv2/opencv.hpp>

#include "SnakeEngine.h"

#include "ControllerBase.h"

class SnakeInterface
{
public:
	SnakeInterface(size_t boardWidth, size_t boardHeight);

	void start();

	void setController(std::unique_ptr<ControllerBase>&& controllerPtr);

	SnakeEngine engine;

private:
	cv::Mat image;
	std::unique_ptr<ControllerBase> controllerPtr;
};

