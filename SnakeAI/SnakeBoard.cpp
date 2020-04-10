#include "SnakeBoard.h"

Board::Board(
	const Board::index& nRows, 
	const Board::index& nCols) :
	BoardTemplate<CELL>(nRows, nCols)
{}

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
			os << static_cast<int>((*this)[row][col]) << ' ';
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

	for (Board::index row = 0; row < NROWS; row++) {
		for (Board::index col = 0; col < NCOLS; col++) {
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

void Board::paste(const Apple& apple)
{
	(*this)(apple) = CELL::APPLE;
}

void Board::paste(const Snake& snake)
{
	for (const auto& positionOnSnake : snake)
	{
		(*this)(positionOnSnake) = CELL::TAIL;
	}

	(*this)(snake.head()) = CELL::HEAD;
}


