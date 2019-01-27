/*******************************************************************************
 * File: MatingPoolSelector.h
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 27/01/2019
 *
 * Version: 1.0
 *
 * Mating pool selector interface. This class defines the API a mating pool
 * selector should implement.
 ******************************************************************************/

#ifndef __SOLVER_MATING_POOL_SELECTOR_H_
#define __SOLVER_MATING_POOL_SELECTOR_H_

#include <cstdint> /* Generic int types */

/**
 * @brief N Queens problem solvers.
 *
 */
namespace nsSolver
{
    /**
     * @brief MatingPoolSlector interface. Define what a mating pool selector
     * should implement. A mating pool selector is used to select the
     * individuals that should mate to produce new offstrings.
     *
     */
    class MatingPoolSelector
    {
        public:
            /**
             * @brief Select the individuals of the population to mate.
             *
             * @param[in] popData The data used to select the population,
             * usually the fitness of the individuals.
             * @param[in] popSize The size of the population.
             * @param[in] selectionSize The number of individual to select.
             * @param[out] selection The selection array to be modified by the
             * algorithm (put the index of the individuals to mate).
             */
            virtual void operator()(const uint32_t* popData,
                                    const uint32_t  popSize,
                                    const uint32_t  selectionSize,
                                    uint32_t*       selection) = 0;
            /**
             * @brief Destroy the Mating Pool Selector object.
             *
             */
            virtual ~MatingPoolSelector(void) {}
    };
}

#endif /* #ifndef __SOLVER_MATING_POOL_SELECTOR_H_ */