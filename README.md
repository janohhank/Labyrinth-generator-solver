# Labyrinth-generator-solver
Simple N*M labyrinth generator and solver with OpenGL display.

This project is just a simple practice how to implement a random labyrinth creating and solving algorithm in C++ with cxx17 standards. Furthermore I want to create an OpenGL 2D renderer for this mini project.

**Build**

CMake based build with OpenGL dependency. Tested in:
 - Debian Stretch, CMake version 3.7.2
 - Ubuntu 18.04.3, CMake version 3.12.3
 - macOS Mojave 10.14.4, CMake version 3.14.3

## Math
Used backtracking type of algorithms for the labyrinth creation and solving.

**Backtracking**

https://en.wikipedia.org/wiki/Backtracking

**Maze generation**

https://en.wikipedia.org/wiki/Maze_generation_algorithm#Depth-first_search

![alt text](https://raw.githubusercontent.com/janohhank/Labyrinth-generator-solver/master/doc/example.png)

## Legend
	red line - labyrinth frame, walls
	blue line - starting position
	green line - exit position
	green pentagon - path of a good solution
	red pentagon - dead-ends the algorithm tried these paths
