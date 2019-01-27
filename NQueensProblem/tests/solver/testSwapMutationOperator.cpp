#include <solver/SwapMutationOperator.h>

#include <iostream>  /* std::cout, std::endl */
#include <cstring>   /* strncmp */
#include <algorithm> /* std::sort */
#include <iomanip>   /* std::setw */
#include <stdexcept> /* std::runtime_exception */
#include <set>       /* std::set */

using namespace nsSolver;

#define POP_SIZE        10000U
#define QUEENSCOUNT     50U

static void initPopulation(uint32_t* individual)
{
    uint32_t i;
    uint32_t j;
    uint32_t index;
    std::random_device rd;
    std::default_random_engine randomGenerator;
    randomGenerator.seed(rd());

    std::set<uint32_t> possiblePos;

    std::uniform_int_distribution<uint32_t> randGen;

    /* Init the possible position set */
    for(i = 0; i < QUEENSCOUNT; ++i)
    {
        possiblePos.insert(i);
    }

    /* With the set of possible position, we avoid multiple queens on the
        * same line
        * This is only usefull when using crossover and mutations operators
        * that keep the number of queens on one line contant.
        */
    for(j = 0; j < QUEENSCOUNT; ++j)
    {
        randGen =
        std::uniform_int_distribution<uint32_t>(0,
                                                possiblePos.size() - 1);
        std::set<uint32_t>::const_iterator it(possiblePos.begin());
        index = randGen(randomGenerator);
        std::advance(it, index);
        individual[j] = *it;
        possiblePos.erase(it);
    }
}

#ifndef _TESTMODE
#define _TESTMODE
#endif

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    #ifdef _TESTMODE

    uint32_t   i;
    uint32_t   j;
    uint32_t   mut;
    uint32_t** pop = new uint32_t*[POP_SIZE];
    uint32_t** popSave = new uint32_t*[POP_SIZE];
    uint32_t*  popFitness = new uint32_t[POP_SIZE];
    std::vector<uint32_t> selection;

    for(i = 0; i < POP_SIZE; ++i)
    {
        pop[i] = new uint32_t[QUEENSCOUNT];
        popSave[i] = new uint32_t[QUEENSCOUNT];;
        popFitness[i] = i;

        initPopulation(pop[i]);
        memcpy(popSave[i], pop[i], sizeof(uint32_t) * QUEENSCOUNT);
    }

    SwapMutationOperator mutationOp;

    mutationOp(pop, POP_SIZE, POP_SIZE / 2, popFitness, QUEENSCOUNT, selection);


    for(i = 0; i < POP_SIZE / 2; ++i)
    {
        for(j = 0; j < QUEENSCOUNT; ++j)
        {
            if(pop[i][j] != popSave[i][j])
            {
                throw std::runtime_error("Individual should't have mutated");
            }
        }
    }
    for(; i < POP_SIZE; ++i)
    {
        mut = 0;
        for(j = 0; j < QUEENSCOUNT; ++j)
        {
            if(pop[i][j] != popSave[i][j])
            {
                ++mut;
            }
        }
        if(mut == 0)
        {
            throw std::runtime_error("Individual should have mutated");
        }
    }

    for(i = 0; i < POP_SIZE; ++i)
    {
        delete[] pop[i];
        delete[] popSave[i];
    }
    delete[] pop;
    delete[] popSave;
    delete[] popFitness;

    std::cout << "\033[1;32mPASSED\033[0m\t" << std::endl;

    return 0;

    #else

    std::cout << "\033[1;33mTEST MODE DISABLED\033[0m\t" << std::endl;

    return -1;

    #endif
}