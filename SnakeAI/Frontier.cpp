#include "Frontier.h"

using namespace std;

template<typename T>
void Frontier::pushIfUnique(T&& costlySnakePath)
{
	// 0.) Calculate hash of new path
	uint64_t hash = costlySnakePath.hashValue();

	// 1.) Is this path already in frontier? We don't want to add it twice
	auto matchingPathIt = this->set<uint64_t>::find(hash);
	if (matchingPathIt == this->set<uint64_t>::end()) {
		// 1-1.) No. There is no matching path. Add new path to frontier
		this->priority_queue<CostlySnakePath>::push(forward<T>(costlySnakePath));
		this->set<uint64_t>::insert(hash);
	}
}

template void Frontier::pushIfUnique(CostlySnakePath&&);
template void Frontier::pushIfUnique(CostlySnakePath&);

void Frontier::pop()
{
	const CostlySnakePath& topPath = this->priority_queue<CostlySnakePath>::top();

	// remove the most promising path from queue
	this->priority_queue<CostlySnakePath>::pop();

	// remove its identifying hash value from the set.
	auto it = this->set<uint64_t>::erase(topPath.hashValue());
}

const CostlySnakePath& Frontier::getNextBestPath() const
{
	return this->priority_queue<CostlySnakePath>::top();
}

bool Frontier::contains(const CostlySnakePath& costlySnakePath) const
{
	auto matchingPathIter = this->set<uint64_t>::find(costlySnakePath.hashValue());

	return matchingPathIter != this->set<uint64_t>::end();
}

bool Frontier::isEmpty() const
{
	return this->priority_queue<CostlySnakePath>::empty();
}
