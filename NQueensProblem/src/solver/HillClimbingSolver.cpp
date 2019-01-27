/******************************************************************************
 * File: HillClimbingSolver.h
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 26/01/2019
 *
 * Version: 1.0
 *
 * HillClimbingSolver implements the Solver class. Any class implementing the
 * Solver interface is assumed to solve the N Queens Problem.
 * The algorithm used to solvle the problem is a hill climbing algorithm.
 ******************************************************************************/

#include <cstdint> /* uint32_t */
#include <vector>  /* std::vector */
#include <random>  /* std::random_device, std::mt19937,
                      std::uniform_int_distribution */

/* Header filed */
#include <solver/HillClimbingSolver.h>

using namespace nsSolver; /* Solver's namespace */

/*******************************************************************************
 * Constructors / Destructors
 ******************************************************************************/
HillClimbingSolver::HillClimbingSolver(const uint32_t queensCount,
                                       const uint32_t iterCount)
{
    this->queensCount = queensCount;
    this->iterCount   = iterCount;

    /* Initialize the random generator */
    std::random_device rd;
    generator = std::mt19937(rd());

    /* Set the random distribution */
    randDist = std::uniform_int_distribution<uint32_t>(0, queensCount - 1);
}

HillClimbingSolver::~HillClimbingSolver(void)
{

}

/*******************************************************************************
 * Public methods
 ******************************************************************************/
void HillClimbingSolver::solve(std::vector<uint32_t>& solution,
                         uint32_t &attackCount)
{
    uint32_t i;
    uint32_t bestAttackCount;
    uint32_t mutFitness[2];
    uint32_t index;

    /* Initializes the data */
    solution.clear();
    attackCount     = 0;
    bestAttackCount = UINT32_MAX;

    /* Check parameters */
    if(this->queensCount == 0 || this->iterCount == 0)
    {
        return;
    }

    /* Initialize the first solution queen */
    for(i = 0; i < this->queensCount; ++i)
    {
        solution.push_back(this->randDist(this->generator));
    }

    /* Search for the best solution now */
    for(i = 0; i < this->iterCount && bestAttackCount != 0; ++i)
    {
        /* Select a random position to modify */
        index = this->randDist(this->generator);

        /* Modify the position + 1 */
        if(solution[index] < this->queensCount - 1)
        {
            ++solution[index];
            mutFitness[0] = getAttackCount(solution);
            --solution[index];
        }
        else
        {
            mutFitness[0] = UINT32_MAX;
        }


        /* Modify the position - 1 */
        if(solution[index] > 0)
        {
            --solution[index];
            mutFitness[1] = getAttackCount(solution);
            ++solution[index];
        }
        else
        {
            mutFitness[1] = UINT32_MAX;
        }

        /* Select the best */
        if(mutFitness[0] <= mutFitness[1])
        {
            if(mutFitness[0] < bestAttackCount)
            {
                bestAttackCount = mutFitness[0];
                ++solution[index];
            }
        }
        else
        {
            if(mutFitness[1] < bestAttackCount)
            {
                bestAttackCount = mutFitness[1];
                --solution[index];
            }
        }
    }

    attackCount = bestAttackCount;
}

/*******************************************************************************
 * Private methods
 ******************************************************************************/
uint32_t
HillClimbingSolver::getAttackCount(const std::vector<uint32_t>& solution) const
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
void HillClimbingSolver::testGetAttackCount(void) const
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

void HillClimbingSolver::testSolve(void)
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