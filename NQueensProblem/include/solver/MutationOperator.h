/*******************************************************************************
 * File: MutationOperator.h
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 27/01/2019
 *
 * Version: 1.0
 *
 * Mutation operator interface. This class defines the API a mutation operator
 * should implement.
 ******************************************************************************/

#ifndef __SOLVER_MUTATION_OPERATOR_H_
#define __SOLVER_MUTATION_OPERATOR_H_

#include <cstdint>       /* Generic int types */
#include <vector>        /* std::vector */

/**
 * @brief N Queens problem solvers.
 *
 */
namespace nsSolver
{
    /**
     * @brief  Mutation operator interface. This class defines the API a
     * mutation operator should implement. A mutation operator is used in
     * genetic algorithm to mutate individuals genes.
     *
     */
    class MutationOperator
    {
        public:
            /**
             * @brief Apply mutation to a set of individual in the population.
             *
             * @param[in] population The population to use.
             * @param[in] populationSize The size of the population.
             * @param[in] selectionSize The number of individual to be selected.
             * @param[in] popFitness The fitness of each individual in the
             *            population.
             * @param[in] individualSize The size of an individual.
             * @param[out] selection The selected individuals that have been
             *             mutated.
             */
            virtual void operator()(uint32_t**             population,
                                    const uint32_t         populationSize,
                                    const uint32_t         selectionSize,
                                    const uint32_t*        popFitness,
                                    const uint32_t         individualSize,
                                    std::vector<uint32_t>& selection) = 0;

            /**
             * @brief Destroy the Mutation Operator object.
             *
             */
            virtual ~MutationOperator(void) {}
    };
}

#endif /* #ifndef __SOLVER_MUTATION_OPERATOR_H_ */