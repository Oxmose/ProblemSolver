/*******************************************************************************
 * File: PopulationSelector.h
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 11/12/2018
 *
 * Version: 1.0
 *
 * Population selection operator interface. This class defines the API a
 * population selection operator should implement.
 ******************************************************************************/

#ifndef __SOLVER_POPULATION_SELECTOR_H_
#define __SOLVER_POPULATION_SELECTOR_H_

#include <cstdint>       /* Generic int types */

/**
 * @brief N Queens problem solvers.
 *
 */
namespace nsSolver
{
    /**
     * @brief Population selection operator interface. This class defines the API a
     * population selection operator should implement.
     * A population selector is used in genetic algorithm to select the
     * individuals that will survive the current generatio.
     *
     */
    class PopulationSelector
    {
        public:
            /**
             * @brief Merge the children to the current population and select
             * individuals. This function only select the fittest individuals.
             *
             * @param[in/out] population The initial population to use and
             * merge.
             * @param[in] popSize The size of the initial population.
             * @param[in/out] popFitness The fitness of the initial population.
             * @param[in] children The children population.
             * @param[in] childrenSize The size of the children population.
             * @param[in] childrenFitness The fitness of the children
             * population.
             * @param[in] individualSize The size of an individual.
             */
            virtual void operator()(uint32_t**       population,
                                    const uint32_t   popSize,
                                    uint32_t*        popFitness,
                                    const uint32_t** children,
                                    const uint32_t   childrenSize,
                                    const uint32_t*  childrenFitness,
                                    const uint32_t   individualSize) = 0;

            /**
             * @brief Destroy the Population Selector object.
             *
             */
            virtual ~PopulationSelector(void) {}
    };
}

#endif /* #ifndef __SOLVER_POPULATION_SELECTOR_H_ */