/******************************************************************************
 * File: Solver.h
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 26/01/2019
 *
 * Version: 1.0
 *
 * Definition of the Solver interface. Any class implementing the Solver
 * interface is assumed to solve the N Queens Problem.
 ******************************************************************************/

#ifndef __SOLVER_SOLVER_H
#define __SOLVER_SOLVER_H

#include <cstdint> /* uint32_t */
#include <vector>  /* std::vector */

/**
 * @brief N Queens problem solvers.
 *
 */
namespace nsSolver
{
    /**
     * @brief Solver interface, defines the Solver types.
     *
     */
    class Solver
    {
        private:

        public:
            /**
             * @brief Destroy the Solver object.
             *
             */
            virtual ~Solver(void){};

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
                               uint32_t &attackCount) = 0;
    };
}

#endif /* #ifndef __SOLVER_SOLVER_H */