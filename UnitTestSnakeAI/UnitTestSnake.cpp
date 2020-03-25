#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>

#include <SnakeAI/Snake.h>

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

			try
			{
				snake.head();
			}
			catch (const std::exception& e)
			{
				Logger::WriteMessage(e.what());
			}

			Assert::IsTrue(snake.head().row() == 0);
			Assert::IsTrue(snake.head().col() == 0);
		}
	};
}