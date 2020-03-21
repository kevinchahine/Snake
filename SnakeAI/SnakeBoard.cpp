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
			cv::Point topLeftOfCell(CELL_WIDTH * col + 2, CELL_HEIGHT * row + 2);
			
			cv::Scalar color{ 0, 255, 0 };
			
			switch ((*this)[row][col]) {
			case CELL::EMPTY:	color = cellColor;	break;
			case CELL::HEAD:	color = headColor;	break;
			case CELL::TAIL:	color = tailColor;	break;
			case CELL::APPLE:	color = appleColor;	break;
			default:
				std::stringstream ss;
				ss << "Unknown cell value at (" 
					<< row << ", " << col << ") equals "
					<< static_cast<int>((*this)[row][col]);

					throw std::exception(ss.str().c_str());
			}

			cv::rectangle(
				image,
				topLeftOfCell,
				topLeftOfCell + cv::Point(CELL_WIDTH - 4, CELL_HEIGHT - 4),
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

void SnakeBoard::paste(const Apple& apple)
{
	(*this)(apple) = CELL::APPLE;
}

void SnakeBoard::paste(const Snake& snake)
{
	for (const auto& snakeElement : snake)
	{
		(*this)(snakeElement) = CELL::TAIL;
	}

	(*this)(snake.head()) = CELL::HEAD;
}

const SnakeBoard::index& SnakeBoard::getNRows() const
{
	return nRows;
}

const SnakeBoard::index& SnakeBoard::getNCols() const
{
	return nCols;
}

