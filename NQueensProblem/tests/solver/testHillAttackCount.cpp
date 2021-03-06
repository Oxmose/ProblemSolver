#include <iostream>

#include "solver/HillClimbingSolver.h"

using namespace nsSolver;

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    #ifdef _TESTMODE

    HillClimbingSolver solver(4, 100);
    solver.testGetAttackCount();

    std::cout << "\033[1;32mPASSED\033[0m\t" << std::endl;

    return 0;

    #else

    std::cout << "\033[1;33mTEST MODE DISABLED\033[0m\t" << std::endl;

    return -1;

    #endif
}