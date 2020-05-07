# Nine20
A C program that solves the square number puzzle by outputting the steps as strings to the standard output. This program utilizes a hash table ADT to store possible moves of the strings. Run `make` to get the executables `Nine20`.

## The Nine Puzzle
The Nine Puzzle is a square 3x3 tray in which are placed 8 square 1x1 tiles numbered from 1 to 8.  The remaining space is empty, so an adjacent tile can slide into that space, leaving its former location empty. A

## Usage
Nine20 [HEIGHT WIDTH] MAXSTEPS INITIAL GOAL

1. Nine20
This is the executable

2. [HEIGHT WIDTH]
These are optional arguments to change the dimensions of the puzzles if needed. The default dimensions are 3 x 3.

3. MAXSTEPS
The limit of the number of steps the program takes as it comes up with more possible steps towards the goal

4. INITIAL and GOAL
Strings containing the elements of the puzzle, essentially making the two dimensional puzzle one dimensional. INITIAL is the starting point and GOAL is the endpoint. These can be numbers or characters.

# testHash
A C program that tests the functions for the hash table ADT.
