#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Rules.c"

//GLOBAL VAR
extern game *g; //global variable (initialized in App.c)


/*
	Change the status of the case of coordonates c1
*/
void write(int status, coordinates c);

/*
	Move a piece from c1 to c2
*/
void movePiece(coordinates c1, coordinates c2);

/*
	Catch eventualy the pieces around c2, using checkCatch from Rules.c
*/
void catchPiece(int currentPlayer, coordinates c2);

/*
	Update the board with the current player's move from c1 to c2
*/

int updateBoard(int currentPlayer, coordinates c1, coordinates c2);
