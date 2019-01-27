/*******************************************************************************
 * File: OrderOneCrossoverOperator.cpp
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 27/01/2019
 *
 * Version: 1.0
 *
 * Crossover operator omplements ad the order 1 operator.
 * Order 1 Crossover is a fairly simple permutation crossover.
 * Basically, a swath of consecutive alleles from parent 1 drops down,
 * and remaining values are placed in the child in the order which they
 * appear in parent 2. [http://www.rubicite.com/Tutorials/GeneticAlgorithms/
 * CrossoverOperators/Order1CrossoverOperator.aspx]
 *
 ******************************************************************************/


#include <cstdint> /* Generic int types */
#include <random>  /* std::random_device, std::uniform_int_distribution */

/* Header file */
#include <solver/OrderOneCrossoverOperator.h>

using namespace nsSolver; /* Solver's namespace */

/*******************************************************************************
 * Constructors / Destructors
 ******************************************************************************/
OrderOneCrossoverOperator::OrderOneCrossoverOperator(void)
{
    /* Initialize the random generator */
    std::random_device rd;
    this->randomGenerator.seed(rd());
}

/*******************************************************************************
 * Public methods
 ******************************************************************************/
void OrderOneCrossoverOperator::operator()(const uint32_t   individualSize,
                                           const uint32_t** pop,
                                           const uint32_t   popSize,
                                           const uint32_t*  matingPool,
                                           const uint32_t   matingPoolSize,
                                           uint32_t**       newChildren)
{
    uint32_t i;
    uint32_t offset;

    const uint32_t* parents[2] = {nullptr, nullptr};
    uint32_t*       children[2];

    /* We cannot mate less than two parents */
    if(matingPoolSize < 2)
    {
        return;
    }

    /* We mate the parents */
    offset = 0;
    for(i = 0; i < matingPoolSize; ++i)
    {
        if(parents[0] == nullptr && matingPool[i] < popSize)
        {
            parents[0] = pop[matingPool[i]];
        }
        else if(matingPool[i] < popSize)
        {

            parents[1] = pop[matingPool[i]];

            children[0] = newChildren[offset];
            children[1] = newChildren[offset + 1];

            mate(individualSize, parents, children);

            parents[0] = nullptr;
            parents[1] = nullptr;
            offset += 2;
        }
    }
}

/*******************************************************************************
 * Private methods
 ******************************************************************************/
void OrderOneCrossoverOperator::mate(const uint32_t   individualSize,
                                     const uint32_t** parents,
                                     uint32_t**       children)
{
    uint32_t startIndex;
    uint32_t endIndex;
    uint32_t i;
    uint32_t j;
    uint32_t value;
    uint32_t cindex;
    uint32_t pindex;
    uint32_t pSel;
    uint32_t placedCount;
    std::vector<bool> placed;
    std::uniform_int_distribution<uint64_t> distributionInt;

    /* Create two children */
    for(i = 0; i < 2; ++i)
    {
        placed      = std::vector<bool>(individualSize, false);
        placedCount = 0;

        /* Select two random points */
        distributionInt = std::uniform_int_distribution<uint64_t>(0,
                            individualSize - 1);
        startIndex = distributionInt(this->randomGenerator);
        distributionInt = std::uniform_int_distribution<uint64_t>(startIndex,
                            individualSize - 1);
        endIndex = distributionInt(this->randomGenerator);

        /* Copy first parent's material */
        for(j = startIndex; j <= endIndex; ++j)
        {
            value = parents[i][j];
            children[i][j] = value;
            placed[value] = true;
        }
        placedCount = endIndex - startIndex + 1;

        cindex = (endIndex + 1) % individualSize;
        pindex = cindex;
        pSel   = (i + 1) % 2;

        /* Fill the rest of the child with parent 2 */
        while(placedCount != individualSize)
        {
            value = parents[pSel][pindex];
            if(!placed[value])
            {
                children[i][cindex] = value;
                ++placedCount;
                placed[value] = true;
                cindex = (cindex + 1) % individualSize;
            }
            pindex = (pindex + 1) % individualSize;
        }
    }
}
