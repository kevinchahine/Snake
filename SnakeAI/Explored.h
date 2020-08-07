#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>

#include "SnakeGame.h"

// Stores SnakeStates what were visited as hashValues
class Explored : public std::set<uint64_t>
{
public:
	bool contains(const SnakeGame& visitedSnakeState) const;

	void insert(const SnakeGame& visitedSnakeState);

private:
};
