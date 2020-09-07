#include "Board.h"

#include <sstream>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

Board::Board(
	const Board::index& nRows, 
	const Board::index& nCols) :
	BoardTemplate<CELL>(nRows, nCols)	
{}

Board::Board(size_t nRows, size_t nCols) :
	BoardTemplate<CELL>(nRows, nCols)
{
}

size_t Board::hashValue() const
{
	size_t hashValue = 0;

	// Calculate the hash value based on the value of every cell in the board
	// There are 4 possible values each cell can have:
	//	CELL::EMPTY = 0,
	//	CELL::HEAD = 1,
	//	CELL::TAIL = 2,
	//	CELL::APPLE = 3
	// The hash value is calculated as:
	// Assume r is the row index
	// Assume c is the column index
	//	Sum of every cell C 

	const size_t NROWS = this->getNRows();
	const size_t NCOLS = this->getNCols();

	for (size_t row = 0; row < NROWS; row++) {
		for (size_t col = 0; col < NCOLS; col++) {
			size_t cellIndex = (row * NCOLS + col + 1);	// Add 1 to row and col so that <0, 0> doesn't get zeroed out
			size_t cellValue = static_cast<size_t>((*this)[row][col]);
			hashValue += cellIndex * cellValue;
		}
	}

	return hashValue;
}

void Board::print(std::ostream& os) const
{
	const size_t NROWS = this->getNRows();
	const size_t NCOLS = this->getNCols();

	for (Board::index row = 0; row < NROWS; row++) {
		for (Board::index col = 0; col < NCOLS; col++) {
			os << (*this)[row][col];
		}
		os << '\n';
	}
	os << '\n';
}

void Board::print(cv::Mat& image) const
{
	const size_t NROWS = this->getNRows();
	const size_t NCOLS = this->getNCols();

	const size_t CELL_WIDTH = image.cols / NROWS;
	const size_t CELL_HEIGHT = image.rows / NCOLS;

	cv::Point upperLeft;
	cv::Point lowerRight;

	image = cv::Mat::zeros(image.size(), image.type());

	// --- Print Dots between cells ---
	for (size_t r = 0; r < NROWS + 1; r++) {
		for (size_t c = 0; c < NCOLS + 1; c++) {
			cv::Point point(CELL_WIDTH * c, CELL_HEIGHT * r);

			cv::circle(image, point, 1, cv::Scalar(128, 128, 128));
		}
	}

	// --- Print Snake ---
	if (snakePtr != nullptr) {
		const Snake& s = *snakePtr;
		Position prevCell = s[0];
		for (size_t i = 1; i < s.size(); i++) {
			Position currCell = s[i];

			if (prevCell.upOne() == currCell) {				// DOWN
				// Curr
				// Prev

				upperLeft = cv::Point(CELL_WIDTH * currCell.col() + 2, CELL_HEIGHT * currCell.row() + 2);
				lowerRight = cv::Point(CELL_WIDTH * prevCell.col(), CELL_HEIGHT * prevCell.row()) +
					cv::Point(CELL_WIDTH - 4, CELL_HEIGHT - 4);
			}
			else if (prevCell.downOne() == currCell) {		// UP 
				// Prev
				// Curr

				upperLeft = cv::Point(CELL_WIDTH * prevCell.col() + 2, CELL_HEIGHT * prevCell.row() + 2);
				lowerRight = cv::Point(CELL_WIDTH * currCell.col(), CELL_HEIGHT * currCell.row()) +
					cv::Point(CELL_WIDTH - 4, CELL_HEIGHT - 4);
			}
			else if (prevCell.leftOne() == currCell) {		// RIGHT
				// Curr Prev

				upperLeft = cv::Point(CELL_WIDTH * currCell.col() + 2, CELL_HEIGHT * currCell.row() + 2);
				lowerRight = cv::Point(CELL_WIDTH * prevCell.col(), CELL_HEIGHT * prevCell.row()) +
					cv::Point(CELL_WIDTH - 4, CELL_HEIGHT - 4);
			}
			else if (prevCell.rightOne() == currCell) {		// LEFT
				// Prev Curr

				upperLeft = cv::Point(CELL_WIDTH * prevCell.col() + 2, CELL_HEIGHT * prevCell.row() + 2);
				lowerRight = cv::Point(CELL_WIDTH * currCell.col(), CELL_HEIGHT * currCell.row()) +
					cv::Point(CELL_WIDTH - 4, CELL_HEIGHT - 4);
			}

			// Draw Cell
			cv::rectangle(
				image,
				upperLeft,
				lowerRight,
				tailColor,
				-1);
			prevCell = currCell;
		}

	// --- Print Head ---
	const Position& head = snakePtr->head();
	upperLeft = cv::Point(CELL_WIDTH * head.col() + 2, CELL_HEIGHT * head.row() + 2);
	lowerRight = upperLeft + cv::Point(CELL_WIDTH - 6, CELL_HEIGHT - 6);
	cv::rectangle(
		image,
		upperLeft,
		lowerRight,
		headColor,
		-1);
	}

	// --- 3.) Print Apple ---
	if (applePtr != nullptr)
	{
		const Apple& m_apple = *applePtr;
		upperLeft = cv::Point(CELL_WIDTH * m_apple.col() + 2, CELL_HEIGHT * m_apple.row() + 2);
		lowerRight = upperLeft + cv::Point(CELL_WIDTH - 6, CELL_HEIGHT - 6);
		cv::rectangle(
			image,
			upperLeft,
			lowerRight,
			appleColor,
			-1);
	}
}

void Board::show(const std::string & windowName) const
{
	cv::Mat image = cv::Mat::zeros(getNRows() * 40, getNCols() * 40, CV_8UC3);
	
	print(image);

	cv::imshow(windowName, image);
	cv::waitKey(1);
}

void Board::clear()
{
	const size_t NROWS = this->getNRows();
	const size_t NCOLS = this->getNCols();

	for (Board::index row = 0; row < NROWS; row++) {
		for (Board::index col = 0; col < NCOLS; col++) {
			(*this)[row][col] = CELL::EMPTY;
		}
	}
}

void Board::paste(const Apple& m_apple)
{
	(*this)(m_apple) = CELL::APPLE;
}

void Board::paste(const Snake& snakePtr)
{
	for (const auto& positionOnSnake : snakePtr)
	{
		(*this)(positionOnSnake) = CELL::TAIL;
	}

	(*this)(snakePtr.head()) = CELL::HEAD;
}

void Board::setSnake(const Snake& snake)
{
	snakePtr = &snake;
}

void Board::setApple(const Apple& m_apple)
{
	applePtr = &m_apple;
}

std::ostream& operator<<(std::ostream& os, const CELL& cell)
{
	switch (cell)
	{
	case CELL::EMPTY:	os << '.';	break;
	case CELL::HEAD:	os << 'H';	break;
	case CELL::TAIL:	os << 'T';	break;
	case CELL::APPLE:	os << 'A';	break;
	default:
		std::cout << __FILE__ << " line " << __LINE__
			<< " unknown case = " << static_cast<int>(cell) << '\n';
		break;
	}

	return os;
}
