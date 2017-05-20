#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Rules.c"

/*
	Change the status of the case of coordonates c1
*/
void write(game *g, int status, coordinates c);

/*
	Move a piece from c1 to c2
*/
void movePiece(game *g, coordinates c1, coordinates c2);

/*
	Catch eventualy the pieces from tab given by checkCatch from Rules.c
*/
void catchPiece(game *g, coordinates *tab);

/*
	Update the board with the player's move from c1 to c2 including catching pieces.
	return a coordinates* tab that contains is own length, c1, c2 and the eventual list of caught piece.
*/

int checkMove(game *g, coordinates c1, coordinates c2);
