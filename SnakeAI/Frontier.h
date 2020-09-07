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
// Template<C>
// C should be either std::less<CostlySnakePath> or std::greater<CostlySnakePath>
template<typename C>
class Frontier : 
	public std::priority_queue<CostlySnakePath, std::vector<CostlySnakePath>, C>,	// sorted in order of ascending/decending cost
	public std::set<uint64_t>														// hash value of CostlySnakePaths
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

template<typename C>
template<typename T>
void Frontier<C>::pushIfUnique(T&& costlySnakePath)
{
	// 0.) Calculate hash of new path
	uint64_t hash = costlySnakePath.hashValue();

	// 1.) Is this path already in frontier? We don't want to add it twice
	auto matchingPathIt = this->std::set<uint64_t>::find(hash);
	if (matchingPathIt == this->std::set<uint64_t>::end()) {
		// 1-1.) No. There is no matching path. Add new path to frontier
		this->std::priority_queue<CostlySnakePath, std::vector<CostlySnakePath>, C>::push(std::forward<T>(costlySnakePath));
		this->std::set<uint64_t>::insert(hash);
	}
}

template<typename C>
void Frontier<C>::pop()
{
	const CostlySnakePath& topPath = this->std::priority_queue<CostlySnakePath, std::vector<CostlySnakePath>, C>::top();

	// remove the most promising path from queue
	this->std::priority_queue<CostlySnakePath, std::vector<CostlySnakePath>, C>::pop();

	// remove its identifying hash value from the set.
	auto it = this->std::set<uint64_t>::erase(topPath.hashValue());
}

template<typename C>
const CostlySnakePath& Frontier<C>::getNextBestPath() const
{
	return this->std::priority_queue<CostlySnakePath, std::vector<CostlySnakePath>, C>::top();
}

template<typename C>
bool Frontier<C>::contains(const CostlySnakePath& costlySnakePath) const
{
	auto matchingPathIter = this->std::set<uint64_t>::find(costlySnakePath.hashValue());

	return matchingPathIter != this->std::set<uint64_t>::end();
}

template<typename C>
bool Frontier<C>::isEmpty() const
{
	return this->std::priority_queue<CostlySnakePath, std::vector<CostlySnakePath>, C>::empty();
}
