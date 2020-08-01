#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>
#include <vector>

#include <SnakeAI/Snake.h>
#include <SnakeAI/SnakeBoard.h>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSnakeAI
{
	TEST_CLASS(UnitTestSnake)
	{
	public:

		TEST_METHOD(Constructors)
		{
			Snake snake(4, 4);

			Assert::IsTrue(snake.size() > 0);

			Assert::IsTrue(snake.head().row() < 4);
			Assert::IsTrue(snake.head().col() < 4);
		}

		TEST_METHOD(EqualTo)
		{
			Snake snake(4, 4);

			// Explicitly set each cell of the snake to look like this
			/*
				s s . .
				s s . .
				. . . . 
				. . . . 
			*/
			snake.clear();
			snake.push_back(Position(0, 0));
			snake.push_back(Position(1, 0));
			snake.push_back(Position(1, 1));
			snake.push_back(Position(0, 1));

			// Cells on the snake
			Assert::IsTrue(snake == Position(0, 0));
			Assert::IsTrue(snake == Position(1, 0));
			Assert::IsTrue(snake == Position(1, 1));
			Assert::IsTrue(snake == Position(0, 1));

			// Cells not on the snake
			Assert::IsFalse(snake == Position(0, 2));
			Assert::IsFalse(snake == Position(0, 3));
			Assert::IsFalse(snake == Position(1, 2));
			Assert::IsFalse(snake == Position(1, 3));

			Assert::IsFalse(snake == Position(2, 0));
			Assert::IsFalse(snake == Position(2, 1));
			Assert::IsFalse(snake == Position(2, 2));
			Assert::IsFalse(snake == Position(2, 3));

			Assert::IsFalse(snake == Position(3, 0));
			Assert::IsFalse(snake == Position(3, 1));
			Assert::IsFalse(snake == Position(3, 2));
			Assert::IsFalse(snake == Position(3, 3));
		}

		TEST_METHOD(BitItself)
		{
			Snake snake(4, 4);

			// Explicitly remove snake
			snake.clear();

			snake.push_back(Position(1, 0));
			Assert::IsFalse(snake.bitItself());

			snake.growRightFast();
			Assert::IsFalse(snake.bitItself());

			snake.growDownFast();
			Assert::IsFalse(snake.bitItself());

			snake.growLeftFast();
			Assert::IsFalse(snake.bitItself());

			snake.growUpFast();			// Bit itself
			Assert::IsTrue(snake.bitItself());
		}

		TEST_METHOD(IsMoveLegal)
		{
			Snake snake(4, 4);

			snake.clear();
			snake.push_back(Position(0, 0));
			snake.push_back(Position(0, 1));	
			// --- neck is at <0, 0> head is at <0, 1> ---
			/*
				n h . .
				. . . .
				. . . .
				. . . .
			*/

			Assert::IsFalse(snake.isMoveUpLegal());
			Assert::IsFalse(snake.isMoveLeftLegal());
			Assert::IsTrue(snake.isMoveDownLegal());
			Assert::IsTrue(snake.isMoveRightLegal());

			snake.moveDownFast();
			snake.moveDownFast();
			snake.moveDownFast();

			/*
				. . . . 
				. . . .
				. n . . 
				. h . .
			*/

			Assert::IsFalse(snake.isMoveUpLegal());
			Assert::IsTrue(snake.isMoveLeftLegal());
			Assert::IsFalse(snake.isMoveDownLegal());
			Assert::IsTrue(snake.isMoveRightLegal());

			snake.moveLeftFast();

			/*
				. . . . 
				. . . .
				. n . . 
				. h . .
			*/

			Assert::IsTrue(snake.isMoveUpLegal());
			Assert::IsFalse(snake.isMoveLeftLegal());
			Assert::IsFalse(snake.isMoveDownLegal());
			Assert::IsFalse(snake.isMoveRightLegal());

		}

		TEST_METHOD(IsOnSnake)
		{
			// Already tested by EqualTo
			Assert::IsTrue(true);
		}

		TEST_METHOD(Head)
		{
			Snake snake(4, 4);

			snake.resetHeadAt(Position(2, 2));

			Assert::IsTrue(snake.head() == Position(2, 2));
		}
		
		TEST_METHOD(Neck)
		{
			Snake snake(4, 4);

			// Explicitly remove snake
			snake.clear();
			// Place snakes head
			snake.push_back(Position(1, 1));
			// Place snakes neck
			snake.push_front(Position(1, 0));
			// --- Snake is pointing right ---

			Assert::IsTrue(snake.neck() == Position(1, 0));
		}

		TEST_METHOD(TailTip)
		{
			Snake snake(4, 4);

			// Explicitly remove snake
			snake.clear();
			// Place snakes head
			snake.push_back(Position(1, 1));
			// Place snakes neck
			snake.push_front(Position(1, 0));
			// --- Snake is pointing right ---

			Assert::IsTrue(snake.tailTip() == Position(1, 0));

			snake.push_front(Position(0, 0));
			Assert::IsFalse(snake.tailTip() == Position(1, 0));
			Assert::IsTrue(snake.tailTip() == Position(0, 0));
		}

		TEST_METHOD(HashValue)
		{
			Snake snake(4, 4);
			Board board(4, 4);

			/* Start snake in this position
			t h . .
			. . . .
			. . . .
			. . . .
			*/
			snake.resetHeadAt(Position(0, 0));
			snake.moveRightFast();
			Assert::IsTrue(snake.hashValue() == 5);

			snake.growRightFast();
			snake.growRightFast();
			Assert::IsTrue(snake.hashValue() == 30);

			snake.growDownFast();
			snake.growLeftFast();
			snake.growLeftFast();
			snake.growLeftFast();
			Assert::IsTrue(snake.hashValue() == 194);

			
			snake.growDownFast();
			snake.growRightFast();
			snake.growRightFast();
			snake.growRightFast();
			Assert::IsTrue(snake.hashValue() == 640);

			snake.growDownFast();
			snake.growLeftFast();
			snake.growLeftFast();
			snake.growLeftFast();
			Assert::IsTrue(snake.hashValue() == 1476);

			stringstream ss;
			board.paste(snake);
			board.print(ss);
			ss << "hash value = " << snake.hashValue() << '\n';
			Logger::WriteMessage(ss.str().c_str());
			
			Assert::IsTrue(true);
		}

		TEST_METHOD(UndoMove)
		{
			Snake snake(4, 4);
			snake.resetHeadAt(Position(1, 1));	// Head is at (1, 1)
			snake.moveRightFast();				// Head is at (1, 2)
			snake.moveRightFast();				// Head is at (1, 3)
			snake.undoMoveSafe(Position(1, 1));		// Head is at (1, 2)

			Assert::IsTrue(snake.head() == Position(1, 2));
			Assert::IsTrue(snake.tailTip() == Position(1, 1));
			Assert::IsTrue(snake.size() == size_t(2));
		}

		TEST_METHOD(UndoGrow)
		{
			Snake snake(4, 4);					// Tail		Head	Size
			snake.resetHeadAt(Position(1, 1));	// (?, ?)	(1, 1)	2
			snake.moveRightFast();				// (1, 1)	(1, 2)	2
			snake.growRightFast();				// (1, 1)	(1, 3)	3
			snake.undoMoveSafe(Position(1, 1));		// (1, 1)	(1, 2)	2

			Assert::IsTrue(snake.head() == Position(1, 2));
			Assert::IsTrue(snake.tailTip() == Position(1, 1));
			Assert::IsTrue(snake.size() == size_t(2));
		}
	};
}