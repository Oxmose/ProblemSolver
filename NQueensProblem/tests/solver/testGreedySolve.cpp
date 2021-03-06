#include <iostream>

#include "solver/GreedySolver.h"

using namespace nsSolver;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    #ifdef _TESTMODE

    GreedySolver* solver = new GreedySolver(4);
    solver->testSolve();
    delete solver;
    solver = new GreedySolver(0);
    solver->testSolve();
    delete solver;

    std::cout << "\033[1;32mPASSED\033[0m\t" << std::endl;

    return 0;

    #else

    std::cout << "\033[1;33mTEST MODE DISABLED\033[0m\t" << std::endl;

    return -1;

    #endif
}