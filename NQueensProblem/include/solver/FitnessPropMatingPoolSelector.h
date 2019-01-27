/*******************************************************************************
 * File: FitnessPropMatingPoolSelector.h
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 27/01/2019
 *
 * Version: 1.0
 *
 * Mating pool selector based on the fitness of each individual. This fitness
 * level is used to associate a probability of selection with each individual
 * chromosome. If fi is the fitness of individual i in the population, its
 * probability of being selected is pi = fi / (sum(i = 1 to N) fi);
 ******************************************************************************/

#ifndef __SOLVER_FITNESS_PROP_MATING_POOL_SELECTOR_H_
#define __SOLVER_FITNESS_PROP_MATING_POOL_SELECTOR_H_

#include <cstdint> /* Generic int types */
#include <random>  /* std::default_random_engine */

#include <solver/MatingPoolSelector.h> /* nsSolver::MatingPoolSelector */

/**
 * @brief N Queens problem solvers.
 *
 */
namespace nsSolver
{
    /**
     * @brief Implements the MatingPoolSelector interface.
     * Mating pool selector based on the fitness of each individual. This
     * fitness level is used to associate a probability of selection with each
     * individual's chromosome. If fi is the fitness of individual i in the
     * population, its probability of being selected is
     * pi = fi / (sum(i = 1 to N) fi);
     *
     */
    class FitnessPropMatingPoolSelector : public MatingPoolSelector
    {
        private:
            /**
             * @brief Random number engine.
             *
             */
            std::default_random_engine randomGenerator;

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
                                    uint32_t*       selection);

            /**
             * @brief Construct a new Fitness Prop Mating Pool Selector object.
             *
             */
            FitnessPropMatingPoolSelector(void);

            /**
             * @brief Destroy the Fitness Prop Mating Pool Selector object.
             *
             */
            virtual ~FitnessPropMatingPoolSelector(void) {}
    };
}

#endif /* #ifndef __SOLVER_FITNESS_PROP_MATING_POOL_SELECTOR_H_ */