# ProblemSolver

Multiple problem solver, using greedy, hill climbing and genetic algorithms.



## N Queens problem

*In folder NQueensProblem*

The N queens puzzle is the problem of placing N chess queens on an N×N chessboard so that no two queens threaten each other. Thus, a solution requires that no two queens share the same row, column, or diagonal. [1]

[1] Wikipedia: https://en.wikipedia.org/wiki/Eight_queens_puzzle


### Compilation

For ease of use (in the development context of the exercise) you can only
compile one type of algorithm at a time.

**Use of `make`:**
* `make` to compile the project.
* `make test=true testname` to execute the test `testname`.

Once compiled the binaries are available in the `bin` folder.

 **Usage:**
 ./NQueensProblem [ALGOTYPE] [N] [ITERCOUNT]
 * ALGOTYPE is the algorithm type used to solve the problem can be GREEDY, HILL or GEN.
 * N Is the number of queens to use to solve the problem.
 * ITERCOUNT is the maximal number of iteration to reach before stopping the algorithm (this is not taken into account for the greedy algorithm).

