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
 * interface is assumed to solve the TSP.
 ******************************************************************************/

#ifndef __SOLVER_SOLVER_H
#define __SOLVER_SOLVER_H

#include <cstdint> /* uint32_t */
#include <vector>  /* std::vector */

/**
 * @brief TSP problem solvers.
 *
 */
namespace nsSolver
{
    /**
     * @brief Defines the city structure.
     *
     */
    struct city
    {
        uint32_t id;
        double x;
        double y;
    };
    typedef struct city city_t;

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
             * @brief Solves the TSP and store the solution in the vector given
             * as parameter.
             *
             * @param[out] solution The vector receiving the solution for the
             * problem. The vector's index represents the cities order of visit.
             *
             * @param[out] distance The distance of the solution.
             */
            virtual void solve(std::vector<uint32_t>& solution,
                               double &distance) = 0;
    };
}

#endif /* #ifndef __SOLVER_SOLVER_H */