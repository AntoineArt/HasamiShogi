#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"


//GLOBAL VAR
extern Game *g; //global variable (initialized in App.c)


/*
	Reset the board b to it's basic state
*/
void resetBoard();

/*
	Return the player who won this turn (0 if none of them, 3 if both loosed)
*/
int checkVictory(int currentPlayer, Coordinates c2);

/*
	Return a table of the coordinates with the size of the table in first position
	There isn't any interaction with the piece's previous position
	WARNING : Allocate memory
*/
Coordinates* checkCatch(int currentPlayer, Coordinates c2);

/*
	Return a table of the coordinates surrounding c, according to the "catch" condition
*/
Coordinates* createTable(Coordinates c, int up, int right, int down, int left, int catching);

/*
	Check if a move is valid
*/
int checkMovement(Coordinates c1, Coordinates c2);

/*
	function that show off the possible play after selection of a token
*/

Coordinates* showPossible(Coordinates c1);
