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