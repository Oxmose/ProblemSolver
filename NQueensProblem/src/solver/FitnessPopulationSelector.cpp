/*******************************************************************************
 * File: FitnessPopulationSelector.h
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 27/01/2019
 *
 * Version: 1.0
 *
 * Implements the PopulationSelector interface. Population selection operator
 * based on the fitness of the individual. Only keeps the fittest individuals in
 * the population.
 ******************************************************************************/

#include <cstdint>   /* Generic int types */
#include <queue>     /* std::priority_queue */
#include <algorithm> /* std::sort */
#include <vector>    /* std::vector */
#include <cstring>   /* memcpy */

 /* Header file */
#include <solver/FitnessPopulationSelector.h>

using namespace nsSolver; /* Solver's namespace */

/**
 * @brief Individual fitness index pair.
 *
 */
typedef std::pair<uint32_t, uint32_t> indivpair_t;

/**
 * @brief Comparison class.
 *
 */
class Compare
{
    public:
        bool operator() (const indivpair_t& a, const indivpair_t& b)
        {
            return a.second < b.second;
        }
};

/**
 * @brief Comparison function
 *
 * @param a The first pair to compare
 * @param b The second pair to compare
 * @return true If a > b
 * @return false If b <= a
 */
static bool popSort(const indivpair_t& a, const indivpair_t& b)
{
    return a.second > b.second;
}

/*******************************************************************************
 * Constructors / Destructors
 ******************************************************************************/
FitnessPopulationSelector::FitnessPopulationSelector(void)
{
}

/*******************************************************************************
 * Public methods
 ******************************************************************************/
void FitnessPopulationSelector::operator()(uint32_t**       population,
                                           const uint32_t   popSize,
                                           uint32_t*        popFitness,
                                           const uint32_t** children,
                                           const uint32_t   childrenSize,
                                           const uint32_t*  childrenFitness,
                                           const uint32_t   individualSize)
{
    uint32_t i;
    uint32_t index;

    std::priority_queue<indivpair_t, std::vector<indivpair_t>, Compare> popElem;
    for(i = 0; i < popSize; ++i)
    {
        popElem.push(std::make_pair(i, popFitness[i]));
    }

    std::vector<indivpair_t> childElem(childrenSize);
    for(i = 0; i < childrenSize; ++i)
    {
        childElem[i] = std::make_pair(i, childrenFitness[i]);
    }
    std::sort(childElem.begin(), childElem.end(), popSort);

    /* Select the n worst individuals and replace them */
    for(i = 0; i < childrenSize; ++i)
    {
        /* If children has a better fitness exchange it */
        if(childElem[i].second < popElem.top().second)
        {
            /* Pop the element */
            index = popElem.top().first;
            popElem.pop();

            /* Copy the data */
            memcpy(population[index], children[childElem[i].first],
                   individualSize * sizeof(uint32_t));

            /* Push the new element and update fitness */
            popElem.push(std::make_pair(index, childrenFitness[childElem[i].first]));
            popFitness[index] = childElem[i].second;
        }
    }
}

/*******************************************************************************
 * Private methods
 ******************************************************************************/