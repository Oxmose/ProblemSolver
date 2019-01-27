/*******************************************************************************
 * File: OrderOneCrossoverOperator.h
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 27/01/2019
 *
 * Version: 1.0
 *
 * Crossover operator omplements ad the order 1 operator.
 * Order 1 Crossover is a fairly simple permutation crossover.
 * Basically, a swath of consecutive alleles from parent 1 drops down,
 * and remaining values are placed in the child in the order which they
 * appear in parent 2. [http://www.rubicite.com/Tutorials/GeneticAlgorithms/
 * CrossoverOperators/Order1CrossoverOperator.aspx]
 *
 ******************************************************************************/

#ifndef __SOLVER_ORDER_ONE_CROSSOVER_OPERATOR_H_
#define __SOLVER_ORDER_ONE_CROSSOVER_OPERATOR_H_

#include <cstdint> /* Generic int types */
#include <random>  /* std::default_random_engine */

#include <solver/CrossoverOperator.h> /* nsSolver::CrossoverOperator */

/**
 * @brief N Queens problem solvers.
 *
 */
namespace nsSolver
{
    /**
     * @brief Order 1 Crossover is a fairly simple permutation crossover.
     * Basically, a swath of consecutive alleles from parent 1 drops down,
     * and remaining values are placed in the child in the order which they
     * appear in parent 2. [http://www.rubicite.com/Tutorials/GeneticAlgorithms/
     * CrossoverOperators/Order1CrossoverOperator.aspx]
     *
     */
    class OrderOneCrossoverOperator: public CrossoverOperator
    {
        private:
            /**
             * @brief Random number engine.
             *
             */
            std::default_random_engine randomGenerator;

            /**
             * @brief apply the crossover between two parents ot create two new
             * children.
             *
             * @param[in] individualSize The size of an individual.
             * @param[in] parents The parents to mate.
             * @param[out] children The array of children to be created.
             */
            void mate(const uint32_t individualSize, const uint32_t** parents,
                      uint32_t**     children);

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
                                    uint32_t**       newChildren);

            /**
             * @brief Construct a new Order One Crossover Operator object.
             *
             */
            OrderOneCrossoverOperator(void);

            /**
             * @brief Destroy the Crossover Operator object.
             *
             */
            virtual ~OrderOneCrossoverOperator(void) {}
    };
}

#endif /* #ifndef __SOLVER_ORDER_ONE_CROSSOVER_OPERATOR_H_ */