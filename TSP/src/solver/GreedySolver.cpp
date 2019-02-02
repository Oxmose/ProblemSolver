/******************************************************************************
 * File: GreedySolver.cpp
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

#include <cstdint>  /* uint32_t */
#include <vector>   /* std::vector */
#include <iostream> /* std::cout, std::endl */
#include <random>   /* std::random_device, std::mt19937,
                       std::uniform_int_distribution */

#include <solver/Solver.h> /* city_t */

/* Header file */
#include <solver/GreedySolver.h>

using namespace nsSolver; /* Solver's namespace */

/*******************************************************************************
 * Constructors / Destructors
 ******************************************************************************/
GreedySolver::GreedySolver(const std::vector<city_t>& cities)
{
    this->cities = cities;

    this->distanceMatrix = nullptr;

    /* Initialize the random generator */
    std::random_device rd;
    generator = std::mt19937(rd());

    /* Set the random distribution */
    randDist = std::uniform_int_distribution<uint32_t>(0, cities.size() - 1);
}

GreedySolver::~GreedySolver(void)
{

}

/*******************************************************************************
 * Public methods
 ******************************************************************************/
void GreedySolver::solve(std::vector<uint32_t>& solution,
                         double &distance)
{
    uint32_t cityCount;
    uint32_t i;
    uint32_t j;
    uint32_t bestIndex;
    double   dX;
    double   dY;
    double   bestDistance;
    std::vector<uint32_t> visited(this->cities.size(), false);
    cityCount = this->cities.size();

    /* Create the distances matrix */
    if(this->distanceMatrix != nullptr)
    {
        for(i = 0; i < cityCount; ++i)
        {
            delete[] this->distanceMatrix[i];
        }
        delete[] this->distanceMatrix;
    }
    this->distanceMatrix = new double*[cityCount];
    for(i = 0; i < cityCount; ++i)
    {
        this->distanceMatrix[i] = new double[cityCount];
    }

    /* Compute the distance matrix */
    for(i = 0; i < cityCount; ++i)
    {
        for(j = 0; j < cityCount; ++j)
        {
            dX = this->cities[i].x - this->cities[j].x;
            dY = this->cities[i].y - this->cities[j].y;
            this->distanceMatrix[i][j] = sqrt(dX * dX + dY * dY);
        }
    }
    std::cout << "Created distance matrix" << std::endl;

    /* Set starting city */
    solution.clear();
    solution.push_back(0);
    visited[0] = true;
    distance = 0;

    /* Fill the rest of the cities */
    for(i = 1; i < cityCount; ++i)
    {
        bestDistance = -1;
        /* Search for the best next distacne */
        for(j = 0; j < cityCount; ++j)
        {
            if(j == i) continue;
            if(!visited[j] &&
               (bestDistance > this->distanceMatrix[i][j] ||
                bestDistance == -1))
                {
                    bestDistance = this->distanceMatrix[i][j];
                    bestIndex = j;
                }
        }
        visited[bestIndex] = true;
        distance += bestDistance;
        solution.push_back(bestIndex);
    }
}

/*******************************************************************************
 * Private methods
 ******************************************************************************/


#ifdef _TESTMODE
/*******************************************************************************
 * Test methods
 ******************************************************************************/
/* LCOV_EXCL_START */


/* LCOV_EXCL_STOP */
#endif