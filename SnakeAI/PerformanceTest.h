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
	PerformanceTest(size_t nRows, size_t nCols, int delayMilliSec = 50);

	void run(size_t nGames);

	void search(size_t nGames);

private:
	SnakeInterface snakeInterface;
	std::unique_ptr<SolverBase> solverPtr;
	std::unique_ptr<AIController> controllerPtr;
};

template<typename SOLVER_T>
PerformanceTest<SOLVER_T>::PerformanceTest(size_t nRows, size_t nCols, int delayMilliSec) :
	snakeInterface(nRows, nCols),
	solverPtr(std::make_unique<SOLVER_T>(snakeInterface.m_gameState)),
	controllerPtr(std::make_unique<AIController>(snakeInterface.m_gameState, std::move(solverPtr), delayMilliSec))
{
	snakeInterface.setController(move(controllerPtr));
}

template<typename SOLVER_T>
void PerformanceTest<SOLVER_T>::run(size_t nGames)
{
	using std::cout;
	
	accumulator_set<double, features<tag::mean, tag::variance, tag::min, tag::max>> acc;

	const size_t nCells = snakeInterface.m_gameState.board().getNCells();

	for (size_t gameNumber = 0; gameNumber < nGames; gameNumber++) {
		cout << typeid(SOLVER_T).name() << " run #" << gameNumber << '\n';

		snakeInterface.run();

		int points = (snakeInterface.m_gameState.snake().size() * 100.0 / nCells);

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

template<typename SOLVER_T>
void PerformanceTest<SOLVER_T>::search(size_t nGames)
{
	using std::cout;

	const size_t nCells = snakeInterface.m_gameState.board().getNCells();

	accumulator_set<double, features<tag::mean, tag::variance, tag::min, tag::max>> acc;

	for (size_t gameNumber = 0; gameNumber < nGames; gameNumber++) {
		cout << typeid(SOLVER_T).name() << " run #" << gameNumber << '\t';

		const_cast<Snake&>(snakeInterface.m_gameState.snake()).resetHeadRandom();

		clock_t startTime = clock();
		auto solution = SOLVER_T::search(snakeInterface.m_gameState.snake());
		clock_t endTime = clock();
		
		clock_t searchTime = endTime - startTime;

		cout << "search time = " << searchTime << " mSec\n";

		acc(searchTime);
	}

	double meanTime = mean(acc);
	double varianceTime = variance(acc);

	cout << "Performance Test <" << typeid(SOLVER_T).name() << ">\n"
		<< "sample runs: " << nGames << '\n'
		<< "mean: " << meanTime << '\n'
		<< "variance: " << varianceTime << '\n'
		//<< "min: " << min(acc) << '\n'
		//<< "max: " << max(acc) << '\n'
		<< "board size = " << nCells << '\n'
		<< '\n';
}