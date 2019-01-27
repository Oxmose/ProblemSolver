#! /bin/bash
make clean

################### Greedy

echo "Test greedy algorithm attack counter"
make test=true testGreedyAttackCount
if [[ $? != 0 ]]; then
    echo "FAIL: Test greedy algorithm attack counter"
    exit -1
fi

echo "Test greedy algorithm solver"
make test=true testGreedySolve
if [[ $? != 0 ]]; then
    echo "FAIL: Test greedy algorithm solver"
    exit -1
fi

################### Climbing Hills

echo "Test hill climbing algorithm attack counter"
make test=true testHillAttackCount
if [[ $? != 0 ]]; then
    echo "FAIL: Test hill climbing algorithm attack counter"
    exit -1
fi

echo "Test hill climbing algorithm solver"
make test=true testHillSolve
if [[ $? != 0 ]]; then
    echo "FAIL: Test hill climbing algorithm solver"
    exit -1
fi

################### Genetic

echo "Test genetic algorithm attack counter"
make test=true testGeneticAttackCount
if [[ $? != 0 ]]; then
    echo "FAIL: Test genetic algorithm attack counter"
    exit -1
fi

echo "Test genetic algorithm population init"
make test=true testGeneticInitPopulation
if [[ $? != 0 ]]; then
    echo "FAIL: Test genetic algorithm population init"
    exit -1
fi

echo "Test genetic algorithm fitness computation"
make test=true testGeneticComputeFitness
if [[ $? != 0 ]]; then
    echo "FAIL: Test genetic algorithm fitness computation"
    exit -1
fi

echo "Test genetic algorithm fitness proportional mating pool selector"
make test=true testFitnessPropMatingPoolSelector
if [[ $? != 0 ]]; then
    echo "FAIL: Test genetic algorithm fitness proportional mating pool selector"
    exit -1
fi

echo "Test genetic algorithm order one crossover operator"
make test=true testOrderOneCrossoverOperator
if [[ $? != 0 ]]; then
    echo "FAIL: Test genetic algorithm order one crossover operator"
    exit -1
fi

echo "Test genetic algorithm swap mutation operator"
make test=true testSwapMutationOperator
if [[ $? != 0 ]]; then
    echo "FAIL: Test genetic algorithm swap mutation operator"
    exit -1
fi

echo "Test genetic algorithm toss probability"
make test=true testTossProbability
if [[ $? != 0 ]]; then
    echo "FAIL: Test genetic algorithm toss probability"
    exit -1
fi


echo "Test genetic algorithm solve"
make test=true testGeneticSolve
if [[ $? != 0 ]]; then
    echo "FAIL: Test genetic algorithm solve"
    exit -1
fi