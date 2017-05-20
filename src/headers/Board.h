#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Rules.c"

//GLOBAL VAR
extern Game *g; //global variable (initialized in App.c)


/*
	Change the status of the case of coordonates c1
*/
void write(int status, Coordinates c);

/*
	Move a piece from c1 to c2
*/
void movePiece(Coordinates c1, Coordinates c2);

/*
	Catch eventualy the pieces around c2, using checkCatch from Rules.c
*/
void catchPiece(int currentPlayer, Coordinates c2);

/*
	Update the board with the current player's move from c1 to c2
*/

int updateBoard(int currentPlayer, Coordinates c1, Coordinates c2);
