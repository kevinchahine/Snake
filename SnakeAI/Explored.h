#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>

#include "SnakeState.h"

// Stores SnakeStates what were visited as hashValues
class Explored : public std::set<uint64_t>
{
public:
	bool contains(const SnakeState& visitedSnakeState) const;

	void insert(const SnakeState& visitedSnakeState);

private:
};
