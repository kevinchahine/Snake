#pragma once

#include <stack>
#include <set>
//#include <queue>
#include <algorithm>

#include "SolverBase.h"

class Node : public std::pair<char, SnakeState>
{
public:
	Node(char move, const SnakeState& gameState);
	Node(const Node&) = default;
	Node(Node&&) noexcept = default;
	~Node() noexcept = default;
	Node& operator=(const Node&) = default;
	Node& operator=(Node&&) = default;

	bool isGoal() const;

	char getMove() const;

	const SnakeState& getGameState() const;
	SnakeState& getGameState();

	bool operator==(const Node& left) const;
}; 

class DepthFirstSearchSolver : public SolverBase
{
public:
	DepthFirstSearchSolver(const SnakeState& gameState);

	virtual void reset() override;

	virtual char solve() override;
	
protected:
	char depthFirstSearch(const SnakeState & currGameState);

	void pushSafeMovesToFrontier(const SnakeState & gameState);

protected:
	std::vector<Node> frontier;
	std::vector<Node> explored;
	std::stack<char> solution;
};
