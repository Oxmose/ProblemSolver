
# ProblemSolver

Multiple problem solver, using greedy, hill climbing and genetic algorithms.


## N Queens problem

*In folder NQueensProblem*

The N queens puzzle is the problem of placing N chess queens on an N×N
chessboard so that no two queens threaten each other. Thus, a solution
requires that no two queens share the same row, column, or diagonal. [1]

[1] Wikipedia: https://en.wikipedia.org/wiki/Eight_queens_puzzle


### Compilation

For ease of use (in the development context of the exercise) you can only
compile one type of algorithm at a time.

**Use of`make`:**
* `make` to compile the project with the default algorithm (greedy).
* `make solver=GREEDY` to compile the project with the greedy algorithm.
* `make solver=HILL` to compile the project with the hill climbing algorithm.
* `make solver=GEN` to compile the project with the genetic algorithm.
* `make test=true testname` to execute the test `testname`.

Once compiled the binaries are available in the `bin` folder.
