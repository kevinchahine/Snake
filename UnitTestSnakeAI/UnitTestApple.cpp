#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>

#include <SnakeAI/Apple.h>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSnakeAI
{
	TEST_CLASS(UnitTestPosition)
	{
	public:

		TEST_METHOD(Constructors)
		{
			Apple apple(4, 4);

			Assert::IsTrue(apple.row() == 0);
			Assert::IsTrue(apple.col() == 0);
		}

		TEST_METHOD(MoveTo)
		{
			Apple apple(4, 4);

			apple.moveTo(1, 2);
			Assert::IsTrue(apple.row() == 1);
			Assert::IsTrue(apple.col() == 2);

			apple.moveTo(4, 4);
			stringstream ss;
			ss << '<' << apple.row() << ", " << apple.col() << ">\n";
			Logger::WriteMessage(ss.str().c_str());
			Assert::IsTrue(apple.row() == 3);
			Assert::IsTrue(apple.col() == 3);
		}

		TEST_METHOD(moveRandom)
		{
			Apple apple(4, 4);

			apple.moveRandom();
			Assert::IsTrue(apple.row() < 4);
			Assert::IsTrue(apple.col() < 4);
		}
	};
}

