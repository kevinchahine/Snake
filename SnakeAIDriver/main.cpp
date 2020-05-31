#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
using namespace boost::accumulators;

#include <SnakeAI/SnakeInterface.h>
#include <SnakeAI/Controllers.hpp>
#include <SnakeAI/Solvers.hpp>
#include <SnakeAI/PerformanceTest.h>

#include "Run.h"

int main()
{
	// Initialize random number generator
	srand(time(NULL));

	try {
		const size_t N_ROWS = 10;
		const size_t N_COLS = 10;
		const size_t N_SAMPLES = 30;

		//PerformanceTest<ReverseAStarSolver> benchReverseAStar(N_ROWS, N_COLS);
		//benchReverseAStar.run(N_SAMPLES);
		//
		//PerformanceTest<AStarSolver> benchAStar(N_ROWS, N_COLS);
		//benchAStar.run(N_SAMPLES);
		//
		//PerformanceTest<BestFirstSolver> benchBFS(N_ROWS, N_COLS);
		//benchBFS.run(N_SAMPLES);
		//
		//PerformanceTest<RandomSolver> benchRandom(N_ROWS, N_COLS);
		//benchRandom.run(N_SAMPLES);
		//
		//PerformanceTest<DefaultSolver> benchDefault(N_ROWS, N_COLS);
		//benchDefault.run(N_SAMPLES);
		//
		run();
	}
	catch (std::exception & e) {
		cout << "Exception caught in " << __FUNCTION__ << ": "
			<< e.what() << '\n';
	}
	
	cout << "Press any key to continue . . .";
	cv::waitKey(0);	// keeps display window open
	std::cin.get();
	return 0;
}
