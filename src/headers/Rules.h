#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"

/*
	Reset the board b to it's basic state
*/
void resetBoard(game *g);

/*
	Return the player who won this turn (0 if none of them, 3 if both loosed)
*/
int checkVictory(game *g, coordinates c2);

/*
	Return a table of the coordinates with the size of the table in first position
	There isn't any interaction with the piece's previous position
	WARNING : Allocate memory
*/
coordinates* checkCatch(game *g, coordinates c2);

/*
	Return a table of the coordinates surrounding c, according to the "catch" condition
*/
coordinates* createTable(game *g, coordinates c, int up, int right, int down, int left, int catching);

/*
	Check if a move is valid 
	1 if valid, 
	2 if on another friendly token
	0 else
	warning, function assume c1 and c2 are in the board, please use checkMove from Board.c to check
*/
int checkMovement(game *g, coordinates c1, coordinates c2);

/*
	function that show off the possible play after selection of a token
*/

coordinates* showPossible(game *g, coordinates c1);
