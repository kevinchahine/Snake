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
			Apple m_apple(4, 4);

			Assert::IsTrue(m_apple.row() == 0);
			Assert::IsTrue(m_apple.col() == 0);
		}

		TEST_METHOD(MoveTo)
		{
			Apple m_apple(4, 4);

			m_apple.moveTo(1, 2);
			Assert::IsTrue(m_apple.row() == 1);
			Assert::IsTrue(m_apple.col() == 2);

			m_apple.moveTo(4, 4);
			stringstream ss;
			ss << '<' << m_apple.row() << ", " << m_apple.col() << ">\n";
			Logger::WriteMessage(ss.str().c_str());
			Assert::IsTrue(m_apple.row() == 3);
			Assert::IsTrue(m_apple.col() == 3);
		}

		TEST_METHOD(moveRandom)
		{
			Apple m_apple(4, 4);

			m_apple.moveRandom();
			Assert::IsTrue(m_apple.row() < 4);
			Assert::IsTrue(m_apple.col() < 4);
		}
	};
}

