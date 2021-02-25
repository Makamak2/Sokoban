# Sokoban
A Sokoban game - Player moves boxes to designated area

================================================================

A simple console-based game of Sokoban programmed in 2017 when I was
learning to program in C and C++. 

The player '@' must push all boxes '#' onto target tiles 'X' to win.
He can traverse the floor '.' while walls 'O' block movement.

The program loads levels from text files. The game board is saved
in a dynamically allocated array. Movement is handled via the
`getchar()` function and a `switch` statement.

While everything in this project was coded by me, I had the aid 
of a much more experienced programmer, who guided me on this project.

NOTE: For the program to run in its current state the line
`#include "stack.h"` on line 12 has to be removed/commented out.
