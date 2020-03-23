#pragma once

#include <stack>
#include <set>
//#include <queue>
#include <algorithm>

#include "SolverBase.h"

class Node : public std::pair<char, SnakeEngine>
{
public:
	Node(char move, const SnakeEngine& gameState);
	Node(const Node&) = default;
	Node(Node&&) noexcept = default;
	~Node() noexcept = default;
	Node& operator=(const Node&) = default;
	Node& operator=(Node&&) = default;

	bool isGoal() const;

	char getMove() const;

	const SnakeEngine& getGameState() const;
	SnakeEngine& getGameState();

	bool operator==(const Node& left) const;
}; 

class DepthFirstSearchSolver : public SolverBase
{
public:
	DepthFirstSearchSolver(const SnakeEngine& engine);

	virtual char solve() override;

protected:
	char depthFirstSearch();

	void pushValidMovesToFrontier(const SnakeEngine & gameState);

protected:
	
	std::vector<Node> frontier;
	std::vector<Node> explored;
	std::stack<char> solution;
};
