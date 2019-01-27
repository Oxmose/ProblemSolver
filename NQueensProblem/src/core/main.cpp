/******************************************************************************
 * File: main.cpp
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 26/01/2019
 *
 * Version: 1.0
 *
 * Main function for the N Queens problem solver.
 ******************************************************************************/

#include <cstdint>  /* uint32_t */
#include <vector>   /* std::vector */
#include <iostream> /* std::cout, std::endl */
#include <cstring>  /* stdncmp */

#include <solver/GreedySolver.h>       /* nsSolver::GreedySolver */
#include <solver/HillClimbingSolver.h> /* nsSolver::HillClimbingSolver*/
#include <solver/GeneticSolver.h>      /* nsSolver::GeneticSolver*/

using namespace nsSolver; /* Solver's namespace */

#ifndef _TESTMODE

static void displayUsage(char* exeName)
{
    std::cout << exeName << "[ALGOTYPE] [N] [ITERCOUNT]"
              << std::endl << "\t"
              << "ALGOTYPE is the algorithm type used to solve the problem can "
              << "be GREEDY, HILL or GEN."
              << std::endl << "\t"
              << "N Is the number of queens to use to solve the problem. "
              << std::endl << "\t"
              << "ITERCOUNT is the maximal number of iteration to reach before"
              << " stopping the algorithm (this is not taken into account for "
              << "the greedy algorithm)." << std::endl;
}

int main(int argc, char** argv)
{
    uint32_t i;
    uint32_t queens;
    uint32_t iterCount;
    uint32_t attackCount;

    std::vector<uint32_t> solution;

    Solver* solver = nullptr;

    if(argc != 4)
    {
        std::cout << "Wrong argument count" << std::endl;
        displayUsage(argv[0]);
        return -1;
    }
    queens    = std::stoi(argv[2]);
    iterCount = std::stoi(argv[3]);

    if(strncmp(argv[1], "GREEDY", 5) == 0)
    {
        solver = new GreedySolver(queens);
    }
    else if(strncmp(argv[1], "HILL", 4) == 0)
    {
        solver = new HillClimbingSolver(queens, iterCount);
    }
    else if(strncmp(argv[1], "GEN", 3) == 0)
    {
        solver = new GeneticSolver(queens, iterCount);
    }
    else
    {
        std::cout << "Wrong algorithm selected to solve the"
              << " problem."
              << std::endl;
        displayUsage(argv[0]);
        return -1;
    }

    solver->solve(solution, attackCount);

    std::cout << "Attack count: " << attackCount << std::endl;
    std::cout << "Solution: " << std::endl;

    for(i = 0; i < solution.size(); ++i)
    {
        std::cout << "[" << i << ";" << solution[i];
        if(i != solution.size() - 1)
            std::cout << "], ";
        else
            std::cout << "]";
    }
    std::cout << std::endl;

    delete solver;
    return 0;
}
#endif