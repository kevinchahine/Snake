#pragma once

#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <queue>
#include <set>

#include "CostlySnakePath.h"

// Stores potential solutions as the following:
//	Snake
//	Apple
//	Path
//	Cost
class Frontier : 
	protected std::priority_queue<CostlySnakePath>,	// sorted in order of ascending cost
	protected std::set<uint64_t>					// hash value of CostlySnakePaths
{
public:
	template<typename T>
	void pushIfUnique(T&& costlySnakePath);
	void pop();

	const CostlySnakePath & getNextBestPath() const;

	bool contains(const CostlySnakePath& costlySnakePath) const;

	bool isEmpty() const;

private:
};
