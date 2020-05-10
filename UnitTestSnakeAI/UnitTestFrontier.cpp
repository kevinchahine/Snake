#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>

#include <SnakeAI/Frontier.h>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSnakeAI
{
	TEST_CLASS(UnitTestFrontier)
	{
	public:

		TEST_METHOD(Constructors)
		{
			Frontier frontier;

			Assert::IsTrue(frontier.isEmpty());
		}

	private:
		
	};
}

