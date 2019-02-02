/******************************************************************************
 * File: main.cpp
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 26/01/2019
 *
 * Version: 1.0
 *
 * Main function for the TSP solver.
 ******************************************************************************/

#include <cstdint>  /* uint32_t */
#include <vector>   /* std::vector */
#include <iostream> /* std::cout, std::endl */
#include <cstring>  /* stdncmp */
#include <string>   /* std::string */
#include <fstream>  /* std::ifstrem */

#include <solver/Solver.h>       /* city_t */
#include <solver/GreedySolver.h> /* nsSolver::GreedySolver */

using namespace nsSolver; /* Solver's namespace */

#ifndef _TESTMODE

static void displayUsage(char* exeName)
{
    std::cout << exeName << "[ALGOTYPE] [FILENAME] [ITERCOUNT]"
              << std::endl << "\t"
              << "ALGOTYPE is the algorithm type used to solve the problem can "
              << "be GREEDY, HILL or GEN."
              << std::endl << "\t"
              << "FILENAME The file containing the cities location."
              << std::endl << "\t"
              << "ITERCOUNT is the maximal number of iteration to reach before"
              << " stopping the algorithm (this is not taken into account for "
              << "the greedy algorithm)." << std::endl;
}

static void parseFile(const std::string& fileName,
                      uint32_t& cityCount,
                      std::vector<city_t>& cities)
{
    city_t   city;
    uint32_t i;

    std::ifstream file(fileName, std::ifstream::in);

    if(!file.good())
    {
        std::cout << "Error while opening cities file." << std::endl;
        exit(-1);
    }

    /* Read the first line, city count */
    file >> cityCount;

    /* Note that nothing is done to check the file integrity */
    for(i = 0; i < cityCount; ++i)
    {
        city.id = i;
        file >> city.x;
        file >> city.y;
        cities.push_back(city);
    }

    file.close();
}

int main(int argc, char** argv)
{
    uint32_t i;
    uint32_t iterCount;
    uint32_t cityCount;
    double   distance;
    std::vector<city_t>   cities;
    std::vector<uint32_t> solution;

    std::string fileName;

    Solver* solver = nullptr;

    if(argc != 4)
    {
        std::cout << "Wrong argument count" << std::endl;
        displayUsage(argv[0]);
        return -1;
    }
    fileName  = argv[2];
    iterCount = std::stoi(argv[3]);

    parseFile(fileName, cityCount, cities);


    if(strncmp(argv[1], "GREEDY", 5) == 0)
    {
        solver = new GreedySolver(cities);
    }
    else if(strncmp(argv[1], "HILL", 4) == 0)
    {
        (void) iterCount;
        //solver = new HillClimbingSolver(queens, iterCount);
    }
    else if(strncmp(argv[1], "GEN", 3) == 0)
    {
        //solver = new GeneticSolver(queens, iterCount);
    }
    else
    {
        std::cout << "Wrong algorithm selected to solve the"
              << " problem."
              << std::endl;
        displayUsage(argv[0]);
        return -1;
    }

    solver->solve(solution, distance);

    std::cout << "Distance: " << distance << std::endl;
    std::cout << "Solution: " << std::endl;

    for(i = 0; i < solution.size(); ++i)
    {
        std::cout << solution[i];
        if(i != solution.size() - 1)
            std::cout << " - ";
    }
    std::cout << std::endl;

    delete solver;
    return 0;
}
#endif