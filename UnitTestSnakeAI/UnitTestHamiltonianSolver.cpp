#include "pch.h"
#include "CppUnitTest.h"

#include <sstream>

#include <SnakeAI/HamiltonianSolver.h>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestSnakeAI
{
	TEST_CLASS(UnitTestHamiltonianSolver)
	{
	public:

		TEST_METHOD(Constructors)
		{
			//Frontier<std::less<CostlySnakePath>> frontier;

			//Assert::IsTrue(frontier.isEmpty());
		}

		TEST_METHOD(IsSolutionFalse)
		{
			//SnakeGame game(4, 4);

			//game.reset(Position(1, 0), Position(3, 3));

			//HamiltonianSolver solver{ game };

			//Assert::IsFalse(HamiltonianSolver::isSolution(game));

			//game.growDownIfLegal();	// (2, 0)
			//game.growDownIfLegal();	// (3, 0)

			//Assert::IsFalse(HamiltonianSolver::isSolution(game));

			//game.growRightIfLegal();	// (3, 1)
			//game.growUpIfLegal();		// (2, 1)
			//game.growUpIfLegal();		// (1, 1)
			//game.growUpIfLegal();		// (0, 1)

			//Assert::IsFalse(HamiltonianSolver::isSolution(game));

			//game.growRightIfLegal();	// (0, 2)
			//game.growDownIfLegal();	// (1, 2)
			//game.growDownIfLegal();	// (2, 2)
			//game.growDownIfLegal();	// (3, 2)

			//Assert::IsFalse(HamiltonianSolver::isSolution(game));

			//game.growRightIfLegal();	// (3, 3)
			//game.growUpIfLegal();		// (2, 3)
			//game.growUpIfLegal();		// (1, 3)
			//game.growUpIfLegal();		// (0, 3)
			//
			//Assert::IsFalse(HamiltonianSolver::isSolution(game));
		}

		TEST_METHOD(IsSolutionTrue)
		{
			SnakeGame game(4, 4);

			game.reset(Position(1, 0), Position(3, 3));

			HamiltonianSolver solver{ game };

			Assert::IsFalse(HamiltonianSolver::isSolution(game));

			//game.growDownIfLegal();	// (2, 0)
			//game.growDownIfLegal();	// (3, 0)
			//
			//Assert::IsFalse(HamiltonianSolver::isSolution(game));
			//
			//game.growRightIfLegal();	// (3, 1)
			//game.growUpIfLegal();		// (2, 1)
			//game.growUpIfLegal();		// (1, 1)
			//
			//Assert::IsFalse(HamiltonianSolver::isSolution(game));
			//
			//game.growRightIfLegal();	// (1, 2)
			//game.growDownIfLegal();	// (2, 2)
			//game.growDownIfLegal();	// (3, 2)
			//
			//Assert::IsFalse(HamiltonianSolver::isSolution(game));
			//
			//game.growRightIfLegal();	// (3, 3)
			//game.growUpIfLegal();		// (2, 3)
			//game.growUpIfLegal();		// (1, 3)
			//game.growUpIfLegal();		// (0, 3)
			//
			//Assert::IsFalse(HamiltonianSolver::isSolution(game));
			//
			//game.growLeftIfLegal();	// (0, 2)
			//
			//Assert::IsFalse(HamiltonianSolver::isSolution(game));
			//
			//game.growLeftIfLegal();	// (0, 1)
			//
			//Assert::IsTrue(HamiltonianSolver::isSolution(game));
		}

		TEST_METHOD(CreateSolution)
		{
		}
	};
}