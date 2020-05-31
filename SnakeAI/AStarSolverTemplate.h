#pragma once

#include <queue>

#include "SolverBase.h"

#include "CostlySnakePath.h"
#include "Frontier.h"
#include "Explored.h"

template<typename C>
class AStarSolverTemplate : public SolverBase
{
public:
	AStarSolverTemplate(const SnakeState& gameState);

	virtual void reset() override;
	virtual char solve() override;

private:
	// Searches for a optimal solution (or path) from start to a goal state.
	// Path is stored in this->solutionPath
	SnakePath search(const SnakeState& start);

protected:
	SnakePath solutionPath;
};

// -------------------------- DEFINITIONS -------------------------------------

template<typename C>
AStarSolverTemplate<C>::AStarSolverTemplate(const SnakeState& gameState) :
	SolverBase(gameState),
	solutionPath(gameState)
{}

template<typename C>
void AStarSolverTemplate<C>::reset()
{
	// Delete solution contents so that next time we'll have to solve
	// a fresh solution
	// Don't know why this is giving a access error
	///this->solutionPath.clear();
}

template<typename C>
char AStarSolverTemplate<C>::solve()
{
	// 1.) Do we need to search for another solution path?
	if (solutionPath.pathLength() > 0) {
		// Nope. We still have moves to make in our solution path
	}
	else {
		// Yes. We used up our solution path. We need so solve another one.
		solutionPath = search(gameState);
	}

	// 2.) Grab the next move from the solution path
	char nextMove = solutionPath.peekNextMove();
	solutionPath.popMove();

	// 3.) Check for errors
	if (nextMove == 'x') {
		//cout << "AStar: Oh no. No good move was found.\n"
		//	<< "Just do any legal and safe move instead.\n";
		nextMove = gameState.getAnyLegalAndSafeMove();
	}

	// 4.) Return nextMove as our decision
	return nextMove;
}

template<typename C>
SnakePath AStarSolverTemplate<C>::search(const SnakeState& start)
{
	// 0.) Initialize node as an empty path that leads at the start state.
	CostlySnakePath node = start;

	// 1.) Create frontier to store potential solutions (paths) in order of
	// ascending cost. Push node to the frontier
	Frontier<C> frontier;
	frontier.pushIfUnique(move(node));

	// 2.) Create explored list to represent snake states that have been visited 
	// and analyzed. Only stores the hash of a snake state to save on speed and memory.
	Explored explored;

	// 3.) Search for shortest path
	while (true) {
		// 3-1.) Did we run out of paths to try?
		if (frontier.isEmpty()) {
			// Yes, return empty path
			//cout << "Frontier is empty. No path to goal was found.\n";
			return SnakePath(start);	// no solution
		}

		// 3-2.) Get the next path to analyze
		node = frontier.getNextBestPath();
		frontier.pop();
		//cout << "Pop frontier: " << node << '\n';

		// 3-3.) Is this the goal state?
		if (node.isGoalState()) {
			// Yes, return node as the solution.
			//cout << "!!!Solution has been found. Yay :) !!!\n";
			//cout << "Solution = " << node << '\n';
			//system("pause");
			return node;
		}

		// 3-4.) Expand the roads from node to get all possible paths.
		for (char safeAndLegalMove : node.destinationSnakeState().getAllLegalAndSafeMoves()) {
			// 3-4-0.) Make a copy of the node path. We will need to modify it later
			CostlySnakePath childNode = node;

			// 3-4-1.) Append a road to the end of the new path
			childNode.pushMove(safeAndLegalMove);
			//cout << "new child node: " << childNode << '\n';

			// 3-4-2.) What game state does the new path end up at?
			const SnakeState& childDestination = childNode.destinationSnakeState();

			// --- Now we have a path and we know where it leads us ---
			// --- Before we add this new path to the frontier, 1st check to see if we should. ---

			// 3-4-3.) Have we explored the destination city already and
			// is it already in the frontier? If so we should not add it.
			//cout << "explored does " << (explored.contains(childDestination) ? "" : "NOT")
			//	<< " contain childDestination\n";
			//cout << "frontier does " << (frontier.contains(childNode) ? "" : "NOT")
			//	<< " contain childNode\n";

			if (!explored.contains(childDestination) &&
				!frontier.contains(childNode)) {
				// We have not explored the destination snake state yet and
				// the path is not already in the frontier, which it now should be.
				// Add this new path to the frontier.
				//cout << "Pushing " << childNode << " to frontier " << '\n';
				frontier.pushIfUnique(childNode);
				explored.insert(childDestination);
			}
			//else if (childPathPtr) {
				// Only important if two adjacent cities have more than one
				// road between them.
			//}
			/*else {
				cout << "new child node\n";
			}*/
			//cin.get();
			//cout << '\n';
		} // end for (const Road &
	} // end while (true)
}
