#include <solver/FitnessPopulationSelector.h>

#include <iostream>  /* std::cout, std::endl */
#include <cstring>   /* strncmp */
#include <algorithm> /* std::sort */
#include <iomanip>   /* std::setw */
#include <stdexcept> /* std::runtime_exception */

using namespace nsSolver;

#define POP_SIZE 5

#ifndef _TESTMODE
#define _TESTMODE
#endif

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    #ifdef _TESTMODE

    uint32_t i;
    uint32_t j;
    uint32_t* pop[POP_SIZE];
    uint32_t* children[POP_SIZE];
    uint32_t fitness[POP_SIZE] = {16, 4, 3, 32, 5};
    uint32_t childrenFitness[POP_SIZE] = {20, 15, 40, 5, 22};

    FitnessPopulationSelector selector;

    for(i = 0; i < POP_SIZE; ++i)
    {
        pop[i] = new uint32_t[4];
        for(j = 0; j < 4; ++j)
        {
            pop[i][j] = i;
        }
        children[i] = new uint32_t[4];
        for(j = 0; j < 4; ++j)
        {
            children[i][j] = i + POP_SIZE;
        }
    }

    selector((uint32_t**)pop,
             POP_SIZE,
             (uint32_t*)fitness,
             (const uint32_t**)children,
             POP_SIZE,
             (const uint32_t*)childrenFitness,
             4);

    if(fitness[0] != 5 ||
       fitness[1] != 4 ||
       fitness[2] != 3 ||
       fitness[3] != 15 ||
       fitness[4] != 5)
    {
        throw std::runtime_error("Wrong population selection");
    }
    for(i = 0; i < POP_SIZE; ++i)
    {
        for(j = 0; j < 4; ++j)
        {
            if(i == 0 && pop[i][j] != 8)
            {
                throw std::runtime_error("Wrong population copy");
            }
            if(i == 1 && pop[i][j] != 1)
            {
                throw std::runtime_error("Wrong population copy");
            }
            if(i == 2 && pop[i][j] != 2)
            {
                throw std::runtime_error("Wrong population copy");
            }
            if(i == 3 && pop[i][j] != 6)
            {
                throw std::runtime_error("Wrong population copy");
            }
            if(i == 4 && pop[i][j] != 4)
            {
                throw std::runtime_error("Wrong population copy");
            }
        }
    }

    for(i = 0; i < POP_SIZE; ++i)
    {
        delete[] pop[i];
        delete[] children[i];
    }

    std::cout << "\033[1;32mPASSED\033[0m\t" << std::endl;

    return 0;

    #else

    std::cout << "\033[1;33mTEST MODE DISABLED\033[0m\t" << std::endl;

    return -1;

    #endif
}