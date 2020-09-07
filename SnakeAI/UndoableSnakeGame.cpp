#include "UndoableSnakeGame.h"

using namespace std;

#include <opencv2/opencv.hpp>

UndoableGame::UndoableGame(size_t boardHeight, size_t boardWidth) :
	m_board{ boardHeight, boardWidth },
	m_snake{ boardHeight, boardWidth },
	m_apple{  }
{
	m_board.setSnake(m_snake);
	m_board.setApple(m_apple);

	init();
}

UndoableGame::UndoableGame(const SnakeGame& snakeGame) :
	m_board(snakeGame.board()),
	m_snake(snakeGame.snake()),
	m_apple(snakeGame.getApple())
{
}

bool UndoableGame::operator==(const UndoableGame& left) const
{
	return m_board.hashValue() == m_board.hashValue();
}

bool UndoableGame::operator<(const UndoableGame& left) const
{
	return m_board.hashValue() < left.m_board.hashValue();
}

size_t UndoableGame::operator()() const
{
	// return the hash value (functor) of board.
	// make sure board is up to date with the snake and m_apple
	return m_board.hashValue();
}

void UndoableGame::init()
{
	reset();

	print();
}

void UndoableGame::reset()
{
	m_board.clear();

	// --- Place snake in a random position ---
	m_snake.resetHeadRandom();
	m_apple.reset();
	m_board.paste(m_snake);

	// --- Place m_apple in a random position ---
	// --- Will make sure it doesn't get placed on snake ---
	// --- Make sure this is called after snake.resetXXX() ---
	moveAppleRandomly();
}

void UndoableGame::reset(const Position& snakeStartingPos, const Position& appleStartingPos)
{
	m_board.clear();

	// --- Place snake in a random position ---
	m_snake.resetHeadAt(snakeStartingPos);
	m_apple.reset();
	m_board.paste(m_snake);

	// --- Place m_apple in a random position ---
	// --- Will make sure it doesn't get placed on snake ---
	moveAppleTo(appleStartingPos);
}

const Board::index& UndoableGame::getNRows() const
{
	return m_board.getNRows();
}

const Board::index& UndoableGame::getNCols() const
{
	return m_board.getNCols();
}

size_t UndoableGame::getNCells() const
{
	return m_board.getNCells();
}

UndoableGame::GAME_STATE UndoableGame::calcGameState()
{
	GAME_STATE state = GAME_STATE::CONTINUE;

	// Did we bite our selves?
	if (m_snake.isBittingItself()) {
		state = GAME_STATE::GAME_OVER;
	}
	// Did we hit a wall?
	// Is it even possible to hit a wall? Hitting a wall is not a legal move and will cause a runtime error
	// else if (false) {
	// 	m_gameState = GAME_STATE::GAME_OVER;
	// }
	// Did we eat the m_apple?
	else if (m_snake.head() == m_apple) {
		// Yes. We need to move m_apple to a random location 
		state = GAME_STATE::CONTINUE;
	}

	// Did we win? Did we cover every cell?
	// *** Not else if, because we have to eat the last m_apple to win ***
	if (m_snake.size() == m_board.num_elements()) {
		// Yes we won.
		state = GAME_STATE::WON;
	}

	return state;
}

const Board& UndoableGame::board() const
{
	return m_board;
}

const Snake& UndoableGame::snake() const
{
	return m_snake;
}

const Apple& UndoableGame::getApple() const
{
	return m_apple;
}

// ========================== IS MOVE LEGAL ===================================

bool UndoableGame::isMoveUpLegal() const
{
	return m_snake.isMoveUpLegal();
}

bool UndoableGame::isMoveDownLegal() const
{
	return m_snake.isMoveDownLegal();
}

bool UndoableGame::isMoveLeftLegal() const
{
	return m_snake.isMoveLeftLegal();
}

bool UndoableGame::isMoveRightLegal() const
{
	return m_snake.isMoveRightLegal();
}

bool UndoableGame::isUndoLegal() const
{
	/*cout << "m_snake : " << m_snake.isUndoLegal() << '\n'
		<< "m_apple : " << m_apple.isUndoLegal() << '\n';*/
	return m_snake.isUndoLegal() && m_apple.isUndoLegal();
}

bool UndoableGame::isMoveLegal(char direction) const
{
	// Are we doing an undo?
	if (direction != 'z') {
		// No undo just a regular move
		return m_snake.isMoveLegal(direction);
	}
	else {
		// Yes its an undo
		return isUndoLegal();
	}
}

char UndoableGame::getAnyLegalMove() const
{
	return m_snake.getAnyLegalMove();
}

// ========================== IS MOVE SAFE ====================================

bool UndoableGame::isMoveUpSafe() const
{
	Position head = m_snake.head();

	return
		m_board(head.upOne()) != CELL::TAIL;
}

bool UndoableGame::isMoveDownSafe() const
{
	Position head = m_snake.head();

	return
		m_board(head.downOne()) != CELL::TAIL;
}

bool UndoableGame::isMoveLeftSafe() const
{
	Position head = m_snake.head();

	return
		m_board(head.leftOne()) != CELL::TAIL;
}

bool UndoableGame::isMoveRightSafe() const
{
	Position head = m_snake.head();

	return
		m_board(head.rightOne()) != CELL::TAIL;
}

bool UndoableGame::isMoveSafe(char direction) const
{
	switch (direction)
	{
	case 'w':	return isMoveUpSafe();
	case 's':	return isMoveDownSafe();
	case 'a':	return isMoveLeftSafe();
	case 'd':	return isMoveRightSafe();
	case 'z':	return isUndoLegal();
	default:	return false;
		/*default:
			std::stringstream ss;
			ss << __FUNCTION__ << ": parameter direction = " << direction
				<< " is not a possible move.";
			throw std::exception(ss.str().c_str());*/
	}
}

char UndoableGame::getAnySafeMove() const
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

char UndoableGame::getAnyLegalAndSafeMove() const
{
	if (isMoveUpLegal() && isMoveUpSafe()) return 'w';
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

boost::container::static_vector<char, 3> UndoableGame::getAllLegalAndSafeMoves() const
{
	boost::container::static_vector<char, 3> moves;

	if (isMoveUpLegal() && isMoveUpSafe())			moves.push_back('w');
	if (isMoveDownLegal() && isMoveDownSafe())		moves.push_back('s');
	if (isMoveLeftLegal() && isMoveLeftSafe())		moves.push_back('a');
	if (isMoveRightLegal() && isMoveRightSafe())	moves.push_back('d');

	return moves;
}

// ========================== MOVE FAST =======================================

void UndoableGame::moveUpFast()
{
	Position tailTip = m_snake.tailTip();

	if (m_snake.head().upOne() == m_apple) {
		m_snake.growUpFast();
		moveAppleRandomly();
	}
	else {
		m_snake.moveUpFast();
		m_board(tailTip) = CELL::EMPTY;
	}

	m_board(m_snake.head()) = CELL::HEAD;
	m_board(m_snake.neck()) = CELL::TAIL;

	m_apple.logPosition();

	//m_board.clear();
	//m_board.paste(m_snake);
	//m_board.paste(m_apple);
}

void UndoableGame::moveDownFast()
{
	Position tailTip = m_snake.tailTip();

	if (m_snake.head().downOne() == m_apple) {
		m_snake.growDownFast();
		moveAppleRandomly();
	}
	else {
		m_snake.moveDownFast();
		m_board(tailTip) = CELL::EMPTY;
	}

	m_board(m_snake.head()) = CELL::HEAD;
	m_board(m_snake.neck()) = CELL::TAIL;

	m_apple.logPosition();

	//m_board.clear();
	//m_board.paste(m_snake);
	//m_board.paste(m_apple);
}

void UndoableGame::moveLeftFast()
{
	Position tailTip = m_snake.tailTip();

	if (m_snake.head().leftOne() == m_apple) {
		m_snake.growLeftFast();
		moveAppleRandomly();
	}
	else {
		m_snake.moveLeftFast();
		m_board(tailTip) = CELL::EMPTY;
	}

	m_board(m_snake.head()) = CELL::HEAD;
	m_board(m_snake.neck()) = CELL::TAIL;

	m_apple.logPosition();

	//m_board.clear();
	//m_board.paste(m_snake);
	//m_board.paste(m_apple);
}

void UndoableGame::moveRightFast()
{
	Position tailTip = m_snake.tailTip();

	if (m_snake.head().rightOne() == m_apple) {
		m_snake.growRightFast();
		moveAppleRandomly();
	}
	else {
		m_snake.moveRightFast();
		m_board(tailTip) = CELL::EMPTY;
	}

	m_board(m_snake.head()) = CELL::HEAD;
	m_board(m_snake.neck()) = CELL::TAIL;

	m_apple.logPosition();

	//m_board.clear();
	//m_board.paste(m_snake);
	//m_board.paste(m_apple);
}

void UndoableGame::undoFast()
{
	// Must be done before undoing snake 
	m_board(m_snake.head()) = CELL::EMPTY;

	// Move snake back to where it was before
	m_snake.undoFast();
	m_board(m_snake.head()) = CELL::HEAD;
	m_board(m_snake.tailTip()) = CELL::TAIL;

	// Move apple back to where it was before
	m_apple.undoFast();
	m_board(m_apple) = CELL::APPLE;

	//m_board.clear();
	//m_board.paste(m_snake);
	//m_board.paste(m_apple);
}

void UndoableGame::moveFast(char direction)
{
	switch (direction)
	{
	case 'w': moveUpFast();		break;
	case 's': moveDownFast();	break;
	case 'a': moveLeftFast();	break;
	case 'd': moveRightFast();	break;
	case 'z': undoFast();		break;
	default:
		std::stringstream ss;
		ss << __FUNCTION__ << ": parameter move = " << direction
			<< "Is not a possible move.";
		throw std::exception(ss.str().c_str());
	}
}

void UndoableGame::moveUpIfLegal()
{
	if (isMoveUpLegal())
		moveUpFast();
}

void UndoableGame::moveDownIfLegal()
{
	if (isMoveDownLegal())
		moveDownFast();
}

void UndoableGame::moveLeftIfLegal()
{
	if (isMoveLeftLegal())
		moveLeftFast();
}

void UndoableGame::moveRightIfLegal()
{
	if (isMoveRightLegal())
		moveRightFast();
}

void UndoableGame::undoIfLegal()
{
	if (isUndoLegal())
		undoFast();
}

void UndoableGame::moveIfLegal(char direction)
{
	switch (direction)
	{
	case 'w': moveUpIfLegal();		break;
	case 's': moveDownIfLegal();	break;
	case 'a': moveLeftIfLegal();	break;
	case 'd': moveRightIfLegal();	break;
	case 'z': undoIfLegal();		break;
	default:
		std::stringstream ss;
		ss << __FUNCTION__ << ": parameter move = " << direction
			<< "Is not a possible move.";
		throw std::exception(ss.str().c_str());
	}
}

void UndoableGame::undoMoveIfLegal(bool appleAlso)
{
	if (isUndoLegal()) {
		undoFast();
	}
}

void UndoableGame::moveAppleRandomly()
{
	// --- Remove m_apple from cell, but only if it is occupied by an m_apple ---
	// This way in case cell is occupied by the snake's head, we won't
	// accidentally remove its head.
	if (m_board(m_apple) == CELL::APPLE) {
		m_board(m_apple) = CELL::EMPTY;
	}

	// --- Move m_apple to a random empty location ---
	// Create a set of all empty spaces
	std::vector<Position> emptyCells;
	emptyCells.reserve(m_board.getNCells() - m_snake.size());

	for (size_t row = 0; row < m_board.getNRows(); row++) {
		for (size_t col = 0; col < m_board.getNCols(); col++) {
			if (m_board[row][col] == CELL::EMPTY) {
				emptyCells.emplace_back(row, col);
			}
		}
	}

	// Pick a random empty cell (will fail to division by 0 if there are no empty cells)
	int randomNumber = rand() % emptyCells.size();
	Position emptyCell = emptyCells.at(randomNumber);

	// Move m_apple to the random empty cell
	m_apple.moveTo(emptyCell);

	// Place the m_apple on the board.
	m_board(m_apple) = CELL::APPLE;
}

void UndoableGame::moveAppleTo(const Position& newApplePos)
{
	// --- Remove m_apple from cell, but only if it is occupied by an m_apple ---
	// This way in case cell is occupied by the snake's head, we won't
	// accidentally remove its head.
	if (m_board(m_apple) == CELL::APPLE) {
		m_board(m_apple) = CELL::EMPTY;
	}

	// --- Move m_apple to the new location (even if it is on the snake itself) ---
	m_apple.moveTo(newApplePos);

	// Place the m_apple on the board.
	m_board(m_apple) = CELL::APPLE;
}

void UndoableGame::print(ostream& os) const
{
	m_snake.print(os);
	m_apple.print(os);
	m_board.print(os);
}
