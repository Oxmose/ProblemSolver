/*******************************************************************************
 * File: CrossoverOperator.h
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 27/01/2019
 *
 * Version: 1.0
 *
 * Crossover operator interface. This class defines the API a crossover operator
 * should implement.
 ******************************************************************************/

#ifndef __SOLVER_CROSSOVER_OPERATOR_H_
#define __SOLVER_CROSSOVER_OPERATOR_H_

#include <cstdint> /* Generic int types */

/**
 * @brief N Queens problem solvers.
 *
 */
namespace nsSolver
{
    /**
     * @brief CrossoverOperator interface. Defines what a crossover operator
     * should implement. A crossover operator is used to mate two individual of
     * a population to create new offstrings.
     *
     */
    class CrossoverOperator
    {
        public:
            /**
             * @brief Generate new offstring from the mating pool given as
             * parameter.
             *
             * @param[in] individualSize The size of an individual.
             * @param[in] pop The population to use.
             * @param[in] popSize The size of the population.
             * @param[in] matingPool The selected individuals to mate (indexes
             * in population).
             * @param[in] matingPoolSize The number of parents that should be
             * mated.
             * @param[out] newChildren The generated children.
             */
            virtual void operator()(const uint32_t   individualSize,
                                    const uint32_t** pop,
                                    const uint32_t   popSize,
                                    const uint32_t*  matingPool,
                                    const uint32_t   matingPoolSize,
                                    uint32_t**       newChildren) = 0;

            /**
             * @brief Destroy the Crossover Operator object.
             *
             */
            virtual ~CrossoverOperator(void) {}
    };
}

#endif /* #ifndef __SOLVER_CROSSOVER_OPERATOR_H_ */