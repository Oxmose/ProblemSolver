# ProblemSolver

Multiple problem solver, using greedy, hill climbing and genetic algorithms.


## N Queens problem

*In folder NQueensProblem*

The N queens puzzle is the problem of placing N chess queens on an N×N chessboard so that no two queens threaten each other. Thus, a solution requires that no two queens share the same row, column, or diagonal. [1]

[1] Wikipedia: https://en.wikipedia.org/wiki/Eight_queens_puzzle


### Compilation

**Use of `make`:**
* `make` to compile the project.
* `make test=true testname` to execute the test `testname`.

Once compiled the binaries are available in the `bin` folder.

 **Usage:**
 ./NQueensProblem [ALGOTYPE] [N] [ITERCOUNT]
 * ALGOTYPE is the algorithm type used to solve the problem can be GREEDY, HILL or GEN.
 * N Is the number of queens to use to solve the problem.
 * ITERCOUNT is the maximal number of iteration to reach before stopping the algorithm (this is not taken into account for the greedy algorithm).


## Travelling Salesman Problem

*In folder TSP*

The travelling salesman problem (TSP) asks the following question: "Given a list of cities and the distances between each pair of cities, what is the shortest possible route that visits each city and returns to the origin city?" It is an NP-hard problem in combinatorial optimization, important in operations research and theoretical computer science. [1]

[1] Wikipedia: https://en.wikipedia.org/wiki/Travelling_salesman_problem


### Compilation

**Use of `make`:**
* `make` to compile the project.
* `make test=true testname` to execute the test `testname`.

Once compiled the binaries are available in the `bin` folder.

 **Usage:**
 ./TSP [ALGOTYPE] [FILENAME] [ITERCOUNT]
 * ALGOTYPE is the algorithm type used to solve the problem can be GREEDY, HILL or GEN.
 * FILENAME The file containing the cities location.
 * ITERCOUNT is the maximal number of iteration to reach before stopping the algorithm (this is not taken into account for the greedy algorithm).

### Input file
The input file is used to gather the cities location. The format of the file must be as follows:

`NB_CITIES
 CITY_0_X, CITY_0_Y
 CITY_1_X, CITY_1_Y`