#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Rules.c"

/*
	Change the status of the case of coordonates c1
*/
void write(Game* g, int status, Coordinates c);

/*
	Move a piece from c1 to c2
*/
void movePiece(Game *g, Coordinates c1, Coordinates c2);

/*
	Catch eventualy the pieces from tab given by checkCatch from Rules.c
*/
void catchPiece(Game *g, Coordinates *tab);

/*
	Reverse catchPiece
*/
void releasePiece(Game *g, Coordinates *tab, int player);

/*
	Update the board with the player's move from c1 to c2 including catching pieces.
	return a coordinates* tab that contains is own length, c1, c2 and the eventual list of caught piece.
	includes checkMovement
*/
int checkMove(Game *g, Coordinates c1, Coordinates c2, int player);


/*
	function that show off the possible play after selection of a token
	WARNING : Allocate memory
*/
Coordinates* showPossible(Game *g, Coordinates c1, int player);

/*
	print the board in console
*/
void printBoard(Game *g);
