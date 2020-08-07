#pragma once

#include <stack>
#include <set>
//#include <queue>
#include <algorithm>

#include "SolverBase.h"

class Node : public std::pair<char, SnakeGame>
{
public:
	Node(char move, const SnakeGame& m_gameState);
	Node(const Node&) = default;
	Node(Node&&) noexcept = default;
	~Node() noexcept = default;
	Node& operator=(const Node&) = default;
	Node& operator=(Node&&) = default;

	bool isGoal() const;

	char getMove() const;

	const SnakeGame& getGameState() const;
	SnakeGame& getGameState();

	bool operator==(const Node& left) const;
}; 

class DepthFirstSearchSolver : public SolverBase
{
public:
	DepthFirstSearchSolver(const SnakeGame& m_gameState);

	virtual void reset() override;

	virtual char solve() override;
	
protected:
	char depthFirstSearch(const SnakeGame & currGameState);

	void pushSafeMovesToFrontier(const SnakeGame & m_gameState);

protected:
	std::vector<Node> frontier;
	std::vector<Node> explored;
	std::stack<char> solution;
};
