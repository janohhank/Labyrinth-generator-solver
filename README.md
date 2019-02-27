# Labyrinth-generator-solver
Simple N*M labyrinth generator and solver with OpenGL display.

This project is just a simple practice how to implement a random labyrinth creating and solving algorithm in C++ with cxx17 standards. Furthermore I want to create a simple OpenGL 2D renderer for this mini project.

# Math
Labyrinth creation algorithm : Depth-First Search : https://en.wikipedia.org/wiki/Maze_generation_algorithm#Depth-first_search

Labyrinth solver algorithm : Backtracking (DFS similar with recursion)

These algorithm complexity are big (exponential in N when the maze in an N*N matrix).

![alt text](https://raw.githubusercontent.com/janohhank/Labyrinth-generator-solver/master/doc/example.png)

# Legend
red line - labyrinth frame, walls
blue line - starting position
green line - exit position
green pentagon - path of good solution
red pentagon - dead-ends the algorithm tried these paths