#include "SnakeState.h"

SnakeState::SnakeState(size_t boardHeight, size_t boardWidth) :
	gameState{ GAME_STATE::CONTINUE },
	board{ boardHeight, boardWidth },
	snake{ boardHeight, boardWidth },
	apple{ boardHeight, boardWidth }
{
	init();
}

bool SnakeState::operator==(const SnakeState& left) const
{
	return board.hashValue() == board.hashValue();
}

bool SnakeState::operator<(const SnakeState& left) const
{
	return board.hashValue() < left.board.hashValue();
}

size_t SnakeState::operator()() const
{
	// return the hash value (functor) of board.
	// make sure board is up to date with the snake and apple
	return board.hashValue();
}

void SnakeState::init()
{
	reset();
}

void SnakeState::reset()
{
	gameState = GAME_STATE::CONTINUE;
	board.clear();

	// --- Place snake in a random position ---
	snake.resetHeadRandom();
	board.paste(snake);

	// --- Place apple in a random position ---
	// --- Will make sure it doesn't get placed on snake ---
	moveAppleRandomly();
	board.paste(apple);
}

SnakeState::GAME_STATE SnakeState::moveSnake(char controlInput)
{
	switch (tolower(controlInput)) {
	case 'w':	this->moveUpIfLegal();		break;
	case 's':	this->moveDownIfLegal();	break;
	case 'a':	this->moveLeftIfLegal();	break;
	case 'd':	this->moveRightIfLegal();	break;
	default:
		std::stringstream ss;
		ss << __FUNCTION__ << ": controlInput = " << controlInput
			<< " is not a legal move";
		throw std::exception(ss.str().c_str());
	}

	return gameState;
}

const Board::index& SnakeState::getNRows() const
{
	return board.getNRows();
}

const Board::index& SnakeState::getNCols() const
{
	return board.getNCols();
}

size_t SnakeState::getNCells() const
{
	return board.getNCells();
}

SnakeState::GAME_STATE SnakeState::calcGameState()
{
	// Did we bite our selves?
	if (snake.bitItself()) {
		std::cout << "Ouch. Game over\n";
		gameState = GAME_STATE::GAME_OVER;
	}
	// Did we hit a wall?
	// Is it even possible to hit a wall? Hitting a wall is not a legal move
	else if (false) {
		std::cout << "Hit a wall\n";
		gameState = GAME_STATE::GAME_OVER;
	}
	// Did we eat the apple?
	else if (snake.head() == apple) {
		// Yes. We need to move apple to a random location 
		// but not on the snake itself. 
		// TODO: This will not be efficient for big boards.
		std::cout << "Yum apples\n";
		gameState = GAME_STATE::CONTINUE;
		do {
			apple.moveRandom();
		} while (snake == apple);
	}

	// Did we win? Did we cover every cell?
	// *** Not else if, because we can eat an apple and win at the same time.
	if (snake.size() == board.num_elements()) {
		// Yes we won.
		std::cout << "Congratulations you won.\n";
		gameState = GAME_STATE::WON;
		return gameState;
	}
	
	return GAME_STATE();
}

SnakeState::GAME_STATE SnakeState::getCurrentState() const
{
	return this->gameState;
}

const Board& SnakeState::getBoard() const
{
	return board;
}

const Snake& SnakeState::getSnake() const
{
	return snake;
}

const Apple& SnakeState::getApple() const
{
	return apple;
}

// ========================== IS MOVE LEGAL ===================================

bool SnakeState::isMoveUpLegal() const
{
	return snake.isMoveUpLegal();
}

bool SnakeState::isMoveDownLegal() const
{
	return snake.isMoveDownLegal();
}

bool SnakeState::isMoveLeftLegal() const
{
	return snake.isMoveLeftLegal();
}

bool SnakeState::isMoveRightLegal() const
{
	return snake.isMoveRightLegal();
}

bool SnakeState::isMoveLegal(char direction) const
{
	return snake.isMoveLegal(direction);
}

char SnakeState::getAnyLegalMove() const
{
	return snake.getAnyLegalMove();
}

// ========================== IS MOVE SAFE ====================================

bool SnakeState::isMoveUpSafe() const
{
	Position head = snake.head();

	return
		board(head.upOne()) != CELL::TAIL;
}

bool SnakeState::isMoveDownSafe() const
{
	Position head = snake.head();

	return
		board(head.downOne()) != CELL::TAIL;
}

bool SnakeState::isMoveLeftSafe() const
{
	Position head = snake.head();

	return
		board(head.leftOne()) != CELL::TAIL;
}

bool SnakeState::isMoveRightSafe() const
{
	Position head = snake.head();

	return
		board(head.rightOne()) != CELL::TAIL;
}

bool SnakeState::isMoveSafe(char direction) const
{
	switch (direction)
	{
	case 'w':	return isMoveUpSafe();
	case 's':	return isMoveDownSafe();
	case 'a':	return isMoveLeftSafe();
	case 'd':	return isMoveRightSafe();
	default:	return false;
	/*default:
		std::stringstream ss;
		ss << __FUNCTION__ << ": parameter direction = " << direction
			<< " is not a possible move.";
		throw std::exception(ss.str().c_str());*/
	}
}

char SnakeState::getAnySafeMove() const
{
	if (isMoveUpSafe()) return 'w';
	else if (isMoveDownSafe()) return 's';
	else if (isMoveLeftSafe()) return 'a';
	else if (isMoveRightSafe()) return 'd';
	else {
		std::stringstream ss;
		ss << __FUNCTION__ << ": No move was found to be safe.";
		throw std::exception(ss.str().c_str());
	}
}

char SnakeState::getAnyLegalAndSafeMove() const
{
	if      (isMoveUpLegal() && isMoveUpSafe()) return 'w';
	else if (isMoveDownLegal() && isMoveDownSafe()) return 's';
	else if (isMoveLeftLegal() && isMoveLeftSafe()) return 'a';
	else if (isMoveRightLegal() && isMoveRightSafe()) return 'd';
	else {
		// No legal and safe move was found. Our only option is to
		// return any legal move which will end up making the snake
		// bit itself.
		return getAnyLegalMove();
	}
}

void SnakeState::moveUpFast()
{
	Position tailTip = snake.tailTip();

	if (snake.head().upOne() == apple) {
		snake.growUpFast();
		std::cout << "Yum apples---\n";
		moveAppleRandomly();
	}
	else {
		snake.moveUpFast();
		board(tailTip) = CELL::EMPTY;
	}

	board(snake.head()) = CELL::HEAD;
	board(snake.neck()) = CELL::TAIL;

	calcGameState();
}

void SnakeState::moveDownFast()
{
	Position tailTip = snake.tailTip();

	if (snake.head().downOne() == apple) {
		std::cout << "Yum apples---\n";
		snake.growDownFast();
		moveAppleRandomly();
	}
	else {
		snake.moveDownFast();
		board(tailTip) = CELL::EMPTY;
	}

	board(snake.head()) = CELL::HEAD;
	board(snake.neck()) = CELL::TAIL;

	calcGameState();
}

void SnakeState::moveLeftFast()
{
	Position tailTip = snake.tailTip();

	if (snake.head().leftOne() == apple) {
		std::cout << "Yum apples---\n";
		snake.growLeftFast();
		moveAppleRandomly();
	}
	else {
		snake.moveLeftFast();
		board(tailTip) = CELL::EMPTY;
	}

	board(snake.head()) = CELL::HEAD;
	board(snake.neck()) = CELL::TAIL;

	calcGameState();
}

void SnakeState::moveRightFast()
{
	Position tailTip = snake.tailTip();

	if (snake.head().rightOne() == apple) {
		std::cout << "Yum apples---\n";
		snake.growRightFast();
		moveAppleRandomly();
	}
	else {
		snake.moveRightFast();
		board(tailTip) = CELL::EMPTY;
	}

	board(snake.head()) = CELL::HEAD;
	board(snake.neck()) = CELL::TAIL;

	calcGameState();
}

void SnakeState::moveFast(char direction)
{
	switch (direction)
	{
	case 'w': moveUpFast();		break;
	case 's': moveDownFast();	break;
	case 'a': moveLeftFast();	break;
	case 'd': moveRightFast();	break;
	default:
		std::stringstream ss;
		ss << __FUNCTION__ << ": parameter move = " << direction
			<< "Is not a possible move.";
		throw std::exception(ss.str().c_str());
	}
}

void SnakeState::moveUpIfLegal()
{
	if (isMoveUpLegal())
		moveUpFast();
}

void SnakeState::moveDownIfLegal()
{
	if (isMoveDownLegal())
		moveDownFast();
}

void SnakeState::moveLeftIfLegal()
{
	if (isMoveLeftLegal())
		moveLeftFast();
}

void SnakeState::moveRightIfLegal()
{
	if (isMoveRightLegal())
		moveRightFast();
}

void SnakeState::moveIfLegal(char direction)
{
	switch (direction)
	{
	case 'w': moveUpIfLegal();		break;
	case 's': moveDownIfLegal();	break;
	case 'a': moveLeftIfLegal();	break;
	case 'd': moveRightIfLegal();	break;
	default:
		std::stringstream ss;
		ss << __FUNCTION__ << ": parameter move = " << direction
			<< "Is not a possible move.";
		throw std::exception(ss.str().c_str());
	}
}

void SnakeState::moveAppleRandomly()
{
	// --- Remove apple from cell, but only if it is occupied by an apple ---
	// This way in case cell is occupied by the snake's head, we won't
	// accidentally remove its head.
	if (board(apple) == CELL::APPLE) {
		board(apple) = CELL::EMPTY;
	}
	
	// --- Move apple to a random empty location ---
	// Create a set of all empty spaces
	std::vector<Position> emptyCells;
	emptyCells.reserve(board.getNCells() - snake.size());

	for (size_t row = 0; row < board.getNRows(); row++) {
		for (size_t col = 0; col < board.getNCols(); col++) {
			if (board[row][col] == CELL::EMPTY) {
				emptyCells.emplace_back(row, col);
			}
		}
	}

	// Pick a random empty cell
	int randomNumber = rand() % emptyCells.size();
	Position emptyCell = emptyCells.at(randomNumber);

	// Move apple to the random empty cell
	apple.moveTo(emptyCell);

	// Place the apple on the board.
	board(apple) = CELL::APPLE;
}
