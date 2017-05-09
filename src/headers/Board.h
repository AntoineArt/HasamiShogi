#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Rules.c"

//GLOBAL VAR
extern game g; //global variable (initialized in App.c)

/*
	Create a 9x9 matrix and all the related vars from struct board depending on the variante of ashami shogi being played
	the new board is referenced as b by the reste of the program
	warning allocate memory !
*/
board allocateBoard(int var);

/*
	Free the memory used by the board
*/
void freeBoard(board b);

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
