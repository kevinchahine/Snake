#include "SnakeBoard.h"

SnakeBoard::SnakeBoard(
	const SnakeBoard::index& nRows, 
	const SnakeBoard::index& nCols) :
	boost::multi_array<CELL, 2>(boost::extents[nRows][nCols]),
	nRows(nRows),
	nCols(nCols)
{}

void SnakeBoard::print(std::ostream& os) const
{
	for (SnakeBoard::index row = 0; row < nRows; row++) {
		for (SnakeBoard::index col = 0; col < nCols; col++) {
			os << static_cast<int>((*this)[row][col]);
		}
		os << '\n';
	}
	os << '\n';
}

void SnakeBoard::print(cv::Mat& image) const
{
	const size_t CELL_WIDTH = image.cols / nCols;
	const size_t CELL_HEIGHT = image.rows / nRows;

	for (SnakeBoard::index row = 0; row < nRows; row++) {
		for (SnakeBoard::index col = 0; col < nCols; col++) {
			cv::Point topLeftOfCell(CELL_WIDTH * col + 8, CELL_HEIGHT * row + 8);
			cv::Scalar color{ 0, 255, 0 };

			cv::rectangle(
				image,
				topLeftOfCell,
				topLeftOfCell + cv::Point(CELL_WIDTH - 16, CELL_HEIGHT - 16),
				color,
				-1);
		}
	}
}

void SnakeBoard::clear()
{
	for (SnakeBoard::index row = 0; row < nRows; row++) {
		for (SnakeBoard::index col = 0; col < nCols; col++) {
			(*this)[row][col] = CELL::EMPTY;
		}
	}
}
