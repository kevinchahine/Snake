#pragma once

#include <iostream>
#include <sstream>

#include <boost/multi_array.hpp>

#include <opencv2/opencv.hpp>

#include "Snake.h"
#include "Apple.h"

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

	// Calculates the hashvalue of the board
	size_t hashValue() const;

	void print(std::ostream& os = std::cout) const;

	void print(cv::Mat& image) const;

	void clear();

	void paste(const Apple& apple);

	void paste(const Snake& snake);
	
	const SnakeBoard::index& getNRows() const;
	const SnakeBoard::index& getNCols() const;

private:
	cv::Scalar cellColor = cv::Scalar{ 129, 129, 129 };
	cv::Scalar headColor = cv::Scalar{ 0, 180, 0 };
	cv::Scalar tailColor = cv::Scalar{ 0, 128, 0 };
	cv::Scalar appleColor = cv::Scalar{ 0, 0, 255 };
};

