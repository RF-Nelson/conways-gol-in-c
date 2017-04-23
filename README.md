An implementation of [Conway's Game of Life](http://en.wikipedia.org/wiki/Conway's_Game_of_Life) in C.

The set of rules are summarized as follows:

1. An alive cell with fewer than two alive neighbors dies in the next generation.
2. An alive cell with more than three alive neighbors also dies in the next generation.
3. An alive cell with exactly two or three alive neighbors stays alive in the next generation.
4. A dead cell with exactly three alive neighbors becomes alive in the next generation.

This implementation uses a 10x10 grid. Off-grid neighbors are always assumed to be dead.

The program is intended to be run from the command line like so:

`./conway.out input.txt 5`

In the example above, `input.txt` is a file holding the initial state of the grid and `5` is the number of generations we want to simulate. The formatting of the input file should match the included example.

The result of the last generation will be saved as `output.txt`.
