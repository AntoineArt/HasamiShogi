#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"
//#include "../SaveSystem.c"

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
	Check if a move is valid
	1 if valid,
	2 if on another friendly token
	0 else
	warning, function assume c1 and c2 are in the board, please use checkMove from Board.c to check
*/
int checkMovement(Game *g, Coordinates c1, Coordinates c2);

void printTab(Coordinates* t, int len);
