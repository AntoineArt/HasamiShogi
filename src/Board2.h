#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int board[9][9];
} matrice;

typedef struct{
	int x,y;
} coordonnees;

/*
	Create a 9x9 matrix
*/
matrice allocateBoard()

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
	Update the board with the consequences of a move
*/
void furtherUpdate();

/*
	Check if a move is valid
*/
bool mouvementValide(int joueur, coordonnees c1, coordonnees c2);

/*
	 Update the board with the current player's move
*/
void updateBoard(coordonnees c1, coordonnees c2);


