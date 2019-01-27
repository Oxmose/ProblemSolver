/*******************************************************************************
 * File: SwapMutationOperator.cpp
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 27/01/2019
 *
 * Version: 1.0
 *
 * Mutation operation. Implements the MutationOperator insterface.
 * The Swap mutation operator select two alleles of an individual and swap them,
 * avoiding multiple duplicates of the same allele.
 ******************************************************************************/


#include <cstdint>   /* Generic int types */
#include <vector>    /* std::vector */
#include <algorithm> /* std::sort */
#include <random>    /* std::random_device, std::uniform_int_distribution,
                        std::uniform_real_distribution*/

 /* Header file */
#include <solver/SwapMutationOperator.h>

using namespace nsSolver; /* Solver's namespace */

/*******************************************************************************
 * Constructors / Destructors
 ******************************************************************************/
SwapMutationOperator::SwapMutationOperator(void)
{
    /* Initialize the random generator */
    std::random_device rd;
    this->randomGenerator.seed(rd());
}

/*******************************************************************************
 * Public methods
 ******************************************************************************/

void SwapMutationOperator::operator()(uint32_t**             population,
                                      const uint32_t         populationSize,
                                      const uint32_t         selectionSize,
                                      const uint32_t*        popFitness,
                                      const uint32_t         individualSize,
                                      std::vector<uint32_t>& selection)
{
    uint32_t i;
    uint32_t startIndex;
    uint32_t endIndex;
    uint32_t tmp;
    std::uniform_int_distribution<uint32_t> distributionInt;

    /* Vector of pair : key = fitness, value = index */
    std::vector<std::pair<uint32_t, uint32_t>> fitIndex(populationSize);

    /* Get the less fittest individuals */
    selection.clear();
    for(i = 0; i < populationSize; ++i)
    {
        fitIndex.push_back(std::make_pair(popFitness[i], i));
    }
    /* LCOV_EXCL_START */
    std::sort(fitIndex.begin(),
              fitIndex.end(),
              std::greater<std::pair<uint32_t, uint32_t>>());
    /* LCOV_EXCL_STOP */

    /* Copy the less fitest individuals index and mutate them */
    for(i = 0; i < selectionSize && i < populationSize; ++i)
    {
        selection.push_back(fitIndex[i].second);

        /* Swap two random alleles */
        distributionInt = std::uniform_int_distribution<uint32_t>(0,
                            individualSize - 2);
        startIndex = distributionInt(this->randomGenerator);
        distributionInt = std::uniform_int_distribution<uint32_t>(
                            startIndex + 1,
                            individualSize - 1);
        endIndex = distributionInt(this->randomGenerator);
        tmp = population[fitIndex[i].second][startIndex];
        population[fitIndex[i].second][startIndex] =
            population[fitIndex[i].second][endIndex];
        population[fitIndex[i].second][endIndex] = tmp;
    }
}

/*******************************************************************************
 * Private methods
 ******************************************************************************/