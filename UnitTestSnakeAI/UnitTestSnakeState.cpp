#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>

#include <SnakeAI/SnakeState.h>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSnakeAI
{
	TEST_CLASS(UnitTestSnakeState)
	{
	public:
		TEST_METHOD(Dimentions) 
		{
			SnakeState snake(4, 6);

			Assert::IsTrue(snake.getNRows() == 4);
			Assert::IsTrue(snake.getNCols() == 6);
		}

		TEST_METHOD(Init)
		{
			SnakeState snake(4, 4);

			snake.init();
		}

		TEST_METHOD(UndoMove)
		{
			SnakeState game(4, 4);
			
			Position snakeStartPos = Position(1, 1);
			Position appleStartPos = Position(3, 3);

			game.reset(snakeStartPos, appleStartPos);

															// Tail		Head	Size
			game.moveRightFast();							// (1, 1)	(1, 2)	2
			game.moveRightFast();							// (1, 2)	(1, 3)	2
			game.undoMove(Position(1, 1), appleStartPos);	// (1, 1)	(1, 2)	2

			const Snake& snake = game.getSnake();
			const Apple& apple = game.getApple();
			const Board& board = game.getBoard();

			Assert::IsTrue(snake.head() == Position(1, 2));
			Assert::IsTrue(snake.tailTip() == Position(1, 1));
			Assert::IsTrue(snake.size() == 2);

			Assert::IsTrue(apple == Position(3, 3));

			// --- Top Row ---
			Assert::IsTrue(board(Position(0, 0)) == CELL::EMPTY);
			Assert::IsTrue(board(Position(0, 1)) == CELL::EMPTY);
			Assert::IsTrue(board(Position(0, 2)) == CELL::EMPTY);
			Assert::IsTrue(board(Position(0, 3)) == CELL::EMPTY);

			// --- 2nd Row ---
			Assert::IsTrue(board(Position(1, 0)) == CELL::EMPTY);
			Assert::IsTrue(board(Position(1, 1)) == CELL::TAIL);
			Assert::IsTrue(board(Position(1, 2)) == CELL::HEAD);
			Assert::IsTrue(board(Position(1, 3)) == CELL::EMPTY);

			// --- 3rd Row ---
			Assert::IsTrue(board(Position(2, 0)) == CELL::EMPTY);
			Assert::IsTrue(board(Position(2, 1)) == CELL::EMPTY);
			Assert::IsTrue(board(Position(2, 2)) == CELL::EMPTY);
			Assert::IsTrue(board(Position(2, 3)) == CELL::EMPTY);

			// --- Bottom Row ---
			Assert::IsTrue(board(Position(3, 0)) == CELL::EMPTY);
			Assert::IsTrue(board(Position(3, 1)) == CELL::EMPTY);
			Assert::IsTrue(board(Position(3, 2)) == CELL::EMPTY);
			Assert::IsTrue(board(Position(3, 3)) == CELL::APPLE);

		}
	};
}