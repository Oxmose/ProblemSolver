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
 * interface is assumed to solve the TSP.
 * The algorithm used to solvle the problem is a greedy algorithm.
 ******************************************************************************/

#ifndef __SOLVER_GREEDY_SOLVER_H
#define __SOLVER_GREEDY_SOLVER_H

#include <cstdint> /* uint32_t, uint64_t */
#include <vector>  /* std::vector */
#include <random>  /* std::random_device, std::mt19937,
                      std::uniform_int_distribution */

#include <solver/Solver.h> /* nsSolver::Sovler, city_t */

/**
 * @brief TSP problem solvers.
 *
 */
namespace nsSolver
{
    /**
     * @brief Greedy Solver, implements the greedy version of the TSP solver.
     *
     */
    class GreedySolver: public Solver
    {
        private:
            /**
             * @brief The cities array the problem has to solve.
             *
             */
            std::vector<city_t> cities;

            /**
             * @brief Stores the distance between each city.
             *
             */
            double** distanceMatrix = nullptr;

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
             * @param[in] cities he cities array the problem has to solve.
             */
            GreedySolver(const std::vector<city_t>& cities);

            /**
             * @brief Solves the TSP and store the solution in the vector given
             * as parameter.
             *
             * @param[out] solution The vector receiving the solution for the
             * problem. The vector's index represents the cities order of visit.
             *
             * @param[out] distance The distance of the solution.
             */
            virtual void solve(std::vector<uint32_t>& solution,
                               double &distance);
    };
}

#endif /* #ifndef __SOLVER_GREEDY_SOLVER_H */