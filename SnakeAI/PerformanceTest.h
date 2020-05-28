#pragma once

#include <iostream>
#include <memory>
#include <typeinfo>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
using namespace boost::accumulators;

#include "SnakeInterface.h"
#include "AIController.h"

template<typename SOLVER_T>
class PerformanceTest
{
public:
	PerformanceTest(const PerformanceTest&) = default;
	PerformanceTest(PerformanceTest&&) noexcept = default;
	virtual ~PerformanceTest() noexcept = default;
	PerformanceTest& operator=(const PerformanceTest&) = default;
	PerformanceTest& operator=(PerformanceTest&&) noexcept = default;

	PerformanceTest(size_t nRows, size_t nCols);

	void run(size_t nGames);

private:
	SnakeInterface snakeInterface;
	std::unique_ptr<SolverBase> solverPtr;
	std::unique_ptr<AIController> controllerPtr;
};

template<typename SOLVER_T>
PerformanceTest<SOLVER_T>::PerformanceTest(size_t nRows, size_t nCols) :
	snakeInterface(nRows, nCols),
	solverPtr(std::make_unique<SOLVER_T>(snakeInterface.gameState)),
	controllerPtr(std::make_unique<AIController>(snakeInterface.gameState, std::move(solverPtr)))
{
	snakeInterface.setController(move(controllerPtr));
}

template<typename SOLVER_T>
void PerformanceTest<SOLVER_T>::run(size_t nGames)
{
	using std::cout;
	
	accumulator_set<double, features<tag::mean, tag::variance, tag::min, tag::max>> acc;

	const size_t nCells = snakeInterface.gameState.getBoard().getNCells();

	for (size_t gameNumber = 0; gameNumber < nGames; gameNumber++) {
		cout << typeid(SOLVER_T).name() << " run #" << gameNumber << '\n';

		snakeInterface.run();

		int points = (snakeInterface.gameState.getSnake().size() * 100.0 / nCells);

		acc(points);
	}

	double meanVal = mean(acc);
	double varianceVal = variance(acc);

	cout << "Performance Test <" << typeid(SOLVER_T).name() << ">\n"
		<< "sample runs: " << nGames << '\n'
		<< "mean: " << meanVal << '\t' << meanVal << '%' << '\n'
		<< "variance: " << varianceVal << '\t' << varianceVal << '%' << '\n'
		//<< "min: " << min(acc) << '\n'
		//<< "max: " << max(acc) << '\n'
		<< "board size = " << nCells << '\n'
		<< '\n';
}
