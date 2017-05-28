#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"

/*
	Reset the board b to it's basic state
*/
void resetBoard(Game *g);

/*
	Return the player who won this turn (0 if none of them, 3 if both loosed)
*/
int checkVictory(Game *g, Coordinates c2);

/*
	Return a table of the coordinates with the size of the table in first position
	There isn't any interaction with the piece's previous position
	WARNING : Allocate memory
*/
Coordinates* checkCatch(Game *g, Coordinates c2);

/*
	Return a table of the coordinates surrounding c, according to the "catch" condition
	WARNING : Allocate memory
*/
Coordinates* createTable(Game *g, Coordinates c, int up, int right, int down, int left, int catching);


/*
	function that show off the possible play after selection of a token
	WARNING : Allocate memory
*/

Coordinates* showPossible(Game *g, Coordinates c1);
