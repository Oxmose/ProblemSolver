#include <solver/OrderOneCrossoverOperator.h>

#include <iostream>  /* std::cout, std::endl */
#include <cstring>   /* strncmp */
#include <algorithm> /* std::sort */
#include <iomanip>   /* std::setw */
#include <stdexcept> /* std::runtime_exception */
#include <set>       /* std::set */

using namespace nsSolver;

#define POP_SIZE        100U
#define SELECTION_COUNT 100U
#define QUEENSCOUNT     100U

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

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    #ifdef _TESTMODE

    uint32_t i;
    uint32_t j;
    uint32_t k;
    uint32_t **pop = new uint32_t*[POP_SIZE];
    uint32_t *matePool = new uint32_t[POP_SIZE];
    uint32_t **children = new uint32_t*[POP_SIZE];

    for(i = 0; i < POP_SIZE; ++i)
    {
        pop[i] = new uint32_t[QUEENSCOUNT];
        children[i] = new uint32_t[QUEENSCOUNT];
        for(j = 0; j < QUEENSCOUNT; ++j)
        {
            initPopulation(pop[i]);
        }
        matePool[i] = i;
    }

    OrderOneCrossoverOperator crossover;

    crossover(QUEENSCOUNT, (const uint32_t **)pop, POP_SIZE,
              (const uint32_t *)matePool, POP_SIZE, children);

    for(i = 0; i < POP_SIZE; ++i)
    {
        for(j = 0; j < QUEENSCOUNT; ++j)
        {
            //std::cout << pop[i][j] << " ";
        }
        //std::cout << std::endl;
    }
    std::cout << std::endl;
    for(i = 0; i < POP_SIZE; ++i)
    {
        for(j = 0; j < QUEENSCOUNT; ++j)
        {
            for(k = j + 1; k < QUEENSCOUNT; ++k)
            {
                if(children[i][j] == children[i][k])
                {
                    throw std::runtime_error("Children has duplicate!");
                }
            }
            //std::cout << children[i][j] << " ";
        }
        //std::cout << std::endl;
    }


    for(i = 0; i < POP_SIZE; ++i)
    {
        delete[] pop[i];
        delete[] children[i];
    }
    delete[] pop;
    delete[] matePool;
    delete[] children;

    std::cout << "\033[1;32mPASSED\033[0m\t" << std::endl;

    return 0;

    #else

    std::cout << "\033[1;33mTEST MODE DISABLED\033[0m\t" << std::endl;

    return -1;

    #endif
}