/*******************************************************************************
 * File: FitnessPopulationSelector.h
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 11/12/2018
 *
 * Version: 1.0
 *
 * Population selection operator based on the fitness of the individual. Only
 * keeps the fittest indiciduals.
 ******************************************************************************/

#ifndef __SELECTOR__FITNESS_POPULATION_SELECTOR_H_
#define __SELECTOR__FITNESS_POPULATION_SELECTOR_H_

#include <cstdint>       /* Generic int types */

#include "engine/types.h" /* Core and selector types */
#include "selector/PopulationSelector.h" /* Selection operator */

namespace nsSelector
{
    class FitnessPopulationSelector : public PopulationSelector
    {
        private:
            /**
             * @brief Replace old population with the newly selected
             * individuals.
             *
             * @param pop The old population.
             * @param child The new children to replace the population.
             */
            void replacePop(nsCacheEngine::lockscheme_t* pop,
                            nsCacheEngine::lockscheme_t* child);

        public:
            /**
             * @brief Merge the children to the current population.
             *
             * @param[in/out] pop The initial population to use and merge.
             * @param[in] popSize The size of the initial population.
             * @param[in/out] popFitness The fitness of the initial population.
             * @param[in] children The children population.
             * @param[in] childrenSize The size of the children population.
             * @param[in] childrenFitness The fitness of the children population.
             */
            virtual void select(nsCacheEngine::lockscheme_t** pop,
                                const uint32_t                popSize,
                                uint64_t*                     popFitness,
                                nsCacheEngine::lockscheme_t** children,
                                const uint32_t                childrenSize,
                                const uint64_t*               childrenFitness);
            /**
             * @brief Destroy the Fitness Population Selector object.
             *
             */
            virtual ~FitnessPopulationSelector(void) {}
    };
}

#endif /* __SELECTOR__FITNESS_POPULATION_SELECTOR_H_ */