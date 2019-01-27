#include <solver/FitnessPropMatingPoolSelector.h>

#include <iostream>  /* std::cout, std::endl */
#include <cstring>   /* strncmp */
#include <algorithm> /* std::sort */
#include <iomanip>   /* std::setw */
#include <stdexcept> /* std::runtime_exception */

using namespace nsSolver;

#define POP_SIZE 100
#define SELECTION_COUNT 20

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    #ifdef _TESTMODE

    uint32_t i;
    uint32_t j;
    uint32_t timeSelected[POP_SIZE] = {0};
    uint32_t selection[SELECTION_COUNT] = {0};
    uint32_t fitness[POP_SIZE] = {0};

    FitnessPropMatingPoolSelector selector;

    for(i = 0; i < POP_SIZE / 2; ++i)
    {
        fitness[i] = POP_SIZE - i;
    }
    for(; i < POP_SIZE; ++i)
    {
        fitness[i] =  i;
    }

    for(i = 0; i < 50000; ++i)
    {
        selector(fitness, POP_SIZE, SELECTION_COUNT, selection);

        for(j = 0; j < SELECTION_COUNT; ++j)
        {
            timeSelected[selection[j]] += 1;
        }
    }

    for(i = 0; i < POP_SIZE; ++i)
    {
        if(i % 10 == 0)
        {
            std::cout << std::endl;
        }
        std::cout << std::setw(3) << i << ": " << std::setw(5)
                  << timeSelected[i] << " | ";

        if(i > 0 && i < 50 && timeSelected[i - 1] < timeSelected[i] - 400)
        {
            throw std::runtime_error("Wrong selection order (0)");
        }
        if(i > 0 && i > 50 && timeSelected[i - 1] > timeSelected[i] + 400)
        {
            throw std::runtime_error("Wrong selection order (1)");
        }
    }

    std::cout << std::endl;

    std::cout << "\033[1;32mPASSED\033[0m\t" << std::endl;

    return 0;

    #else

    std::cout << "\033[1;33mTEST MODE DISABLED\033[0m\t" << std::endl;

    return -1;

    #endif
}