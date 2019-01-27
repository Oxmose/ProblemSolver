/******************************************************************************
 * File: GreedySolver.cpp
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 26/01/2019
 *
 * Version: 1.0
 *
 * GreedySolver implements the Solver class. Any class implementing the Solver
 * interface is assumed to solve the N Queens Problem.
 * The algorithm used to solvle the problem is a greedy algorithm.
 ******************************************************************************/

#include <cstdint> /* uint32_t */
#include <vector>  /* std::vector */
#include <random>  /* std::random_device, std::mt19937,
                      std::uniform_int_distribution */

/* Header file */
#include <solver/GreedySolver.h>

using namespace nsSolver; /* Solver's namespace */

/*******************************************************************************
 * Constructors / Destructors
 ******************************************************************************/
GreedySolver::GreedySolver(const uint32_t queensCount)
{
    this->queensCount = queensCount;

    /* Initialize the random generator */
    std::random_device rd;
    generator = std::mt19937(rd());

    /* Set the random distribution */
    randDist = std::uniform_int_distribution<uint32_t>(0, queensCount - 1);
}

GreedySolver::~GreedySolver(void)
{

}

/*******************************************************************************
 * Public methods
 ******************************************************************************/
void GreedySolver::solve(std::vector<uint32_t>& solution,
                         uint32_t &attackCount)
{
    uint32_t i;
    uint32_t j;
    uint32_t bestAttackCount;
    uint32_t currentAttackCount;
    uint32_t bestPosition;

    /* Initializes the data */
    solution.clear();
    attackCount     = 0;
    bestAttackCount = 0;

    /* Check parameters */
    if(this->queensCount == 0)
    {
        return;
    }

    /* Initialize the first queen */
    solution.push_back(this->randDist(this->generator));

    /* Now we fill the array until we reached the amount of queens */
    for(i = 1; i < this->queensCount; ++i)
    {
        /* Init bound data */
        bestPosition    = 0;
        bestAttackCount = UINT32_MAX;

        solution.push_back(0);

        /* Search for best position */
        for(j = 0; j < this->queensCount; ++j)
        {
            solution[i] = j;
            currentAttackCount = getAttackCount(solution);

            /* If we found better, replace the solution */
            if(currentAttackCount < bestAttackCount)
            {
                bestAttackCount = currentAttackCount;
                bestPosition    = j;
            }
        }

        /* Emplace the solution */
        solution[i] = bestPosition;
    }

    attackCount = bestAttackCount;
}

/*******************************************************************************
 * Private methods
 ******************************************************************************/
uint32_t
GreedySolver::getAttackCount(const std::vector<uint32_t>& solution) const
{
    uint32_t i;
    uint32_t j;
    uint32_t attackCount;

    attackCount = 0;
    for(i = 0; i < this->queensCount; ++i)
    {
        for(j = i + 1; j < this->queensCount; ++j)
        {
            /* Check same lines, first diagonal and second diagonal */
            if(solution[i] == solution[j] ||
               (j - i) == abs(solution[i] - solution[j]))
            {
                ++attackCount;
            }
        }
    }

    return attackCount;
}

#ifdef _TESTMODE
/*******************************************************************************
 * Test methods
 ******************************************************************************/
/* LCOV_EXCL_START */

#include <stdexcept> /* std::runtime_error */
void GreedySolver::testGetAttackCount(void) const
{
    uint32_t val;
    std::vector<uint32_t> sol(4);

    /* Test same line */
    sol[0] = 0;
    sol[1] = 3;
    sol[2] = 3;
    sol[3] = 0;
    if((val = getAttackCount(sol)) != 2)
    {
        throw std::runtime_error("Wrong attack count for line test: " +
                                 std::to_string(val));
    }

    /* Test first diagonal */
    sol[0] = 0;
    sol[1] = 1;
    sol[2] = 2;
    sol[3] = 3;
    if((val = getAttackCount(sol)) != 6)
    {
        throw std::runtime_error("Wrong attack count for first diagonal test " +
                                 std::to_string(val));
    }

    /* Test second diagonal */
    sol[0] = 3;
    sol[1] = 2;
    sol[2] = 1;
    sol[3] = 0;
    if((val = getAttackCount(sol)) != 6)
    {
        throw std::runtime_error("Wrong attack count for second diagonal test "+
                                 std::to_string(val));
    }
}

void GreedySolver::testSolve(void)
{
    uint32_t val;
    std::vector<uint32_t> sol(4);

    solve(sol, val);
    if(getAttackCount(sol) != val)
    {
        throw std::runtime_error("Solution does not match" +
                                 std::to_string(val) + ":" +
                                 std::to_string(getAttackCount(sol)));
    }
}

/* LCOV_EXCL_STOP */
#endif