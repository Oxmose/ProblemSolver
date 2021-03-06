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

#ifndef __SOLVER_FITNESS_POPULATION_SELECTOR_H_
#define __SOLVER_FITNESS_POPULATION_SELECTOR_H_

#include <cstdint>       /* Generic int types */

#include <solver/PopulationSelector.h> /* nsSolver::PopulationSelector */

/**
 * @brief N Queens problem solvers.
 *
 */
namespace nsSolver
{
    /**
     * @brief Implements the PopulationSelector interface. Population selection
     * operator based on the fitness of the individual. Only keeps the fittest
     * individuals in the population.
     *
     */
    class FitnessPopulationSelector : public PopulationSelector
    {
        private:


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
                                    const uint32_t   individualSize);

            /**
             * @brief Construct a new Fitness Population Selector object.
             *
             */
            FitnessPopulationSelector(void);

            /**
             * @brief Destroy the Fitness Population Selector object.
             *
             */
            virtual ~FitnessPopulationSelector(void) {}
    };
}

#endif /* #ifndef __SOLVER_FITNESS_POPULATION_SELECTOR_H_ */