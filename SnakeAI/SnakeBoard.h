#pragma once

#include <iostream>
#include <sstream>

#include <opencv2/opencv.hpp>

#include "BoardTemplate.h"
#include "Snake.h"
#include "Apple.h"

enum class CELL : uint8_t {
	EMPTY = 0,
	HEAD = 1,
	TAIL = 2,
	APPLE = 3
};

class Board : public BoardTemplate<CELL>
{
public:
	Board(const Board::index & nRows, const Board::index & nCols);

	// Calculates the hashvalue of the board
	size_t hashValue() const;

	void print(std::ostream& os = std::cout) const;

	void print(cv::Mat& image) const;

	void clear();

	void paste(const Apple& apple);

	void paste(const Snake& snake);
	
private:
	cv::Scalar cellColor = cv::Scalar{ 129, 129, 129 };
	cv::Scalar headColor = cv::Scalar{ 0, 180, 0 };
	cv::Scalar tailColor = cv::Scalar{ 0, 128, 0 };
	cv::Scalar appleColor = cv::Scalar{ 0, 0, 255 };
};

