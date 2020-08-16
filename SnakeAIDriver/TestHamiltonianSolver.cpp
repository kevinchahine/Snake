#include "TestHamiltonianSolver.h"

void snake::test::generateSolution()
{
	Snake snake(4, 4);
	snake.resetHeadAt(Position(1, 1));

	/*	. v . .
		. o . .
		. . . .
		. . . .		*/

	snake.growDownFast();
	snake.growRightFast();
	snake.growUpFast();
	snake.growUpFast();

	/*	. v o .
		. v ^ .
		. > ^ .
		. . . .
	*/

	snake.growRightFast();
	snake.growDownFast();
	snake.growDownFast();
	snake.growDownFast();
	snake.growLeftFast();
	snake.growLeftFast();
	snake.growLeftFast();
	snake.growUpFast();
	snake.growUpFast();
	snake.growUpFast();

	Board board(snake.getNRows(), snake.getNCols());
	board.paste(snake);
	board.print();

	//auto pathBoard = HamiltonianSolver::generateSolution(snake);

	//pathBoard.print();
}
