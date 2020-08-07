#pragma once

#include <functional>
#include <memory>

#include "SolverBase.h"

template<class SolverA, class SolverB>
class AdvancedSolver : public SolverBase
{
public:
using UniaryOp = std::function<bool(const SnakeGame&)>;

public:
	AdvancedSolver(const SnakeGame& m_gameState, const UniaryOp & uniaryOp);

	virtual void reset() override;

	virtual char solve() override;

protected:
	std::unique_ptr<SolverBase> solverAPtr;
	std::unique_ptr<SolverBase> solverBPtr;
	UniaryOp op;
};

template<class SolverA, class SolverB>
AdvancedSolver<SolverA, SolverB>::AdvancedSolver(
	const SnakeGame& m_gameState, const UniaryOp& uniaryOp) :
	SolverBase(m_gameState),
	solverAPtr(std::make_unique<SolverA>(m_gameState)),
	solverBPtr(std::make_unique<SolverB>(m_gameState)),
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
	if (op(m_gameState) == true) {
		return solverAPtr->solve();
	}
	else {
		return solverBPtr->solve();
	}
}
