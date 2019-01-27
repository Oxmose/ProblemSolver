/******************************************************************************
 * File: GreedySolver.h
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 26/01/2019
 *
 * Version: 1.0
 *
 * GreedySolver implements the Solver class. Any class implementing the Solver
 * interface is assumed to solve the N Queens Problem.
 * The algorithm used to solvle the problem is a greedy algorithm.
 ******************************************************************************/

#ifndef __SOLVER_GREEDY_SOLVER_H
#define __SOLVER_GREEDY_SOLVER_H

#include <cstdint> /* uint32_t */
#include <vector>  /* std::vector */
#include <random>  /* std::random_device, std::mt19937,
                      std::uniform_int_distribution */

#include <solver/Solver.h> /* nsSolver::Sovler */

/**
 * @brief N Queens problem solvers.
 *
 */
namespace nsSolver
{
    /**
     * @brief Greedy Solver, implements the greedy version of the N Queens
     * problem solver.
     *
     */
    class GreedySolver: public Solver
    {
        private:
            /**
             * @brief The number of queens the problem has to solve.
             *
             */
            uint32_t queensCount;

            /**
             * @brief Random engine, must be seeded at object initialization.
             *
             */
            std::mt19937 generator;

            /**
             * @brief Random distribution.
             *
             */
            std::uniform_int_distribution<uint32_t> randDist;

            /**
             * @brief Computer the number of attacks of the current solution.
             *
             * @param[in] solution The current solution for which we need to
             * compute the number of possible attacks.
             *
             * @return uint32_t The number of possible attacks for the solution.
             */
            uint32_t
            getAttackCount(const std::vector<uint32_t>& solution) const;

        public:
            /**
             * @brief Destroy the GreedySolver object.
             *
             */
            virtual ~GreedySolver(void);

            /**
             * @brief Default contructor, unused.
             *
             */
            GreedySolver(void) = delete;

            /**
             * @brief Construct a new Greedy Solver object
             *
             * @param[in] queensCount The number of queens the problem has to
             * solve.
             */
            GreedySolver(const uint32_t queensCount);

            /**
             * @brief Solves the N Queens problem and store the solution in the
             * vector given as parameter.
             *
             * @param[out] solution The vector receiving the solution for the
             * problem. The vector's index represents the Queen's column, the
             * value at the index represents the Queen's line. -1 represents no
             * Queen in the column.
             *
             * @param[out] attackCount The number of possible attack with the
             * current solution.
             */
            virtual void solve(std::vector<uint32_t>& solution,
                               uint32_t &attackCount);

#ifdef _TESTMODE
            /**
             * @brief Tests the attackCount method
             *
             */
            void testGetAttackCount(void) const;

            /**
             * @brief Tests the solve method.
             *
             */
            void testSolve(void);
#endif

    };
}

#endif /* #ifndef __SOLVER_GREEDY_SOLVER_H */