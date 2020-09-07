#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
using namespace boost::accumulators;

#include <opencv2/highgui.hpp>

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
		const size_t N_ROWS = 6;
		const size_t N_COLS = 6;
		const size_t N_SAMPLES = 10;
		const int DELAY = 1;

		//PerformanceTest<DefaultSolver> benchDefault(N_ROWS, N_COLS, DELAY);
		//benchDefault.run(N_SAMPLES);
		
		//PerformanceTest<RandomSolver> benchRandom(N_ROWS, N_COLS, DELAY);
		//benchRandom.run(N_SAMPLES);

		//PerformanceTest<BestFirstSolver> benchBFS(N_ROWS, N_COLS, DELAY);
		//benchBFS.run(N_SAMPLES);
		
		//PerformanceTest<ReverseAStarSolver> benchReverseAStar(N_ROWS, N_COLS, DELAY);
		//benchReverseAStar.run(N_SAMPLES);
		
		//PerformanceTest<AStarSolver> benchAStar(N_ROWS, N_COLS, DELAY);
		//benchAStar.run(N_SAMPLES);

		//PerformanceTest<HamiltonianSolver> benchHamiltonian(N_ROWS, N_COLS, DELAY);
		//benchHamiltonian.search(N_SAMPLES);
				
		run();

		//snake::test::generateSolution();

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
