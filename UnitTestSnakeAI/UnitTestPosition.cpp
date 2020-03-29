#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>

#include <SnakeAI/Position.h>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSnakeAI
{
	TEST_CLASS(UnitTestPosition)
	{
	public:

		TEST_METHOD(Constructors)
		{
			Position defaultP;
			Position fullP(1, 2);
			
			stringstream ss;
			ss << '<' << defaultP.row() << ", " << defaultP.col() << '>';
			Logger::WriteMessage(ss.str().c_str());
			Assert::IsTrue(defaultP.row() == 0, L"Row does not match");
			Assert::IsTrue(defaultP.col() == 0, L"Col does not match");
			
			Assert::IsTrue(fullP.row() == 1);
			Assert::IsTrue(fullP.col() == 2);

			Position copyP(fullP.downOne());

			Assert::IsTrue(copyP.row() == 2);
			Assert::IsTrue(copyP.col() == 2);
		}

		TEST_METHOD(EqualToOperator)
		{
			Position a{ 4, 4 };
			Position b{ 5, 5 };
			Position c{ 4, 6 };
			Position d{ 6, 4 };
			Position e{ 4, 4 };

			Assert::IsFalse(a == b);
			Assert::IsFalse(a == c);
			Assert::IsFalse(a == d);
			Assert::IsTrue(a == e);
		}

		TEST_METHOD(MovementFunctions)
		{
			Position pos{ 3, 3 };

			pos = pos.upOne();
			Assert::IsTrue(pos.row() == 2);
			Assert::IsTrue(pos.col() == 3);

			pos = pos.downOne();
			Assert::IsTrue(pos.row() == 3);
			Assert::IsTrue(pos.col() == 3);
			
			pos = pos.leftOne();
			Assert::IsTrue(pos.row() == 3);
			Assert::IsTrue(pos.col() == 2);

			pos = pos.rightOne();
			Assert::IsTrue(pos.row() == 3);
			Assert::IsTrue(pos.col() == 3);
		}
	};
}

