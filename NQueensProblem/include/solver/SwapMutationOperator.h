/*******************************************************************************
 * File: SwapMutationOperator.h
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

#ifndef __SOLVER_SWAP_MUTATION_OPERATOR_H_
#define __SOLVER_SWAP_MUTATION_OPERATOR_H_

#include <cstdint> /* Generic int types */
#include <vector>  /* std::vector */
#include <random>  /* std::default_random_engine */

#include <solver/MutationOperator.h> /* nsSolver::MutationOperator */

/**
 * @brief N Queens problem solvers.
 *
 */
namespace nsSolver
{
    /**
     * @brief  SwapMutation operator. Implements the MutationOperator
     * insterface.
     * The Swap mutation operator select two alleles of an individual and swap
     * them, avoiding multiple duplicates of the same allele.
     *
     */
    class SwapMutationOperator: public MutationOperator
    {
        private:
            /**
             * @brief Random number engine.
             *
             */
            std::default_random_engine randomGenerator;

        public:
            /**
             * @brief Apply mutation to a set of individual in the population.
             * The fontion select the selectionSize less fittest individuals and
             * mutate them.
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
                                    std::vector<uint32_t>& selection);

            /**
             * @brief Construct a new Swap Mutation Operator object.
             *
             */
            SwapMutationOperator(void);

            /**
             * @brief Destroy the Mutation Operator object.
             *
             */
            virtual ~SwapMutationOperator(void) {}
    };
}

#endif /* #ifndef __SOLVER_SWAP_MUTATION_OPERATOR_H_ */