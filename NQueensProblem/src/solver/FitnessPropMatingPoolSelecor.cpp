/*******************************************************************************
 * File: FitnessPropMatingPoolSelector.cpp
 *
 * Author: Alexy Torres Aurora Dugo
 *
 * Date: 27/01/2019
 *
 * Version: 1.0
 *
 * Mating pool selector based on the fitness of each individual. This fitness
 * level is used to associate a probability of selection with each individual
 * chromosome. If fi is the fitness of individual i in the population, its
 * probability of being selected is pi = fi / (sum(i = 1 to N) fi);
 ******************************************************************************/

#include <cstdint> /* Generic int types */
#include <vector>  /* std::vector */
#include <random>  /* std::random_device, std::uniform_int_distribution,
                      std::uniform_real_distribution*/

 /* Header file */
#include <solver/FitnessPropMatingPoolSelector.h>

using namespace nsSolver; /* Solver's namespace */

/*******************************************************************************
 * Constructors / Destructors
 ******************************************************************************/
FitnessPropMatingPoolSelector::FitnessPropMatingPoolSelector(void)
{
    /* Initialize the random generator */
    std::random_device rd;
    this->randomGenerator.seed(rd());
}

/*******************************************************************************
 * Public methods
 ******************************************************************************/

void FitnessPropMatingPoolSelector::operator()(const uint32_t* popData,
                                               const uint32_t  popSize,
                                               const uint32_t  selectionSize,
                                               uint32_t*       selection)
{
    uint32_t i;
    uint32_t index;
    uint32_t lastIndex;
    uint64_t maxFitness;
    double randPoint;
    double fitW;

    std::vector<bool> alreadySelected(popSize, false);

    std::uniform_int_distribution<uint64_t> distributionInt(0, popSize - 1);
    std::uniform_real_distribution<double> distributionDouble(0, 1.0);

    maxFitness = 0.0;

    /* Init the selection and compute the fitnessSum */
    for(i = 0; i < popSize; ++i)
    {
        if(maxFitness < popData[i])
        {
            maxFitness = popData[i];
        }
    }

    /* Now select toSelect individuals by stochastic acceptance */
    lastIndex = 0;
    for(i = 0; i < selectionSize; ++i)
    {
        while(true)
        {
            index = distributionInt(this->randomGenerator);
            randPoint = distributionDouble(this->randomGenerator);
            fitW = (double)popData[index] / (double)maxFitness;
            if(!alreadySelected[index] && randPoint < fitW)
            {
                break;
            }

        }
        selection[lastIndex++] = index;
        alreadySelected[index] = true;
    }
}

/*******************************************************************************
 * Private methods
 ******************************************************************************/