#pragma once

#include <iostream>

#include <boost/multi_array.hpp>

#include <opencv2/opencv.hpp>

class SnakeBoard : public boost::multi_array<uint8_t, 2>
{
public:
	SnakeBoard(const SnakeBoard::index & nRows, const SnakeBoard::index & nCols);

	void print(std::ostream& os = std::cout) const;

	void print(cv::Mat& image) const;

private:
	SnakeBoard::index nRows;
	SnakeBoard::index nCols;

	cv::Scalar headColor = cv::Scalar{ 0, 128, 0 };
	cv::Scalar tailColor = cv::Scalar{ 192, 192, 192 };
	cv::Scalar appleColor = cv::Scalar{ 255, 0, 0 };
};

