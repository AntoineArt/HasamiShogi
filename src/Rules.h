#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Types.h"

//GLOBAL VAR
extern game g; //global variable (initialized in App.c)


/*
	Reset the board b to it's basic state
*/
void resetBoard();

/*
	Return the player who won this turn (0 if none of them, 3 if both loosed)
*/
int checkVictory(int currentPlayer, coordinates c2);

/*
	Return a table of the coordinates with the size of the table in first position
	There isn't any interaction with the piece's previous position
	WARNING : Allocate memory
*/
coordinates* checkCatch(int currentPlayer, coordinates c2);

/*
	Return a table of the coordinates surrounding c, according to the "catch" condition
*/
coordinates* createTable(coordinates c, int up, int right, int down, int left, int catching);

/*
	Check if a move is valid
*/
int checkMovement(coordinates c1, coordinates c2);

/*
	function that show off the possible play after selection of a token
*/

coordinates* showPossible(coordinates c1);
