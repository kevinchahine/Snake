#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>

#include <SnakeAI/Board.h>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSnakeAI
{
	TEST_CLASS(UnitTestSnakeBoard)
	{
	public:
		TEST_METHOD(Constructors)
		{
			Board board(4, 5);

			Assert::IsTrue(board.getNRows() == 4);
			Assert::IsTrue(board.getNCols() == 5);

			stringstream ss;
			ss << "num_elements() == " << board.num_elements() << '\n';

			for (size_t row = 0; row < board.getNRows(); row++) {
				for (size_t col = 0; col < board.getNCols(); col++) {
					ss << static_cast<int>(board[row][col]) << '\t';
				}
				ss << '\n';
			}
			ss << '\n';

			Logger::WriteMessage(ss.str().c_str());
			Assert::IsTrue(board.num_elements() == 4 * 5);
		}

		TEST_METHOD(Dimentions)
		{
			Board board{ 4, 6 };

			Assert::IsTrue(board.getNRows() == 4);
			Assert::IsTrue(board.getNCols() == 6);
		}

		TEST_METHOD(HashValue)
		{
			Board board(4, 4);

			Assert::IsTrue(board.hashValue() == 0);

			/*
				A H . T
				. T T T
				. . . T
				. . . T
			*/
			board[0][0] = CELL::APPLE;
			board[0][1] = CELL::HEAD;
			board[0][3] = CELL::TAIL;
			
			board[1][1] = CELL::TAIL;
			board[1][2] = CELL::TAIL;
			board[1][3] = CELL::TAIL;

			board[2][3] = CELL::TAIL;

			board[3][3] = CELL::TAIL;

			size_t expectedHashValue = 111;

			stringstream ss;
			board.print(ss);

			ss << "expectedHashValue = " << expectedHashValue << '\n'
				<< "board.hashValue() = " << board.hashValue() << '\n';
			Logger::WriteMessage(ss.str().c_str());

			Assert::IsTrue(board.hashValue() == expectedHashValue);
		}

		TEST_METHOD(Clear)
		{
			Board board(4, 4);

			// Place a snakes tail on every cell
			for (Board::index row = 0; row < board.getNRows(); row++) {
				for (Board::index col = 0; col < board.getNCols(); col++) {
					board[row][col] = CELL::TAIL;
				}
			}

			// Clear the board making every cell empty
			board.clear();

			// Make sure every cell is empty
			bool isEveryCellEmpty = true;
			for (Board::index row = 0; row < board.getNRows(); row++) {
				for (Board::index col = 0; col < board.getNCols(); col++) {
					if (board[row][col] != CELL::EMPTY) {
						isEveryCellEmpty = false;
					}
				}
			}
			Assert::IsTrue(isEveryCellEmpty);
		}

		TEST_METHOD(Paste)
		{
			Apple m_apple(4, 4);
			Snake snake(4, 4);
			Board board(4, 4, snake, m_apple);

			m_apple.moveTo(1, 2);
			snake.resetHeadAt(Position(0, 0));
			snake.growRightFast();
			snake.moveRightFast();

			board.paste(m_apple);
			board.paste(snake);

			stringstream ss;
			board.print(ss);
			Logger::WriteMessage(ss.str().c_str());

			Assert::IsTrue(board[1][2] == CELL::APPLE);
			Assert::IsTrue(board[0][0] == CELL::TAIL);
			Assert::IsTrue(board[0][1] == CELL::TAIL);
			Assert::IsTrue(board[0][2] == CELL::HEAD);
		}
	};
}