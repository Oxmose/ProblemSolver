/******************************************************************************
 * File: GeneticSolver.cpp
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 26/01/2019
 *
 * Version: 1.0
 *
 * GeneticSolver implements the Solver class. Any class implementing the
 * Solver interface is assumed to solve the N Queens Problem.
 * The algorithm used to solvle the problem is a genetic algorithm.
 ******************************************************************************/

#include <cstdint> /* uint32_t */
#include <vector>  /* std::vector */
#include <set>     /* std::set */
#include <random>  /* std::random_device, std::mt19937,
                      std::uniform_int_distribution */

/* nsSolver::FitnessPropMatingPoolSelector */
#include <solver/FitnessPropMatingPoolSelector.h>

/* Header filed */
#include <solver/GeneticSolver.h>

using namespace nsSolver; /* Solver's namespace */

/*******************************************************************************
 * Constructors / Destructors
 ******************************************************************************/
GeneticSolver::GeneticSolver(const uint32_t queensCount,
                             const uint32_t iterCount)
{
    uint32_t i;

    /* Initialize the internal data */
    this->queensCount    = queensCount;
    this->iterCount      = iterCount;

    /* Genetic paramters */
    this->populationSize    = GEN_POPULATION_SIZE;
    this->matingPoolSize    = GEN_MATING_POOL_SIZE;
    this->injectionPoolSize = GEN_INJECTION_POOL_SIZE;

    /* Operators initialization */
    this->matingPoolSelector = new FitnessPropMatingPoolSelector();

    /* Data and structures initialization */
    this->population = new uint32_t*[this->populationSize];
    for(i = 0; i < this->populationSize; ++i)
    {
        this->population[i] = new uint32_t[this->queensCount];
    }
    this->populationFitness = new uint32_t[this->populationSize];

    this->matingPool = new uint32_t[this->matingPoolSize];

    this->children = new uint32_t*[this->matingPoolSize];
    for(i = 0; i < this->matingPoolSize; ++i)
    {
        this->children[i] = new uint32_t[this->queensCount];
    }
    this->childrenFitness = new uint32_t[this->matingPoolSize];

    this->injectionPool = new uint32_t*[this->injectionPoolSize];
    for(i = 0; i < this->injectionPoolSize; ++i)
    {
        this->injectionPool[i] = new uint32_t[this->queensCount];
    }
    this->injectionFitness = new uint32_t[this->injectionPoolSize];

    /* Initialize the random generator */
    std::random_device rd;
    generator = std::mt19937(rd());

    /* Set the random distribution */
    randDist = std::uniform_int_distribution<uint32_t>(0, queensCount - 1);
}

GeneticSolver::~GeneticSolver(void)
{
    uint32_t i;

    /* Delete heaped data */
    delete this->matingPoolSelector;

    for(i = 0; i < this->populationSize; ++i)
    {
        delete[] this->population[i];
    }
    delete[] this->population;
    delete[] this->populationFitness;

    delete[] this->matingPool;

    for(i = 0; i < this->matingPoolSize; ++i)
    {
        delete[] this->children[i];
    }
    delete[] this->children;
    delete[] this->childrenFitness;

    for(i = 0; i < this->injectionPoolSize; ++i)
    {
        delete[] this->injectionPool[i];
    }
    delete[] this->injectionPool;
    delete[] this->injectionFitness;
}

/*******************************************************************************
 * Public methods
 ******************************************************************************/
void GeneticSolver::solve(std::vector<uint32_t>& solution,
                          uint32_t &attackCount)
{
    uint32_t i;
    uint32_t bestFitness;
    uint32_t bestFitnessIndex;

    /* Initializes the data */
    solution.clear();

    /* Check parameters */
    if(this->queensCount == 0 || this->iterCount == 0)
    {
        return;
    }

    /* Initialize the population */
    initPopulation();

    /* Compute the first fitness */
    computeFitness(false, false);

    /* Generations loop */
    for(i = 0; i < this->iterCount; ++i)
    {
        /* Select the mating pool */
        (*this->matingPoolSelector)(this->populationFitness,
                                    this->populationSize,
                                    this->matingPoolSize,
                                    this->matingPool);

        /* Apply crossover */

        /* Apply mutation */

        /* Apply injection */

        /* Compute new fitness */

        /* Population selection */

    }

    /* Find the best solution */
    bestFitness      = this->populationFitness[0];
    bestFitnessIndex = 0;
    for(i = 1; i < this->populationSize; ++i)
    {
        if(this->populationFitness[i] < bestFitness)
        {
            bestFitness      = this->populationFitness[i];
            bestFitnessIndex = i;
        }
    }

    /* Save the solution */
    solution.insert(solution.begin(),
                    this->population[bestFitnessIndex],
                    this->population[bestFitnessIndex] + this->queensCount);
    attackCount = bestFitnessIndex;
}

/*******************************************************************************
 * Private methods
 ******************************************************************************/
uint32_t
GeneticSolver::getAttackCount(const uint32_t* solution) const
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

void GeneticSolver::initPopulation(void)
{
    uint32_t i;
    uint32_t j;
    uint32_t index;

    uint32_t* individual;

    std::set<uint32_t> possiblePos;
    std::set<uint32_t> currentPossiblePos;

    std::uniform_int_distribution<uint32_t> randGen;

    /* Init the possible position set */
    for(i = 0; i < this->queensCount; ++i)
    {
        possiblePos.insert(i);
    }

    /* For each individual, generate random positions */
    for(i = 0; i < this->populationSize; ++i)
    {
        currentPossiblePos = std::set<uint32_t> (possiblePos);
        individual = this->population[i];

        /* With the set of possible position, we avoid multiple queens on the
         * same line
         * This is only usefull when using crossover and mutations operators
         * that keep the number of queens on one line contant.
         */
        for(j = 0; j < this->queensCount; ++j)
        {
            randGen =
            std::uniform_int_distribution<uint32_t>(0,
                                                currentPossiblePos.size() - 1);
            std::set<uint32_t>::const_iterator it(currentPossiblePos.begin());
            index = randGen(this->generator);
            std::advance(it, index);
            individual[j] = *it;
            currentPossiblePos.erase(it);
        }

        /* Init fitness */
        this->populationFitness[i] = UINT32_MAX;
    }
}

void GeneticSolver::computeFitness(const bool computeChildren,
                                   const bool computeInjectionPool)
{
    uint32_t i;

    /* Compute the population fitness */
    for(i = 0; i < this->populationSize; ++i)
    {
        /* If the fitness is UINT32_MAX, we need to compute it */
        if(this->populationFitness[i] == UINT32_MAX)
        {
            this->populationFitness[i] = getAttackCount(this->population[i]);
        }
    }

    /* If we need to compute children fitness */
    if(computeChildren)
    {
        for(i = 0; i < this->matingPoolSize; ++i)
        {
            /* If the fitness is UINT32_MAX, we need to compute it */
            if(this->childrenFitness[i] == UINT32_MAX)
            {
                this->childrenFitness[i] = getAttackCount(this->children[i]);
            }
        }
    }

    /* If we need to compute the inject pool fitness */
    if(computeInjectionPool)
    {
        for(i = 0; i < this->injectionPoolSize; ++i)
        {
            /* If the fitness is UINT32_MAX, we need to compute it */
            if(this->injectionFitness[i] == UINT32_MAX)
            {
                this->injectionFitness[i] =
                    getAttackCount(this->injectionPool[i]);
            }
        }
    }
}

#ifdef _TESTMODE
/*******************************************************************************
 * Test methods
 ******************************************************************************/
/* LCOV_EXCL_START */

#include <stdexcept> /* std::runtime_error */
#include <cstring>   /* memcpy */
void GeneticSolver::testGetAttackCount(void) const
{
    uint32_t val;
    uint32_t sol[4];

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

void GeneticSolver::testSolve(void)
{
    uint32_t val;
    uint32_t i;

    std::vector<uint32_t> sol(4);
    uint32_t solArr[4];

    solve(sol, val);
    for(i = 0; i < 4; ++i)
    {
        solArr[i] = sol[i];
    }
    if(getAttackCount(solArr) != val)
    {
        throw std::runtime_error("Solution does not match" +
                                 std::to_string(val) + ":" +
                                 std::to_string(getAttackCount(solArr)));
    }
}

void GeneticSolver::testInitPopulation(void)
{
    uint32_t i;
    uint32_t j;
    uint32_t k;

    initPopulation();

    for(i = 0; i < this->populationSize; ++i)
    {
        for(j = 0; j < this->queensCount; ++j)
        {
            for(k = j + 1; k < this->queensCount; ++k)
            {
                if(this->population[i][j] == this->population[i][k])
                {
                    throw std::runtime_error(
                        std::string("Double position found in initial") +
                        std::string(" population"));
                }
            }
            if(this->population[i][j] >= this->queensCount)
            {
                throw std::runtime_error(
                    std::string("Erroneous position found in initial") +
                    std::string(" population"));
            }
        }
    }
}

void GeneticSolver::testComputeFitness(void)
{
    uint32_t i;

    initPopulation();

    computeFitness(false, false);

    memcpy(this->children, this->population,
           sizeof(uint32_t*) * this->matingPoolSize);
    for(i = 0; i < this->matingPoolSize; ++i)
    {
        this->childrenFitness[i] = UINT32_MAX;
    }
    memcpy(this->injectionPool, this->population,
           sizeof(uint32_t*) * this->injectionPoolSize);
    for(i = 0; i < this->injectionPoolSize; ++i)
    {
        this->injectionFitness[i] = UINT32_MAX;
    }


    for(i = 0; i < this->populationSize; ++i)
    {
        if(this->populationFitness[i] != getAttackCount(this->population[i]))
        {
            throw std::runtime_error(
                    std::string("Erroneous fitness found in population"));
        }
    }
    for(i = 0; i < this->matingPoolSize; ++i)
    {
        if(this->childrenFitness[i] != UINT32_MAX)
        {
            throw std::runtime_error(
                    std::string("Erroneous fitness found in child population"));
        }
    }
    for(i = 0; i < this->injectionPoolSize; ++i)
    {
        if(this->injectionFitness[i] != UINT32_MAX)
        {
            throw std::runtime_error(
                    std::string("Erroneous fitness found in injection") +
                    std::string(" population"));
        }
    }

    computeFitness(true, false);

    for(i = 0; i < this->populationSize; ++i)
    {
        if(this->populationFitness[i] != getAttackCount(this->population[i]))
        {
            throw std::runtime_error(
                    std::string("Erroneous fitness found in population"));
        }
    }
    for(i = 0; i < this->matingPoolSize; ++i)
    {
        if(this->childrenFitness[i] != getAttackCount(this->children[i]))
        {
            throw std::runtime_error(
                    std::string("Erroneous fitness found in child population"));
        }
    }
    for(i = 0; i < this->injectionPoolSize; ++i)
    {
        if(this->injectionFitness[i] != UINT32_MAX)
        {
            throw std::runtime_error(
                    std::string("Erroneous fitness found in injection") +
                    std::string(" population"));
        }
    }

    computeFitness(false, true);

    for(i = 0; i < this->populationSize; ++i)
    {
        if(this->populationFitness[i] != getAttackCount(this->population[i]))
        {
            throw std::runtime_error(
                    std::string("Erroneous fitness found in population"));
        }
    }
    for(i = 0; i < this->matingPoolSize; ++i)
    {
        if(this->childrenFitness[i] != getAttackCount(this->children[i]))
        {
            throw std::runtime_error(
                    std::string("Erroneous fitness found in child population"));
        }
    }
    for(i = 0; i < this->injectionPoolSize; ++i)
    {
        if(this->injectionFitness[i] != getAttackCount(injectionPool[i]))
        {
            throw std::runtime_error(
                    std::string("Erroneous fitness found in injection") +
                    std::string(" population"));
        }
    }
}
/* LCOV_EXCL_STOP */
#endif