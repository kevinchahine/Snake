#pragma once

#include <iostream>

#include <boost/multi_array.hpp>

#include <opencv2/opencv.hpp>

enum class CELL : uint8_t {
	EMPTY = 0,
	HEAD = 1,
	TAIL = 2,
	APPLE = 3
};

class SnakeBoard : public boost::multi_array<CELL, 2>
{
public:
	SnakeBoard(const SnakeBoard::index & nRows, const SnakeBoard::index & nCols);

	//void drawSnake();

	void print(std::ostream& os = std::cout) const;

	void print(cv::Mat& image) const;

	void clear();

private:
	SnakeBoard::index nRows;
	SnakeBoard::index nCols;

	cv::Scalar cellColor = cv::Scalar{ 129, 129, 129 };
	cv::Scalar headColor = cv::Scalar{ 0, 128, 0 };
	cv::Scalar tailColor = cv::Scalar{ 192, 192, 192 };
	cv::Scalar appleColor = cv::Scalar{ 255, 0, 0 };
};

