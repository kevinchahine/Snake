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
	};
}