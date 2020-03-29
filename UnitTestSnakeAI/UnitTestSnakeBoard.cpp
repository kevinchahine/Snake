#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>

#include <SnakeAI/SnakeState.h>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSnakeAI
{
	TEST_CLASS(UnitTestSnakeBoard)
	{
	public:
		TEST_METHOD(Constructors)
		{
			SnakeBoard board(4, 5);

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
			SnakeBoard board{ 4, 6 };

			Assert::IsTrue(board.getNRows() == 4);
			Assert::IsTrue(board.getNCols() == 6);
		}

		TEST_METHOD(HashValue1)
		{
			SnakeBoard board(4, 4);

			/*
				
			*/
		}
		TEST_METHOD(HashValue)
		{
			SnakeBoard board(4, 4);

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
	};
}