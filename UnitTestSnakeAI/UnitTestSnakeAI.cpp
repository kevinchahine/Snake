#include "pch.h"
#include "CppUnitTest.h"

#include <SnakeAI/AIController.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSnakeAI
{
	TEST_CLASS(UnitTestSnakeAI)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Snake snake{ 4, 4 };
			
			snake.resetHeadAt(Position(2, 2));

			Assert::IsTrue(snake.head() == Position(2, 2));
		}
	};
}
