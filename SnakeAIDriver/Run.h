#pragma once

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

void run();
