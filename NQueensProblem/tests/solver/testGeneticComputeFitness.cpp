#include <iostream>

#include "solver/GeneticSolver.h"

using namespace nsSolver;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    #ifdef _TESTMODE

    GeneticSolver solver(8, 100);
    solver.testComputeFitness();

    std::cout << "\033[1;32mPASSED\033[0m\t" << std::endl;

    return 0;

    #else

    std::cout << "\033[1;33mTEST MODE DISABLED\033[0m\t" << std::endl;

    return -1;

    #endif
}