#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Rules.c"

/*
	structure that describe the board status
	contains the map of pieces
	contains the piece counter of both player
	knows the gameMode
	knows the variante that is currently being played
*/
typedef struct {
  int **map;  //the game board with the pieces
  int countPlayer1; //the number of pieces owned by the first player
  int countPlayer2; //the number of pieces owned by the second player
} board;

typedef struct{
	int x,y;
} coordonates;

/*
	Create a 9x9 matrix and all the related vars from struct Board() depending on the variante of ashami shogi being played
	warning allocate memory !
*/
board allocateBoard(int var);

/*
	Free the memory used by the board
*/
void freeBoard(board b);

/*
	Reset the matrix to it's basic state
*/
void resetBoard(matrice m)

/*
	Change le statut de la case de coordonnées c1
*/
void write(int status, coordonnees c);

/*
	Move a piece from c1 to c2
*/
void movePiece(coordonnees c1, coordonnees c2);

/*
	catch eventualy the pieces around c2, using checkCatch from Rules.c
*/
void catchPiece(int currentPlayer, coordonates c2);

/*
	 Update the board with the current player's move from c1 to c2
*/
void updateBoard(int currentPlayer, coordonnees c1, coordonnees c2);


