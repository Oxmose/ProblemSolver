/******************************************************************************
 * File: GeneticSolver.h
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 26/01/2019
 *
 * Version: 1.0
 *
 * GeneticSolver implements the Solver class. Any class implementing the
 * Solver interface is assumed to solve the N Queens Problem.
 * The algorithm used to solvle the problem is a genetic algorithm.
 ******************************************************************************/

#ifndef __SOLVER_GENETIC_SOLVER_H
#define __SOLVER_GENETIC_SOLVER_H

#include <cstdint> /* uint32_t */
#include <vector>  /* std::vector */
#include <random>  /* std::random_device, std::mt19937,
                      std::uniform_int_distribution */

/* nsSolver::MatingPoolSelector */
#include <solver/MatingPoolSelector.h>
/* nsSolver::Crossoveroperator */
#include <solver/CrossoverOperator.h>
/* nsSolver::MutationOperator */
#include <solver/MutationOperator.h>

#include <solver/Solver.h> /* nsSolver::Sovler */

#define GEN_POPULATION_SIZE     100
#define GEN_MATING_POOL_SIZE    40
#define GEN_INJECTION_POOL_SIZE 20
#define GEN_CROSSOVER_PROBA     0.9
#define GEN_MUTATION_PROBA      0.4
#define GEN_MUTATION_SIZE       50
#define GEN_INJECTION_RATE      25

/**
 * @brief N Queens problem solvers.
 *
 */
namespace nsSolver
{
    /**
     * @brief Genetic Solver, implements the genetic version of the N Queens
     * problem solver.
     *
     */
    class GeneticSolver: public Solver
    {
        private:
            /**
             * @brief The number of queens the problem has to solve.
             *
             */
            uint32_t queensCount;

            /**
             * @brief The maximum number of tieration before the algorithm must
             * stop.
             *
             */
            uint32_t iterCount;

            /**
             * @brief Size of the population.
             *
             */
            uint32_t populationSize;

            /**
             * @brief Store the population.
             *
             */
            uint32_t** population;

            /**
             * @brief Store the population fitness.
             *
             */
            uint32_t* populationFitness;

            /**
             * @brief Size of the mating pool.
             *
             */
            uint32_t matingPoolSize;

            /**
             * @brief Store the index of the individuals to mate.
             *
             */
            uint32_t* matingPool;

            /**
             * @brief Store the children.
             *
             */
            uint32_t** children;

            /**
             * @brief Store the children fitness.
             *
             */
            uint32_t* childrenFitness;

            /**
             * @brief Injection pool size;
             *
             */
            uint32_t injectionPoolSize;

            /**
             * @brief Store the injected individuals.
             *
             */
            uint32_t** injectionPool;

            /**
             * @brief Store the injection pool fitness.
             *
             */
            uint32_t* injectionFitness;

            /**
             * @brief Size of the population that should be mutated.
             *
             */
            uint32_t mutationSize;

            /**
             * @brief Random engine, must be seeded at object initialization.
             *
             */
            std::mt19937 generator;

            /**
             * @brief Genetic mating pool selector.
             *
             */
            MatingPoolSelector* matingPoolSelector = nullptr;

            /**
             * @brief Genetic crossover operator.
             *
             */
            CrossoverOperator* crossoverOperator = nullptr;

            /**
             * @brief Genetic mutation operator.
             *
             */
            MutationOperator* mutationOperator = nullptr;

            /**
             * @brief Computer the number of attacks of the current solution.
             *
             * @param[in] solution The current solution for which we need to
             * compute the number of possible attacks.
             *
             * @return uint32_t The number of possible attacks for the solution.
             */
            uint32_t
            getAttackCount(const uint32_t* solution) const;

            /**
             * @brief Initialize the algorithm population.
             *
             */
            void initPopulation(void);

            /**
             * @brief Computes the fitness of the current populations we store.
             *
             * @param computeChildren Set to true if you wish to compute the
             * children fitnesses.
             * @param computeInjectionPool Set the tru if you wish to compute
             * the injection pool fitnesses.
             */
            void computeFitness(const bool computeChildren,
                                const bool computeInjectionPool);

            /**
             * @brief Generate a random toss and returns true if the toss is
             * under the given probability.
             *
             * @param[in] probability The probability to test.
             *
             * @returns True if the toss is under the given probability, false
             * otherwise.
             */
            bool tossProbability(const double probability);

        public:
            /**
             * @brief Destroy the GeneticSolver object.
             *
             */
            virtual ~GeneticSolver(void);

            /**
             * @brief Default contructor, unused.
             *
             */
            GeneticSolver(void) = delete;

            /**
             * @brief Construct a new Genetic Solver object
             *
             * @param[in] queensCount The number of queens the problem has to
             * solve.
             * @param[in] iterCount The maximal number of iteration before the
             * algorithm should stop.
             */
            GeneticSolver(const uint32_t queensCount,
                          const uint32_t iterCount);

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

            /**
             * @brief Tests the initialization of the population.
             *
             */
            void testInitPopulation(void);

            /**
             * @brief Tests the compute fitness function.
             *
             */
            void testComputeFitness(void);

            /**
             * @brief Tests the TossProbability method.
             *
             */
            void testTossProbability(void);
#endif

    };
}

#endif /* #ifndef __SOLVER_GENETIC_SOLVER_H */