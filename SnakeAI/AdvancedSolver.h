#pragma once

#include <functional>
#include <memory>

#include "SolverBase.h"

template<class SolverA, class SolverB>
class AdvancedSolver : public SolverBase
{
public:
using UniaryOp = std::function<bool(const SnakeState&)>;

public:
	AdvancedSolver(const SnakeState& gameState, const UniaryOp & uniaryOp);

	virtual void reset() override;

	virtual char solve() override;

protected:
	std::unique_ptr<SolverBase> solverAPtr;
	std::unique_ptr<SolverBase> solverBPtr;
	UniaryOp op;
};

template<class SolverA, class SolverB>
AdvancedSolver<SolverA, SolverB>::AdvancedSolver(
	const SnakeState& gameState, const UniaryOp& uniaryOp) :
	SolverBase(gameState),
	solverAPtr(std::make_unique<SolverA>(gameState)),
	solverBPtr(std::make_unique<SolverB>(gameState)),
	op(uniaryOp)
{}

template<class SolverA, class SolverB>
void AdvancedSolver<SolverA, SolverB>::reset()
{
	solverAPtr->reset();
	solverBPtr->reset();
}

template<class SolverA, class SolverB>
char AdvancedSolver<SolverA, SolverB>::solve()
{
	if (op(gameState) == true) {
		return solverAPtr->solve();
	}
	else {
		return solverBPtr->solve();
	}
}
